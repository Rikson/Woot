/* 
 * File:   iDictionaryManager.h
 * Author: abhishek-srinath
 *
 * Created on September 28, 2011, 11:13 PM
 */
#include <iostream>
#include <string>
#include<fstream>
#include <map>
#include "boost/shared_ptr.hpp"
#include "iDictionary.h"
#include "../distributedFileSystem/iDistributedFileSystemManager.h"

#ifndef IDICTIONARYMANAGER_H
#define	IDICTIONARYMANAGER_H

using namespace std;

class iDictionaryManager {
public:
    typedef boost::shared_ptr<iDictionaryManager> iDtrMgr;

    virtual ~iDictionaryManager() {
    }

    virtual iDictionary::iDtr createDictionary(const string name, const size_t barrel_size) = 0;

    virtual iDictionary::iDtr getDictionary(const string name) = 0;

};

class DictionaryManager : public iDictionaryManager {
private:
    map<string, iDictionary::iDtr> dictionaryMap;
    iDistributedFileSystemManager::iDFSM DFSM;

public:

    DictionaryManager(iDistributedFileSystemManager::iDFSM DFSM) {
        this->DFSM = DFSM;
    }

    virtual ~DictionaryManager() {
    }

    iDictionary::iDtr createDictionary(const string name, const size_t barrel_size);

    iDictionary::iDtr getDictionary(const string name);
};

#endif	/* IDICTIONARYMANAGER_H */

