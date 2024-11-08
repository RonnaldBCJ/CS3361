


#include <ctype.h>
#include <string.h>
#include <stdio.h>

#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1


#define UNKNOWN 99

/* Token codes */

#define INT_LIT 10
#define IDENT 11
#define MOD_OP 12
#define LESSER_OP 13
#define GREATER_OP 14
#define EQUAL_OP 16
#define NEQUAL_OP 17
#define LEQUAL_OP 18
#define GEQUAL_OP 19


#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
//#define LEFT_PAREN 25
//#define RIGHT_PAREN 26

#define BOOL_AND 27
#define BOOL_OR 28
#define BOOL_NOT 29
#define KEY_IN 30
#define KEY_OUT 31
#define KEY_IF 32
#define KEY_ELSE 33
#define OPEN_PAREN 34
#define CLOSE_PAREN 35
#define OPEN_CURL 36
#define CLOSE_CURL 37
#define SEMICOLON 38



int lex();

#endif
