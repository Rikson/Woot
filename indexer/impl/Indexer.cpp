
#include "../iIndexer.h"
#include <iostream>
#include <sstream>

using namespace std;

void InvertedIndexer::put(int termId, int docId) {
    map<int, int> tempMap;
    map<int, map<int, int> >::iterator mapItr;
    mapItr = indexingMap.find(termId);

    if (mapItr != indexingMap.end()) {
        tempMap = (*mapItr).second;
    }
    tempMap.insert(pair<int, int>(docId, docId));
    indexingMap[termId] = tempMap;
}

void InvertedIndexer::put(int termId, map<int, int>inputMap) {
    map<int, int> tempMap;
    map<int, map<int, int> >::iterator mapItr;
    mapItr = indexingMap.find(termId);

    if (mapItr != indexingMap.end()) {
        tempMap = (*mapItr).second;
    }
    tempMap.insert(inputMap.begin(), inputMap.end());
    indexingMap[termId] = tempMap;
}

void InvertedIndexer::flush() {
    map<int, int>tempMap;
    map<int, int>::iterator tempMapItr;
    map< int, map<int, int> >::iterator mapItr;
    string contents;

    for (mapItr = indexingMap.begin(); mapItr != indexingMap.end(); mapItr++) {
        stringstream keyContents;
        stringstream valueContents;

        tempMap = (*mapItr).second;
        keyContents << (*mapItr).first;

        for (tempMapItr = tempMap.begin(); tempMapItr != tempMap.end(); tempMapItr++) {
            valueContents << (*tempMapItr).first;
        }
        contents = keyContents.str() + "->" + valueContents.str() + "\n";
        finalIndexingMap.insert(pair<int, string > ((*mapItr).first, contents));
    }

}
