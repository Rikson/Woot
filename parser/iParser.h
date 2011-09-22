/* 
 * File:   iParser.h
 * Author: rikson
 *
 * Created on September 10, 2011, 12:19 PM
 */

/**
 * Document parser.
 * 
 * Parses the given document and return a list of token strings
 */

#include <string>
#include <vector>
#include "iDocument.h"

#ifndef IPARSER_H
#define	IPARSER_H

using namespace std;

class iParser {
public:
    typedef boost::shared_ptr<iParser> iPsr;

    virtual ~iParser() {
    }

    virtual vector<string> parse(iDocument::iDoc document) = 0;
};

class PlainTextParser : public iParser {
public:

    PlainTextParser() {

    }

    vector<string> parse(iDocument::iDoc document);

protected:

    static enum States {
        start,
        wordify,
        filter,
        tokenize,
        end
    } states;

    static enum WordDelimitters {
        space,
        comma,
        period,
        newline
    } wordDelimitters;

    vector<string> parse(const string text);

    string getNextWord(const string &text, int index);
    
    string applyFilters (const string word);
    
    int wordDelimiter (const char c);
};

class WikiParser : public PlainTextParser {
public:

    WikiParser() {

    }

protected:
    vector<string> wordifyText(string text);
};

#endif	/* IPARSER_H */

