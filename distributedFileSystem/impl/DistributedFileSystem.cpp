/**
 * Distributed File System.
 */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "../../include/FileManager.h"
#include "../../include/DeTemplatizer.h"
#include "../../include/Templatizer.h"
#include "../iDistributedFileSystem.h"

using namespace std;

const string SINK = "sink";
const string DATA_CONTAINER = "data";

DistributedFileSystem::DistributedFileSystem(const string name, const string base_path, const size_t barrel_size) {
    FileManager fileManager;

    this->name = name;

    this->max_barrel_size = barrel_size;

    this->max_no_of_records_in_memory = barrel_size;

    this->max_barrels_per_directory = 1000;

    this->no_of_barrels = 0;

    this->record_count = 0;
    
    this->sink_path = base_path + "/" + SINK;
    if (!fileManager.findIfExists(this->sink_path) && !fileManager.createDirectory(this->sink_path)) {
        cout << "Failed to create DFS sink." << endl;
        exit(1);
    }
    
    

    // Create file system directory
    this->base_path = this->sink_path + "/" + name;
    if (!fileManager.findIfExists(this->base_path) && !fileManager.createDirectory(this->base_path)) {
        cout << "Failed to create base directory for " << this->name << endl;
        exit(1);
    }

    // Create meta data for the file system.
    this->metadata_path = this->base_path + "/" + name + ".info";
    if (!fileManager.findIfExists(this->metadata_path) && !fileManager.createFile(this->metadata_path, "")) {
        cout << "Failed to create meta data file for " << this->name << endl;
        exit(1);
    }

    // Create file system data directory.
    this->data_container_path = this->base_path + "/" + DATA_CONTAINER;
    if (!fileManager.findIfExists(this->data_container_path) && !fileManager.createDirectory(this->data_container_path)) {
        cout << "Failed to create data directory for " << this->name << endl;
        exit(1);
    }

    this->dataImage.set_empty_key(0);
    this->dataImage.set_deleted_key(-1);

    this->insertionSink.set_empty_key(0);
    this->dataImage.set_deleted_key(-1);
}

/**
 * Returns a record identified by <code>key</code>.
 * If no record exists for the given key, return <code>0</code>
 * @param key
 * @return 
 */
string DistributedFileSystem::get(unsigned int key) {
    FileManager fileManager;

    if (this->dataImage.find(key) == this->dataImage.end()) {
        if (this->insertionSink.find(key) == this->insertionSink.end()) {
            const string barrel_path = this->getBarrelPath(key);
            if (!fileManager.findIfExists(barrel_path)) {
                return 0;
            }

            dense_hash_map<unsigned int, string, hash<int>, eq> barrel = this->loadBarrel(barrel_path);
            if (barrel.find(key) == barrel.end()) {
                return 0;
            }

            // Swap out a barrel to make room for the new one.
            if (this->dataImage.size() == this->max_no_of_records_in_memory) {
                dense_hash_map<unsigned int, string, hash<int>, eq>::iterator itr;

                int i;
                for (itr = this->dataImage.begin(); i < barrel.size(); i++, itr++) {
                    this->dataImage.erase(itr);
                }
            }
            this->dataImage.insert(barrel.begin(), barrel.end());

            return this->dataImage[key];
        }

        return this->insertionSink[key];
    }

    return this->dataImage[key];
}

/**
 * Inserts the given record.
 * NOTE: This API will only insert the record into the file system memory image, not disk. In order
 * to persist the record on to the disk, call <code>flush()<code>
 * @param key
 * @param value
 */
void DistributedFileSystem::put(const unsigned int key, string value) {
    if (this->insertionSink.find(key) == this->insertionSink.end()) {
        this->record_count++;
        //cout << ": \r" << this->record_count << " no of tokens processed in " << this->name;
    }
    this->insertionSink[key] = value;
}

/**
 * Flushes all the records in the file system memory image on to the disk.
 * 
 * TODO: Optimize this. In the below scheme all barrels could possibly be loaded into memory and lead
 * to overloading the memory. Consider implementing efficient barrel swapping algorithms taking into
 * account the number of records that have been staged to be written into disk.
 */
void DistributedFileSystem::flush() {
    map<int, map<string, string> > metadata;
    map<int, map<string, string> > barrels;
    cout << "flush..";
    dense_hash_map<unsigned int, string, hash<int>, eq>::iterator itr;
    for (itr = this->insertionSink.begin(); itr != this->insertionSink.end(); itr++) {
        int barrel_no = this->getBarrelNo((*itr).first);

        if ((barrels[barrel_no]).empty()) {
            barrels[barrel_no] = this->loadBarrelToMap(this->getBarrelPath((*itr).first));
        }

        stringstream key;
        key << (*itr).first;
        barrels[barrel_no][key.str()] = (*itr).second;
    }

    map<int, map<string, string> >::iterator it;
    for (it = barrels.begin(); it != barrels.end(); it++) {
        map<string, string> barrel = (*it).second;
        string barrel_path = this->unloadBarrel((*it).first, barrel);

        stringstream barrel_no, barrel_size;
        barrel_no << (*it).first;
        barrel_size << barrel.size();
        metadata[((*it).first)] = this->getBarrelCfgMap(barrel_no.str(), barrel_path, barrel_size.str());
    }

    this->updateMetadata(metadata);
    this->insertionSink.clear();
}

/**
 * Loads the given barrel from the disk into a hash map.
 * @param barrel_no
 * @return 
 */
dense_hash_map<unsigned int, string, hash<int>, eq> DistributedFileSystem::loadBarrel(const string barrel_path) {
    FileManager fileManager;
    dense_hash_map<unsigned int, string, hash<int>, eq> barrel;
    barrel.set_empty_key(0);

    if (!fileManager.findIfExists(barrel_path)) {
        return barrel;
    }

    const string s_barrel = fileManager.readFile(barrel_path);
    map<string, string> m_barrel = this->detemplatizeBarrel(s_barrel);

    map<string, string>::iterator itr;
    for (itr = m_barrel.begin(); itr != m_barrel.end(); itr++) {
        barrel[atoi(((*itr).first).c_str())] = (*itr).second;
    }

    return barrel;
}

/**
 * Loads the given barrel from the disk into a hash map.
 * @param barrel_no
 * @return 
 */
map<string, string> DistributedFileSystem::loadBarrelToMap(const string barrel_path) {
    FileManager fileManager;
    map<string, string> barrel;

    if (!fileManager.findIfExists(barrel_path)) {
        return barrel;
    }

    const string s_barrel = fileManager.readFile(barrel_path);
    map<string, string> m_barrel = this->detemplatizeBarrel(s_barrel);

    map<string, string>::iterator itr;
    for (itr = m_barrel.begin(); itr != m_barrel.end(); itr++) {
        barrel[((*itr).first).c_str()] = (*itr).second;
    }

    return barrel;
}

/**
 * Unloads the given barrel onto the disk.
 * @return 
 */
string DistributedFileSystem::unloadBarrel(const int barrel_no, map<string, string> barrel) {
    FileManager fileManager;

    const string barrel_path = this->getBarrelPath(atoi((*barrel.begin()).first.c_str()));

    if (!fileManager.findIfExists(barrel_path) && !fileManager.createFile(barrel_path, "")) {
        cout << "Failed to create barrel: " << barrel_no << endl;
        return 0;
    }

    const string contents = this->templatize(barrel);
    fileManager.writeFile(barrel_path, contents);

    return barrel_path;
}

/**
 * Returns the barrel path of the barrel which contains the record identified by <code>key</code>
 * @param key
 * @return 
 */
string DistributedFileSystem::getBarrelPath(const unsigned int key) {
    FileManager fileManager;
    stringstream barrel_no, directory_no;
    int i_barrel_no = key / this->max_barrel_size;
    barrel_no << i_barrel_no;
    directory_no << (i_barrel_no / this->max_barrels_per_directory);

    string directory_path = this->data_container_path + "/" + directory_no.str();
    if (!fileManager.findIfExists(directory_path) && !fileManager.createDirectory(directory_path)) {
        cout << "Failed to create barrel directory for barrel no. : " << barrel_no.str() << endl;
        return 0;
    }

    return directory_path + "/" + barrel_no.str() + ".dat";
}

/**
 * Returns the barrel no. of the barrel which contains the record identified by <code>key</code>
 * @param key
 * @return 
 */
int DistributedFileSystem::getBarrelNo(const unsigned int key) {
    return key / this->max_barrel_size;
}

string DistributedFileSystem::templatize(map<string, string> barrel) {
    vector<string> header;
    header.push_back("Key");
    header.push_back("Value");

    Templatizer *templatizer = new Templatizer(header, "$", "\n");

    return templatizer->templatize(barrel);
}

map<string, string> DistributedFileSystem::detemplatizeBarrel(const string barrel) {
    DeTemplatizer *detemplatizer = new DeTemplatizer("$", "\n");

    return detemplatizer->deTemplatizeStrToMap(barrel);
}

map<string, string> DistributedFileSystem::getBarrelCfgMap(string barrel_no, string barrel_path, string record_count) {
    map<string, string> map;
    map.insert(pair<string, string > ("barrel_no", barrel_no));
    map.insert(pair<string, string > ("barrel_path", barrel_path));
    map.insert(pair<string, string > ("record_count", record_count));

    return map;
}

/**
 * Updates the meta data file with the given meta data.
 * Also updates the in-memory image of meta data.
 * @param 
 * @return 
 */
void DistributedFileSystem::updateMetadata(map<int, map<string, string> > metadata) {
    map<int, map<string, string> >::iterator itr;
    for (itr = metadata.begin(); itr != metadata.end(); itr++) {
        this->metadataImage[(*itr).first] = (*itr).second;
    }

    FileManager fileManager;
    vector<string> header;
    header.push_back("barrel_no");
    header.push_back("barrel_path");
    header.push_back("record_count");

    Templatizer *templatizer = new Templatizer(header, "$", "\n");
    string metainfo = templatizer->templatize(this->metadataImage);

    if (!fileManager.findIfExists(this->metadata_path) && !fileManager.createFile(this->metadata_path, "")) {
        cout << "No meta data file exists. Failed to create a new one." << endl;
        exit(1);
    }
    fileManager.writeFile(this->metadata_path, metainfo);
}

