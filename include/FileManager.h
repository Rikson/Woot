/*
 * FileManager.h
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

using namespace std;

class FileManager {

public:
	FileManager();
	virtual ~FileManager();
	bool createFile(const string path, const string contents);
	bool createDirectory(const string path);
	string readFile(const string path);
	bool writeFile(const string path,const string content);
	void deleteFile(const string path);
        vector<string> listFilesInDirectory(string path);

};

#endif /* FILEMANAGER_H_ */
