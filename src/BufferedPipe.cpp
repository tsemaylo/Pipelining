/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file BufferedPipe.cpp
 *
 * Implementation of BufferedPipe class.
 *
 * @since 26.03.2018
 * @author tsemaylo
 */

#include "BufferedPipe.h"
#include "Operation.h"

#include <iostream>
#include <chrono>

void BufferedPipe::bufferHandling() {
    while (this->doBufferHandling) {
        // make a small delay to reduce CPU load
        // may be considered harmful for hi-performace tasks
        std::this_thread::sleep_for(std::chrono::microseconds(200));

        std::lock_guard<std::mutex> guard(this->protectBuffer);

        if (!this->buffer.empty()) {
            this->pipeReady = false;

            ByteVector dataItem = this->buffer.front();
            this->buffer.pop_front();

            ByteVector dataItemRes = this->operation.apply(dataItem);
            if (this->next != 0l) {
                this->next->feed(dataItemRes);
            }
            this->pipeReady = true;
        }
    }
}

BufferedPipe::BufferedPipe(Operation &_op) : Pipe(_op), doBufferHandling(true), pipeReady(true) {
    // reset and create handling thread
    if (this->inBufferMgmt.joinable()) {
        this->inBufferMgmt.join();
    }
    this->inBufferMgmt = std::thread([this] {
        this->bufferHandling(); });
}

void BufferedPipe::feed(const ByteVector &data) {
    std::lock_guard<std::mutex> guard(this->protectBuffer);
    this->buffer.push_back(data);
}

void BufferedPipe::wait() {
    while (!(this->buffer.empty() && this->pipeReady));
    if (this->next != 0l) {
        this->next->wait();
    }
}

BufferedPipe::~BufferedPipe() {
    // stop thread processing
    this->doBufferHandling = false;

    // join thread
    if (this->inBufferMgmt.joinable()) {
        this->inBufferMgmt.join();
    }
}
