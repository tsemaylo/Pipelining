/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Branch.h
 *
 * Implementation of Branch class.
 *
 * @since 27.03.2018
 * @author tsemaylo
 */

#include "Branch.h"
#include "Operation.h"

// since Branch has no operation attached, the "empty" operation is defined.
class NopOperation : public Operation {
public:
    ByteVector apply(const ByteVector&) final {
        return ByteVector();
    }
    
    virtual ~NopOperation() {

    }
};
static NopOperation nop;

Branch::Branch(Pipe* _branch1, Pipe* _branch2) :
Pipe(nop), branch1(_branch1), branch2(_branch2) {
    
}

void Branch::feed(const ByteVector& data) {
    if(this->conditionBranch1(data)) {
        this->branch1->feed(data);
    }
    
    if(this->conditionBranch2(data)) {
        this->branch2->feed(data);
    }
}

void Branch::setConditionBranch1(std::function<bool (const ByteVector&)> conditionBranch1) {
    this->conditionBranch1 = conditionBranch1;
}

void Branch::setConditionBranch2(std::function<bool (const ByteVector&)> conditionBranch2) {
    this->conditionBranch2 = conditionBranch2;
}

void Branch::wait() {
    if(this->branch1 != 0l) {
        this->branch1->wait();
    }
    
    if(this->branch2 != 0l) {
        this->branch2->wait();
    }
}

Branch::~Branch() {

}
