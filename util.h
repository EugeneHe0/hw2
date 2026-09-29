#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> rst;

    typename std::set<T>::iterator it;

    for(it=s1.begin(); it != s1.end(); ++it) if(s2.find(*it)!=s2.end()) rst.insert(*it);
    //loop s1 and compare it with s2's elements
    //then, there should be only mutual eles in rst
    return rst;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> rst;

    typename std::set<T>::iterator it;

    for(it=s1.begin();it!=s1.end();++it) rst.insert(*it);
    //first put everything in s1
    for(it=s2.begin();it!=s2.end();++it) rst.insert(*it);
    //then add ele which only in s2 so that can contain all eles

    return rst;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
