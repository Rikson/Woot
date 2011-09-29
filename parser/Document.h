/* 
 * File:   Document.h
 * Author: rikson
 *
 * Created on September 15, 2011, 11:58 PM
 */

#include <string>
#include "iDocument.h"
#include "../include/FileManager.h"

#ifndef DOCUMENT_H
#define	DOCUMENT_H

using namespace std;


class Document : public iDocument {
private:
    string name;
    string filepath;
    string contents;

public:

    Document(string filepath, string contents) {
        FileManager fileManager;
        this->name = fileManager.getFileName(filepath);
        this->filepath = filepath;
        this->contents = contents;
    }

    virtual ~Document() {
    }
    
    string getDocumentName() {
        return this->name;
    }

    string getFilepath() {
        return this->filepath;
    }

    string getContents() {
        return this->contents;
    }
};

#endif	/* DOCUMENT_H */

