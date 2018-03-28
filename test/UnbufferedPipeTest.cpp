#include <gtest/gtest.h>
#include <memory>
#include <string.h>
#include <vector>

#include "UnbufferedPipe.h"
#include "Operation.h"

/**
 * Test pipeline for stringfs as an input
 * 
 * Step 1 - make uppercase
 * Step 2 - Reverse string
 * Step 3 - print tothe output 
 */

class MakeUppercase : public Operation {
public:        
    ByteVector apply(const ByteVector& data) final {
        std::string str(data.begin(), data.end());
        std::transform(str.begin(), str.end(), str.begin(), toupper);
        
        ByteVector res(str.begin(), str.end());
        return res;
    }

    virtual ~MakeUppercase() {

    }
};

class Reverse : public Operation {
public:
    ByteVector apply(const ByteVector& data) final {
        ByteVector res;
        for (size_t i = data.size(); i > 0; --i) {
            res.push_back(data[i - 1]);
        }
        
        return res;
    }
    
    virtual ~Reverse() {
    }
};

class CheckOutput : public Operation {
public:
    std::string getOutput() const {
        return this->strOut.str();
    }
    
    ByteVector apply(const ByteVector& data) final {
        std::string str(data.begin(), data.end());
        this->strOut << str << "|";
        return ByteVector();
    }
    
    virtual ~CheckOutput() {

    }
    
private:
    std::stringstream strOut;
};

ByteVector makeByteVector(const std::string &str) {
    ByteVector data(str.begin(), str.end());
    return data;
}

TEST(UnbufferedPipeTest , PipelineOfThreeSteps_NormalCase){
    MakeUppercase makeUppercase;
    UnbufferedPipe step1(makeUppercase);
    
    Reverse reverse;
    UnbufferedPipe step2(reverse);
    
    CheckOutput out;
    UnbufferedPipe step3(out);
    
    
    step1.sink(step2.sink(&step3));
    
    step1.feed(makeByteVector("test"));
    step1.feed(makeByteVector("MOLOKO"));
    step1.feed(makeByteVector("some string"));
    
    ASSERT_EQ("TSET|OKOLOM|GNIRTS EMOS|", out.getOutput());
}