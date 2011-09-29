/*
 * Templatizer.h
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#ifndef TEMPLATIZER_H_
#define TEMPLATIZER_H_
#include <string>
#include <vector>
#include <map>

using namespace std;
using std::vector;

class Templatizer {
public:
	Templatizer();
	virtual ~Templatizer();
	Templatizer(vector<string> listOfArguments, string argumentSeparator, string recordSeparator);
	string templatize(map< int, map<string,string> > recordList);
	string templatize(map<string,string> recordList);
};

#endif /* TEMPLATIZER_H_ */
