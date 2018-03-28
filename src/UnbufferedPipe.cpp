/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file UnbufferedPipe.cpp
 *
 * Implementation of UnbufferedPipe class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#include "UnbufferedPipe.h"
#include "Operation.h"

UnbufferedPipe::UnbufferedPipe(Operation &_op) : Pipe(_op) {

}

void UnbufferedPipe::feed(const ByteVector &data) {
    ByteVector res = operation.apply(data);
    if (this->next != 0l) {
        this->next->feed(res);
    }
}

void UnbufferedPipe::wait() {
    if (this->next != 0l) {
        this->next->wait();
    }
}

UnbufferedPipe::~UnbufferedPipe() {

}

