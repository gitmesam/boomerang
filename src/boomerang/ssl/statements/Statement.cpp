#pragma region License
/*
 * This file is part of the Boomerang Decompiler.
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 */
#pragma endregion License
#include "Statement.h"

#include "boomerang/core/Project.h"
#include "boomerang/core/Settings.h"
#include "boomerang/db/Prog.h"
#include "boomerang/db/proc/UserProc.h"
#include "boomerang/ssl/exp/Binary.h"
#include "boomerang/ssl/exp/Const.h"
#include "boomerang/ssl/exp/Location.h"
#include "boomerang/ssl/exp/RefExp.h"
#include "boomerang/ssl/statements/CallStatement.h"
#include "boomerang/util/log/Log.h"
#include "boomerang/visitor/expmodifier/CallBypasser.h"
#include "boomerang/visitor/expvisitor/UsedLocsFinder.h"
#include "boomerang/visitor/stmtexpvisitor/UsedLocsVisitor.h"
#include "boomerang/visitor/stmtmodifier/StmtPartModifier.h"


Statement::Statement()
    : m_bb(nullptr)
    , m_proc(nullptr)
    , m_number(0)
{
}


void Statement::setProc(UserProc *proc)
{
    m_proc = proc;

    const bool assumeABICompliance = (proc && proc->getProg())
                                         ? proc->getProg()->getProject()->getSettings()->assumeABI
                                         : false;
    LocationSet exps, defs;
    addUsedLocs(exps);
    getDefinitions(defs, assumeABICompliance);
    exps.makeUnion(defs);

    for (SharedExp exp : exps) {
        if (exp->isLocation()) {
            exp->access<Location>()->setProc(proc);
        }
    }
}


OStream &operator<<(OStream &os, const Statement *s)
{
    if (s == nullptr) {
        os << "nullptr ";
        return os;
    }

    s->print(os);
    return os;
}


bool Statement::isFlagAssign() const
{
    return m_kind == StmtType::Assign &&
           static_cast<const Assign *>(this)->getRight()->isFlagCall();
}


QString Statement::toString() const
{
    QString tgt;
    OStream ost(&tgt);
    print(ost);
    return tgt;
}


bool Statement::canPropagateToExp(const Exp &exp)
{
    if (!exp.isSubscript()) {
        return false;
    }

    const RefExp &ref = static_cast<const RefExp &>(exp);

    if (ref.isImplicitDef()) {
        // Can't propagate statement "-" or "0" (implicit assignments)
        return false;
    }

    const Statement *def = ref.getDef();

    //    if (def == this)
    // Don't propagate to self! Can happen with %pc's (?!)
    //        return false;
    if (def->isNullStatement()) {
        // Don't propagate a null statement! Can happen with %pc's (would have no effect, and would
        // infinitely loop)
        return false;
    }

    if (!def->isAssign()) {
        return false; // Only propagate ordinary assignments (so far)
    }

    const Assign *adef = static_cast<const Assign *>(def);

    if (adef->getType()->isArray()) {
        // Assigning to an array, don't propagate (Could be alias problems?)
        return false;
    }

    return true;
}


bool Statement::propagateTo(Settings *settings, std::map<SharedExp, int, lessExpStar> *destCounts,
                            LocationSet *usedByDomPhi, bool force)
{
    bool change            = false;
    int changes            = 0;
    const int propMaxDepth = settings->propMaxDepth;

    do {
        LocationSet exps;
        // addUsedLocs(..,true) -> true to also add uses from collectors. For example, want to
        // propagate into the reaching definitions of calls. Third parameter defaults to false, to
        // find all locations, not just those inside m[...]
        addUsedLocs(exps, true);
        change = false; // True if changed this iteration of the do/while loop

        // Example: m[r24{10}] := r25{20} + m[r26{30}]
        // exps has r24{10}, r25{20}, m[r26{30}], r26{30}
        for (SharedExp e : exps) {
            if (!canPropagateToExp(*e)) {
                continue;
            }

            assert(dynamic_cast<Assignment *>(e->access<RefExp>()->getDef()) != nullptr);
            Assignment *def = static_cast<Assignment *>(e->access<RefExp>()->getDef());
            SharedExp rhs   = def->getRight();

            // If force is true, ignore the fact that a memof should not be propagated (for switch
            // analysis)
            if (rhs->containsBadMemof() && !(force && rhs->isMemOf())) {
                // Must never propagate unsubscripted memofs, or memofs that don't yet have symbols.
                // You could be propagating past a definition, thereby invalidating the IR
                continue;
            }

            SharedExp lhs = def->getLeft();

            if (settings->experimental) {
                // This is Mike's experimental propagation limiting heuristic. At present, it is:
                // for each component of def->rhs
                //   test if the base expression is in the set usedByDomPhi
                //     if so, check if this statement OW overwrites a parameter (like ebx = ebx-1)
                //     if so, check for propagating past this overwriting statement, i.e.
                //        domNum(def) <= domNum(OW) && dimNum(OW) < domNum(def)
                //        if so, don't propagate (heuristic takes effect)
                if (usedByDomPhi) {
                    LocationSet rhsComps;
                    rhs->addUsedLocs(rhsComps);
                    LocationSet::iterator rcit;

                    for (rcit = rhsComps.begin(); rcit != rhsComps.end(); ++rcit) {
                        if (!(*rcit)->isSubscript()) {
                            continue; // Sometimes %pc sneaks in
                        }

                        SharedExp rhsBase = (*rcit)->getSubExp1();
                        // We don't know the statement number for the one definition in usedInDomPhi
                        // that might exist, so we use findNS()
                        SharedExp OW = usedByDomPhi->findNS(rhsBase);

                        if (OW) {
                            Statement *OWdef = OW->access<RefExp>()->getDef();

                            if (!OWdef->isAssign()) {
                                continue;
                            }

                            SharedExp lhsOWdef = static_cast<Assign *>(OWdef)->getLeft();
                            LocationSet OWcomps;
                            def->addUsedLocs(OWcomps);

                            bool isOverwrite = false;

                            for (const SharedExp &loc : OWcomps) {
                                if (loc->equalNoSubscript(*lhsOWdef)) {
                                    isOverwrite = true;
                                    break;
                                }
                            }

                            if (isOverwrite) {
                                break;
                            }

                            if (OW != nullptr) {
                                LOG_MSG("OW is %1", OW);
                            }
                        }
                    }
                }
            }


            // Check if the -l flag (propMaxDepth) prevents this propagation,
            // but always propagate to %flags
            if (!destCounts || lhs->isFlags() || def->getRight()->containsFlags()) {
                change |= doPropagateTo(e, def, settings);
            }
            else {
                std::map<SharedExp, int, lessExpStar>::iterator ff = destCounts->find(e);

                if (ff == destCounts->end()) {
                    change |= doPropagateTo(e, def, settings);
                }
                else if (ff->second <= 1) {
                    change |= doPropagateTo(e, def, settings);
                }
                else if (rhs->getComplexityDepth(m_proc) < propMaxDepth) {
                    change |= doPropagateTo(e, def, settings);
                }
            }
        }
    } while (change && ++changes < 10);

    // Simplify is very costly, especially for calls.
    // I hope that doing one simplify at the end will not affect any
    // result...
    simplify();

    // Note: change is only for the last time around the do/while loop
    return changes > 0;
}


bool Statement::propagateFlagsTo(Settings *settings)
{
    bool change = false;
    int changes = 0;

    do {
        LocationSet exps;
        addUsedLocs(exps, true);

        for (SharedExp e : exps) {
            if (!e->isSubscript()) {
                continue; // e.g. %pc
            }

            Assignment *def = dynamic_cast<Assignment *>(e->access<RefExp>()->getDef());

            if ((def == nullptr) ||
                (nullptr == def->getRight())) { // process if it has definition with rhs
                continue;
            }

            SharedExp base = e->access<Exp, 1>(); // Either RefExp or Location ?

            if (base->isFlags() || base->isMainFlag()) {
                change |= doPropagateTo(e, def, settings);
            }
        }
    } while (change && ++changes < 10);

    simplify();
    return change;
}


void Statement::setTypeForExp(SharedExp, SharedType)
{
    assert(false);
}


bool Statement::doPropagateTo(const SharedExp &e, Assignment *def, Settings *settings)
{
    // Respect the -p N switch
    if (settings->numToPropagate >= 0) {
        if (settings->numToPropagate == 0) {
            return false;
        }

        settings->numToPropagate--;
    }

    LOG_VERBOSE2("Propagating %1 into %2", def, this);
    const bool change = replaceRef(e, def);
    LOG_VERBOSE2("    result %1", this);
    return change;
}


bool Statement::replaceRef(SharedExp e, Assignment *def)
{
    SharedExp rhs = def->getRight();

    assert(rhs);

    SharedExp base = e->getSubExp1();
    // Could be propagating %flags into %CF
    SharedExp lhs = def->getLeft();

    /* When one of the main flags is used bare, and was defined via a flag function,
     * apply the semantics for it. For example, the x86 'sub lhs, rhs' instruction effectively
     * sets the CF flag to 'lhs <u rhs'.
     * Extract the arguments of the flag function call, and apply the semantics manually.
     * This should rather be done in the SSL file (not hard-coded), but doing this currently breaks
     * Type Analysis (because Type Analysis is also done for subexpressions of dead definitions).
     * Note: the flagcall is a binary, with a Const (the name), and a list of expressions. Example
     * for the 'SUBFLAGS' flag call:
     *
     *          defRhs
     *         /     \
     *     Const    opList
     * "SUBFLAGS"   /    \
     *             P1   opList
     *                  /    \
     *                 P2   opList
     *                      /    \
     *                     P3   opNil
     */
    if (lhs && lhs->isFlags()) {
        if (!rhs || !rhs->isFlagCall()) {
            return false;
        }

        const QString flagFuncName = rhs->access<Const, 1>()->getStr();

        if (flagFuncName.startsWith("SUBFLAGSFL")) {
            switch (base->getOper()) {
            case opCF: {
                // for float cf we'll replace the CF with (P1<P2)
                SharedExp replacement = Binary::get(opLess, rhs->access<Exp, 2, 1>(),
                                                    rhs->access<Exp, 2, 2, 1>());
                searchAndReplace(*RefExp::get(Terminal::get(opCF), def), replacement, true);
                return true;
            }
            case opZF: {
                // for float zf we'll replace the ZF with (P1==P2)
                SharedExp replacement = Binary::get(opEquals, rhs->access<Exp, 2, 1>(),
                                                    rhs->access<Exp, 2, 2, 1>());
                searchAndReplace(*RefExp::get(Terminal::get(opZF), def), replacement, true);
                return true;
            }

            default: break;
            }
        }
        else if (flagFuncName.startsWith("SUBFLAGS")) {
            const SharedExp subLhs    = rhs->access<Exp, 2, 1>();
            const SharedExp subRhs    = rhs->access<Exp, 2, 2, 1>();
            const SharedExp subResult = rhs->access<Exp, 2, 2, 2, 1>();

            switch (base->getOper()) {
            case opCF: {
                const SharedExp replacement = Binary::get(opLessUns, subLhs, subRhs);
                searchAndReplace(*RefExp::get(Terminal::get(opCF), def), replacement, true);
                return true;
            }
            case opZF: {
                // for zf we only want to check if the result part of the subflags is equal to zero
                const SharedExp replacement = Binary::get(opEquals, subResult, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opZF), def), replacement, true);
                return true;
            }
            case opNF: {
                // for sf we only want to check if the result part of the subflags is less than zero
                const SharedExp replacement = Binary::get(opLess, subResult, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opNF), def), replacement, true);
                return true;
            }
            case opOF: {
                // (op1 < 0 && op2 >= 0 && result >= 0) || (op1 >= 0 && op2 < 0 && result < 0)
                const SharedExp replacement = Binary::get(
                    opOr,
                    Binary::get(opAnd,
                                Binary::get(opAnd, Binary::get(opLess, subLhs, Const::get(0)),
                                            Binary::get(opGtrEq, subRhs, Const::get(0))),
                                Binary::get(opGtrEq, subResult, Const::get(0))),
                    Binary::get(opAnd,
                                Binary::get(opAnd, Binary::get(opGtrEq, subLhs, Const::get(0)),
                                            Binary::get(opLess, subRhs, Const::get(0))),
                                Binary::get(opLess, subResult, Const::get(0))));
                searchAndReplace(*RefExp::get(Terminal::get(opOF), def), replacement, true);
                return true;
            }
            default: break;
            }
        }
        else if (flagFuncName.startsWith("LOGICALFLAGS")) {
            const SharedExp param = rhs->access<Exp, 2, 1>();
            switch (base->getOper()) {
            case opNF: {
                SharedExp replacement = Binary::get(opLess, param, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opNF), def), replacement, true);
                return true;
            }
            case opZF: {
                SharedExp replacement = Binary::get(opEquals, param, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opZF), def), replacement, true);
                return true;
            }
            case opCF: {
                SharedExp replacement = Const::get(0);
                searchAndReplace(*RefExp::get(Terminal::get(opCF), def), replacement, true);
                return true;
            }
            case opOF: {
                const SharedExp replacement = Const::get(0);
                searchAndReplace(*RefExp::get(Terminal::get(opOF), def), replacement, true);
                return true;
            }
            default: break;
            }
        }
        else if (flagFuncName.startsWith("INCDECFLAGS")) {
            const SharedExp param = rhs->access<Exp, 2, 1>();
            switch (base->getOper()) {
            case opOF: {
                const SharedExp replacement = Const::get(0);
                searchAndReplace(*RefExp::get(Terminal::get(opOF), def), replacement, true);
                return true;
            }
            case opZF: {
                const SharedExp replacement = Binary::get(opEquals, param, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opZF), def), replacement, true);
                return true;
            }
            case opNF: {
                const SharedExp replacement = Binary::get(opLess, param, Const::get(0));
                searchAndReplace(*RefExp::get(Terminal::get(opNF), def), replacement, true);
                return true;
            }
            default: break;
            }
        }
    }

    // do the replacement
    // bool convert = doReplaceRef(re, rhs);
    return searchAndReplace(*e, rhs, true); // Last parameter true to change collectors
}


bool Statement::isNullStatement() const
{
    if (m_kind != StmtType::Assign) {
        return false;
    }

    SharedExp right = static_cast<const Assign *>(this)->getRight();

    if (right->isSubscript()) {
        // Must refer to self to be null
        return this == right->access<RefExp>()->getDef();
    }
    else {
        // Null if left == right
        return *static_cast<const Assign *>(this)->getLeft() == *right;
    }
}


void Statement::bypass()
{
    // Use the Part modifier so we don't change the top level of LHS of assigns etc
    CallBypasser cb(this);
    StmtPartModifier sm(&cb);

    accept(&sm);

    if (cb.isTopChanged()) {
        simplify(); // E.g. m[esp{20}] := blah -> m[esp{-}-20+4] := blah
    }
}


void Statement::addUsedLocs(LocationSet &used, bool cc /* = false */, bool memOnly /*= false */)
{
    UsedLocsFinder ulf(used, memOnly);
    UsedLocsVisitor ulv(&ulf, cc);

    accept(&ulv);
}


SharedType Statement::meetWithFor(const SharedType &ty, const SharedExp &e, bool &changed)
{
    bool thisCh        = false;
    SharedType typeFor = getTypeForExp(e);

    assert(typeFor);
    SharedType newType = typeFor->meetWith(ty, thisCh);

    if (thisCh) {
        changed = true;
        setTypeForExp(e, newType->clone());
    }

    return newType;
}
