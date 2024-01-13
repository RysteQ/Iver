#ifndef DEF_Lexer
#define DEF_Lexer

#include <list>
#include <string>
#include <cstdlib>
#include "../Models/Lexeme.hpp"

#ifndef NULL_TERMINATOR
#define NULL_TERMINATOR '\0'
#endif

class Lexer {
    public:
        /// @brief Analyze the input string for any lexemes, does NOT provide ANY syntax error handling
        /// @param input The string to analyze for any lexemes
        /// @return The list of lexemes found
        static std::list<Lexeme> Lex(std::string input);
    
    private:
        /// @brief Resets the fields to their original values
        static void Reset();

        /// @brief Advances the current byte, it also handles the line and column values
        static void Advance();

        /// @brief Calls the Advance() method multiple times
        /// @param steps_to_advance The times to call the Advance() method
        static void InDepthAdvance(unsigned short steps_to_advance);

        /// @brief Peeks a single byte
        /// @return The character peeked or a NULL_TERMINATOR if the string does not have any more valid characters to peek for
        static char Peek();

        /// @brief Peeks (but does not advances) into the following bytes BUT does not protect if the depth + current byte exceeds the to_analyze string length
        /// @param depth The depth of the peek
        /// @return The peeked string value
        static std::string InDepthPeek(unsigned short depth);

        /// @brief Add the new lexeme at the end of the list
        /// @param Token The token type of the lexeme
        /// @param Key This is used for variables, this will contain the name of the variable
        /// @param Type This is used to indicate the values of the variable (after the assignment)
        /// @param Value A void pointer pointing to the value the lexeme has
        static void AddLexeme(TokenType Token, std::string Key = "", ValueType Type = NoN, void* Value = NULL);

        /// @brief Checks if the variable name is valid and calls the Advance function, when the variable name stops being valid it adds the variable lexeme to the list alongside its name
        static void AddVariableLexeme();

        /// @brief Advances and adds a value lexeme inside the lexemes list with they value and type
        static void AddValueLexeme();

        /// @brief A fancier way than typing if InDepthPeek is equal to X value then InDepthAdvance by Y and AddLexeme
        /// @param to_check_against The keyword to check for
        /// @param Token The token type to add if the lexeme was found
        /// @return True if the lexeme was found, false if it wasn't
        static bool InDepthAdvanceIfLexeme(std::string to_check_against, TokenType Token);

        static std::string to_analyze;
        static std::list<Lexeme> lexemes;
        static unsigned int line;
        static unsigned int column;
        static unsigned int current_byte;
};

#endif