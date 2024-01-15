cmake_minimum_required(VERSION 3.28) 

project(iverLang) 

set(CMAKE_CXX_STANDARD 20) 

# fix this junk one day
add_executable(iver src/interpreter.cpp src/Models/Lexeme.hpp src/Models/Lexeme.cpp src/Lexer/Lexer.hpp src/Lexer/Lexer.cpp src/IO/FileHandler.cpp src/Enums/TokenType.cpp src/Enums/ValueType.cpp) 