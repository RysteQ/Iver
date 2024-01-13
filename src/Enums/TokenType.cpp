#ifndef DEF_TokenType
#define DEF_TokenType

enum TokenType {
    ASSIGNMENT,

    ADD, SUB, MUL, DIV, MOD, POW, INC, DEC,
    SRT_ADD, SRT_SUB, SRT_MUL, SRT_DIV, SRT_MOD, SRT_POW,
    PARENTHESES_START, PARENTHESES_END,

    BIGGER_THAN, SMALLER_THAN, BIGGER_OR_EQUAL, SMALLER_OR_EQUAL,
    LOGICAL_EQUAL, LOGICAL_NOT_EQUAL, LOGICAL_OR, LOGICAL_AND,
    LOGICAL_NOT,

    FUNCTION, IF, ELSE, WHILE_LOOP, FOR_LOOP, END,

    VARIABLE, VALUE,

    PRINT,
    READ,

    COMMENT, EOL, EOP
};

#endif