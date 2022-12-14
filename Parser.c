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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

hdr_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
hdr_void matchToken(hdr_int tokenCode, hdr_int tokenAttribute) {
	hdr_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
hdr_void syncErrorHandler(hdr_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
hdr_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	case ASSIN_T:
		printf("ASSIN_T\n");
		break;
	case ART_T:
		printf("ART_T\n");
		break;
	case VID_T:
		printf("VID_T\n");
		break;
	case INL_T:
		printf("INL_T\n");
		break;
	case RTE_T:
		printf("RTE_T\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
hdr_void program() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
		
		//	dataSession();
			codeSession();
			break;
		}
		else if(!strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0){
			codeSession();
			break;
		}

		else {
			printError();
		}

		
	
	case STR_T:

	;
	break;
	case VID_T:
		statements();

	break;

	
	
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
// hdr_void dataSession() {
// 	matchToken(KW_T, KW_data);
// 	matchToken(LBR_T, NO_ATTR);
// 	optVarListDeclarations();
// 	matchToken(RBR_T, NO_ATTR);
// 	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
// }

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
hdr_void optVarListDeclarations() {
	switch (lookahead.code) {
		case INT:
		case STR:
		
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
hdr_void codeSession() {
matchToken(MNID_T,NO_ATTR);
matchToken(LBR_T,NO_ATTR);
statement();
while(lookahead.code != RBR_T && lookahead.code != EOF){
	statement();
}
matchToken(RBR_T,NO_ATTR);
printf("HDR_Implemention: Implemention Parsed\n");

	

}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
hdr_void optionalStatements() {
	switch (lookahead.code) {
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
hdr_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
hdr_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
hdr_void statement() {
	switch (lookahead.code) {

	case KW_T:
	
		outputStatement();
		printf("hdr: keyword parsed\n");

		
	break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		else{
			matchToken(MNID_T, NO_ATTR);
			statements();
		}
	break;


	case VID_T:
		matchToken(VID_T, NO_ATTR);
		matchToken(ASSIN_T, NO_ATTR);
		if(lookahead.code == EOS_T) printError();

		// if(lookahead.code  VID_T)
		// {
		// 	outputVariableList();
		// }
		//  matchToken(VID_T, NO_ATTR);
		hdr_int controlT = 0;
		while(lookahead.code != EOS_T && controlT != 200){
			if(lookahead.code == INL_T){
				matchToken(INL_T,NO_ATTR);
				printf("hdr: integer parsed\n");
			}
			else if(lookahead.code == STR_T){
				matchToken(STR_T,NO_ATTR);
				printf("hdr: string operator parsed\n");
			}
			else if(lookahead.code == ART_T){
				matchToken(ART_T,NO_ATTR);
				printf("hdr: Arithmetic operator pased\n");
			}else if(lookahead.code == VID_T){
				matchToken(VID_T,NO_ATTR);
				printf("hdr: Vairable parsed\n");
			}
			controlT += 1;
		}

		if(controlT == 200) printError();
		matchToken(EOS_T,NO_ATTR);
		printf("%s%s\n",STR_LANGNAME,": Assignment statment parsed");
	break;

	

	case RBR_T:
		printf("empty_function parsed:\n");

	break;

	
		


    
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
} 

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
 hdr_void outputStatement() {
	lookahead.attribute.codeType = PRINT;
	matchToken(KW_T, PRINT);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
hdr_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		printf("hdr: string var list parsed\n");
		break;
	case INL_T:
		matchToken(INL_T,NO_ATTR);
		printf("hdr: Integer var parsed\n");
		
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
