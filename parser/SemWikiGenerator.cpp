/*
 * SemWiki Generator
 */

#include "SemWikiGenerator.h"

void SemWikiGenerator::createSemWikiFile(string name, map<string, string> metaData, string metaBoxType, string metaBoxInfo,
        vector<string> links, vector<string> categories, map<int, string> sectionMap, map<int, string> sectionIndexMap) {
    FileManager fileManager;
    const string path = this->base_path + "/" + name;
    fileManager.createFile(path, "");

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
    for (int i = 0; i < links.size(); i++) {
        buffer += links[i];

        if (i != links.size()) {
            buffer += " $ ";
        }
    }
    buffer += "\n\n";

    buffer += "<#CATEGORY>\n";
    for (int i = 0; i < categories.size(); i++) {
        buffer += categories[i];

        if (i != categories.size()) {
            buffer += " $ ";
        }
    }
    buffer += "\n\n";

    fileManager.writeFile(path, buffer);
}
