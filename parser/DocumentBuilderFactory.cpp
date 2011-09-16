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

    enum DocumentTypes {
        plaintxt,
        wiki
    };

    /**
     * Returns an appropriate <code>iDocumentBuilder</code> for the given type document type.
     * @param type
     * @return 
     */
    static iDocumentBuilder* getDocumentBuilder(DocumentTypes type) {
        switch (type) {
            case plaintxt:
                return new PlainTextDocumentBuilder();
            case wiki:
                return new WikiDocumentBuilder();
        }

        return NULL;
    }

};