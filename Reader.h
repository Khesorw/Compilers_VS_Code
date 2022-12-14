/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ hdr__ LANGUAGE ......... |
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <stdlib.h>
#include <limits.h> /* implementation-defined data type ranges and limits */



/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for hydra */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
#define HD_SET_FUL 0x08 //0000.1000
#define HD_RST_FUL 0xF7 //1111.0111
#define HD_CHK_FUL 0x08 //0000.1000
/* TO_DO: BIT 2: EMP: Empty */
#define HD_SET_EMP 0x04 //0000.0100
#define HD_RST_EMP 0xFB //1111.1011
#define HD_CHK_EMP 0x04 //0000.0100
/* TO_DO: BIT 1: REL = Relocation */
#define HD_SET_REL 0x01 //0000.0010
#define HD_RST_REL 0x02 //1111.1101
#define HD_CHK_REL 0x01 //0000.0010
/* TO_DO: BIT 0: END = EndOfBuffer */
#define END 0x00
 

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
//is value for the mode
typedef struct position {
	hdr_int mark;			/* the offset to the mark position (in chars) */
	hdr_int read;			/* the offset to the get a char position (in chars) */
	hdr_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	hdr_char*	content;			/* pointer to the beginning of character array (character buffer) */
	hdr_int	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	hdr_int	increment;			/* character array increment factor */
	hdr_int	mode;				/* operational mode indicator */
	hdr_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	hdr_int	histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(hdr_int, hdr_int, hdr_int);
ReaderPointer	readerAddChar		(ReaderPointer const, hdr_char);
hdr_boln		readerClear		    (ReaderPointer const);
hdr_boln		readerFree		    (ReaderPointer const);
hdr_boln		readerIsFull		(ReaderPointer const);
hdr_boln		readerIsEmpty		(ReaderPointer const);
hdr_boln		readerSetMark		(ReaderPointer const, hdr_int);
hdr_int		readerPrint		    (ReaderPointer const);
hdr_int		readerLoad			(ReaderPointer const, FILE* const);
hdr_boln		readerRecover		(ReaderPointer const);
hdr_boln		readerRetract		(ReaderPointer const);
hdr_boln		readerRestore		(ReaderPointer const);
/* Getters */
hdr_char		readerGetChar		(ReaderPointer const);
hdr_char*		readerGetContent	(ReaderPointer const, hdr_int);
hdr_int		readerGetPosRead	(ReaderPointer const);
hdr_int		readerGetPosWrte	(ReaderPointer const);
hdr_int		readerGetPosMark	(ReaderPointer const);
hdr_int		readerGetSize		(ReaderPointer const);
hdr_int		readerGetInc		(ReaderPointer const);
hdr_int		readerGetMode		(ReaderPointer const);
hdr_byte		readerGetFlags		(ReaderPointer const);
hdr_int		readerShowStat		(ReaderPointer const);

#endif
