#include "../iDistributedFileSystemManager.h"
#include "../../include/FileManager.h"
#include "../../dictionary/iDictionary.h"
#include <string>
#include <fstream>
#include<iostream>
#include <vector>
using namespace std;
static int count = 0;
const string CODE = "003";
const string DELIMITER = ":";
const string METADATA_FILE = "metadata.info";

/**
 * Constructor.
 * 
 * Created the master file which stores all the meta data about various distributed file systems.
 */
DistributedFileSystemManager :: DistributedFileSystemManager(const string root_path) {
    this->root_path = root_path;
    
    // Create meta data file.
    const string path = root_path + "/" +  METADATA_FILE;
    
    FileManager fileManager;
    bool result = fileManager.createFile (path, "");
}

iDistributedFileSystem::iDFS DistributedFileSystemManager::createDistributedFileSystem(const string file_system_name, const string dfs_base_path, const size_t barrel_size, const string keyType) {
    return iDistributedFileSystem::iDFS(new DistributedFileSystem(file_system_name, this->root_path, barrel_size, keyType));
}

iDistributedFileSystem::iDFS DistributedFileSystemManager::getFileSystem(const string file_system_name) {
    
}



