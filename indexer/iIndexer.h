/* 
 * File:   iIndexer.h
 * Author: rikson
 *
 * Created on September 10, 2011, 12:23 PM
 */

/**
 * Indexer.
 */

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "../distributedFileSystem/iDistributedFileSystem.h"
#include <google/dense_hash_map>

#ifndef IINDEXER_H
#define	IINDEXER_H

using namespace std;
using google::dense_hash_map;
using tr1::hash;

class iIndexer {
public:

    virtual ~iIndexer() {
    }

    virtual unsigned int size() = 0;
};

class InvertedIndexer : public iIndexer {
private:
    string name;

    iDistributedFileSystem::iDFS DFS;

public:
    typedef boost::shared_ptr<InvertedIndexer> iInvIdx;

    InvertedIndexer(string name, iDistributedFileSystem::iDFS DFS) {
        this->name = name;
        this->DFS = DFS;
    }

    ~InvertedIndexer() {
    };

    void put(unsigned int termId, unsigned int docId);

    void flush();

    unsigned int size();
};

class ForwardIndexer : public iIndexer {
private:
    string name;

    iDistributedFileSystem::iDFS DFS;

public:
    typedef boost::shared_ptr<ForwardIndexer> iFwdIdx;
    
    ForwardIndexer(string name, iDistributedFileSystem::iDFS DFS) {
        this->name = name;
        this->DFS = DFS;
    }

    ~ForwardIndexer() {
    }

    void put(unsigned int documentId, unsigned int termId, set<int> positions);

    void flush();

    unsigned int size();
};

#endif	/* IINDEXER_H */
