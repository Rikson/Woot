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

string FileManager::getFileName(string filepath) {
    int index = filepath.find_last_of("/") + 1;
    return filepath.substr(index, filepath.size() - index);
}

bool FileManager::createFile(string path, string contents) {
    if (!findIfExists(path)) {
        if (contents.size() > 0) {
            writeFile(path, contents);
            return true;
        } else {
            ofstream write;
            write.open(path.c_str(), ios::app);
            write << "";
            write.close();
            return true;
        }
    } else {
        cout << "The file: " + path + " already exists";
    }
    return false;
}

bool FileManager::createDirectory(string path) {
    if (!findIfExists(path)) {
        if (mkdir(path.c_str(), 0755) == 0) {
            return true;
        } else {
            cerr << "Error while creating the Directory: " + path << endl;
            return false;
        }
    } else {
        cout << "The directory: " + path + " already exists";
    }
    return false;
}

bool FileManager::findIfExists(string filename) {
    ifstream ifile(filename.c_str());
    return ifile;
}

string FileManager::readFile(string path) {
    string readString;
    if (findIfExists(path)) {
        std::ifstream if_stream(path.c_str());
        std::string localCopyOfString((std::istreambuf_iterator<char>(if_stream)),
                std::istreambuf_iterator<char>());
        readString = localCopyOfString;
    } else {
        cout << "The file to read: " + path + " does not exist";
    }
    return readString;
}

bool FileManager::writeFile(string path, string content) {
    if (findIfExists(path)) {
        fstream myfile;
        myfile.open(path.c_str(), ios::out);
        myfile << content;
        myfile.close();
        return true;
    } else {
        cout << "The file to write: " + path + " does not exist";
    }
    return false;
}

void FileManager::deleteFile(string path) {
    if (findIfExists(path)) {
        if (remove(path.c_str()) != 0)
            perror("Error deleting file");
        else
            puts("File successfully deleted");
    } else {
        cout << "The file to delete: " + path + " does not exist";
    }
}

//int findCharacterLength(string inputString){
//	cout << inputString.size();
//	return 0;
//}DeTemplatizer

bool FileManager::createDirectoriesRecursively(string path) {
    DeTemplatizer deTemplatize;
    vector<string> tokenVector;
    deTemplatize.tokenize(path, tokenVector, "/");
    string pathToCheck = "";
    for (int i = 0; i < (int) tokenVector.size(); i++) {
        pathToCheck += "/" + tokenVector[i];
        if (!findIfExists(pathToCheck)) {
            bool created = createDirectory(pathToCheck);
            cout << "Created Directory: " + pathToCheck + " successfully? ";
            cout << created;
            cout << "\n";
        } else {
            cout << "The directory: " + pathToCheck + " already exists\n";
        }
        if (i == (int) tokenVector.size() - 1) {
            return true;
        }
    }
    return false;
}

string FileManager::convertIntToString(int number) {
    stringstream stream;
    stream << number;
    return stream.str();
}

vector<string> FileManager::listFilesInDirectory(string path) {
    vector<string> directoryEntries;
    DIR* dir = ::opendir(path.c_str());
    if (dir == NULL)
        return directoryEntries;
    struct dirent* entity;
    while ((entity = readdir(dir))) {
        string directoryItem(entity->d_name);
        if (directoryItem != "." && directoryItem != "..") {
            directoryEntries.push_back(path + "/" + directoryItem);
        }
    }
    closedir(dir);
    return directoryEntries;
}