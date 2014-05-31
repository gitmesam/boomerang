/* Generated by the New Jersey Machine-Code Toolkit, version 0.5a */
/* command line: tools -debug-match dbm -matcher disassembler.m -decoder dec -encoder enc -verbose hppa.spec
 * hppadis.spec */
/* must #include <mclib.h> before this file */
enum c_c_tag {
    c_arith_dw_TAG = 6,
    c_arith_none_TAG = 7,
    c_arith_w_TAG = 5,
    c_bbs_dw_TAG = 4,
    c_bbs_w_TAG = 3,
    c_cmpb_dw_TAG = 2,
    c_cmpb_w_TAG = 1,
};
typedef struct c_c_instance {
    int tag;
    union {
        struct {
            unsigned c3_16 : 3;
        } c_arith_dw;
        struct {
            char avoid_empty_structures;
        } c_arith_none;
        struct {
            unsigned c3_16 : 3;
        } c_arith_w;
        struct {
            unsigned c_16 : 1;
        } c_bbs_dw;
        struct {
            unsigned c_16 : 1;
        } c_bbs_w;
        struct {
            unsigned c3_16 : 3;
        } c_cmpb_dw;
        struct {
            unsigned c3_16 : 3;
        } c_cmpb_w;
    } u;
} c_c_Instance;
enum c_null_tag {
    c_br_nnull_TAG = 1,
    c_br_null_TAG = 2,
};
typedef struct c_null_instance {
    int tag;
    union {
        struct {
            char avoid_empty_structures;
        } c_br_nnull;
        struct {
            char avoid_empty_structures;
        } c_br_null;
    } u;
} c_null_Instance;
enum c_wcr_tag {
    c_mfctl_TAG = 2,
    c_mfctl_w_TAG = 1,
};
typedef struct c_wcr_instance {
    int tag;
    union {
        struct {
            unsigned r_06 : 5;
        } c_mfctl;
        struct {
            char avoid_empty_structures;
        } c_mfctl_w;
    } u;
} c_wcr_Instance;
enum c_bit_tag {
    c_bitpos_dw_TAG = 2,
    c_bitpos_w_TAG = 1,
    c_bitsar_TAG = 3,
};
typedef struct c_bit_instance {
    int tag;
    union {
        struct {
            unsigned p_06 : 5;
        } c_bitpos_dw;
        struct {
            unsigned p_06 : 5;
        } c_bitpos_w;
        struct {
            char avoid_empty_structures;
        } c_bitsar;
    } u;
} c_bit_Instance;
enum c_addr_tag {
    c_addr_m_TAG = 4,
    c_addr_ma_TAG = 2,
    c_addr_mb_TAG = 1,
    c_addr_s_TAG = 3,
    c_addr_sm_TAG = 5,
};
typedef struct c_addr_instance {
    int tag;
    union {
        struct {
            char avoid_empty_structures;
        } c_addr_m;
        struct {
            char avoid_empty_structures;
        } c_addr_ma;
        struct {
            char avoid_empty_structures;
        } c_addr_mb;
        struct {
            char avoid_empty_structures;
        } c_addr_s;
        struct {
            char avoid_empty_structures;
        } c_addr_sm;
    } u;
} c_addr_Instance;
enum addr_tag {
    addr_index_TAG = 1,
    addr_ldo_TAG = 6,
    addr_lldisp_TAG = 4,
    addr_lsdisp_TAG = 2,
    addr_sldisp_TAG = 5,
    addr_ssdisp_TAG = 3,
};
typedef struct addr_instance {
    int tag;
    union {
        struct {
            c_addr_Instance c_addr;
            int x;
            int ss;
            int b;
        } addr_index;
        struct {
            c_addr_Instance c_addr;
            int ldisp;
            int b;
        } addr_ldo;
        struct {
            c_addr_Instance c_addr;
            int ldisp;
            int ss;
            int b;
        } addr_lldisp;
        struct {
            c_addr_Instance c_addr;
            int im5;
            int ss;
            int b;
        } addr_lsdisp;
        struct {
            c_addr_Instance c_addr;
            int ldisp;
            int ss;
            int b;
        } addr_sldisp;
        struct {
            c_addr_Instance c_addr;
            int im5;
            int ss;
            int b;
        } addr_ssdisp;
    } u;
} addr_Instance;
enum c_faddr_tag {
    c_faddrs_TAG = 1,
};
typedef struct c_faddr_instance {
    int tag;
    union {
        struct {
            char avoid_empty_structures;
        } c_faddrs;
    } u;
} c_faddr_Instance;
enum faddr_tag {
    index_faddr_TAG = 1,
    sdisps_faddr_TAG = 2,
};
typedef struct faddr_instance {
    int tag;
    union {
        struct {
            int x;
            int s;
            int b;
        } index_faddr;
        struct {
            int d;
            int s;
            int b;
        } sdisps_faddr;
    } u;
} faddr_Instance;
extern c_c_Instance c_cmpb_w(unsigned /* [0..7] */ c3_16);
extern c_c_Instance c_cmpb_dw(unsigned /* [0..7] */ c3_16);
extern c_c_Instance c_bbs_w(unsigned /* [0..1] */ c_16);
extern c_c_Instance c_bbs_dw(unsigned /* [0..1] */ c_16);
extern c_c_Instance c_arith_w(unsigned /* [0..7] */ c3_16);
extern c_c_Instance c_arith_dw(unsigned /* [0..7] */ c3_16);
extern c_c_Instance c_arith_none(void);
extern c_null_Instance c_br_nnull(void);
extern c_null_Instance c_br_null(void);
extern c_wcr_Instance c_mfctl_w(void);
extern c_wcr_Instance c_mfctl(unsigned /* [0..31] */ r_06);
extern c_bit_Instance c_bitpos_w(unsigned /* [0..31] */ p_06);
extern c_bit_Instance c_bitpos_dw(unsigned /* [0..31] */ p_06);
extern c_bit_Instance c_bitsar(void);
extern c_addr_Instance c_addr_mb(void);
extern c_addr_Instance c_addr_ma(void);
extern c_addr_Instance c_addr_s(void);
extern c_addr_Instance c_addr_m(void);
extern c_addr_Instance c_addr_sm(void);
extern addr_Instance addr_index(c_addr_Instance c_addr, int x, int ss, int b);
extern addr_Instance addr_lsdisp(c_addr_Instance c_addr, int im5, int ss, int b);
extern addr_Instance addr_ssdisp(c_addr_Instance c_addr, int im5, int ss, int b);
extern addr_Instance addr_lldisp(c_addr_Instance c_addr, int ldisp, int ss, int b);
extern addr_Instance addr_sldisp(c_addr_Instance c_addr, int ldisp, int ss, int b);
extern addr_Instance addr_ldo(c_addr_Instance c_addr, int ldisp, int b);
extern void NOP(void);
extern void COPY(unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ t_27);
extern void ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                unsigned /* [0..31] */ t_27);
extern void ADD_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void ADD_c(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void ADD_c_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void SHL1ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void SHL1ADD_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void SHL2ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void SHL2ADD_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void SHL3ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void SHL3ADD_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void SUB(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                unsigned /* [0..31] */ t_27);
extern void SUB_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void SUB_t(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void SUB_t_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void SUB_b(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void SUB_b_v(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void DS(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_27);
extern void ANDCM(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void AND(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                unsigned /* [0..31] */ t_27);
extern void OR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_27);
extern void XOR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                unsigned /* [0..31] */ t_27);
extern void UXOR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                 unsigned /* [0..31] */ t_27);
extern void COMCLR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void UADDCM(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void UADDCMT(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    unsigned /* [0..31] */ t_27);
extern void ADD_l(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void SHL1ADD_l(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void SHL2ADD_l(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void SHL3ADD_l(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                      unsigned /* [0..31] */ t_27);
extern void DCOR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                 unsigned /* [0..31] */ t_27);
extern void IDCOR(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  unsigned /* [0..31] */ t_27);
extern void HADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                 unsigned /* [0..31] */ t_27);
extern void HADD_s(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void HADD_u(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void HSUB(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                 unsigned /* [0..31] */ t_27);
extern void HSUB_s(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void HSUB_u(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                   unsigned /* [0..31] */ t_27);
extern void HAVG(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                 unsigned /* [0..31] */ t_27);
extern void HSHL1ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void HSHL2ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void HSHL3ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void HSHR1ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void HSHR2ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void HSHR3ADD(c_c_Instance c_c, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                     unsigned /* [0..31] */ t_27);
extern void ADDI(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void ADDI_v(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void ADDI_t(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void ADDI_t_v(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void SUBI(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void SUBI_v(c_c_Instance c_c, int imm11, unsigned /* [0..31] */ r_06, unsigned /* [0..31] */ t_11);
extern void ADDIL(int imm21, unsigned /* [0..31] */ r_06);
extern void LDBX(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDHX(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDWX(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDWAX(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDCWX(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDBS(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDHS(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDWS(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDWAS(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void LDCWS(addr_Instance addr, unsigned /* [0..31] */ t_27);
extern void STBS(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STHS(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STWS(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STBYS(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STWAS(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void LDB(addr_Instance addr, unsigned /* [0..31] */ t_11);
extern void LDH(addr_Instance addr, unsigned /* [0..31] */ t_11);
extern void LDW(addr_Instance addr, unsigned /* [0..31] */ t_11);
extern void LDWM(addr_Instance addr, unsigned /* [0..31] */ t_11);
extern void LDO(addr_Instance addr, unsigned /* [0..31] */ t_11);
extern void STB(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STH(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STW(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void STWM(unsigned /* [0..31] */ r_11, addr_Instance addr);
extern void LDIL(int imm21, unsigned /* [0..31] */ t_06);
extern void BL(c_null_Instance c_null, int ubr_target, unsigned /* [0..31] */ t_06);
extern void GATE(c_null_Instance c_null, int ubr_target, unsigned /* [0..31] */ t_06);
extern void BL_PUSH(c_null_Instance c_null, int ubr_target, unsigned /* [0..31] */ t_06);
extern void BL_LONG(c_null_Instance c_null, int ubr_target);
extern void BLR(c_null_Instance c_null, unsigned /* [0..31] */ x_11, unsigned /* [0..31] */ t_06);
extern void BV(c_null_Instance c_null, unsigned /* [0..31] */ x_11, unsigned /* [0..31] */ b_06);
extern void BVE(unsigned /* [0..1] */ p_31, c_null_Instance c_null, unsigned /* [0..31] */ b_06);
extern void BVE_l(unsigned /* [0..1] */ p_31, c_null_Instance c_null, unsigned /* [0..31] */ b_06);
extern void BE(c_null_Instance c_null, addr_Instance addr);
extern void BLE(c_null_Instance c_null, addr_Instance addr);
extern void BREAK(unsigned /* [0..31] */ im5_27, unsigned /* [0..8191] */ im13_06);
extern void SSM(unsigned /* [0..1023] */ im10_06, unsigned /* [0..31] */ t_27);
extern void RSM(unsigned /* [0..1023] */ im10_06, unsigned /* [0..31] */ t_27);
extern void RFI(void);
extern void RFI_r(void);
extern void SYNC(void);
extern void SYNCDMA(void);
extern void MTSM(unsigned /* [0..31] */ r_11);
extern void MTSARCM(unsigned /* [0..31] */ r_11);
extern void MFCTL(c_wcr_Instance c_wcr, unsigned /* [0..31] */ t_27);
extern void MFCTL_w(c_wcr_Instance c_wcr, unsigned /* [0..31] */ t_27);
extern void MTCTL(unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ ct_06);
extern void MFIA(unsigned /* [0..31] */ t_27);
extern void LDSID(unsigned /* [0..3] */ s2_16, unsigned /* [0..31] */ b_06, unsigned /* [0..31] */ t_27);
extern void MTSP(unsigned /* [0..31] */ r_11, int sr);
extern void MFSP(int sr, unsigned /* [0..31] */ t_27);
extern void COMBT(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  int target);
extern void COMBF(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                  int target);
extern void CMPBdwt(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    int target);
extern void CMPBdwf(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, unsigned /* [0..31] */ r_06,
                    int target);
extern void COMIBT(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ im5_11, unsigned /* [0..31] */ r_06,
                   int target);
extern void COMIBF(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ im5_11, unsigned /* [0..31] */ r_06,
                   int target);
extern void CMPIBdw(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ im5_11,
                    unsigned /* [0..31] */ r_06, int target);
extern void BB(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, c_bit_Instance c_bit, int target);
extern void BVB(c_c_Instance c_c, c_null_Instance c_null, unsigned /* [0..31] */ r_11, c_bit_Instance c_bit,
                int target);
extern void FID(int fmt, int r, int t);
extern void FCPY(int fmt, int r, int t);
extern void FABS(int fmt, int r, int t);
extern void FSQRT(int fmt, int r, int t);
extern void FRND(int fmt, int r, int t);
extern void FNEG(int fmt, int r, int t);
extern void FNEGABS(int fmt, int r, int t);
extern void FCPY_E(int f, int r, int t);
extern void FABS_E(int f, int r, int t);
extern void FSQRT_E(int f, int r, int t);
extern void FRND_E(int f, int r, int t);
extern void FNEG_E(int f, int r, int t);
extern void FNEGABS_E(int f, int r, int t);
extern void FCNVFF(int sf, int df, int r, int t);
extern void FCNVXF(int sf, int df, int r, int t);
extern void FCNVFX(int sf, int df, int r, int t);
extern void FCNVFXT(int sf, int df, int r, int t);
extern void FCNVFF_E(int sf, int df, int r, int t);
extern void FCNVXF_E(int sf, int df, int r, int t);
extern void FCNVFX_E(int sf, int df, int r, int t);
extern void FCNVFXT_E(int sf, int df, int r, int t);
extern void FCMP(int fmt, int c, int r1, int r2);
extern void FTEST(int fmt, int c, int r1, int r2);
extern void FCMP_E(unsigned /* [0..1] */ f_20, int c, int r1, int r2);
extern void FTEST_E(unsigned /* [0..1] */ f_20, int c, int r1, int r2);
extern void FADD(int fmt, int r1, int r2, int t);
extern void FSUB(int fmt, int r1, int r2, int t);
extern void FMPY(int fmt, int r1, int r2, int t);
extern void FDIV(int fmt, int r1, int r2, int t);
extern void FADD_E(int fmt, int r1, int r2, int t);
extern void FSUB_E(int fmt, int r1, int r2, int t);
extern void FMPY_E(int fmt, int r1, int r2, int t);
extern void FDIV_E(int fmt, int r1, int r2, int t);
extern c_faddr_Instance c_faddrs(void);
extern faddr_Instance index_faddr(int x, int s, int b);
extern faddr_Instance sdisps_faddr(int d, int s, int b);
extern void FLDWX(c_faddr_Instance c_faddr, faddr_Instance faddr, unsigned /* [0..31] */ t_27);
extern void FLDDX(c_faddr_Instance c_faddr, faddr_Instance faddr, unsigned /* [0..31] */ t_27);
extern void FLDWS(c_faddr_Instance c_faddr, faddr_Instance faddr, unsigned /* [0..31] */ t_27);
extern void FLDDS(c_faddr_Instance c_faddr, faddr_Instance faddr, unsigned /* [0..31] */ t_27);
extern void FSTWX(c_faddr_Instance c_faddr, int r, faddr_Instance faddr);
extern void FSTDX(c_faddr_Instance c_faddr, int r, faddr_Instance faddr);
extern void FSTWS(c_faddr_Instance c_faddr, int r, faddr_Instance faddr);
extern void FSTDS(c_faddr_Instance c_faddr, int r, faddr_Instance faddr);
