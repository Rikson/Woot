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
#include "parser/iParser.h"

using namespace std;

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
    
    iDocumentBuilder::iDocBlr plainTextDocumentBuilder = DocumentBuilderFactory::getDocumentBuilder(1);
    iDocument::iDoc plainTextDocument = plainTextDocumentBuilder->build("./sampledata.txt");
    PlainTextParser* plainTextParser = new PlainTextParser ();
    vector<string> result = plainTextParser->parse(plainTextDocument);
    
    vector<string>::const_iterator itr = result.begin();
    while (itr != result.end()) {
        cout << *itr << endl;
        itr++;
    }

    return 0;
}


