/*
 * DeTemplatizer.h
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#ifndef DETEMPLATIZER_H_
#define DETEMPLATIZER_H_
#include <string>
#include <vector>
#include <map>

using namespace std;
using std::vector;

class DeTemplatizer {
public:
	DeTemplatizer();
	virtual ~DeTemplatizer();
	DeTemplatizer(string argumentSeparator, string recordSeparator);
	vector< map<string,string> > deTemplatize(string);
	map<string,string> deTemplatizeStrToMap(string);
//private:
	void tokenize(string str, vector<string> &tokens,const string delimiters);
};

#endif /* DETEMPLATIZER_H_ */
