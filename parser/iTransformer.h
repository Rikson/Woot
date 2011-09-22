/* 
 * File:   iTransformer.h
 * Author: rikson
 *
 * Created on September 21, 2011, 9:17 PM
 */

#include <string>
#include <boost/shared_ptr.hpp>

#ifndef ITRANSFORMER_H
#define	ITRANSFORMER_H

using namespace std;

/**
 * Transformer: transforms the input word into another form.
 */
class iTransformer {
public:
    typedef boost::shared_ptr<iTransformer> iTfr;
    
    virtual ~iTransformer () {}
    
    virtual string transform (string word) = 0;
};

class LowerCaseTransformer : public iTransformer {
public:
    
    string transform (string word);
};

#endif	/* ITRANSFORMER_H */

