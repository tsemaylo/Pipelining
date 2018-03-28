/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Reformat.cpp
 *
 * Implementation of Reformat class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#include "Reformat.h"

#include <string>

static const std::string INPUT = "input: ";
static const std::string AS = " as ";

ByteVector Reformat::apply(const ByteVector& data) {
    std::string str(data.begin(), data.end());
    size_t posStart = str.find(INPUT);
    if(std::string::npos == posStart) {
        return ByteVector();
    }
    
    posStart += INPUT.length();
    
    size_t posDelimiter = str.find(AS);
    if(std::string::npos == posDelimiter) {
        return ByteVector();
    }
    
    std::string deviceName = str.substr(posStart, posDelimiter - posStart);
    posDelimiter += AS.length();
    std::string deviceLocation = str.substr(posDelimiter, str.length() - posDelimiter);
    
    // TODO can be inefficient, but so far OK
    std::string result = deviceName + " | " + deviceLocation ;
    
    return ByteVector(result.begin(), result.end());
}

Reformat::~Reformat() {

}
 