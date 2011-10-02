/**
 * Count dictionary
 */

#include <sstream>

#include "../iCountDictionary.h"

using tr1::hash;

int CountDictionary::get(const int key) {
    int count = 0;
    const string value = this->DFS->get(key);

    if (!value.empty()) {
        count = atoi(value.c_str());
    }

    return count;
}

int CountDictionary::getKey (const string value) {
    hash<string> hash;
    
    // Type case from unsigned long int to unsigned int to reduce the hash range.
    unsigned int key = hash(value);
    
    return key;
}

void CountDictionary::add(const string value) {
    hash<string> hash;

    // Type case from unsigned long int to unsigned int to reduce the hash range.
    unsigned int key = hash(value);

    int count = this->get(key) + 1;
    stringstream s_count;
    s_count << count;
    this->DFS->put(key, s_count.str());
}

void CountDictionary::flush() {
    this->DFS->flush();
}

int CountDictionary::size() {
    return this->DFS->size();
}