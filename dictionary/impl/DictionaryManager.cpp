#include "../iDictionaryManager.h"
#include "../../distributedFileSystem/iDistributedFileSystemManager.h"

#include<iostream>
#include<string>

using namespace std;

iDictionary::iDtr DictionaryManager::createDictionary(const string name, const size_t barrel_size) {
    iDistributedFileSystem::iDFS DFS = this->DFSM->createDistributedFileSystem(name, barrel_size);
    iDictionary::iDtr Dtr = iDictionary::iDtr(new Dictionary(name, DFS));

    dictionaryMap.insert(pair<string, iDictionary::iDtr > (name, Dtr));

    return Dtr;
}

iDictionary::iDtr DictionaryManager::getDictionary(const string name) {
    iDictionary::iDtr Dtr;
    if (this->dictionaryMap[name]) {
        return dictionaryMap[name];
    } else {
        iDistributedFileSystem::iDFS DFS = this->DFSM->getDistributedFileSystem(name);
        if (DFS) {
            return iDictionary::iDtr(new Dictionary(name, DFS));
        } else {
            cout << "Dictionary not found.";
        }
    }
    
    return Dtr;
}

