#include "functions.h"
#include "bigint/bigint.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Need at least 2 filenames!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> training_languages;

    for (int i = 1; i < (argc-1); ++i)
        training_languages.push_back(std::string(argv[i]));
    
	std::string test_language = argv[argc-1];
    std::cout << detect_language(test_language, training_languages) << std::endl;
}
