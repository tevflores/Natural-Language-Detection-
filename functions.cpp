#include "functions.h"
#include "bigint/bigint.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

const char B = 26;

bool convert_char(char &ch, unsigned int &i) {

    if (ch >= 'a' && ch <= 'z') i = (unsigned int)(ch - 'a' + 0);
    else if (ch >= 'A' && ch <= 'Z') i = (unsigned int)(ch - 'A' + 0);
    else return false;

    return true;
}



std::vector<unsigned int> get_frequency_vector(const std::string file_name) {
    std::vector <unsigned int> frequency(B*B*B, 0);
    char c;
    unsigned int i1, i2, i3, count, temp;
    count = 0;

    std::ifstream infile(file_name);

    while (infile.get(c)) {
    	if (convert_char(c, temp)) {
    		count++;
    		switch (count) {
    			case 1: i1 = temp; break;
    			case 2: i2 = temp; break;
    			case 3: i3 = temp; frequency[B*B*i1 + B*i2 + i3]++; break;
    			default:
    			i1 = i2;
    			i2 = i3;
    			i3 = temp;
    			frequency[B*B*i1 + B*i2 + i3]++;
    		}


    	}

    }
    if (count < 3) {
    	std::cerr << "Not enough characters in " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }

    return frequency;
}
std::string detect_language(const std::string &test_language, const std::vector<std::string> &language_names) {
    std::string answer;
    std::vector<double> similar;
    std::vector<unsigned int> test = get_frequency_vector(test_language);

    for (size_t i = 0; i < language_names.size(); i++) {
        similar.push_back(compare(test, get_frequency_vector(language_names[i])));
    }

    double max = 0.0;
    for (size_t i = 0; i < similar.size(); i++) {
        if (similar[i] > max) {
            max = similar[i];
            answer = language_names[i];
        }
    }

    return answer;
}

double compare(std::vector<unsigned int> test, std::vector<unsigned int> lang) {

    /*
    calcualte the dot product of "test" and "lang" for the numerator
    calculate the norm of vectors "test" and "lang",
    then multiply them together for the denominator
    */
    bigint numerator;
    bigint denominator;
    bigint deno1;
    bigint deno2;
    for (size_t i = 0; i < test.size(); i++) {
        numerator += test[i] * lang[i];
        deno1 += test[i] * test[i];
        deno2 += lang[i] * lang[i];
    }
    numerator *= numerator;
    denominator = deno1 * deno2;

    //multiply by one million for scaled division
    numerator *= 1000000;

    //divide the scaled numerator by the denominator, then convert bigint to int
    bigint not_result = numerator / denominator;
    int still_not_result = stoi(not_result.to_string(false));

    //perform floating-point division to get a decimal number
    double real_result = still_not_result / 1000000.0;

    //return the square root of that value to get cosine similarity and not cosine^2 similarity
    return sqrt(real_result);
}