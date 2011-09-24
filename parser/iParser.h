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
#include "iTransformer.h"
#include "iFilter.h"

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
private:
    vector<iTransformer::iTfr> transformers;

    vector<iFilter::iFlr> filters;
public:

    PlainTextParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters) {
        this->transformers = transformers;
        this->filters = filters;
    }

    vector<string> parse(iDocument::iDoc document);

protected:

    static enum States {
        start,
        wordify,
        transform,
        filter,
        tokenize,
        end
    } states;

    static enum Delimitters {
        left_angular_bracket,
        right_angular_bracket,
        colon,
        exclamation,
        space,
        comma,
        period,
        tab,
        newline,
        carriage_return
    } delimitters;

    virtual vector<string> parse(const string text);

    virtual string getNextWord(const string &text, int index);

    virtual string transformWord(string word);

    virtual bool filterWord(const string word);

    int wordDelimiter(const char c);
    
    vector<string> wordifyText(string text);
};

class WikiParser : public PlainTextParser {
public:

    WikiParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters) : PlainTextParser(transformers, filters) {

    }
    
    vector<string> parse(iDocument::iDoc document);

protected:
    vector<string> parse(const string text);
};

#endif	/* IPARSER_H */

