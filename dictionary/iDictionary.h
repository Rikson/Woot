/* 
 * File:   iDictionary.h
 * Author: rikson
 *
 * Created on September 10, 2011, 12:21 PM
 */

/**
 * Dictionary interface.
 */

#include <string>
#include <boost/shared_ptr.hpp>
#include "../distributedFileSystem/iDistributedFileSystem.h"

#ifndef IDICTIONARY_H
#define	IDICTIONARY_H

using namespace std;

class iDictionary {
public:
    typedef boost::shared_ptr<iDictionary> iDtr;
    
    virtual ~iDictionary () {}
    
    virtual string get (const int key) = 0;
    
    virtual void add (const string value) = 0;
    
    virtual void flush() = 0;
};

class Dictionary : public iDictionary {
private:
    string name;
    iDistributedFileSystem::iDFS DFS;
    
public:
    
    Dictionary(string name, string base_path) {
        this->name = name;
        this->DFS = iDistributedFileSystem::iDFS(new DistributedFileSystem(name, base_path, 100000));
    }
    
    ~Dictionary () {
        this->flush();
    }
    
    string get (const int key);
    
    void add (const string value);
    
    void flush();
};

#endif	/* IDICTIONARY_H */

