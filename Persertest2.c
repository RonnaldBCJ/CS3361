//cd /mnt/c/Users/wyatt/OneDrive\ -\ Texas\ Tech\ University/Desktop/C\ FIles/parser/parser/

#include "front.h"

#include "parser.h"

typedef enum {
    IDENT, INT_LIT, ASSIGN_OP, ADD_OP, SUB_OP, MULT_OP, DIV_OP, MOD_OP,
    LESSER_OP, GREATER_OP, EQUAL_OP, NEQUAL_OP, LEQUAL_OP, GEQUAL_OP,
    BOOL_AND, BOOL_OR, BOOL_NOT, KEY_IN, KEY_OUT, KEY_IF, KEY_ELSE,
    OPEN_PAREN, CLOSE_PAREN, OPEN_CURL, CLOSE_CURL, SEMICOLON, UNKNOWN
} TokenType;

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
static int lookup(char ch);
static TokenType getToken(const char *lexeme);
static void printToken(const char *lexeme, TokenType token);
int lex();  // Forward declaration of lex function

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) 
{
    printf("Cooke Analyzer :: R11825913\n");

    if (argc != 2) {
        printf("Usage: %s <path_to_source_file>\n", argv[0]);
        return 1;
    }

    /* Open the input data file and process its contents */
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open %s\n", argv[1]);
    } else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the token */
static int lookup(char ch || char ch[]) {
    switch (ch) {
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
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
        case '<':
            addChar();
            nextToken = LESSER_OP;
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            break;
        case '(':
            addChar();
            nextToken = OPEN_PAREN;
            break;
        case ')':
            addChar();
            nextToken = CLOSE_PAREN;
            break;
        case '{':
            addChar();
            nextToken = OPEN_CURL;
            break;
        case '}':
            addChar();
            nextToken = CLOSE_CURL;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}
static int lookupString(const char* str) {
    if (strncmp(str, "input", 5) == 0) {
        addChar();
        nextToken = KEY_IN;
    } else if (strncmp(str, "output", 6) == 0) {
        addChar();
        nextToken = KEY_OUT;
    } else if (strncmp(str, "if", 2) == 0) {
        addChar();
        nextToken = KEY_IF;
    } else if (strncmp(str, "else", 4) == 0) {
        addChar();
        nextToken = KEY_ELSE;
    } else if (strncmp(str, "EQUAL_OP", 8) == 0) {
        addChar();
        nextToken = EQUAL_OP;
    } else if (strncmp(str, "!=", 2) == 0) {
        addChar();
        nextToken = NEQUAL_OP;
    } else if (strncmp(str, "<=", 2) == 0) {
        addChar();
        nextToken = LEQUAL_OP;
    } else if (strncmp(str, ">=", 2) == 0) {
        addChar();
        nextToken = GEQUAL_OP;
    } else if (strncmp(str, "&&", 2) == 0) {
        addChar();
        nextToken = BOOL_AND;
    } else if (strncmp(str, "||", 2) == 0) {
        addChar();
        nextToken = BOOL_OR;
    } else {
        addChar();
        nextToken = UNKNOWN;
    }
    return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen < 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long\n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = 'L'; // LETTER
        else if (isdigit(nextChar))
            charClass = 'D'; // DIGIT
        else
            charClass = 'U'; // UNKNOWN
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
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
        case 'L':
            addChar();
            getChar();
            while (charClass == 'L' || charClass == 'D') {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Parse integer literals */
        case 'D':
            addChar();
            getChar();
            while (charClass == 'D') {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case 'U':
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            strcpy(lexeme, "EOF");
            break;
    } /* End of switch */

    printToken(lexeme, nextToken);
    return nextToken;
} /* End of function lex */

/*****************************************************/
/* printToken - a function to print the lexeme and its corresponding token */
static void printToken(const char *lexeme, TokenType token) {
    const char *tokenNames[] = {
        "IDENT", "INT_LIT", "ASSIGN_OP", "ADD_OP", "SUB_OP", "MULT_OP", "DIV_OP", "MOD_OP",
        "LESSER_OP", "GREATER_OP", "EQUAL_OP", "NEQUAL_OP", "LEQUAL_OP", "GEQUAL_OP",
        "BOOL_AND", "BOOL_OR", "BOOL_NOT", "KEY_IN", "KEY_OUT", "KEY_IF", "KEY_ELSE",
        "OPEN_PAREN", "CLOSE_PAREN", "OPEN_CURL", "CLOSE_CURL", "SEMICOLON", "UNKNOWN"
    };
     if (token >= 0 && token <= UNKNOWN) {
        printf("%s\t%s\n", lexeme, tokenNames[token]);
    } else {
        printf("Error: Invalid token value\n");
    }
}
