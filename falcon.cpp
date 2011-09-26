/* 
 * File:   main.cpp
 * Author: rikson
 *
 * Created on September 9, 2011, 10:54 PM
 */

#include <iostream>
#include <string>
#include <vector>

#include "include/constants.h"
#include "parser/iDocumentBuilder.h"
#include "parser/iDocument.h"
#include "parser/DocumentBuilderFactory.h"
#include "distributedFileSystem/iDistributedFileSystemManager.h"
#include "parser/iParser.h"
#include "parser/iTransformer.h"
#include "parser/iFilter.h"
#include "parser/tokenizer/iTokenizer.h"

using namespace std;

const string DISTRIBUTED_FILESYSTEM_BASE_PATH = "/home/rikson/sandbox/Woot/distributedFileSystem";

/*
 * 
 */
int main(int argc, char** argv) {
    string code;

    cout << "Welcome to Falcon 1.0!" << endl;
//    cout << endl << "Please enter the CODE: ";
//
//    cin >> code;
//
//    if (code == Constant::CODE) {
//        cout << endl << "CODE match.";
//        cout << endl << "Please be patient with us while we are still Wooting!" << endl;
//    } else {
//        cout << "CODE mismatch!" << endl;
//    }

    //iDocumentBuilder::iDocBlr plainTextDocumentBuilder = DocumentBuilderFactory::getDocumentBuilder(1);
    iDocumentBuilder::iDocBlr wikiDocumentBuilder = DocumentBuilderFactory::getDocumentBuilder(1);

    iTransformer::iTfr transformer = iTransformer::iTfr(new LowerCaseTransformer());
    vector<iTransformer::iTfr> transformers;
    transformers.push_back(transformer);

    iFilter::iFlr filter = iFilter::iFlr(new StopWordFilter());
    vector<iFilter::iFlr> filters;
    filters.push_back(filter);
    
    iTokenizer::iTkz tokenizer = iTokenizer::iTkz(new Tokenizer());

    //PlainTextParser* plainTextParser = new PlainTextParser(transformers, filters, tokenizer);
    WikiParser* wikiParser = new WikiParser(transformers, filters, tokenizer);

    for (int i = 0; i < 1; i++) {
        //iDocument::iDoc plainTextDocument = plainTextDocumentBuilder->build("/home/rikson/data/news/FT911-1");
        //vector<string> result = plainTextParser->parse(plainTextDocument);
        iDocument::iDoc wikiDocument = wikiDocumentBuilder->build("/home/rikson/data/wiki/Buffalo,_New_York.txt");
        vector<string> result = wikiParser->parse(wikiDocument);
        vector<string>::const_iterator itr = result.begin();
        while (itr != result.end()) {
            cout << *itr << endl;
            itr++;
        }

    }

    //iDistributedFileSystemManager::iDFSM DFM = iDistributedFileSystemManager::iDFSM(new DistributedFileSystemManager(DISTRIBUTED_FILESYSTEM_BASE_PATH));
    //iDistributedFileSystem::iDFS termCountDictionary = DFM->createDistributedFileSystem("Term_Count_dictionary", DISTRIBUTED_FILESYSTEM_BASE_PATH, 10000, "forward");

    return 0;
}


