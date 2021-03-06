/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file BufferedPipe.h
 *
 * Definition of BufferedPipe class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#ifndef BUFFEREDPIPE_H
#define BUFFEREDPIPE_H

#include <deque>
#include <mutex>
#include <thread>

#include "Pipe.h"

/**
 * Class BufferedPipe is a Pipe implementation which provides bufferized supply 
 * of operation with data.
 * 
 * Can be seen as parallel pipe. Creates a thread to handle new buffer entries 
 * "in background".
 */
class BufferedPipe : public Pipe {
public:
    BufferedPipe(Operation &_op);

    void feed(const ByteVector &data) final;
    void wait() final;

    virtual ~BufferedPipe();

    // since we have sophisticated destructor
    BufferedPipe(const BufferedPipe& other) = delete;
    BufferedPipe(const BufferedPipe&& other) = delete;
    BufferedPipe& operator=(const BufferedPipe& right) = delete;

private:
    std::deque<ByteVector> buffer;
    std::mutex protectBuffer;
    bool doBufferHandling = false;
    std::thread inBufferMgmt;
    bool pipeReady = true; // ready stet is set when no entries in buffer and no operations are running

    void bufferHandling();
};

#endif /* BUFFEREDPIPE_H */

