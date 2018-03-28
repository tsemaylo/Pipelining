/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Pipe.cpp
 *
 * Implementation of basic functionality of Pipe abstract class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#include "Pipe.h"
#include "PipelineException.h"

Pipe::Pipe(Operation &_op) : operation(_op){

}

Pipe *Pipe::sink(Pipe* _next) {
    if(this->next == 0l){
        this->next = _next;
        return this;
    }

    throw PipelineException("The sink is already initilized.");
}

Pipe::~Pipe() {

}

