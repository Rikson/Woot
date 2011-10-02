/* 
 * File:   iFilter.h
 * Author: rikson
 *
 * Created on September 21, 2011, 9:09 PM
 */

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#ifndef IFILTER_H
#define	IFILTER_H

using namespace std;

/**
 * Filter: determines whether to filter a given input word.
 */
class iFilter {
public:
    typedef boost::shared_ptr<iFilter> iFlr;
    
    virtual ~iFilter () {}
    
    virtual bool filter (string word) = 0;
};

class StopWordFilter : public iFilter {
private:
    map<string, string> stopWords;
public:
    
    StopWordFilter();
    
    bool filter (string word);
};

#endif	/* IFILTER_H */

