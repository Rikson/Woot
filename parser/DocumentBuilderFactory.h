/* 
 * File:   DocumentBuilderFactory.h
 * Author: rikson
 *
 * Created on September 16, 2011, 3:14 AM
 */

/**
 * Document Builder.
 * 
 * Takes in a file resource and spits out a <code>iDocument</code> instance.
 */

#include <string>
#include "iDocument.h"
#include "iDocumentBuilder.h"
#include "../include/FileManager.h"
#include "PlainTextDocument.h"
#include "WikiDocument.h"


using namespace std;

class PlainTextDocumentBuilder : public iDocumentBuilder {
public:

    PlainTextDocumentBuilder() {
    }

    iDocument::iDoc build(string filepath) {
        string contents = FileManager::getFile (filepath);
        
        return iDocument::iDoc(new PlainTextDocument (filepath, contents));
    }
};

class WikiDocumentBuilder : public iDocumentBuilder {
public:

    WikiDocumentBuilder() {
    }

    iDocument::iDoc build(string filepath) {
        string contents = FileManager::getFile (filepath);
        
        return iDocument::iDoc(new WikiDocument (filepath, contents));
    }
};

class DocumentBuilderFactory {

    ~DocumentBuilderFactory() {

    }

private:

    DocumentBuilderFactory() {

    }

public:

    static enum DocumentTypes {
        plaintxt,
        wiki
    } types;

    /**
     * Returns an appropriate <code>iDocumentBuilder</code> for the given type document type.
     * @param type
     * @return 
     */
    static iDocumentBuilder::iDocBlr getDocumentBuilder(int type) {
        cout << "Getting document builder ..." << endl;
        switch (type) {
            case plaintxt:
                return iDocumentBuilder::iDocBlr(new PlainTextDocumentBuilder());
            case wiki:
                return iDocumentBuilder::iDocBlr(new WikiDocumentBuilder());
        }
    }

};

#ifndef DOCUMENTBUILDERFACTORY_H
#define	DOCUMENTBUILDERFACTORY_H



#endif	/* DOCUMENTBUILDERFACTORY_H */

