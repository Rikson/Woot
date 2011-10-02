#include "../iCountDictionaryManager.h"
#include "../../distributedFileSystem/iDistributedFileSystemManager.h"

#include<iostream>
#include<string>

using namespace std;

iCountDictionary::iCDtr CountDictionaryManager::createDictionary(const string name, const size_t barrel_size) {
    iDistributedFileSystem::iDFS DFS = this->DFSM->createDistributedFileSystem(name, barrel_size);
    iCountDictionary::iCDtr Dtr = iCountDictionary::iCDtr(new CountDictionary(name, DFS));

    dictionaryMap.insert(pair<string, iCountDictionary::iCDtr > (name, Dtr));

    return Dtr;
}

iCountDictionary::iCDtr CountDictionaryManager::getDictionary(const string name) {
    iCountDictionary::iCDtr Dtr;
    if (this->dictionaryMap[name]) {
        return dictionaryMap[name];
    } else {
        iDistributedFileSystem::iDFS DFS = this->DFSM->getDistributedFileSystem(name);
        if (DFS) {
            return iCountDictionary::iCDtr(new CountDictionary(name, DFS));
        } else {
            cout << "CountDictionary not found.";
        }
    }
    
    return Dtr;
}

