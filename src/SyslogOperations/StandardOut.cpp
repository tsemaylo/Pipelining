/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file StandardOut.h
 *
 * Definition of StandardOut class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#include <iostream>
#include "StandardOut.h"

ByteVector StandardOut::apply(const ByteVector& data) {
    if(!data.empty()){
        std::string str(data.begin(), data.end());
        std::cout << str << std::endl << std::flush;
    }
    return ByteVector();
}

StandardOut::~StandardOut() {
}
