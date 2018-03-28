/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file UnbufferedPipe.h
 *
 * Definition of UnbufferedPipe class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#ifndef UNBUFFEREDPIPE_H
#define UNBUFFEREDPIPE_H

#include "Pipe.h"

/**
 * Class UnbufferedPipe represents unbuffered data transition from input (feed)
 * to the next procession step (sink).
 */
class UnbufferedPipe : public Pipe{
public:
    UnbufferedPipe(Operation &);
    virtual ~UnbufferedPipe();
    
    void feed(const ByteVector &data) final;
    void wait() final;

};

#endif /* UNBUFFEREDPIPE_H */

