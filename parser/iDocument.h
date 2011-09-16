/* 
 * File:   iDocument.h
 * Author: rikson
 *
 * Created on September 10, 2011, 12:48 PM
 */

/**
 * Document interface.
 * 
 * Represents any kind of document that can be fed into the <code>iParser</code>
 */

#include <string>
#include <boost/shared_ptr.hpp>

#ifndef IDOCUMENT_H
#define	IDOCUMENT_H

using namespace std;

class iDocument {
public:
    typedef boost::shared_ptr<iDocument> iDoc;
    
    virtual ~iDocument () {}
    
    virtual string getFilepath () = 0;
    
    virtual string getContents () = 0;
};


#endif	/* IDOCUMENT_H */

