/* 
 * File:   iDocumentBuilder.h
 * Author: rikson
 *
 * Created on September 10, 2011, 5:32 PM
 */

#include <string>

using namespace std;

#ifndef IDOCUMENTBUILDER_H
#define	IDOCUMENTBUILDER_H

class iDocumentBuilder {
public:
    virtual ~iDocumentBuilder () {}
    
    virtual iDocument* build (string filepath) = 0;
}; 

#endif	/* IDOCUMENTBUILDER_H */

