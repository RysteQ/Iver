#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "IO/FileHandler.cpp"
#include "Lexer/Lexer.hpp"
#include "Models/Lexeme.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Please enter an input file\nIver [file]" << std::endl;
		return EXIT_FAILURE;
	}

	std::string file_contents = FileHandler::ReadFile(argv[1]);
	std::cout << file_contents;
	std::vector<Lexeme> lexemes = Lexer::Lex(file_contents);

	Lexer::PrintTokents(lexemes);

	return EXIT_SUCCESS;
}
