/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Operation.h
 *
 * Definition of Operation interface.
 *
 * @since 25.03.2018
 * @author tsemaylo
 */

#ifndef OPERATION_H
#define OPERATION_H

#include "ByteVector.h"

class Operation {
public:
    virtual ByteVector apply(const ByteVector &data) = 0;
    virtual ~Operation() {
    }
};

#endif /* OPERATION_H */

