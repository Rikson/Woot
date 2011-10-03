
#include "../iIndexer.h"
#include <iostream>
#include <sstream>

using namespace std;

void InvertedIndexer::put(unsigned int termId, unsigned int docId) {
    stringstream s_posting;
    s_posting << docId;
    
    string postings = this->DFS->get(termId);
    
    if (!postings.empty()) {
        postings += "|";
    }
    
    postings += s_posting.str();
    
    this->DFS->put(termId, postings);
}

void InvertedIndexer::flush() {
    this->DFS->flush();
}

unsigned int InvertedIndexer::size() {
    return this->DFS->size();
}