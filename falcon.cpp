
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
#include "dictionary/iDictionaryManager.h"
#include "dictionary/iCountDictionaryManager.h"

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
bool LOGGING_ENABLED;

/*
 * Falcon
 */
int main(int argc, char** argv) {

    FileManager manager;

    if (argc != 3) {
        cout << "Please enter only 2 arguments for executing Falcon" << endl;
        cout << "Usage: falcon [OPTION] <configuration-file-with-path>" << endl;
        cout << "       [OPTION]      [FUNCTION]" << endl;
        cout << "         -i        Indexing Mode" << endl;
        cout << "         -r        Retrieving Mode" << endl;
        exit(0);
    }

    string mode = argv[1];
    string cfg_filename = argv[2];
    string configFileContents = manager.readFile(cfg_filename);
    DeTemplatizer deTemplatizer;
    vector<string> configParams;
    deTemplatizer.tokenize(configFileContents, configParams, ",");

    DATA_FILESYSTEM_BASE_PATH = configParams[0];
    DISTRIBUTED_FILESYSTEM_BASE_PATH_INDEX = configParams[1];
    DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY = configParams[2].substr(0, configParams[2].size());
    BARREL_SIZE = 10; //configParams[3];

    string modeChar = mode.substr(1, mode.size());
    if (modeChar == "help") {
        cout << "Usage: falcon [OPTION] <configuration-file-with-path>" << endl;
        cout << "       [OPTION]      [FUNCTION]\n";
        cout << "         -i        Indexing Mode\n";
        cout << "         -r        Retrieving Mode\n";
        exit(0);
    }
    if (mode.substr(1, mode.size()) != "i" && mode.substr(1, mode.size()) != "r") {
        cout << "falcon: invalid option -- '" << modeChar << "'\n";
        cout << "Try `falcon -help' for more information.\n";
        exit(0);
    }

    cout << "Mode Selected: " << mode << "\n";
    cout << "Data FileSystem Base Path: " << DATA_FILESYSTEM_BASE_PATH << "\n";
    cout << "Base Path Dictionary: " << DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY << "\n";
    cout << "Base Path Index: " << DISTRIBUTED_FILESYSTEM_BASE_PATH_INDEX << "\n";

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

    iDistributedFileSystemManager::iDFSM DFSM = iDistributedFileSystemManager::iDFSM(new DistributedFileSystemManager(DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));
    iDictionaryManager::iDtrMgr DtrMgr = iDictionaryManager::iDtrMgr(new DictionaryManager(DFSM));
    iCountDictionaryManager::iCDtrMgr CDtrMgr = iCountDictionaryManager::iCDtrMgr(new CountDictionaryManager(DFSM));

    iDictionary::iDtr fileDictionary = DtrMgr->createDictionary("File Dictionary", 1000000);
    iDictionary::iDtr termDictionary = DtrMgr->createDictionary("Term Dictionary", 1000000);

    iCountDictionary::iCDtr termCountDictionary = CDtrMgr->createDictionary("Term Count Dictionary", 1000000);
    iCountDictionary::iCDtr rawTokenCountDictionary = CDtrMgr->createDictionary("Raw Token Count Dictionary", 1000000);

    iDictionary::iDtr authorDictionary = DtrMgr->createDictionary("Author Dictionary", 1000000);
    iDictionary::iDtr categoryDictionary = DtrMgr->createDictionary("Category Dictionary", 1000000);

    iDistributedFileSystem::iDFS linkRepository = DFSM->createDistributedFileSystem("Link Repository", 1000000);

    SemWikiGenerator::iSWG semWikiGenerator = SemWikiGenerator::iSWG(new SemWikiGenerator(DISTRIBUTED_FILESYSTEM_BASE_PATH_DICTIONARY));

    // Loading and Initializing the Plain and Wiki Text Parser
    PlainTextParser* plainTextParser = new PlainTextParser(transformers, filters, tokenizer, termDictionary, termCountDictionary, rawTokenCountDictionary);
    WikiParser* wikiParser = new WikiParser(transformers, filters, tokenizer, termDictionary, termCountDictionary, rawTokenCountDictionary, authorDictionary, categoryDictionary, linkRepository, semWikiGenerator);

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
    authorDictionary->flush();
    categoryDictionary->flush();
    linkRepository->flush();

    cout << endl << termDictionary->size() << " no of tokens added to term dictionary" << endl;
    cout << endl << fileDictionary->size() << " no of files added to file dictionary" << endl;
    cout << endl << "No of files processed : " << no_of_files << endl;


    return 0;
}