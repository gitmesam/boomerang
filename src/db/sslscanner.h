#pragma once

#ifndef FLEX_HEADER_sslscanner_h
#define FLEX_HEADER_sslscanner_h
#define YY_SSLScanner_CHAR    char
//#line 1 "//usr/local/lib/flexskel.h"
/* A lexical scanner header generated by flex */
/* MODIFIED FOR C++ CLASS BY Alain Coetmeur: coetmeur(at)icdc.fr */
/* Note that (at) mean the 'at' symbol that I cannot write */
/* because it is expanded to the class name */
/* made at Informatique-CDC, Research&development department */
/* company from the Caisse Des Depots et Consignations */

/*********************************************/
/* SYSTEM dependent declaration, includes... */
/*********************************************/
/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_PROTOS
#define YY_USE_PROTOS
#endif
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else /* ! __cplusplus */
#ifdef __STDC__
#ifdef __GNUC__
#else
#endif /* __GNUC__ */
#ifndef YY_USE_PROTOS
#define YY_USE_PROTOS
#endif
#endif /* __STDC__ */
#endif /* ! __cplusplus */
/*********************************************/
/* COMPILER DEPENDENT   MACROS               */
/*********************************************/
/* use prototypes in function declarations */
#ifndef YY_PROTO
#ifdef YY_USE_PROTOS
#define YY_PROTO(proto)    proto
#else
#define YY_PROTO(proto)    ()
#endif
#endif
#include <cstdio>

/* % here is the declaration from section1 %header{  */
//#line 29 "sslscanner.l"
#include "sslparser.h"
#define MAX_LINE    1024 // the longest SSL spec line
//#line 45 "sslscanner.l"
#define YY_SSLScanner_CONSTRUCTOR_CODE
//#line 46 "sslscanner.l"
#define YY_SSLScanner_INPUT_CODE   \
	if (in.eof()) {				   \
		result = 0;				   \
	}							   \
	else {						   \
		in.read(buffer, max_size); \
		result = in.gcount();	   \
	}							   \
	return result;

//#line 53 "sslscanner.l"
#define YY_SSLScanner_MEMBERS												\
public:																		\
	int           theLine;           /* the current line number */			\
	char          lineBuf[MAX_LINE]; /* the current line */					\
	bool          traceLines;        /* echo each lines as it is scanned */	\
	std::istream& in;
//#line 60 "sslscanner.l"
#define YY_SSLScanner_LEX_PARAM    yy_SSLParser_stype & yylval
//#line 62 "sslscanner.l"
//#line 52 "//usr/local/lib/flexskel.h"

#ifdef YY_USE_CLASS
#ifdef YY_SSLScanner_IOSTREAM
#include <iostream.h>
#define YY_SSLScanner_IFILE            istream
#define YY_SSLScanner_OFILE            ostream
#define YY_SSLScanner_ERRFILE          cerr

#ifndef YY_SSLScanner_IFILE_DEFAULT
#define YY_SSLScanner_IFILE_DEFAULT    &cin
#endif

#ifndef YY_SSLScanner_OFILE_DEFAULT
#define YY_SSLScanner_OFILE_DEFAULT    &cout
#endif

#endif
#endif

#ifndef YY_SSLScanner_IFILE
#define YY_SSLScanner_IFILE    FILE
#endif

#ifndef YY_SSLScanner_OFILE
#define YY_SSLScanner_OFILE    FILE
#endif

#ifndef YY_SSLScanner_ERRFILE
#define YY_SSLScanner_ERRFILE    stderr
#endif

#ifndef YY_SSLScanner_IFILE_DEFAULT
#define YY_SSLScanner_IFILE_DEFAULT    stdin
#endif

#ifndef YY_SSLScanner_OFILE_DEFAULT
#define YY_SSLScanner_OFILE_DEFAULT    stdout
#endif

#ifndef YY_SSLScanner_TEXT
#define YY_SSLScanner_TEXT    yytext
#endif
#ifndef YY_SSLScanner_LENG
#define YY_SSLScanner_LENG    yyleng
#endif
#ifndef YY_SSLScanner_IN
#define YY_SSLScanner_IN      yyin
#endif
#ifndef YY_SSLScanner_OUT
#define YY_SSLScanner_OUT     yyout
#endif

#ifndef YY_SSLScanner_LEX_RETURN
#define YY_SSLScanner_LEX_RETURN    int
#else
#ifndef YY_SSLScanner_LEX_DEFINED
#define YY_SSLScanner_LEX_DEFINED
#endif
#endif

#ifndef YY_SSLScanner_LEX
#define YY_SSLScanner_LEX    yylex
#else
#ifndef YY_SSLScanner_LEX_DEFINED
#define YY_SSLScanner_LEX_DEFINED
#endif
#endif

#ifndef YY_SSLScanner_LEX_PARAM
#ifndef YY_USE_PROTOS
#define YY_SSLScanner_LEX_PARAM
#else
#define YY_SSLScanner_LEX_PARAM    void
#endif
#else
#ifndef YY_SSLScanner_LEX_DEFINED
#define YY_SSLScanner_LEX_DEFINED
#endif
#endif

#ifndef YY_SSLScanner_LEX_PARAM_DEF
#define YY_SSLScanner_LEX_PARAM_DEF
#else
#ifndef YY_SSLScanner_LEX_DEFINED
#define YY_SSLScanner_LEX_DEFINED
#endif
#endif

#ifndef YY_SSLScanner_RESTART
#define YY_SSLScanner_RESTART              yyrestart
#endif
#ifndef YY_SSLScanner_SWITCH_TO_BUFFER
#define YY_SSLScanner_SWITCH_TO_BUFFER     yy_switch_to_buffer
#endif
#ifndef YY_SSLScanner_LOAD_BUFFER_STATE
#define YY_SSLScanner_LOAD_BUFFER_STATE    yy_load_buffer_state
#endif

#ifndef YY_SSLScanner_CREATE_BUFFER
#define YY_SSLScanner_CREATE_BUFFER    yy_create_buffer
#ifndef YY_USE_CLASS
#ifndef yy_new_buffer
#define yy_new_buffer                  yy_create_buffer
#endif
#endif
#endif
#ifndef YY_SSLScanner_DELETE_BUFFER
#define YY_SSLScanner_DELETE_BUFFER    yy_delete_buffer
#endif
#ifndef YY_SSLScanner_INIT_BUFFER
#define YY_SSLScanner_INIT_BUFFER      yy_init_buffer
#endif

#ifdef YY_SSLScanner_FLEX_DEBUG
#ifndef YY_SSLScanner_DEBUG
#define YY_SSLScanner_DEBUG    1
#endif
#else
#ifndef YY_SSLScanner_DEBUG
#define YY_SSLScanner_DEBUG    0
#endif
#endif

#if YY_SSLScanner_DEBUG != 0
#ifndef YY_SSLScanner_DEBUG_FLAG
#define YY_SSLScanner_DEBUG_FLAG    yy_flex_debug
#endif
#ifndef YY_SSLScanner_DEBUG_INIT
#define YY_SSLScanner_DEBUG_INIT    1
#endif
#endif

#ifndef YY_USE_CLASS
#else

#ifndef YY_SSLScanner_CURRENT_BUFFER
#define YY_SSLScanner_CURRENT_BUFFER    YY_CURRENT_BUFFER
#endif
#ifndef YY_SSLScanner_ECHO
#define YY_SSLScanner_ECHO              yy_echo
#endif
#ifdef YY_SSLScanner_ECHO_PURE
#define YY_SSLScanner_ECHO_NOCODE
#endif

#ifndef YY_SSLScanner_ECHO_CODE
#ifndef YY_SSLScanner_IOSTREAM
#define YY_SSLScanner_ECHO_CODE    fwrite((char *)YY_SSLScanner_TEXT, YY_SSLScanner_LENG, 1, YY_SSLScanner_OUT);
#else
#define YY_SSLScanner_ECHO_CODE    (YY_SSLScanner_OUT->write((char *)YY_SSLScanner_TEXT, YY_SSLScanner_LENG));
#endif
#endif

#ifndef YY_SSLScanner_INPUT
#define YY_SSLScanner_INPUT    yy_input
#endif
#ifdef YY_SSLScanner_INPUT_PURE
#define YY_SSLScanner_INPUT_NOCODE
#endif

#ifndef YY_SSLScanner_INPUT_CODE
#ifndef YY_SSLScanner_IOSTREAM
#define YY_SSLScanner_INPUT_CODE    return result = fread(buffer, 1, max_size, YY_SSLScanner_IN);

#else
#define YY_SSLScanner_INPUT_CODE												\
	if (YY_SSLScanner_IN->eof()) {												\
		result = 0; }															\
	else {																		\
		YY_SSLScanner_IN->read(buffer, max_size);								\
		result = YY_SSLScanner_IN->gcount();									\
		YY_SSLScanner_IN->clear(YY_SSLScanner_IN->rdstate() & (~ios::failbit));	\
		if (YY_SSLScanner_IN->bad()) {											\
			result = -1; }														\
	}																			\
	return result;

#endif
#endif

#ifdef YY_SSLScanner_FATAL_ERROR_PURE
#define YY_SSLScanner_FATAL_ERRO_NOCODE
#endif
#ifndef YY_SSLScanner_FATAL_ERROR
#define YY_SSLScanner_FATAL_ERROR    yy_fatal_error
#endif

#ifndef YY_SSLScanner_FATAL_ERROR_CODE
#ifndef YY_SSLScanner_IOSTREAM
#define YY_SSLScanner_FATAL_ERROR_CODE \
	fputs(msg, YY_SSLScanner_ERRFILE); \
	putc('\n', YY_SSLScanner_ERRFILE); \
	exit(1);
#else
#define YY_SSLScanner_FATAL_ERROR_CODE	  \
	YY_SSLScanner_ERRFILE << msg << endl; \
	exit(1);
#endif
#endif

#ifndef YY_SSLScanner_WRAP
#define YY_SSLScanner_WRAP    yy_wrap
#endif
#ifdef YY_SSLScanner_WRAP_PURE
#define YY_SSLScanner_WRAP_NOCODE
#endif
#ifndef YY_SSLScanner_WRAP_CODE
#define YY_SSLScanner_WRAP_CODE    return 1;

#endif

#ifndef YY_SSLScanner_MEMBERS
#define YY_SSLScanner_MEMBERS
#endif
#ifndef YY_SSLScanner_CONSTRUCTOR_CODE
#define YY_SSLScanner_CONSTRUCTOR_CODE
#endif
#ifndef YY_SSLScanner_DESTRUCTOR_CODE
#define YY_SSLScanner_DESTRUCTOR_CODE
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

class SSLScanner
{
private:    /* data */
	YY_SSLScanner_CHAR *yy_c_buf_p;
	YY_SSLScanner_CHAR yy_hold_char;
	int yy_n_chars;
	int yy_init;
	int yy_start;
	int yy_did_buffer_switch_on_eof;

private:    /* functions */
	void yy_initialize();
	int input();

	int yyinput() { return input(); }
	int yy_get_next_buffer();
	void yyunput(YY_SSLScanner_CHAR c, YY_SSLScanner_CHAR *buf_ptr);

	/* use long instead of yy_state_type because it is undef */
	long yy_get_previous_state_(void);
	long yy_try_NUL_trans_(long current_state_);

protected:    /* non virtual */
	YY_BUFFER_STATE YY_SSLScanner_CURRENT_BUFFER;
	void YY_SSLScanner_RESTART(YY_SSLScanner_IFILE *input_file);
	void YY_SSLScanner_SWITCH_TO_BUFFER(YY_BUFFER_STATE new_buffer);
	void YY_SSLScanner_LOAD_BUFFER_STATE(void);
	YY_BUFFER_STATE YY_SSLScanner_CREATE_BUFFER(YY_SSLScanner_IFILE *file, int size);
	void YY_SSLScanner_DELETE_BUFFER(YY_BUFFER_STATE b);
	void YY_SSLScanner_INIT_BUFFER(YY_BUFFER_STATE b, YY_SSLScanner_IFILE *file);

protected:    /* virtual */
	virtual void YY_SSLScanner_ECHO()
#ifdef YY_SSLScanner_ECHO_PURE
		= 0
#endif
	;
	virtual int YY_SSLScanner_INPUT(char *buf, int& result, int max_size)
#ifdef YY_SSLScanner_INPUT_PURE
		= 0
#endif
	;
	virtual void YY_SSLScanner_FATAL_ERROR(char *msg)
#ifdef YY_SSLScanner_FATAL_ERROR_PURE
		= 0
#endif
	;
	virtual int YY_SSLScanner_WRAP()
#ifdef YY_SSLScanner_WRAP_PURE
		= 0
#endif
	;

public:
	YY_SSLScanner_CHAR *YY_SSLScanner_TEXT;
	int YY_SSLScanner_LENG;
	YY_SSLScanner_IFILE *YY_SSLScanner_IN;
	YY_SSLScanner_OFILE *YY_SSLScanner_OUT;
	YY_SSLScanner_LEX_RETURN YY_SSLScanner_LEX(YY_SSLScanner_LEX_PARAM);
	SSLScanner(std::istream& ins, bool trace);
	virtual ~SSLScanner();
#if YY_SSLScanner_DEBUG != 0
	int YY_SSLScanner_DEBUG_FLAG;
#endif

public:    /* added members */
	YY_SSLScanner_MEMBERS
};

#endif

/* declaration of externs for public use of yylex scanner */

/* % here is the declaration from section2 %header{ */
//#line 327 "sslscanner.l"
#endif
//#line 375 "//usr/local/lib/flexskel.h"

/* end of generated header */
