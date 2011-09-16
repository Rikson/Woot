/* 
 * File:   iDocumentBuilder.h
 * Author: rikson
 *
 * Created on September 10, 2011, 5:32 PM
 */

#include <string>
#include <boost/shared_ptr.hpp>
#include "iDocument.h"

using namespace std;

#ifndef IDOCUMENTBUILDER_H
#define	IDOCUMENTBUILDER_H

class iDocumentBuilder {
public:
    typedef boost::shared_ptr<iDocumentBuilder> iDocBlr;

    virtual ~iDocumentBuilder () {}
    
    virtual iDocument::iDoc build (string filepath) = 0;
}; 

#endif	/* IDOCUMENTBUILDER_H */

