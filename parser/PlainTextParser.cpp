/**
 * Plain text parser
 * 
 * Parses simple plain text documents assuming that it does not contain any annotations, meta data, links etc.
 */

#include <cstring>
#include <string>
#include <vector>

#include "iParser.h"
#include "PlainTextDocument.h"

vector<string> PlainTextParser::parse(iDocument::iDoc document) {
    return this->parse(document->getContents());
}

vector<string> PlainTextParser::parse(string text) {
    vector<string> result;

    int state = start;
    switch (state) {
        case start:

        case wordify:
            result = this->wordifyText(text);
        case filter:

        case tokenize:

        case end:

        default:
            break;
    }

    return result;
}

vector<string> PlainTextParser::wordifyText(string text) {
    vector<string> result;
    string WORD_DELIMITERS = " ,.";

    char * buffer = new char [text.length() + 1]; //Copy input text to a buffer.
    strcpy(buffer, text.c_str());

    char * word = strtok(buffer, WORD_DELIMITERS.c_str());
    while (word != NULL) {
        result.push_back(word);
        word = strtok(NULL, WORD_DELIMITERS.c_str());
    }

    delete[] buffer;
    
    return result;
}