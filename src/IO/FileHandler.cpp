#include <string>
#include <iostream>
#include <fstream>

class FileHandler {
    public:
        static std::string ReadFile(const char* filename) {
            std::ifstream input_file(filename);
            std::string file_contents;
            
            input_file >> file_contents;

            return file_contents;
        }
};