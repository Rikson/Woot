/**
 * Wiki Parser.
 * 
 * Parses wiki documents that are represented in a textual format. These documents can have meta data and links.
 */

#include <sstream>
#include <cmath>
#include <stack>
#include <map>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>
#include "iParser.h"
#include "../include/FileManager.h"

using namespace boost;
using tr1::hash;

/**
 * State machine.
 * 
 * State-of-the-art : parses the document in a single pass, identifying all required elements like sections, links categories
 * infobox, tokens etc.
 * 
 * @param text
 * @return 
 */
dense_hash_map<unsigned int, string, tr1::hash<int>, eq> WikiParser::parse(iDocument::iDoc document) {
    string text = document->getContents();
    string documentName = document->getDocumentName();
    dense_hash_map<unsigned int, string, tr1::hash<int>, eq> result;
    dense_hash_map< unsigned int, set<int>, tr1::hash<int>, eq > postings;
    result.set_empty_key(0);
    result.set_deleted_key(-1);
    postings.set_empty_key(0);
    postings.set_deleted_key(-1);
    
    string word;
    string token;
    unsigned int docID;
    unsigned int termID;
    string metainfo;
    string highlevelSection;
    string metaboxinfo;
    string metaBoxType;
    bool control;
    stack<char> metainfoStack;
    stack<string> highlevelSectionStack;
    map<string, string> highlevelSections;
    set<string> links;
    set<string> categories;
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
    
    docID = this->addToFileDictionary(document->getFilepath());
    
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

                    if (!metaboxStack.empty()) {
                        metaboxinfo += text.substr(index, 1);
                    }

                    if (!sectionStack.empty()) {
                        sections[sectionStack.top()] += text.substr(index, 1);
                    }

                    switch (c) {
                        case '<':
                            metainfoStack.push(c);

                            // We are only interested in meta information in the format : <<metainfo>> and not <metainfo>
                            if (!highlevelSectionStack.empty() && metainfoStack.size() == 2) {
                                trim(highlevelSection);
                                highlevelSections.insert((pair<string, string > (highlevelSectionStack.top(), highlevelSection)));

                                if (boost::iequals(highlevelSectionStack.top(), "Author")) {
                                    unsigned int authorID = this->authorDictionary->add(highlevelSection);
                                    this->authorIndexer->put(authorID ,docID);
                                }

                                highlevelSectionStack.pop();
                                highlevelSection = "";
                            }

                            index++;
                            break;

                        case '>':
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

                            if (!metainfo.empty()) {
                                highlevelSectionStack.push(metainfo);
                            }
                            metainfo = "";
                            index++;
                            break;

                        case '{':
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

                        case '}':
                            if (!metaboxStack.empty()) {
                                metaboxStack.pop();
                                index++;
                            } else {
                                word.append(text.substr(index, 1));
                                index++;
                            }
                            break;

                        case '=':
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
                                s_index += 10000 * sectionIndex[0];

                                for (int i = 1; i <= depth; i++) {
                                    s_index += (10000 * sectionIndex[i] / (int) (pow((double) 10, i)));
                                }

                                sectionStack.push(s_index);
                                sectionIndexMap.insert(pair<int, string > (s_index, sectionName));
                            } else {
                                word.append(text.substr(index, 1));
                                index++;
                            }
                            break;

                        case ' ':

                        case ',':

                        case '.':

                        case ':':

                        case '\n':
                            index++;
                            control = false;
                            break;

                        case '(':

                        case ')':
                            index++;
                            break;

                        case '[':
                            if (this->wordDelimiter(text[index + 1]) == left_square_bracket && text.substr(index + 2, 5) != "Image") {
                                int j = index + 2;
                                string link;
                                while (this->wordDelimiter(text[j]) != right_square_bracket) {
                                    link.append(text.substr(j, 1));
                                    j++;
                                }
                                links.insert(link);

                                int k = index + 2;
                                if (iequals("category:", text.substr(k, 9))) {
                                    string category = text.substr(k + 9, j - (k + 9));
                                    categories.insert(category);
                                    unsigned int categoryID = this->categoryDictionary->add(category);
                                    this->categoryIndexer->put(categoryID, docID);
                                }

                                index += 2;
                            } else {
                                index++;
                            }
                            break;

                        case ']':
                            index++;
                            break;

                        case '!':
                            index++;
                            break;

                        case '-':
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

                this->addToRawCountDictionary(word);
            case transform:
                word = this->transformWord(word);

            case filter:
                if (this->filterWord(word)) continue;

            case tokenize:
                token = this->tokenizeWord(word);
            case end:
                termID = this->addToTermDictionary(token);
                result[termID] = token;
                postings[termID].insert(index - word.length());
                this->addToTermCountDictionary(token);

                this->addToInvertedIndex(termID, docID);
            default:
                break;
        }
    }
    
    dense_hash_map<unsigned int, set<int>, tr1::hash<int>, eq>::iterator itr;
    
    for (itr = postings.begin(); itr != postings.end(); itr++) {
        this->forwardIndexer->put(docID, (*itr).first, (*itr).second);
    }

    if (!highlevelSection.empty() && !highlevelSectionStack.empty()) {
        trim(highlevelSection);
        highlevelSections.insert((pair<string, string > (highlevelSectionStack.top(), highlevelSection)));
        highlevelSectionStack.pop();
    }

    this->addToLinkRepository(documentName.substr(0, documentName.find_last_of(".")), links);
    this->semWikiGenerator->createSemWikiFile(documentName, highlevelSections, metaBoxType, metaboxinfo, links, categories, sections, sectionIndexMap);

    return result;
}

/**
 * TODO : Clean the links before adding to the repository i.e, strip off all irrelevant components marked by for instance ':'
 * @param documentName
 * @param links
 */
void WikiParser::addToLinkRepository(const string documentName, set<string> links) {
    stringstream linkstream;
    tr1::hash<string> hash;
    set<string>::iterator it;
    for (it = links.begin(); it != links.end();) {
        linkstream << (*it);

        it++;
        if (it != links.end()) {
            linkstream << "`";
        }
    }
    
    // Type case from unsigned long int to unsigned int to reduce the tr1::hash range.
    unsigned int key = hash(documentName);
    
    this->linkRepository->put(key, linkstream.str());
}
