/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Reformat.h
 *
 * Definition of Reformat class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#ifndef REFORMAT_H
#define REFORMAT_H

#include "Operation.h"

/**
 * The purpose of the Reformat class is to reformat the syslog string into the 
 * following format: Device_Name | Device_Location
 * 
 * The input string has the form:
 * <random text> input: <device name> as <device location>
 */
class Reformat : public Operation {
public:
    ByteVector apply(const ByteVector& data) final;

    virtual ~Reformat();


};

#endif /* REFORMAT_H */

