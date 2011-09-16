/* 
 * File:   WikiDocument.h
 * Author: rikson
 *
 * Created on September 15, 2011, 11:59 PM
 */

/**
 * Wiki document.
 */

#include <string>
#include "Document.h"

#ifndef WIKIDOCUMENT_H
#define	WIKIDOCUMENT_H

using namespace std;

class WikiDocument : public Document {
public:

    WikiDocument(string filepath, string contents) : Document(filepath, contents) {

    }

};

#endif	/* WIKIDOCUMENT_H */

