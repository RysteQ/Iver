#include <string>

#include "../Enums/TokenType.cpp"
#include "../Enums/ValueType.cpp"

class Lexeme {
    public:
        Lexeme(TokenType Token, std::string Key, ValueType Type, void* Value, unsigned int Line, unsigned int Column) {
            token = Token;
            key = Key;
            type = Type;
            value = Value;
            line = Line;
            column = Column;
        }
    
        TokenType Token() { return token; }
        std::string Key() { return key; }
        ValueType Type() { return type; }
        void* Value() { return value; }
        unsigned int Line() { return line; }
        unsigned int Column() { return column; }

    private:
        TokenType token;
        std::string key;
        ValueType type;
        void* value;
        unsigned int line;
        unsigned int column;
};