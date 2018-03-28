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

#ifndef STANDARDOUT_H
#define STANDARDOUT_H

#include "Operation.h"

class StandardOut : public Operation{
public:
    ByteVector apply(const ByteVector& data) final;
    virtual ~StandardOut();
};

#endif /* STANDARDOUT_H */

