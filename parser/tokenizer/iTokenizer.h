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

#ifndef ITOKENIZER_H
#define	ITOKENIZER_H

using namespace std;

class iTokenizer {
public:
    virtual ~iTokenizer() {}
    
    virtual iToken tokenize (string text) = 0;
};


#endif	/* ITOKENIZER_H */

