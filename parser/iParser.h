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
#include "../dictionary/iCountDictionary.h"
#include "SemWikiGenerator.h"
#include "../indexer/iIndexer.h"

#ifndef IPARSER_H
#define	IPARSER_H

using namespace std;

struct eqstr
{
  bool operator()(string s1, string s2) const
  {
    return (s1 == s2);
  }
};

class iParser {
public:
    typedef boost::shared_ptr<iParser> iPsr;

    virtual ~iParser() {
    }

    virtual dense_hash_map<unsigned int, string, hash<int>, eq> parse(iDocument::iDoc document) = 0;
};

class PlainTextParser : public iParser {
private:
    unsigned int termIDIndex;

    vector<iTransformer::iTfr> transformers;

    vector<iFilter::iFlr> filters;

    iTokenizer::iTkz tokenizer;

    iDictionary::iDtr fileDictionary;
    
    iDictionary::iDtr termDictionary;

    iCountDictionary::iCDtr termCountDictionary;

    iCountDictionary::iCDtr rawTokenCountdictionary;
    
    InvertedIndexer::iInvIdx invertedIndexer;
public:

    PlainTextParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters, iTokenizer::iTkz tokenizer, iDictionary::iDtr fileDictionary, iDictionary::iDtr termDictionary, iCountDictionary::iCDtr termCountDictionary, iCountDictionary::iCDtr rawTokenCountdictionary, InvertedIndexer::iInvIdx invertedIndexer) {
        termIDIndex = 0;

        this->transformers = transformers;
        this->filters = filters;
        this->tokenizer = tokenizer;

        this->fileDictionary = fileDictionary;
        this->termDictionary = termDictionary;
        this->termCountDictionary = termCountDictionary;
        this->rawTokenCountdictionary = rawTokenCountdictionary;
        
        this->invertedIndexer = invertedIndexer;
    }

    dense_hash_map<unsigned int, string, hash<int>, eq> parse(iDocument::iDoc document);

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

    unsigned int addToFileDictionary(const string file);
    
    unsigned int addToTermDictionary(const string token);

    void addToTermCountDictionary(const string token);

    void addToRawCountDictionary(const string rawToken);
    
    void addToInvertedIndex (unsigned int termID, unsigned int docID);
};

class WikiParser : public PlainTextParser {
private:

    iDictionary::iDtr authorDictionary;
    
    iDictionary::iDtr categoryDictionary;
    
    iDistributedFileSystem::iDFS linkRepository;
    
    SemWikiGenerator::iSWG semWikiGenerator;
    
    InvertedIndexer::iInvIdx authorIndexer;
    
    InvertedIndexer::iInvIdx categoryIndexer;
    
    ForwardIndexer::iFwdIdx forwardIndexer;
public:

    WikiParser(vector<iTransformer::iTfr> transformers, vector<iFilter::iFlr> filters, iTokenizer::iTkz tokenizer, iDictionary::iDtr fileDictionary, iDictionary::iDtr termDictionary, iCountDictionary::iCDtr termCountDictionary, iCountDictionary::iCDtr rawTokenCountdictionary, iDictionary::iDtr authorDictionary, iDictionary::iDtr categoryDictionary, iDistributedFileSystem::iDFS linkRepository, SemWikiGenerator::iSWG semWikiGenerator, InvertedIndexer::iInvIdx invertedIndexer, InvertedIndexer::iInvIdx authorIndexer, InvertedIndexer::iInvIdx categoryIndexer, ForwardIndexer::iFwdIdx forwardIndexer) : PlainTextParser(transformers, filters, tokenizer, fileDictionary, termDictionary, termCountDictionary, rawTokenCountdictionary, invertedIndexer) {
        this->authorDictionary = authorDictionary;
        this->categoryDictionary = categoryDictionary;
        this->linkRepository = linkRepository;
        this->semWikiGenerator = semWikiGenerator;
        this->authorIndexer = authorIndexer;
        this->categoryIndexer = categoryIndexer;
        this->forwardIndexer = forwardIndexer;
    }

    dense_hash_map<unsigned int, string, hash<int>, eq> parse(iDocument::iDoc document);
    
private:
    
    void addToLinkRepository (const string documentName, set<string> links);
};

#endif	/* IPARSER_H */

