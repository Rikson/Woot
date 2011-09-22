/**
 * Plain text parser
 * 
 * Parses simple plain text documents assuming that it does not contain any annotations, meta data, links etc.
 */

#include <cstring>
#include <string>
#include <vector>
#include <map>

#include "iParser.h"
#include "PlainTextDocument.h"

vector<string> PlainTextParser::parse(iDocument::iDoc document) {
    return this->parse(document->getContents());
}

/**
 * State machine.
 * 
 * Parses the given text and generates a list of tokens.
 * @param text
 * @return 
 */
vector<string> PlainTextParser::parse(const string text) {
    vector<string> result;

    string word;
    string filteredWord;
    string token;
    int index;
    int state = start;

    for (index = 0; index < text.length();) {
        switch (state) {
            case start:
                word = "";
                token = "";
            case wordify:
                word = this->getNextWord(text, index);
                index += word.length() + 1;
                
                if (word.empty()) continue;
            case filter:
                filteredWord = this->applyFilters(word);
                
                if (filteredWord.empty()) continue;
            case tokenize:
                token = word;
            case end:
                result.push_back(word);
            default:
                break;
        }
    }

    return result;
}

/**
 * State Machine to parse and extract the next 'word' from the input stream.
 * 
 * @param text
 * @param index
 * @return 
 */
string PlainTextParser::getNextWord(const string &text, int index) {
    string w = "";

    while (true) {
        if (index >= text.length()) {
            return w;
        }

        const char c = text[index];
        int state = PlainTextParser::wordDelimiter(c);

        switch (state) {
            case space:

            case comma:

            case period:

            case newline:
                return w;
            default:
                w.append(text.substr(index, 1));
                index++;
        }
    }
}

/**
 * Applies a set of filters to the given word.
 * For ex: Converts all words to lower case, removes stop words.
 * 
 * @param word
 * @return 
 */
string PlainTextParser::applyFilters(const string word) {
    return word;
}

/**
 * Returns a <code>WordDelimiter</code> constant for the given character.
 * @param c
 * @return 
 */
int PlainTextParser::wordDelimiter(const char c) {
    static map<char, int> delimiters;

    delimiters[' '] = space;
    delimiters[','] = comma;
    delimiters['.'] = period;
    delimiters['\n'] = newline;

    if (delimiters.find(c) != delimiters.end()) {
        return delimiters[c];
    }

    return -1;
}