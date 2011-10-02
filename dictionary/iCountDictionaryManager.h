/* 
 * File:   iCountDictionaryManager.h
 * Author: rikson
 *
 * Created on September 28, 2011, 11:13 PM
 */
#include <iostream>
#include <string>
#include<fstream>
#include <map>
#include "boost/shared_ptr.hpp"
#include "iCountDictionary.h"
#include "../distributedFileSystem/iDistributedFileSystemManager.h"

#ifndef ICOUNTDICTIONARYMANAGER_H
#define	ICOUNTDICTIONARYMANAGER_H

using namespace std;

class iCountDictionaryManager {
public:
    typedef boost::shared_ptr<iCountDictionaryManager> iCDtrMgr;

    virtual ~iCountDictionaryManager() {
    }

    virtual iCountDictionary::iCDtr createDictionary(const string name, const size_t barrel_size) = 0;

    virtual iCountDictionary::iCDtr getDictionary(const string name) = 0;

};

class CountDictionaryManager : public iCountDictionaryManager {
private:
    map<string, iCountDictionary::iCDtr> dictionaryMap;
    iDistributedFileSystemManager::iDFSM DFSM;

public:

    CountDictionaryManager(iDistributedFileSystemManager::iDFSM DFSM) {
        this->DFSM = DFSM;
    }

    virtual ~CountDictionaryManager() {
    }

    iCountDictionary::iCDtr createDictionary(const string name, const size_t barrel_size);

    iCountDictionary::iCDtr getDictionary(const string name);
};

#endif	/* ICOUNTDICTIONARYMANAGER_H */

