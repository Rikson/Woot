/* 
 * File:   iDistributedFileSystemManager.h
 * Author: abhishek-srinath
 *
 * Created on September 21, 2011, 12:15 PM
 */

#include <string>
#include<iostream>
#include<fstream>
#include <map>
#include "boost/shared_ptr.hpp"
#include "iDistributedFileSystem.h"

#ifndef IDistributedFileSystemManager_H
#define	IDistributedFileSystemManager_H

using namespace std;

/**
 * Distributed File System Manager interface.
 */
class iDistributedFileSystemManager {
public:
    typedef boost::shared_ptr<iDistributedFileSystemManager> iDFSM;

    virtual ~iDistributedFileSystemManager() {
    }

    /**
     * Create a new distributed file system.
     * 
     * @param file_system_name
     * @param barrel_size
     * @param keyType
     * @return 
     */
    virtual iDistributedFileSystem::iDFS createDistributedFileSystem(const string file_system_name, const string dfs_base_path, const size_t barrel_size) = 0;
    
    /**
     * Get a reference to the given distributed file system.
     * 
     * @param file_system_name
     * @return 
     */
    virtual iDistributedFileSystem::iDFS getFileSystem(const string file_system_name) = 0;

};

class DistributedFileSystemManager : public iDistributedFileSystemManager {
private:
    string root_path;
    vector < map<string, string> > metadata;
public:

    DistributedFileSystemManager(const string root_path);

    ~DistributedFileSystemManager() {
    }

    iDistributedFileSystem::iDFS createDistributedFileSystem(const string file_system_name, const string dfs_base_path, const size_t barrel_size);
    
    iDistributedFileSystem::iDFS getFileSystem(const string file_system_name);
};


#endif	/* IDistributedFileSystemManager_H */

