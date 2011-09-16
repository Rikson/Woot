
/**
 * Plain text parser.
 * 
 * Parses a plain text document assuming the document does not have any annotations, links, meta data etc.
 */

#include <string>
#include <vector>
#include "iDocument.h"
#include "iParser.h"

using namespace std;

class PlainTextParser : public iParser {
    public:
        ~ PlainTextParser () {}
        
        vector<string> parse (iDocument::iDoc document) {
            
        }
};
