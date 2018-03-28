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

/**
 * Interface Operation is a generic base for function to process a single data item.
 * 
 * Implementations of Operation may have a state to support more sophisticated functionality.
 */
class Operation {
public:
    /**
     * Apply the operation to data.
     * 
     * Passed data argument is considered as immutable. The new data item must be 
     * returned from the method.
     */
    virtual ByteVector apply(const ByteVector &data) = 0;

    virtual ~Operation() {
    }
};

#endif /* OPERATION_H */

