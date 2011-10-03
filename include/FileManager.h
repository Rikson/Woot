/*
 * FileManager.h
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include "DeTemplatizer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
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
    
    string getFileName(string filepath);
    
    bool createFile(string path, string contents);
    
    bool createDirectory(string path);
    
    string readFile(string path);
    
    bool writeFile(string path, string content);
    
    void deleteFile(string path);
    
    bool createDirectoriesRecursively(string path);
    
    string convertIntToString(int number);
    
    vector<string> listFilesInDirectory(string path);
  
    bool findIfExists(string filename);
    
    bool deleteDirectory(string path);
};

#endif /* FILEMANAGER_H_ */