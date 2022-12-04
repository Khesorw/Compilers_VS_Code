/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern hdr_int line;
extern Token tokenizer();
extern hdr_char* keywordTable[];
hdr_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"hdr"
#define LANG_WRTE		"print"
#define LANG_READ		"input"
#define LANG_MAIN		"main:"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	PRINT,
	INPUT,
	INT,
	STR,
	BIT,
	IF,
	ELSE,
	WHILE,
	FOR,
	BREAK,
	RETURN,
	DEF
};

/* Function definitions */
hdr_void startParser();
hdr_void matchToken(hdr_int, hdr_int);
hdr_void syncErrorHandler(hdr_int);
hdr_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
hdr_void codeSession();
hdr_void dataSession();
hdr_void optVarListDeclarations();
hdr_void optionalStatements();
hdr_void outputStatement();
hdr_void outputVariableList();
hdr_void program();
hdr_void statement();
hdr_void statements();
hdr_void statementsPrime();

#endif
