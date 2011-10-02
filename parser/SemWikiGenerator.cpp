/*
 * SemWiki Generator
 */

#include "SemWikiGenerator.h"

void SemWikiGenerator::createSemWikiFile(string name, map<string, string> metaData, string metaBoxType, string metaBoxInfo,
        set<string> links, set<string> categories, map<int, string> sectionMap, map<int, string> sectionIndexMap) {
    FileManager fileManager;
    const string path = this->base_path + "/" + name;

    string buffer;
    buffer += "<#ARTICAL NAME>\n";
    buffer += name + "\n\n";

    buffer += "<#AUTHOR>\n";
    buffer += metaData["Author"] + "\n\n";

    buffer += "<#TIMESTAMP\n";
    buffer += metaData["Timestamp"] + "\n\n";

    buffer += "<#" + metaBoxType + ">\n";
    buffer += metaBoxInfo + "\n\n";

    buffer += "<#SECTIONS>\n";
    map<int, string>::iterator itr;
    for (itr = sectionMap.begin(); itr != sectionMap.end(); itr++) {
        buffer += "<#" + sectionIndexMap[(*itr).first] + ">\n";
        buffer += (*itr).second.substr(0, 200) + "\n\n";
    }

    buffer += "<#LINKS>\n";
    set<string>::iterator it;
    for (it = links.begin(); it != links.end();) {
        buffer += (*it);

        it++;
        if (it != links.end()) {
            buffer += " $ ";
        }
    }
    buffer += "\n\n";

    buffer += "<#CATEGORY>\n";
    for (it = categories.begin(); it != categories.end();) {
        buffer += (*it);
        ;

        it++;
        if (it != categories.end()) {
            buffer += " $ ";
        }
    }
    buffer += "\n\n";

    if (!fileManager.findIfExists(path) && !fileManager.createFile(path, "")) {
        cout << "Failed to create semwiki file - " << path << endl;
        exit(1);
    }
    fileManager.writeFile(path, buffer);
}
