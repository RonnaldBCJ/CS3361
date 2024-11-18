/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages. 
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

#include "front.h"
#include "parser.h"
#include "parser.c"
/* Global Variable */
int nextToken;
const char* displayResult(int token);
/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */
int main()   
{
    printf("Running");
    /* Open the input data file and process its contents */
    if ((in_fp = fopen("front.in", "r")) == NULL) {
        printf("ERROR - cannot open front.in \n");
    } else {
        printf("File good :)");
        getChar();
        do {
            lex();
            expr();
        } while (nextToken != EOF);
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        case '&': //DOUBLES
            addChar();
            getChar();
            if (nextChar == '&') {
                addChar();
                nextToken = BOOL_AND;
            } else {
                ungetc(nextChar, in_fp);       //UNDOUBLES IT?    KEEP   
                nextToken = UNKNOWN;
            }
            break;
        case '|':
            addChar();
            getChar();
            if (nextChar == '|') {
                addChar();
                nextToken = BOOL_OR;
                }
            else {
                ungetc(nextChar, in_fp);
                nextToken = UNKNOWN;
                }
            break;
        case '!':    
            addChar();
            getChar();
            if (nextChar == '=') {
                addChar();
                nextToken = NEQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = BOOL_NOT;
            }
            
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '=':
            addChar();   
            getChar();
            if (nextChar == '=') {
                addChar();
                nextToken = EQUAL_OP;
            } else {
                ungetc(nextChar, in_fp);
                nextToken = ASSIGN_OP;
            }
            break;
        case '<':
            addChar();
            getChar();
            if (nextChar == '=') {
                addChar();
                nextToken = LEQUAL_OP;
                }
            else { 
                ungetc(nextChar, in_fp);
                nextToken = LESSER_OP;
                }
            break;
        case '>':
            addChar();
            getChar();
            if (nextChar == '=') {
                addChar();
                nextToken = GEQUAL_OP;
                } else {
                ungetc(nextChar, in_fp);
                nextToken = GREATER_OP;
                }
            break;
        default:
            nextToken = UNKNOWN;
            addChar();
            break;
    }
    return nextToken;
}


/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */


static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}



//////END OF TEST CODE
/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */

    if (nextToken != EOF){
        printf("%s\t%s\n", lexeme, displayResult(nextToken));
        }
    return nextToken;
}
    

    const char* displayResult(int token){
        switch(token){
            case ASSIGN_OP:
                return "ASSIGN_OP";
            case LESSER_OP:
                return "LESSER_OP";
            case GREATER_OP:
                return "GREATER_OP";
            case EQUAL_OP:
                return "EQUAL_OP";
            case NEQUAL_OP:
                return "NEQUAL_OP";
            case LEQUAL_OP:
                return "LEQUAL_OP";
            case GEQUAL_OP:
                return "GEQUAL_OP";     
            case OPEN_PAREN:
                return "OPEN_PAREN";
            case CLOSE_PAREN:
                return "CLOSE_PAREN";
            case OPEN_CURL:
                return "OPEN_CURL";
            case CLOSE_CURL:
                return "CLOSE_CURL";
            case ADD_OP:
                return "ADD_OP";
            case SUB_OP:
                return "SUB_OP";
            case MULT_OP:
                return "MULT_OP";
            case DIV_OP:
                return "DIV_OP";
            case MOD_OP:
                return "MOD_OP";
            case BOOL_AND:
                return "BOOL_AND";
            case BOOL_OR:
                return "BOOL_OR";   
            case BOOL_NOT:
                return "BOOL_NOT";
            case SEMICOLON:
                return "SEMICOLON";
            case INT_LIT:
                return "INT_LIT";
            case IDENT:
                return "IDENT";
            case KEY_IN:
                return "KEY_IN";
            case KEY_OUT:
                return "KEY_OUT";
            case KEY_IF:    
                return "KEY_IF";
            case KEY_ELSE:
                return "KEY_ELSE";
            case EOF:      
                return "EOF";
            default:    
                return "UNKNOWN";   
        }
    }


