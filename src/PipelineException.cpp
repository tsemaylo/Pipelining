/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file PipelineException.cpp
 *
 * Implementation of PipelineException class.
 *
 * @since 28.03.2018
 * @author tsemaylo
 */

#include "PipelineException.h"

PipelineException::PipelineException(const char* msg) :
exception(), msg(msg) {
}

const char* PipelineException::what() const noexcept {
    return this->msg;
}



