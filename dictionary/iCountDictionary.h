/* 
 * File:   iCountDictionary.h
 * Author: rikson
 *
 * Created on October 1, 2011, 10:32 PM
 */

#include <string>
#include <boost/shared_ptr.hpp>
#include "../distributedFileSystem/iDistributedFileSystem.h"

#ifndef ICOUNTDICTIONARY_H
#define	ICOUNTDICTIONARY_H

using namespace std;

class iCountDictionary {
public:
    typedef boost::shared_ptr<iCountDictionary> iCDtr;

    virtual ~iCountDictionary() {
    }

    virtual int get(const int key) = 0;
    
    virtual int getKey (const string value) = 0;

    virtual void add(const string value) = 0;
    
    virtual int size() = 0;

    virtual void flush() = 0;
};

class CountDictionary : public iCountDictionary {
private:
    string name;
    iDistributedFileSystem::iDFS DFS;

public:

    CountDictionary(string name, string base_path) {
        this->name = name;
        this->DFS = iDistributedFileSystem::iDFS(new DistributedFileSystem(name, base_path, 100000));
    }

    ~CountDictionary() {
        this->flush();
    }

    int get(const int key);
    
    int getKey (const string value);

    void add(const string value);
    
    int size();

    void flush();
};


#endif	/* ICOUNTDICTIONARY_H */

