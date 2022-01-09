#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

///////////////////////////////////////////////////////////////////
// INCLUDES GO HERE
///////////////////////////////////////////////////////////////////
#include "bigint/bigint.h"


///////////////////////////////////////////////////////////////////
// FUNCTION HEADERS GO HERE
///////////////////////////////////////////////////////////////////

/*
Takes a char ch. If ch is a Roman letter (a-z, A-Z) converts it to its
numeric representation for the base-26 encoding, e.g. a becomes 0.
This result is placed in the unsigned int i.
Returns a boolean indicating whether this conversion was successful:
true if the char was in the range a-z or A-Z; false otherwise.
*/
bool convert_char(char &ch, unsigned int &i);


/*
Takes a string which must be a valid path to a file.
Returns a vector of unsigned ints representing the trigram frequencies
of that file, in canonical base-26 order (aaa to zzz)
*/
std::vector<unsigned int> get_frequency_vector(const std::string file_name);


// uses the above functions to find which language is most similar to the test_language.
/*
Take a string indicating a query (test) filename,
and a vector of strings each of which is a filename.
Return that filename from the vector whose contents are most similar to the query,
in terms of trigram frequency cosine similarity.
*/
std::string detect_language(const std::string &test_language, const std::vector<std::string> &language_names);

/*
Takes two frequency vectors and compares them
using their cosine similarity.
Returns a value between 0 and 1
this represents their similarity.
*/
double compare(std::vector<unsigned int> test, std::vector<unsigned int> lang);

#endif
