/**
 * Dictionary
 */

#include <string>
#include "../iDictionary.h"

using namespace std;
using tr1::hash;

string Dictionary::get(const int key) {
    return this->DFS->get(key);
}

void Dictionary::add(const string value) {
    hash<string> hash;
    
    // Type case from unsigned long int to unsigned int to reduce the hash range.
    unsigned int key = hash(value);
    
    this->DFS->put(key, value);
}

void Dictionary::flush() {
    this->DFS->flush();
}
