/* 
 * File:   PlainTextDocument.h
 * Author: rikson
 *
 * Created on September 15, 2011, 11:59 PM
 */

/**
 * Plain text document.
 */

#include <string>
#include "Document.h"

#ifndef PLAINTEXTDOCUMENT_H
#define	PLAINTEXTDOCUMENT_H

using namespace std;

class PlainTextDocument : public Document {
public:

    PlainTextDocument(string filepath, string contents) : Document(filepath, contents) {

    }

};


#endif	/* PLAINTEXTDOCUMENT_H */

