/**
 * Stop Word Filter.
 */

#include <string>
#include "../iFilter.h"

using namespace std;

StopWordFilter::StopWordFilter() {
    //initializing stopWords
    this->stopWords["a"] = "a";
    this->stopWords["able"] = "able";
    this->stopWords["about"] = "about";
    this->stopWords["across"] = "across";
    this->stopWords["after"] = "after";
    this->stopWords["all"] = "all";
    this->stopWords["almost"] = "almost";
    this->stopWords["also"] = "also";
    this->stopWords["am"] = "am";
    this->stopWords["among"] = "among";
    this->stopWords["an"] = "an";
    this->stopWords["and"] = "and";
    this->stopWords["any"] = "any";
    this->stopWords["are"] = "are";
    this->stopWords["as"] = "as";
    this->stopWords["at"] = "at";
    this->stopWords["be"] = "be";
    this->stopWords["because"] = "because";
    this->stopWords["been"] = "been";
    this->stopWords["but"] = "but";
    this->stopWords["by"] = "by";
    this->stopWords["can"] = "can";
    this->stopWords["cannot"] = "cannot";
    this->stopWords["could"] = "could";
    this->stopWords["dear"] = "dear";
    this->stopWords["did"] = "did";
    this->stopWords["do"] = "do";
    this->stopWords["does"] = "does";
    this->stopWords["either"] = "either";
    this->stopWords["else"] = "else";
    this->stopWords["ever"] = "ever";
    this->stopWords["every"] = "every";
    this->stopWords["for"] = "for";
    this->stopWords["from"] = "from";
    this->stopWords["get"] = "get";
    this->stopWords["got"] = "got";
    this->stopWords["had"] = "had";
    this->stopWords["has"] = "has";
    this->stopWords["have"] = "have";
    this->stopWords["he"] = "he";
    this->stopWords["her"] = "her";
    this->stopWords["hers"] = "hers";
    this->stopWords["him"] = "him";
    this->stopWords["his"] = "his";
    this->stopWords["how"] = "how";
    this->stopWords["however"] = "however";
    this->stopWords["i"] = "i";
    this->stopWords["if"] = "if";
    this->stopWords["in"] = "in";
    this->stopWords["into"] = "into";
    this->stopWords["is"] = "is";
    this->stopWords["it"] = "it";
    this->stopWords["its"] = "its";
    this->stopWords["just"] = "just";
    this->stopWords["least"] = "least";
    this->stopWords["let"] = "let";
    this->stopWords["like"] = "like";
    this->stopWords["likely"] = "likely";
    this->stopWords["may"] = "may";
    this->stopWords["me"] = "me";
    this->stopWords["might"] = "might";
    this->stopWords["most"] = "most";
    this->stopWords["must"] = "mut";
    this->stopWords["my"] = "my";
    this->stopWords["neither"] = "neither";
    this->stopWords["no"] = "no";
    this->stopWords["nor"] = "nor";
    this->stopWords["not"] = "not";
    this->stopWords["of"] = "of";
    this->stopWords["off"] = "off";
    this->stopWords["often"] = "often";
    this->stopWords["on"] = "on";
    this->stopWords["only"] = "only";
    this->stopWords["or"] = "or";
    this->stopWords["other"] = "other";
    this->stopWords["our"] = "our";
    this->stopWords["own"] = "own";
    this->stopWords["rather"] = "rather";
    this->stopWords["said"] = "said";
    this->stopWords["say"] = "say";
    this->stopWords["says"] = "says";
    this->stopWords["she"] = "she";
    this->stopWords["should"] = "should";
    this->stopWords["since"] = "since";
    this->stopWords["so"] = "so";
    this->stopWords["some"] = "some";
    this->stopWords["than"] = "than";
    this->stopWords["that"] = "that";
    this->stopWords["the"] = "the";
    this->stopWords["their"] = "their";
    this->stopWords["them"] = "them";
    this->stopWords["then"] = "then";
    this->stopWords["there"] = "there";
    this->stopWords["these"] = "these";
    this->stopWords["they"] = "they";
    this->stopWords["this"] = "this";
    this->stopWords["tis"] = "tis";
    this->stopWords["to"] = "to";
    this->stopWords["too"] = "too";
    this->stopWords["twas"] = "twas";
    this->stopWords["us"] = "us";
    this->stopWords["wants"] = "wants";
    this->stopWords["was"] = "was";
    this->stopWords["we"] = "we";
    this->stopWords["were"] = "were";
    this->stopWords["what"] = "what";
    this->stopWords["when"] = "when";
    this->stopWords["where"] = "where";
    this->stopWords["which"] = "which";
    this->stopWords["while"] = "while";
    this->stopWords["who"] = "who";
    this->stopWords["whom"] = "whom";
    this->stopWords["why"] = "why";
    this->stopWords["will"] = "will";
    this->stopWords["with"] = "with";
    this->stopWords["would"] = "would";
    this->stopWords["yet"] = "yet";
    this->stopWords["you"] = "you";
    this->stopWords["your"] = "your";
}

bool StopWordFilter::filter(string word) {
    map<string, string>::iterator it;
    it = stopWords.find(word);
    if (it != stopWords.end()) {
        return true;
    } 
    
    return false;
};
