/* 
 * File:   iDistributedFileSystem.h
 * Author: rikson
 *
 * Created on September 23, 2011, 4:55 PM
 */

#include <string>
#include <vector>
#include <map>
#include <google/dense_hash_map>
#include "boost/shared_ptr.hpp"

#ifndef IDISTRIBUTEDFILESYSTEM_H
#define	IDISTRIBUTEDFILESYSTEM_H

using namespace std;
using google::dense_hash_map;
using tr1::hash;

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
    virtual string get(const unsigned int key) = 0;

    /**
     * Add the given record to the file system.
     * @param key
     * @param value
     * @return 
     */
    virtual void put(const unsigned int key, string value) = 0;

    /**
     * Flush all the in-memory records to the disk.
     */
    virtual void flush() = 0;
    
    /**
     * Get the size i.e number of records in the file system.
     * @return 
     */
    virtual int size() = 0;
};

struct eq {

    bool operator()(unsigned int i1, unsigned int i2) const {
        return (i1 == i2);
    }
};

class DistributedFileSystem : public iDistributedFileSystem {
private:
    /**
     * Name of the distributed file system
     */
    string name;
    
    /**
     * Sink path of the file system.
     */
    string sink_path;

    /**
     * Base path of the file system.
     */
    string base_path;

    /**
     * Path of the file system meta data file.
     */
    string metadata_path;

    /**
     * Data container path
     */
    string data_container_path;

    /**
     * Maximum size(no. of records) of each barrel.
     */
    size_t max_barrel_size;

    /**
     * Maximum number of barrels that can be stored in a directory.
     */
    int max_barrels_per_directory;

    /**
     * Maximum number of records that can be cached in memory.
     */
    int max_no_of_records_in_memory;

    /**
     * The number of barrels that are *existing* in the file system.
     */
    int no_of_barrels;

    /**
     * The number of records in the file system.
     */
    unsigned int record_count;

    /**
     * Memory image of the file system meta data.
     */
    map< int, map<string, string> > metadataImage;

    /**
     * Memory image of a subset of the total records (as determined by the @param<max_no_of_records_in_memory> of file system data.
     */
    dense_hash_map<unsigned int, string, hash<int>, eq> dataImage;

    /**
     * Memory image that will store all the records that are inserted into the file system using
     * <code>put()</code>. 
     * NOTE: This is a volatile sink, unless <code>flush()</code>'ed the records won't be persisted
     * on the disk.
     */
    dense_hash_map<unsigned int, string, hash<int>, eq> insertionSink;

public:

    DistributedFileSystem(const string name, const string root_path, const size_t barrel_size);

    ~DistributedFileSystem() {
        this->flush();
    }

    /**
     * Returns a record identified by <code>key</code>.
     * If no record exists for the given key, return <code>0</code>
     * @param key
     * @return 
     */
    string get(const unsigned int key);

    /**
     * Inserts the given record.
     * NOTE: This API will only insert the record into the file system memory image, not disk. In order
     * to persist the record on to the disk, call <code>flush()<code>
     * @param key
     * @param value
     */
    void put(const unsigned int key, const string value);

    /**
     * Flushes all the records in the file system memory image on to the disk.
     */
    void flush();
    
    /**
     * Get the size i.e number of records in the file system.
     * @return 
     */
    int size();

private:

    /**
     * Loads the given barrel from the disk into a hash map.
     * @param barrel_no
     * @return 
     */
    dense_hash_map<unsigned int, string, hash<int>, eq> loadBarrel(const string barrel_path);

    /**
     * Loads the given barrel from the disk into a ordered map.
     * @param barrel_no
     * @return 
     */
    map<string, string> loadBarrelToMap(const string barrel_path);

    /**
     * Unloads the given barrel onto the disk.
     * @return 
     */
    string unloadBarrel(const int barrel_no, map<string, string>);

    /**
     * Returns the barrel no. of the barrel which contains the record identified by <code>key</code>
     * @param key
     * @return 
     */
    int getBarrelNo(const unsigned int key);

    /**
     * Returns the barrel path of the barrel which contains the record identified by <code>key</code>
     * @param key
     * @return 
     */
    string getBarrelPath(const unsigned int key);

    /**
     * Updates the meta data file with the given meta data.
     * Also updates the in-memory image of meta data.
     * @param 
     * @return 
     */
    void updateMetadata(map<int, map<string, string> > metadata);

    /**
     * Templatizes the barrel into a string that can be stored onto the disk.
     * @param barrel
     * @return 
     */
    string templatize(map<string, string> barrel);

    /**
     * De-templatizes the barrel into a map that can be loaded into memory
     * @param barrel
     * @return 
     */
    map<string, string> detemplatizeBarrel(const string barrel);

    /**
     * Loads the meta data from the disk on to the file system mete data image.
     */
    void loadMetadata();

    /**
     * Utility method to construct a barrel config map from the given parameters.
     * @param barrel_no
     * @param barrel_path
     * @param record_count
     * @return 
     */
    map<string, string> getBarrelCfgMap(string barrel_no, string barrel_path, string record_count);
};

#endif	/* IDISTRIBUTEDFILESYSTEM_H */

