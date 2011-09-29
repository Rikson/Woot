/*
 * DeTemplatizer.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#include "../DeTemplatizer.h"
#include <iostream>
#include <string>

using namespace std;
//using namespace boost;

string argumentSeparatorLocalDeTemplatizer;
string recordSeparatorLocalDeTemplatizer;

DeTemplatizer::DeTemplatizer() {
	// TODO Auto-generated constructor stub
}

DeTemplatizer::~DeTemplatizer() {
	// TODO Auto-generated destructor stub
}

DeTemplatizer::DeTemplatizer(string argumentSeparator, string recordSeparator) {
	argumentSeparatorLocalDeTemplatizer = argumentSeparator;
	recordSeparatorLocalDeTemplatizer = recordSeparator;
}

vector< map<string,string> > DeTemplatizer::deTemplatize(string recordListString){
	vector< map<string,string> > recordList;
	map<string,string> recordRowMap;
	std::vector<string> headerRow;
	std::vector<string> individualRecordRow;
	std::vector<string> individualRecord;
	map<string,string>::iterator mapIterator;
	vector< map<string,string> >::iterator recordIterator;

	string headerListString = recordListString.substr(0,recordListString.find_first_of(recordSeparatorLocalDeTemplatizer));
	tokenize(headerListString,headerRow,argumentSeparatorLocalDeTemplatizer);

	recordListString = recordListString.substr(recordListString.find_first_of(recordSeparatorLocalDeTemplatizer)+1,recordListString.size());
	tokenize(recordListString,individualRecordRow,recordSeparatorLocalDeTemplatizer);

	for(int i=0;i<(int)individualRecordRow.size();i++){
		individualRecord.clear();
		tokenize(individualRecordRow[i],individualRecord,argumentSeparatorLocalDeTemplatizer);
		recordRowMap.clear();
		for(int j=0;j<(int)individualRecord.size();j++){
			mapIterator = recordRowMap.begin();
			recordRowMap.insert (mapIterator, pair<string,string>(headerRow[j],individualRecord[j]));
		}
		recordIterator = recordList.begin();
		recordList.insert(recordIterator, recordRowMap);
	}
	return recordList;
}

map<string,string> DeTemplatizer::deTemplatizeStrToMap(string recordListString){
	map<string,string> recordList;
//	map<string,string> recordRowMap;
//	std::vector<string> headerRow;
	std::vector<string> individualRecordRow;
	std::vector<string> individualRecord;
//	map<string,string>::iterator mapIterator;
	vector<string>::iterator recordIterator;

//	string headerListString = recordListString.substr(0,recordListString.find_first_of(recordSeparatorLocalDeTemplatizer));
//	tokenize(headerListString,headerRow,argumentSeparatorLocalDeTemplatizer);

	recordListString = recordListString.substr(recordListString.find_first_of(recordSeparatorLocalDeTemplatizer)+1,recordListString.size());
	tokenize(recordListString,individualRecordRow,recordSeparatorLocalDeTemplatizer);
	recordIterator = individualRecordRow.begin();
//	cout << individualRecordRow.size();
	for(int i=0;i<(int)individualRecordRow.size();i++){
//		recordList.clear();
//		cout << individualRecordRow[i] + "\n";
		individualRecord.clear();
		tokenize(individualRecordRow[i],individualRecord,argumentSeparatorLocalDeTemplatizer);
		//cout << individualRecord[0] + " : " + individualRecord[1] + "\n";;
//		recordRowMap.clear();
//		for(int j=0;j<(int)individualRecord.size();j++){
		recordList.insert(map<string,string>::value_type (individualRecord[0],individualRecord[1]));
//		}
//		recordIterator = recordList.begin();
//		recordList.insert(recordIterator, recordRowMap);
	}
	return recordList;
}


void DeTemplatizer::tokenize(string str, vector<string> &tokens,const string delimiters) {
	size_t lastPos = str.find_first_not_of(delimiters, 0);
	size_t pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)    {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return;
}
