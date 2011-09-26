/* 
 * File:   iTokenizer.h
 * Author: rikson
 *
 * Created on September 10, 2011, 12:21 PM
 */

/**
 * Tokenizer
 * 
 * Takes an input text, applies a series of transformations and returns a token.
 * Ideally the input text should be a single canonical (meaningful) word. For ex: falcon, Las Vegas
 */

#include <vector>
#include <boost/shared_ptr.hpp>

#ifndef ITOKENIZER_H
#define	ITOKENIZER_H

using namespace std;

class iTokenizer {
public:
    typedef boost::shared_ptr<iTokenizer> iTkz;

    virtual ~iTokenizer() {
    }

    virtual string tokenize(string word) = 0;
};

class Tokenizer : public iTokenizer {
public:

    Tokenizer() {

    }

    string tokenize(string word);

protected:

    int getLastCharacterOffsetForStemming(string inputString);
};


#endif	/* ITOKENIZER_H */

