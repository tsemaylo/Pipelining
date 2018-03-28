/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file FilterInputDevices.h
 *
 * Definition of FilterInputDevices class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#ifndef FILTERINPUTDEVICES_H
#define FILTERINPUTDEVICES_H

#include "Operation.h"

/**
 * Operation to filter out everything that doesnt contsain "input:" substring.
 */
class FilterInputDevices : public Operation{
public:
    ByteVector apply(const ByteVector& data) final;
    virtual ~FilterInputDevices();

};

#endif /* FILTERINPUTDEVICES_H */

