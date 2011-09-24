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
#include "iTransformer.h"
#include "iFilter.h"
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

            case transform:
                word = this->transformWord(word);

            case filter:
                if (this->filterWord(word)) continue;

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
 * Transforms the given word to a desired form.
 * @param word
 * @return 
 */
string PlainTextParser::transformWord(string word) {
    string transformedWord = word;
    for (int i = 0; i < this->transformers.size(); i++) {
        transformedWord = this->transformers[i]->transform(transformedWord);
    }
    
    return transformedWord;
}

/**
 * Applies a set of filters to the given word.
 * For ex: removes stop words.
 * 
 * @param word
 * @return 
 */
bool PlainTextParser::filterWord(const string word) {
    for (int i = 0; i < this->filters.size(); i++) {
        if (this->filters[i]->filter(word)) return true;
    }
    
    return false;
}

/**
 * Returns a <code>WordDelimiter</code> constant for the given character.
 * @param c
 * @return 
 */
int PlainTextParser::wordDelimiter(const char c) {
    static map<char, int> delimiters;

    delimiters['<'] = left_angular_bracket;
    delimiters['>'] = right_angular_bracket;
    delimiters[':'] = colon;
    delimiters['!'] = exclamation;
    delimiters[' '] = space;
    delimiters[','] = comma;
    delimiters['.'] = period;
    delimiters['\t'] = tab;
    delimiters['\n'] = newline;
    delimiters['\r'] = carriage_return;
    

    if (delimiters.find(c) != delimiters.end()) {
        return delimiters[c];
    }

    return -1;
}
