#include "Lexer.hpp"

std::list<Lexeme> Lexer::Lex(std::string input) {
    Reset();
    
    to_analyze = input;

    while (lexemes.back().Token() != EOP) {
        char current_character = input[current_byte];
        
        switch (current_character) {
            case '=': AddLexeme(ASSIGNMENT); break;
            
            case '+':
                if (InDepthAdvanceIfLexeme("++", INC))
                    break;
                
                if (InDepthAdvanceIfLexeme("+=", SRT_ADD))
                    break;
                
                AddLexeme(ADD);
                break;

            case '-': 
                if (InDepthAdvanceIfLexeme("--", DEC))
                    break;
                
                if (InDepthAdvanceIfLexeme("+=", SRT_SUB))
                    break;

                AddLexeme(SUB);
                break;

            case '*':
                if (InDepthAdvanceIfLexeme("*=", SRT_MUL))
                    break;
                    
                AddLexeme(MUL);
                break;

            case '/': 
                if (InDepthAdvanceIfLexeme("/=", SRT_DIV))
                    break;
                
                AddLexeme(DIV);
                break;

            case '%':
                if (InDepthAdvanceIfLexeme("%=", SRT_MOD))
                    break;
                
                AddLexeme(MOD);
                break;

            case '^':
                if (InDepthAdvanceIfLexeme("^=", SRT_POW))
                    break;
                
                AddLexeme(POW);
                break;
            
            case '(': AddLexeme(PARENTHESES_START); break;
            case ')': AddLexeme(PARENTHESES_END); break;
            
            case '<':
                if (InDepthAdvanceIfLexeme("+=", SMALLER_OR_EQUAL))
                    break;
                
                AddLexeme(SMALLER_THAN);
                break;

            case '>':
                if (InDepthAdvanceIfLexeme("++", BIGGER_OR_EQUAL))
                    break;
                
                AddLexeme(BIGGER_THAN);
                break;

            case 'i':
                if (InDepthAdvanceIfLexeme("is ", LOGICAL_EQUAL))
                    break;
                
                if (InDepthAdvanceIfLexeme("if ", IF))
                    break;

                AddVariableLexeme();
                break;

            case 'n':
                if (InDepthAdvanceIfLexeme("not ", LOGICAL_NOT))
                    break;

                AddVariableLexeme();
                break;
            
            case 'a':
                if (InDepthAdvanceIfLexeme("and ", LOGICAL_AND))
                    break;
                
                AddVariableLexeme();
                break;
            
            case 'o':
                if (InDepthAdvanceIfLexeme("or ", LOGICAL_OR))
                    break;
                
                AddVariableLexeme();
                break;
            
            case 'p':
                if (InDepthAdvanceIfLexeme("print ", PRINT))
                    break;
                
                AddVariableLexeme();
                break;
            
            case 'r':
                if (InDepthAdvanceIfLexeme("read ", READ))
                    break;
                
                AddVariableLexeme();
                break;

            case 'f':
                if (InDepthAdvanceIfLexeme("function ", FUNCTION))
                    break;
                
                if (InDepthAdvanceIfLexeme("for ", FOR_LOOP))
                    break;
                
                AddVariableLexeme();
                break;

            case 'e':
                if (InDepthAdvanceIfLexeme("end ", END))
                    break;

                AddVariableLexeme();
                break;

            case 'w':
                if (InDepthAdvanceIfLexeme("while  ", WHILE_LOOP))
                    break;

                AddVariableLexeme();
                break;

            case '\n': AddLexeme(EOL); break;
            case NULL_TERMINATOR: AddLexeme(EOP); break;
            
            // TODO
            default:
                if ((current_character >= '0' && current_character <= '9') || current_character == '\"') {
                    AddValueLexeme();
                    break;
                }

                AddVariableLexeme();
                break;
        }

        Advance();
    }

    return lexemes;
}

void Lexer::Reset() {
    lexemes.clear();
    line = 0;
    column = 0;
    current_byte = 0;
}

void Lexer::Advance() {
    if (current_byte < to_analyze.length())
        current_byte++;

    if (to_analyze[current_byte - 1] == '\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
}

void Lexer::InDepthAdvance(unsigned short steps_to_advance) {
    for (unsigned short i = 0; i < steps_to_advance; i++)
        Advance();
}

char Lexer::Peek() {
    if ((current_byte + 1) < to_analyze.length())
        return to_analyze[current_byte + 1];

    return NULL_TERMINATOR;
}

std::string Lexer::InDepthPeek(unsigned short depth) {
    return to_analyze.substr(current_byte + 1, depth);
}

void Lexer::AddLexeme(TokenType Token, std::string Key = "", ValueType Type = NoN, void* Value = NULL) {
    lexemes.push_back(Lexeme(Token, "", Type, Value, line, column));
}

void Lexer::AddVariableLexeme() {
    unsigned int start_byte = current_byte;

    while ((to_analyze[current_byte] >= 'a' && to_analyze[current_byte] <= 'z') || (to_analyze[current_byte] >= 'A' && to_analyze[current_byte] <= 'Z'))
        Advance();
    
    AddLexeme(VARIABLE, to_analyze.substr(start_byte, current_byte - start_byte));
}

void Lexer::AddValueLexeme() {
    unsigned int start_byte = current_byte;
    std::string* string_pointer = NULL;
    long* number_pointer;
    double* float_pointer;

    if (to_analyze[current_byte] == '\"') {
        Advance();

        while (to_analyze[current_byte] != '\"')
            Advance();

        if ((current_byte - start_byte) != 0) {
            string_pointer = (std::string*) malloc(current_byte - start_byte);
            *string_pointer = to_analyze.substr(start_byte, current_byte);
        }

        AddLexeme(VALUE, "", STRING, string_pointer);
        free(string_pointer);
    } else {
        ValueType value_type = INTEGER;
        std::string number;

        Advance();
        
        while ((to_analyze[current_byte] >= '0' && to_analyze[current_byte] <= '9'))
            Advance();

        number.append(to_analyze.substr(start_byte, current_byte - start_byte));

        if (value_type == INTEGER) {
            number_pointer = (long*) malloc(sizeof(long));
            *number_pointer = std::stol(number);

            AddLexeme(VALUE, "", INTEGER, number_pointer);
        } else {
            float_pointer = (double*) malloc(sizeof(double));
            *float_pointer = std::stod(number);

            AddLexeme(VALUE, "", FLOAT, float_pointer);
        }
    }
}

bool Lexer::InDepthAdvanceIfLexeme(std::string to_check_against, TokenType Token) {
    if (to_analyze.substr(current_byte, to_check_against.length()) == to_check_against) {
        InDepthAdvance(to_check_against.length() - 1);
        AddLexeme(Token);
        return true;
    }

    return false;
}