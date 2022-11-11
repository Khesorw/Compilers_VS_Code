/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
//#include <null.h> /* NULL pointer constant is defined there */
#include "Reader.h"
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer-Leteral token */
	SEOF_T		/* 11: Source end-of-file token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	hdr_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	hdr_int intValue;						/* integer literal attribute (value) */
	hdr_int keywordIndex;					/* keyword index in the keyword table */
	hdr_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	hdr_float floatValue;					/* floating-point literal attribute (value) */
	hdr_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	hdr_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	hdr_byte flags;			/* Flags information */
	union {
		hdr_int intValue;				/* Integer value */
		hdr_float floatValue;			/* Float value */
		hdr_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	hdr_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 9

/* TO_DO: Transition table - type of states defined in separate table */
static hdr_int transitionTable[][TABLE_COLUMNS] = {
/*   [A-z] , [0-9],    /#,    #/,    ", :,     other
	   L(0),  D(1), CS(2), CE(3), Q(4), CO(5),  O(6) */
	{     1,  8,    6,     ESNR,    4,   ESNR,  ESNR}, // S0: NOAS
	{     1,  1,    ESWR,  ESWR, ESNR,    3,    2}, // S1: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,    FS}, // S2: ASNR (KEY)
	{    FS,    FS,   FS,   FS,   FS,   FS,    FS}, // S3: ASWR (MVID)
	{     4,     4,    4,    4,    5,    4,    4 }, // S4: NOAS[3]
	{    FS,    FS,   FS,   FS,   FS,   FS,    FS}, // S5: SL (SL)
	{    6,     6,     6,    7,    6,    6,    6}, // S6: NOAS[4] (ES)
	{    FS,    FS,   FS,   FS,   FS,   FS,    FS},  // S7: MLTC (ER)
	{    ESWR,	8,	  ESWR, ESWR, ESWR, ESWR,  ESWR	 }, //S8: NOAS[5]
	{	   FS,	FS,	   FS,   FS,   FS,   FS,   FS} //S9: IL
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static hdr_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	FSNR, /* 06 (Err1 - no retract) */
	FSWR  /* 07 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
hdr_int startScanner(ReaderPointer psc_buf);
static hdr_int nextClass(hdr_char c);			/* character class function */
static hdr_int nextState(hdr_int, hdr_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(hdr_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(hdr_char lexeme[]);
Token funcID	(hdr_char lexeme[]);
Token funcKEY	(hdr_char lexeme[]);
Token funcErr	(hdr_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 12

/* TO_DO: Define the list of keywords */
static hdr_char* keywordTable[KWT_SIZE] = {
	"print",
	"input",
	"int",
	"string",
	"bit",
	"if",
	"else",
	"while",
	"for",
	"break",
	"return",
	"def"
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	hdr_char indentationCharType;
	hdr_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
