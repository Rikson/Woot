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
#include "tokenizer/iTokenizer.h"

using tr1::hash;

/**
 * State machine.
 * 
 * Parses the given text and generates a list of tokens.
 * @param text
 * @return 
 */
dense_hash_map<unsigned int, string, hash<int>, eq> PlainTextParser::parse(iDocument::iDoc document) {
    string text = document->getContents();
    dense_hash_map<unsigned int, string, hash<int>, eq> result;
    result.set_empty_key(0);
    result.set_deleted_key(-1);

    string word;
    string token;
    unsigned int docID;
    unsigned int termID;
    int index;
    int state = start;
    bool control;

    docID = this->addToFileDictionary(document->getFilepath());

    for (index = 0; index < text.length();) {
        switch (state) {
            case start:
                word = "";
                token = "";
            case interpret:
                control = true;
                while (control) {
                    if (index >= text.length()) {
                        control = false;
                    }

                    const char c = text[index];

                    switch (c) {
                        case ' ':

                        case ',':

                        case '.':

                        case ':':

                        case '\n':
                            index++;
                            control = false;
                            break;

                        case '-':

                        case '?':

                        case '(':

                        case ')':
                            index++;
                            break;

                        default:
                            word.append(text.substr(index, 1));
                            index++;
                            break;
                    }
                }

                if (word.empty()) continue;

                this->addToRawCountDictionary(word);
            case transform:
                word = this->transformWord(word);

            case filter:
                if (this->filterWord(word)) continue;

            case tokenize:
                token = this->tokenizeWord(word);
            case end:
                termID = this->addToTermDictionary(token);
                result[termID] = token;
                this->addToTermCountDictionary(token);

                this->addToInvertedIndex(termID, docID);
            default:
                break;
        }
    }

    return result;
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

string PlainTextParser::tokenizeWord(const string word) {
    return this->tokenizer->tokenize(word);
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
    delimiters['['] = left_square_bracket;
    delimiters[']'] = right_square_bracket;
    delimiters['!'] = exclamation;
    delimiters['-'] = hyphen;
    delimiters['{'] = left_curly_brace;
    delimiters['}'] = right_curly_brace;
    delimiters['='] = equals;
    delimiters['('] = left_parenthesis;
    delimiters[')'] = right_parenthesis;
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

unsigned int PlainTextParser::addToFileDictionary(const string file) {
    return this->fileDictionary->add(file);
}

unsigned int PlainTextParser::addToTermDictionary(const string token) {
    return this->termDictionary->add(token);
}

void PlainTextParser::addToTermCountDictionary(const string token) {
    this->termCountDictionary->add(token);
}

void PlainTextParser::addToRawCountDictionary(const string rawToken) {
    this->rawTokenCountdictionary->add(rawToken);
}

void PlainTextParser::addToInvertedIndex(unsigned int termID, unsigned int docID) {
    this->invertedIndexer->put(termID, docID);
}