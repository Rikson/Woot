/**
 * Document Builder.
 * 
 * Takes in a file resource and spits out a <code>iDocument</code> instance.
 */

#include <string>
#include "iDocument.h"
#include "iDocumentBuilder.h"

using namespace std;

class PlainTextDocumentBuilder : public iDocumentBuilder {
public:

    PlainTextDocumentBuilder() {
    }

    iDocument* build(string filepath) {

    }
};

class WikiDocumentBuilder : public iDocumentBuilder {
public:

    WikiDocumentBuilder() {
    }

    iDocument* build(string filepath) {

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