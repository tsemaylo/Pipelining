/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Reformat.h
 *
 * Implementation of Reformat class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#include "Reformat.h"

#include <string>

static const std::string INPUT = "input:";
static const std::string AS = "as";

ByteVector Reformat::apply(const ByteVector& data) {
    std::string str(data.begin(), data.end());
    size_t posStart = str.find(INPUT);
    if(std::string::npos == posStart) {
        return ByteVector();
    }
    
    posStart += INPUT.length() + 1;
    
    size_t posDelimiter = str.find(AS);
    posDelimiter -= 1;
    
    std::string deviceName = str.substr(posStart, posDelimiter - posStart);
    posDelimiter += AS.length() + 2;
    std::string deviceLocation = str.substr(posDelimiter, str.length() - posDelimiter);
    
    std::string result = deviceName + " | " + deviceLocation ;
    
    return ByteVector(result.begin(), result.end());
}

Reformat::~Reformat() {

}
 