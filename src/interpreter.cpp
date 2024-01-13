#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "IO/FileHandler.cpp"
#include "Lexer/Lexer.hpp"
#include "Models/Lexeme.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Please enter an input file\nIver [file]" << std::endl;
		return EXIT_FAILURE;
	}

	std::string file_contents = FileHandler::ReadFile(argv[1]);
	std::list<Lexeme> lexemes = Lexer::Lex(file_contents);

	return EXIT_SUCCESS;
}
