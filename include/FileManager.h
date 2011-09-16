/* 
 * File:   FileManager.h
 * Author: rikson
 *
 * Created on September 11, 2011, 7:45 PM
 */

/**
 * File manager.
 * 
 * Provides utility functions to manage file resources.
 */


#ifndef FILEMANAGER_H
#define	FILEMANAGER_H

#include <string>

using namespace std;

class FileManager {

    ~FileManager() {

    }

public:

    static string getFile(string filepath);
};

string FileManager::getFile(string filepath) {
    return "file";
}

#endif	/* FILEMANAGER_H */

