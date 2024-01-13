#ifndef DEF_Lexeme
#define DEF_Lexeme

#include <string>
#include "../Enums/TokenType.cpp"
#include "../Enums/ValueType.cpp"

class Lexeme {
    public:
        Lexeme(TokenType Token, std::string Key, ValueType Type, void* Value, unsigned int Line, unsigned int Column);

        TokenType Token();
        std::string Key();
        ValueType Type();
        void* Value();
        unsigned int Line();
        unsigned int Column();

    private:
        TokenType token;
        std::string key;
        ValueType type;
        void* value;
        unsigned int line;
        unsigned int column;
};

#endif