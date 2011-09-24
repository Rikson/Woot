/* 
 * File:   iDistributedFileSystem.h
 * Author: abhishek-srinath
 *
 * Created on September 23, 2011, 4:55 PM
 */

#include <string>
#include <vector>
#include <map>
#include "boost/shared_ptr.hpp"

#ifndef IDISTRIBUTEDFILESYSTEM_H
#define	IDISTRIBUTEDFILESYSTEM_H

using namespace std;

/**
 * Distributed File System interface.
 */
class iDistributedFileSystem {
public:
    typedef boost::shared_ptr<iDistributedFileSystem> iDFS;

    virtual ~iDistributedFileSystem() {
    }

    /**
     * Get a record identified by the given key.
     * @param key
     * @param file_system_name
     * @return 
     */
    virtual string get(int key) = 0;

    /**
     * Add the given record to the file system.
     * @param key
     * @param value
     * @return 
     */
    virtual void put(int key, string value) = 0;
    
    /**
     * Flush all the in-memory records to the disk.
     */
    virtual void flush () = 0;
};

class DistributedFileSystem : public iDistributedFileSystem {
private:
    string name;
    string base_path;
    size_t barrel_size;
    size_t no_of_barrels;
    string key_type;
    int record_count;
    vector< map<string, string> > metadata;
    
public:

    DistributedFileSystem(const string name, const string root_path, const size_t barrel_size, const string key_type);

    string get(const int key);

    void put(const int key, const string value);
    
    void flush ();

private:
    
    /**
     * Creates the meta data file for the distributed file system.
     * @return 
     */
    string createMetadataFile();
    
    /**
     * Creates a new barrel and returns its path.
     * @return 
     */
    string createBarrel(const string contents);
    
    /**
     * Updates the meta data file with the given meta data.
     * Also updates the in-memory image of meta data.
     * @param 
     * @return 
     */
    void updateMetadata(vector < map<string, string> >);
};

#endif	/* IDISTRIBUTEDFILESYSTEM_H */

