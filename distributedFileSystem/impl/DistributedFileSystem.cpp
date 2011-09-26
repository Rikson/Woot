/**
 * Distributed File System.
 */

#include <string>
#include <sstream>
#include <fstream>
#include<iostream>
#include <map>
#include <vector>
#include "../../include/FileManager.h"
#include "../iDistributedFileSystem.h"

using namespace std;

const string SINK = "sink";
const string DATA_CONTAINER = "data";

DistributedFileSystem::DistributedFileSystem(const string name, const string root_path, const size_t barrel_size, const string key_type) {
    FileManager fileManager;
    const string sink_path = root_path + "/" + SINK;
    fileManager.createDirectory(sink_path);
    
    this->base_path = sink_path + "/" + name;
    
    this->name = name;
    
    this->barrel_size = barrel_size;
    
    this->no_of_barrels = 0;
    
    this->key_type = key_type;
    
    // Create file system directory
    const string directory_path = this->base_path;
    fileManager.createDirectory(directory_path);
    const string data_container_path = directory_path + "/" + DATA_CONTAINER;
    fileManager.createDirectory(data_container_path);
    
    // Create meta data for the file system.
    const string metadata_path = directory_path + "/" + name + ".info";
    fileManager.createFile(metadata_path, "");

    // Create new barrel.
    const string barrel_path = this->createBarrel("");
    
    // Populate meta data.
    map<string, string> metarecord;
    metarecord.insert(pair<string, string>("barrel_no", "1"));
    metarecord.insert(pair<string, string>("record_count", "0"));
    metarecord.insert(pair<string, string>("barrel_path", barrel_path));
    vector < map<string, string> > metadata;
    metadata.push_back(metarecord);
    
    // Update the meta data file.
    this->updateMetadata(metadata);
}

string DistributedFileSystem::get(int key) {

}

void DistributedFileSystem::put(int key, string value) {

}

void DistributedFileSystem::flush() {
    
}

string DistributedFileSystem::createBarrel(const string contents) {
    FileManager fileManager;
    stringstream barrel_no;
    barrel_no << (this->no_of_barrels + 1);
    const string barrel_path = this->base_path + "/" + DATA_CONTAINER + "/" + barrel_no.str() + ".dat";
    
    fileManager.createFile(barrel_path, "");
    
    return barrel_path;
}

void DistributedFileSystem::updateMetadata(vector<map<string,string> >) {
    FileManager fileManager;
    fileManager.writeFile(this->base_path + "/" + this->name + ".info", "test");
}
