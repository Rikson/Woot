
#include "include/constants.h"
#include "parser/iDocumentBuilder.h"
#include "parser/iDocument.h"
#include "parser/DocumentBuilderFactory.h"
#include "distributedFileSystem/iDistributedFileSystemManager.h"
#include "parser/iParser.h"
#include "parser/iTransformer.h"
#include "parser/iFilter.h"
#include "dictionary/iDictionary.h"
#include "dictionary/iCountDictionary.h"
#include "parser/SemWikiGenerator.h"

#include <iostream>
#include <string>
#include <vector>
#include <google/sparse_hash_map>
#include <boost/smart_ptr/shared_ptr.hpp>

using namespace std;
using google::sparse_hash_map;
using tr1::hash;

static string DATA_FILESYSTEM_BASE_PATH;
static string DISTRIBUTED_FILESYSTEM_BASE_PATH_INDEX;
static string DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY;
static int BARREL_SIZE;

/*
 * Falcon
 */
int main(int argc, char** argv) {

    cout << "Reading Configuration File" << endl;

    FileManager manager;
    string cfg_filename = argv[2];
    string configFileContents = manager.readFile(cfg_filename);
    DeTemplatizer deTemplatizer;
    vector<string> configParams;
    deTemplatizer.tokenize(configFileContents, configParams, ",");

    DATA_FILESYSTEM_BASE_PATH = configParams[0];
    DISTRIBUTED_FILESYSTEM_BASE_PATH_INDEX = configParams[1];
    DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY = configParams[2].substr(0, configParams[2].size() - 1);
    BARREL_SIZE = 10; //configParams[3];

    // configFileContents[3,4...] = To be handled

    iDocumentBuilder::iDocBlr plainTextDocumentBuilder = DocumentBuilderFactory::getDocumentBuilder(0);
    iDocumentBuilder::iDocBlr wikiDocumentBuilder = DocumentBuilderFactory::getDocumentBuilder(1);

    // Initializing Transformers
    iTransformer::iTfr transformer = iTransformer::iTfr(new LowerCaseTransformer());
    vector<iTransformer::iTfr> transformers;
    transformers.push_back(transformer);

    // Initializing Filters
    iFilter::iFlr filter = iFilter::iFlr(new StopWordFilter());
    vector<iFilter::iFlr> filters;
    filters.push_back(filter);

    // Initializing Tokenizer
    iTokenizer::iTkz tokenizer = iTokenizer::iTkz(new Tokenizer());

    iDictionary::iDtr fileDictionary = iDictionary::iDtr(new Dictionary("File Dictionary", DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));
    iDictionary::iDtr termDictionary = iDictionary::iDtr(new Dictionary("Term Dictionary", DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));
    iCountDictionary::iCDtr termCountDictionary = iCountDictionary::iCDtr(new CountDictionary("Term Count Dictionary", DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));
    iCountDictionary::iCDtr rawTokenCountDictionary = iCountDictionary::iCDtr(new CountDictionary("Raw Token Count Dictionary", DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));

    SemWikiGenerator::iSWG semWikiGenerator = SemWikiGenerator::iSWG(new SemWikiGenerator (DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));
    
    // Loading and Initializing the Plain and Wiki Text Parser
    PlainTextParser* plainTextParser = new PlainTextParser(transformers, filters, tokenizer, termDictionary, termCountDictionary, rawTokenCountDictionary);
    WikiParser* wikiParser = new WikiParser(transformers, filters, tokenizer, termDictionary, termCountDictionary, rawTokenCountDictionary, semWikiGenerator);

    FileManager fileManager;
    unsigned no_of_files = 0;

    // News data
    vector<string> newsFiles = fileManager.listFilesInDirectory(DATA_FILESYSTEM_BASE_PATH + "/news");
    vector<string>::iterator nIt;
    for (nIt = newsFiles.begin(); nIt < newsFiles.end(); nIt++) {
        no_of_files++;
        fileDictionary->add(*nIt);
        iDocument::iDoc plainTextDocument = plainTextDocumentBuilder->build(*nIt);
        vector<string> result = plainTextParser->parse(plainTextDocument);
    }
    
    // Wiki data
    vector<string> wikiFiles = fileManager.listFilesInDirectory(DATA_FILESYSTEM_BASE_PATH + "/wiki");
    vector<string>::iterator wIt;
    for (wIt = wikiFiles.begin(); wIt < wikiFiles.end(); wIt++) {
        no_of_files++;
        fileDictionary->add(*wIt);
        iDocument::iDoc wikiDocument = wikiDocumentBuilder->build(*wIt);
        vector<string> result = wikiParser->parse(wikiDocument);
    }

    fileDictionary->flush();
    termDictionary->flush();
    termCountDictionary->flush();
    rawTokenCountDictionary->flush();

    cout << endl << termDictionary->size() << " no of tokens added to term dictionary" << endl;
    cout << endl << fileDictionary->size() << " no of files added to file dictionary" << endl;
    cout << endl << "No of files processed : " << no_of_files << endl;


    return 0;
}