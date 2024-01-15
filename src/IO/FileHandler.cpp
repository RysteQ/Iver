#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class FileHandler {
    public:
        static std::string ReadFile(const char* filename) {
            std::ifstream input_file(filename);
            std::stringstream file_contents_stream;
            std::string file_contents;

            file_contents_stream << input_file.rdbuf();
            file_contents = file_contents_stream.str();

            return file_contents;
        }
};