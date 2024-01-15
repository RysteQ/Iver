#ifndef DEF_Lexer
#define DEF_Lexer

#include <iostream>
#include <vector>
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
        /// @return The vector of lexemes found
        static std::vector<Lexeme> Lex(std::string input);

        /// @brief This is a test method, the purpose of this test method is to take a vector and print out the tokens in a human readable form (string) for debugging purposes
        /// @param tokens The vector of tokens to print out in a readable form
        static void PrintTokents(std::vector<Lexeme> tokens);
    
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

        /// @brief Add the new lexeme at the end of the vector
        /// @param Token The token type of the lexeme
        /// @param Key This is used for variables, this will contain the name of the variable
        /// @param Type This is used to indicate the values of the variable (after the assignment)
        /// @param Value A void pointer pointing to the value the lexeme has
        static void AddLexeme(TokenType Token, std::string Key = "", ValueType Type = NoN, void* Value = NULL);

        /// @brief Checks if the variable name is valid and calls the Advance function, when the variable name stops being valid it adds the variable lexeme to the vector alongside its name
        static void AddVariableLexeme();

        /// @brief Advances and adds a value lexeme inside the lexemes vector with they value and type
        static void AddValueLexeme();

        /// @brief A fancier way than typing if InDepthPeek is equal to X value then InDepthAdvance by Y and AddLexeme
        /// @param to_check_against The keyword to check for
        /// @param Token The token type to add if the lexeme was found
        /// @return True if the lexeme was found, false if it wasn't
        static bool InDepthAdvanceIfLexeme(std::string to_check_against, TokenType Token);

        /// @brief A helper function to inform the user of an error that was encountered
        /// @param error_message The user friendly message informing the user of said error
        static void LexerInternalError(std::string error_message);

        inline static std::string to_analyze;
        inline static std::vector<Lexeme> lexemes;
        inline static unsigned int line;
        inline static unsigned int column;
        inline static unsigned int current_byte;
};

#endif