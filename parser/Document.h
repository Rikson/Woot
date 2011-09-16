/* 
 * File:   Document.h
 * Author: rikson
 *
 * Created on September 15, 2011, 11:58 PM
 */

#include <string>
#include "iDocument.h"

#ifndef DOCUMENT_H
#define	DOCUMENT_H

using namespace std;


class Document : public iDocument {
private:
    string filepath;
    string contents;

public:

    Document(string filepath, string contents) {
        this->filepath = filepath;
        this->contents = contents;
    }

    virtual ~Document() {
    }

    string getFilepath() {
        return this->filepath;
    }

    string getContents() {
        return this->contents;
    }
};

#endif	/* DOCUMENT_H */

