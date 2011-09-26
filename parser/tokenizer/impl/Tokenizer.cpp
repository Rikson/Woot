/**
 * Tokenizer
 */

#include <string>
#include "../iTokenizer.h"
#include "../../../include/stemmer.h"

using namespace std;

string Tokenizer::tokenize(string word) {
	char *inputStringChar = (char*)word.c_str();
	int stemmedIndex = stem(inputStringChar,0,getLastCharacterOffsetForStemming(word));
	return word.substr(0,stemmedIndex+1);
}

int Tokenizer::getLastCharacterOffsetForStemming(string inputString){
	return inputString.size()-1;
};
