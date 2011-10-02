/* 
 * File:   SemWikiGenerator.h
 * Author: rikson
 *
 * Created on October 2, 2011, 12:22 AM
 */

#include <string>
#include <set>
#include <map>
#include <boost/shared_ptr.hpp>
#include "../include/FileManager.h"

#ifndef SEMWIKIGENERATOR_H
#define	SEMWIKIGENERATOR_H

using namespace std;

const string SEMWIKI_DIRECTORY = "semwiki";

class SemWikiGenerator {
private:
    string base_path;

public:

    typedef boost::shared_ptr<SemWikiGenerator> iSWG;
    
    SemWikiGenerator(const string root_path) {
        this->base_path = root_path + "/" + SEMWIKI_DIRECTORY;;

        FileManager fileManager;
        if (!fileManager.findIfExists(this->base_path) && !fileManager.createDirectory(this->base_path)) {
            cout << "Failed to create semwiki directory." << endl;
            exit(1);
        }
    }

    void createSemWikiFile(string name, map<string, string> metaData, string metaBoxType, string metaBoxInfo,
            set<string> links, set<string> categories, map<int, string> sectionMap, map<int, string> sectionIndexMap);
};

#endif	/* SEMWIKIGENERATOR_H */

