#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
//NEW TOKENS
#define KEY_IN 12
#define KEY_OUT 13
#define KEY_IF 14
#define KEY_ELSE 15
#define OPEN_CURL 16
#define CLOSE_CURL 17
// OG
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
// NEW
#define LESSER_OP 27 
#define GREATER_OP 28
#define EQUAL_OP 29
#define NEQUAL_OP 30
#define LEQUAL_OP 31
#define GEQUAL_OP 32
#define OPEN_PAREN 33
#define CLOSE_PAREN 34
#define MOD_OP 35
#define BOOL_AND 36
#define BOOL_OR 37
#define BOOL_NOT 38
#define SEMICOLON 39


int lex();

#endif
