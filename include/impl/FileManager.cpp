/*
 * FileManager.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: vivek
 */

#include <dirent.h>
#include "../FileManager.h"

FileManager::FileManager() {
	// TODO Auto-generated constructor stub

}

FileManager::~FileManager() {
	// TODO Auto-generated destructor stub
}

bool FileManager::createFile(const string path, const string contents){
	if(contents.size() > 0){
		writeFile(path,contents);
		return true;
	}
	else{
		ofstream write;
		write.open(path.c_str(),ios::app);
		write << "";
		write.close();
		return true;
	}
	return false;
}

bool FileManager::createDirectory(const string path){
    if(mkdir(path.c_str(), 0777) == -1) {
        cerr << "Error while creating the Directory: " + path << endl;
        return true;
    }
    else{
    	return false;
    }
    return false;
}

string FileManager::readFile(const string path){
	std::ifstream t(path.c_str());
	std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	return str;
}

bool FileManager::writeFile(const string path, const string content){
	fstream myfile;
	myfile.open (path.c_str(), ios::out);
	myfile << content;
	myfile.close();
	return true;
}

void FileManager::deleteFile(const string path){
	  if(remove(path.c_str()) != 0)
	    perror("Error deleting file");
	  else
	    puts("File successfully deleted");
}

vector<string> FileManager::listFilesInDirectory(string path) {
    vector<string> directoryEntries;
    DIR* dir = ::opendir(path.c_str());
    if(dir == NULL)
        return directoryEntries;
    struct dirent* entity;
    while((entity=readdir(dir))) {
        string directoryItem(entity->d_name);
        if(directoryItem != "." && directoryItem != "..") {
            directoryEntries.push_back(path + "/" + directoryItem);
        }
    }
    closedir(dir);
    return directoryEntries;
}