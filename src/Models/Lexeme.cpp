#include "Lexeme.hpp"

Lexeme::Lexeme(TokenType Token, std::string Key, ValueType Type, void* Value, unsigned int Line, unsigned int Column) {
    token = Token;
    key = Key;
    type = Type;
    value = Value;
    line = Line;
    column = Column;
}

TokenType Lexeme::Token() { return token; }
std::string Lexeme::Key() { return key; }
ValueType Lexeme::Type() { return type; }
void* Lexeme::Value() { return value; }
unsigned int Lexeme::Line() { return line; }
unsigned int Lexeme::Column() { return column; }