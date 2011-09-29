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
#include "tokenizer/iTokenizer.h"
#include "../dictionary/iDictionary.h"

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
    unsigned int termIDIndex;
    
    vector<iTransformer::iTfr> transformers;

    vector<iFilter::iFlr> filters;

    iTokenizer::iTkz tokenizer;
    
    iDictionary::iDtr dictionary;
public:

    PlainTextParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters, iTokenizer::iTkz tokenizer, iDictionary::iDtr dictionary) {
        termIDIndex = 0;
        
        this->transformers = transformers;
        this->filters = filters;
        this->tokenizer = tokenizer;
        
        this->dictionary = dictionary;
    }

    vector<string> parse(iDocument::iDoc document);

protected:

    static enum States {
        start,
        interpret,
        transform,
        filter,
        tokenize,
        end
    } states;

    static enum Delimitters {
        left_angular_bracket,
        right_angular_bracket,
        colon,
        left_square_bracket,
        right_square_bracket,
        exclamation,
        hyphen,
        left_curly_brace,
        right_curly_brace,
        equals,
        left_parenthesis,
        right_parenthesis,
        space,
        comma,
        period,
        tab,
        newline,
        carriage_return
    } delimitters;

    virtual string transformWord(string word);

    virtual bool filterWord(const string word);

    virtual string tokenizeWord(const string word);

    int wordDelimiter(const char c);

    vector<string> wordifyText(string text);
};

class WikiParser : public PlainTextParser {
public:

    WikiParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters, iTokenizer::iTkz tokenizer, iDictionary::iDtr dictionary) : PlainTextParser(transformers, filters, tokenizer, dictionary) {

    }

    vector<string> parse(iDocument::iDoc document);

protected:
    
    void createSemWikiFile (string basePath, string name, map<string, string> metaData, string metaBoxType, string metaBoxInfo, 
            vector<string> links, vector<string> categories, map<int, string> sectionMap, map<int, string> sectionIndexMap);
};

#endif	/* IPARSER_H */

