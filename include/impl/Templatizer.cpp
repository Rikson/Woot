/*
 * Templatizer.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#include "../Templatizer.h"
#include <string>
#include <iostream>
#include <vector>

vector<string> fileHeaders;
string argumentSeparatorLocalTemplatizer;
string recordSeparatorLocalTemplatizer;

Templatizer::Templatizer() {
	// TODO Auto-generated constructor stub
}

Templatizer::~Templatizer() {
	// TODO Auto-generated destructor stub
}

Templatizer::Templatizer(vector<string> listOfArguments, string argumentSeparator, string recordSeparator) {
	fileHeaders = listOfArguments;
	argumentSeparatorLocalTemplatizer = argumentSeparator;
	recordSeparatorLocalTemplatizer = recordSeparator;
}

string Templatizer::templatize(map< int, map<string,string> > recordList){
	string returnString;
	map< int, map<string,string> >::iterator stringIteratorOut;
	vector<string>::iterator stringIteratorIn;
	map<string,string>::iterator mapIterator;
	for(stringIteratorIn = fileHeaders.begin(); stringIteratorIn != fileHeaders.end(); stringIteratorIn++) {
		returnString += *stringIteratorIn;
		returnString += argumentSeparatorLocalTemplatizer;
	}
	returnString = returnString.substr(0,returnString.size()-1);
	returnString += recordSeparatorLocalTemplatizer;
	for(stringIteratorOut=recordList.begin(); stringIteratorOut!=recordList.end(); stringIteratorOut++) {
		map<string,string> localMap = (*stringIteratorOut).second;
		for(int i=0;i<(int)localMap.size();i++){
			returnString += localMap[fileHeaders[i]];
			returnString += argumentSeparatorLocalTemplatizer;
		}
		returnString = returnString.substr(0,returnString.size()-1);
		returnString += recordSeparatorLocalTemplatizer;
	}
	return returnString;
}

string Templatizer::templatize(map<string,string> recordList){
	string returnString;
	vector<string>::iterator stringIteratorIn;
	map<string,string>::iterator mapIterator;
	for(stringIteratorIn = fileHeaders.begin(); stringIteratorIn != fileHeaders.end(); stringIteratorIn++) {
		returnString += *stringIteratorIn;
		returnString += argumentSeparatorLocalTemplatizer;
	}
	returnString = returnString.substr(0,returnString.size()-1);
	returnString += recordSeparatorLocalTemplatizer;
	for(mapIterator=recordList.begin(); mapIterator!=recordList.end(); mapIterator++) {
		string key = mapIterator->first;
		string value = mapIterator->second;
		returnString += key;
		returnString += argumentSeparatorLocalTemplatizer;
		returnString += value;
		returnString += recordSeparatorLocalTemplatizer;
	}
	returnString = returnString.substr(0,returnString.size()-1);
	return returnString;
}
