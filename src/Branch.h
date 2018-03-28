/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Branch.h
 *
 * Definition of Branch class.
 *
 * @since 27.03.2018
 * @author tsemaylo
 */

#ifndef BRANCH_H
#define BRANCH_H


#include <functional>
#include "Pipe.h"

/**
 * Branch class provides the possibility to split pipeline into two parallel procession 
 * pipelines and then merge the results into output sink.
 */
class Branch : public Pipe {
public:

    /**
     * Construct the branched pipe with two alternative sub-pipelines to be executed parallel.
     * 
     * Note that both alternative branch-pipes can have the same sink, that allows to "merge" data.
     * By default the data will go to the both pipes.
     * 
     * @param _branch1 Pointer to a Pipe for the first alternatve.
     * @param _branch2 Pointer to a Pipe for the secont alternatve.
     */
    Branch(Pipe* _branch1, Pipe* _branch2);

    void feed(const ByteVector&) final;
    void wait() final;
    virtual ~Branch();

    /**
     * Set conditional lambda defining which data items will go to the first pipe-branch.
     * 
     * @param conditionBranch1 Lambda function returning true for data items which will go to first branch.
     */
    void setConditionBranch1(std::function<bool (const ByteVector&) > conditionBranch1);

    /**
     * Set conditional lambda defining which data items will go to the second pipe-branch.
     * 
     * @param conditionBranch2 Lambda function returning true for data items which will go to second branch.
     */
    void setConditionBranch2(std::function<bool (const ByteVector&) > conditionBranch2);


private:
    Pipe *branch1=0l;
    Pipe *branch2=0l;

    std::function<bool (const ByteVector &) > conditionBranch1 = [](const ByteVector &) {
        return true;
    };
    std::function<bool (const ByteVector &) > conditionBranch2 = [](const ByteVector &) {
        return true;
    };
};

#endif /* BRANCH_H */

