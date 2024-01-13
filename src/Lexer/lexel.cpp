#include <list>
#include <string>
#include "../Models/Lexeme.cpp"

#ifndef NULL_TERMINATOR
#define NULL_TERMINATOR '\0'
#endif

class Lexer {
    public:
        static std::list<Lexeme> Lex(std::string input) {
            Reset();
            
            to_analyze = input;

            AnalyzerPhase();
            CleanupPhase();            

            return lexemes;
        }
    
    private:
        static void AnalyzerPhase() {
            while (lexemes.back().Token() != EOP) {
                char current_character = to_analyze[current_byte];
                
                switch (current_character) {
                    // Maths related
                    case '=': AddLexeme(ASSIGNMENT); break;
                    
                    case '+':
                        if (Peek() == '+') {
                            Advance();
                            AddLexeme(INC);
                        } else if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_ADD);
                        } else
                            AddLexeme(ADD);

                        break;

                    case '-': 
                        if (Peek() == '-') {
                            Advance();
                            AddLexeme(DEC);
                        } else if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_SUB);
                        } else
                            AddLexeme(SUB);
                        
                        break;

                    case '*': 
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_MUL);
                        } else
                            AddLexeme(MUL);
                        
                        break;

                    case '/': 
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_DIV);
                        } else
                            AddLexeme(DIV);
                        break;

                    case '%': 
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_MOD);
                        } else
                            AddLexeme(MOD);
                        
                        break;

                    case '^': 
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(SRT_POW);
                        } else
                            AddLexeme(POW);
                        
                        break;
                    
                    case '(': AddLexeme(PARENTHESES_START); break;
                    case ')': AddLexeme(PARENTHESES_END); break;
                    
                    // Logical operations related
                    case '<':
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(SMALLER_OR_EQUAL);
                        } else
                            AddLexeme(SMALLER_THAN);
                        
                        break;

                    case '>':
                        if (Peek() == '=') {
                            Advance();
                            AddLexeme(BIGGER_OR_EQUAL);
                        } else
                            AddLexeme(BIGGER_THAN);
                        
                        break;

                    case 'i':
                        if (InDepthPeek(2) == "s ") {
                            InDepthAdvance(2);
                            AddLexeme(LOGICAL_EQUAL);
                        } else
                            AddVariableLexeme();

                        break;

                    case 'n':
                        if (InDepthPeek(3) == "ot ") {
                            InDepthAdvance(3);
                            AddLexeme(LOGICAL_NOT);
                        } else
                            AddVariableLexeme();

                        break;
                    
                    case 'a':
                        if (InDepthPeek(3) == "nd ") {
                            InDepthAdvance(3);
                            AddLexeme(LOGICAL_AND);
                        } else
                            AddVariableLexeme();

                        break;
                    
                    case 'o':
                        if (InDepthPeek(2) == "r ") {
                            InDepthAdvance(2);
                            AddLexeme(LOGICAL_OR);
                        } else
                            AddVariableLexeme();

                        break;

                    // Miscellaneous related
                    case '\n': AddLexeme(EOL); break;
                    case NULL_TERMINATOR: AddLexeme(EOP); break;

                    // TODO: VARIABLES
                    default:
                        if (current_character >= '0' || current_character <= '9') {

                        } else if (current_character == '\"') {
                        } else
                            AddVariableLexeme();

                        break;
                }

                Advance();
            }
        }

        static void CleanupPhase() {

        }

        static void Reset() {
            lexemes.clear();
            line = 0;
            column = 0;
            current_byte = 0;
        }

        static void Advance() {
            if (current_byte < to_analyze.length())
                current_byte++;

            if (to_analyze[current_byte - 1] == '\n') {
                line++;
                column = 0;
            } else {
                column++;
            }
        }

        static void InDepthAdvance(unsigned short steps_to_advance) {
            for (unsigned short i = 0; i < steps_to_advance; i++)
                Advance();
        }

        static char Peek() {
            if ((current_byte + 1) < to_analyze.length())
                return to_analyze[current_byte + 1];

            return NULL_TERMINATOR;
        }

        static std::string InDepthPeek(unsigned short depth) {
            return to_analyze.substr(current_byte + 1, depth);
        }

        static void AddLexeme(TokenType Token, std::string Key, ValueType Type = NoN, void* Value = NULL) {
            lexemes.push_back(Lexeme(Token, Key, Type, Value, line, column));
        }

        static void AddVariableLexeme() {
            unsigned int start_byte = current_byte;

            while (to_analyze[current_byte] != ' ')
                current_byte++;
            
            lexemes.push_back(Lexeme(VARIABLE, to_analyze.substr(start_byte, current_byte - start_byte), NoN, NULL, line, column));
        }

        static std::string to_analyze;
        static std::list<Lexeme> lexemes;
        static unsigned int line;
        static unsigned int column;
        static unsigned int current_byte;
};