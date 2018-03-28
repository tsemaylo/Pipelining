/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Pipe.h
 *
 * Definition of Pipe abstract class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#ifndef PIPE_H
#define PIPE_H

#include "ByteVector.h"

class Operation;

/**
 * Pipe is an abstract class representing the comminication channel between steps 
 * of the processing pipeline. Incorporates filter/operation to be performed on the 
 * incoming data.
 */
class Pipe {
public:
    /**
     * 
     * @param _op  Operation to be applied to the pipe input.
     */
    Pipe(Operation & _op);
    virtual ~Pipe();

    /**
     * Feed the data into pipe.
     * 
     * Method represents input of the pipe.
     * 
     * @param data   Vector of bytes with data to be processed.
     */
    virtual void feed(const ByteVector &data) = 0;

    /**
     * Set the output of the pipe
     * 
     * @param next  The next pipe representing the next execution step in the pipeline.
     * 
     * @return Pointer to this pipe.
     */
    virtual Pipe *sink(Pipe *next);

    /**
     * Wait untill pipeline will finish its work.
     * 
     * Make sense for buffered pipes, because it may take a time to process the whole buffer.
     */
    virtual void wait() = 0;

protected:
    Operation &operation;
    Pipe *next = 0l; // the next step of the pipeline
};

#endif /* PIPE_H */

