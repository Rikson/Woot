/**
 * Wiki Parser.
 * 
 * Parses wiki documents that are represented in a textual format. These documents can have meta data and links.
 */

#include <stack>
#include "iParser.h"

vector<string> WikiParser::parse(iDocument::iDoc document) {
    return PlainTextParser::parse(document);
}

vector<string> WikiParser::parse(const string text) {
    vector<string> result;

    string word;
    string token;
    string metainfo;
    bool control;
    stack<string> metainfoStack;
    stack<string> sectionStack;
    int index;
    int state = start;

    for (index = 0; index < text.length();) {
        switch (state) {
            case start:
                word = "";
                token = "";
            case wordify:

                control = true;
                while (control) {
                    if (index >= text.length()) {
                        control = false;
                    }

                    string ch;
                    const char c = text[index];
                    int state = PlainTextParser::wordDelimiter(c);

                    switch (state) {
                        case left_angular_bracket:
                            metainfoStack.push("" + c);
                            index++;
                            break;
                            
                        case right_angular_bracket:
//                            ch = metainfoStack.top();
//                            while (!metainfoStack.empty() && this->wordDelimiter(ch[0]) != left_angular_bracket){
//                                metainfo += metainfoStack.top();
//                                metainfoStack.pop();
//                                ch = metainfoStack.top();
//                            }
//                            
//                            cout<< metainfo<<endl;
                            index++;
                            break;
                            
                        case space:

                        case comma:

                        case period:

                        case newline:
                            index++;
                            control = false;
                            break;
                        default:
                            if (!metainfoStack.empty()) {
                                metainfoStack.push("" + c);
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
                token = word;
            case end:
                result.push_back(word);
            default:
                break;
        }
    }

    return result;
}