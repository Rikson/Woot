/**
 * Wiki Parser.
 * 
 * Parses wiki documents that are represented in a textual format. These documents can have meta data and links.
 */

#include <sstream>
#include <cmath>
#include <stack>
#include <map>
#include <boost/algorithm/string.hpp>
#include "iParser.h"

using namespace boost;

vector<string> WikiParser::parse(iDocument::iDoc document) {
    return PlainTextParser::parse(document);
}

/**
 * State machine.
 * 
 * State-of-the-art : parses the document in a single pass, identifying all required elements like sections, links categories
 * infobox, tokens etc.
 * 
 * @param text
 * @return 
 */
vector<string> WikiParser::parse(const string text) {
    vector<string> result;

    string word;
    string token;
    string metainfo;
    string highlevelSection;
    string metaboxinfo;
    string metaBoxType;
    bool control;
    stack<char> metainfoStack;
    stack<string> highlevelSectionStack;
    map<string, string> highlevelSections;
    vector<string> links;
    vector<string> categories;
    stack<string> metaboxStack;
    int sectionIndex[4];
    map<int, string > sections;
    map<int, string > sectionIndexMap;
    stack< int > sectionStack;
    int index;
    int state = start;

    sectionIndex[0] = 0;
    sectionIndex[1] = 0;
    sectionIndex[2] = 0;
    sectionIndex[3] = 0;
    for (index = 0; index < text.length();) {
        switch (state) {
            case start:
                word = "";
                token = "";
            case interpret:

                control = true;
                while (control) {
                    if (index >= text.length()) {
                        control = false;
                    }

                    string ch;
                    const char c = text[index];
                    int state = PlainTextParser::wordDelimiter(c);

                    if (!metaboxStack.empty()) {
                        metaboxinfo += text.substr(index, 1);
                    }

                    if (!sectionStack.empty()) {
                        sections[sectionStack.top()] += text.substr(index, 1);
                    }

                    switch (state) {
                        case left_angular_bracket:
                            metainfoStack.push(c);

                            // We are only interested in meta information in the format : <<metainfo>> and not <metainfo>
                            if (!highlevelSectionStack.empty() && metainfoStack.size() == 2) {
                                trim(highlevelSection);
                                highlevelSections.insert((pair<string, string > (highlevelSectionStack.top(), highlevelSection)));
                                //cout << highlevelSectionStack.top() << " : " << highlevelSection << endl;
                                highlevelSectionStack.pop();
                                highlevelSection = "";
                            }

                            index++;
                            break;

                        case right_angular_bracket:
                            if (!metainfoStack.empty()) {
                                ch = metainfoStack.top();
                                metainfoStack.pop();
                                while (!metainfoStack.empty() && this->wordDelimiter(ch[0]) != left_angular_bracket) {
                                    metainfo += ch;
                                    ch = metainfoStack.top();
                                    metainfoStack.pop();
                                }
                            }

                            reverse(metainfo.begin(), metainfo.end());
                            //cout << metainfo << endl; 

                            if (!metainfo.empty()) {
                                highlevelSectionStack.push(metainfo);
                            }
                            metainfo = "";
                            index++;
                            break;

                        case left_curly_brace:
                            if (this->wordDelimiter(text[index + 1]) == left_curly_brace && (iequals("infobox", text.substr(index + 2, 7)) || iequals("taxobox", text.substr(index + 2, 7)))) {
                                metaBoxType = text.substr(index + 2, 7);
                                metaboxStack.push("{");
                                metaboxStack.push("{");
                                metaboxinfo += "{{";
                                index += 2;
                            } else if (!metaboxStack.empty()) {
                                metaboxStack.push("{");
                                index++;
                            } else {
                                word.append(text.substr(index, 1));
                                index++;
                            }
                            break;

                        case right_curly_brace:
                            if (!metaboxStack.empty()) {
                                metaboxStack.pop();
                                index++;
                            } else {
                                word.append(text.substr(index, 1));
                                index++;
                            }
                            break;

                        case equals:
                            if (this->wordDelimiter(text[index + 1]) == equals) {
                                index += 2;
                                int depth = 0;
                                while (this->wordDelimiter(text[index]) == equals) {
                                    index++;
                                    depth++;
                                }
                                string sectionName;
                                while (this->wordDelimiter(text[index]) != equals) {
                                    sectionName.append(1, text[index]);
                                    index++;
                                }
                                while (this->wordDelimiter(text[index]) == equals) {
                                    index++;
                                }
                                sectionIndex[depth]++;
                                if (depth < 3) {
                                    sectionIndex[depth + 1] = 0; // reset sub index to 0
                                }
                                
                                int s_index = 0;
                                s_index += 10000*sectionIndex[0];

                                for (int i = 1; i <= depth; i++) {
                                    s_index += (10000*sectionIndex[i]/(pow(10,i)));
                                }

                                sectionStack.push(s_index);
                                sectionIndexMap.insert(pair<int, string> (s_index, sectionName));
                            } else {
                                word.append(text.substr(index, 1));
                                index++;
                            }
                            break;

                        case space:

                        case comma:

                        case period:

                        case colon:

                        case newline:
                            if (metainfoStack.empty()) {
                                highlevelSection.append(1, c);
                            }
                            index++;
                            control = false;
                            break;

                        case left_parenthesis:

                        case right_parenthesis:
                            index++;
                            break;

                        case left_square_bracket:
                            if (this->wordDelimiter(text[index + 1]) == left_square_bracket) {
                                int j = index + 2;
                                string link;
                                while (this->wordDelimiter(text[j]) != right_square_bracket) {
                                    link.append(text.substr(j, 1));
                                    j++;
                                }
                                links.push_back(link);

                                int k = index + 2;
                                if (iequals("category:", text.substr(k, 9))) {
                                    //cout << text.substr(k + 9, j - (k + 9)) << endl;
                                    categories.push_back(text.substr(k + 9, j - (k + 9)));
                                }

                                index += 2;
                            } else {
                                index++;
                            }
                            break;

                        case right_square_bracket:
                            index++;
                            break;

                        case exclamation:
                            index++;
                            break;

                        case hyphen:
                            // Ignore comments
                            if (this->wordDelimiter(text[index - 1]) == exclamation && this->wordDelimiter(text[index - 2]) == left_angular_bracket) {
                                // We are only interested in meta information in the format : <<metainfo>> and not <metainfo>
                                if (metainfoStack.size() == 1) {
                                    metainfoStack.pop();
                                }
                                while (this->wordDelimiter(text[index]) != right_angular_bracket || this->wordDelimiter(text[index - 1]) != hyphen) {
                                    index++;
                                }
                                break;
                            }

                        default:
                            // We are only interested in meta information in the format : <<metainfo>> and not <metainfo>
                            if (metainfoStack.size() == 1) {
                                metainfoStack.pop();
                            }

                            if (metainfoStack.empty()) {
                                highlevelSection.append(1, c);
                            }

                            if (!metainfoStack.empty()) {
                                metainfoStack.push(c);
                            }

                            word.append(text.substr(index, 1));
                            index++;
                            break;
                    }
                }

                if (word.empty()) continue;

            case transform:
                word = this->transformWord(word);

            case filter:
                if (this->filterWord(word)) continue;

            case tokenize:
                token = this->tokenizeWord(word);
            case end:
                result.push_back(token);
            default:
                break;
        }
    }

    if (!highlevelSection.empty() && !highlevelSectionStack.empty()) {
        trim(highlevelSection);
        highlevelSections.insert((pair<string, string > (highlevelSectionStack.top(), highlevelSection)));
        highlevelSectionStack.pop();
    }

    map<int, string>::iterator itr;
    for (itr = sections.begin(); itr != sections.end(); itr++) {
        cout << (*itr).first << " : " << sectionIndexMap[(*itr).first] << " : " << (*itr).second.substr(0, 200) << endl;
    }

    return result;
}