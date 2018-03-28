/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file FilterInputDevices.h
 *
 * Implementation of FilterInputDevices class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#include <string>
#include "FilterInputDevices.h"

ByteVector FilterInputDevices::apply(const ByteVector& data) {
    std::string str(data.begin(), data.end());
    if(std::string::npos == str.find("input:")) {
        return ByteVector();
    }
    return ByteVector(data);
}

FilterInputDevices::~FilterInputDevices() {

}

