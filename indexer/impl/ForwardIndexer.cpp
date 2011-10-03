/*
 * ForwardIndexer.cpp
 *
 *  Created on: Sep 29, 2011
 *      Author: vivek
 */

#include "../iIndexer.h"
#include <iostream>
#include <sstream>

void ForwardIndexer::put(unsigned int documentId, unsigned int termId, set<int> positions) {
    stringstream s_posting;
    s_posting << termId << ":";
    
    set<int>::iterator itr;
    for (itr = positions.begin(); itr != positions.end(); ) {
        s_posting << (*itr);
        
        itr++;
        if (itr != positions.end()) {
            s_posting << ',';
        }
    }
    
    string postings = this->DFS->get(documentId);
    
    if (!postings.empty()) {
        postings += "|";
    }
    
    postings += s_posting.str();
    
    this->DFS->put(documentId, postings);
}

void ForwardIndexer::flush() {
    this->DFS->flush();
}

unsigned int ForwardIndexer::size() {
    return this->DFS->size();
}

