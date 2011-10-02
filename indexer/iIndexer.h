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
#include <vector>

#ifndef IINDEXER_H
#define	IINDEXER_H

using namespace std;

class iIndexer {
public:

    virtual ~iIndexer() {
    }
    
    void put(int termId, int docId);
    
    void put(int termId, map<int, int>inputMap);
    
    void flush();
};

class InvertedIndexer : public iIndexer {
private:
    map<int, map<int, int> > indexingMap;
    map<int, string> finalIndexingMap;

public:

    ~InvertedIndexer() {
    };
    
    void put(int termId, int docId);
    
    void put(int termId, map<int, int>inputMap);
    
    void flush();
};
#endif	/* IINDEXER_H */

