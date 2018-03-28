#include <gtest/gtest.h>
#include <memory>
#include <string.h>
#include <vector>

#include "Branch.h"
#include "BufferedPipe.h"
#include "Operation.h"

/**
 * Test pipeline for strings as an input
 * 
 * Step 1 - make uppercase
 * Step 2 - For items ended with even numbers
 *    Step 2.1 - Reverse string
 *  othewise
 *    Step 2.1 - put spaces between letters and 
 *    Step 2.2 - Reverse string
 * Step 3 - print to the output 
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

class InsertSpaces : public Operation {
public:

    ByteVector apply(const ByteVector& data) final {
        ByteVector res;
        bool first = true;
        for (uint8_t byte : data) {
            if (!first) {
                res.push_back(' ');
            }
            res.push_back(byte);
            first = false;
        }
        return res;
    }

    virtual ~InsertSpaces() {
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

TEST(Branch, PipelineWithParallelSteps_NormalCase) {
    MakeUppercase makeUppercase;
    BufferedPipe step1(makeUppercase);


    Reverse reverse;
    BufferedPipe step21a(reverse);

    InsertSpaces insertSpaces;
    BufferedPipe step21b(insertSpaces);

    BufferedPipe step22(reverse);

    CheckOutput out;
    BufferedPipe step3(out);

    auto checkIfEven = [](const ByteVector & data) {
        std::string str(data.begin(), data.end());
        char lastChar = str.back();
        if (lastChar >= '0' && lastChar <= '9') {
            int n = str.back() - '0';
            return (n % 2) == 0;
        }
        return false;
    };

    Branch step2(step21a.sink(&step3), step21b.sink(step22.sink(&step3)));
    step2.setConditionBranch1(checkIfEven);
    step2.setConditionBranch2([&checkIfEven](const ByteVector & data) {
        return !checkIfEven(data); });

    step1.sink(&step2);

    step1.feed(makeByteVector("test1"));
    step1.feed(makeByteVector("test2"));
    step1.feed(makeByteVector("test3"));
    step1.feed(makeByteVector("test4"));
    step1.feed(makeByteVector("test5"));

    step1.wait();

    // results may come in random order due to parallel 
    // and therefore undeterministic processing
    EXPECT_NE(std::string::npos, out.getOutput().find("1 T S E T"));
    EXPECT_NE(std::string::npos, out.getOutput().find("3 T S E T"));
    EXPECT_NE(std::string::npos, out.getOutput().find("5 T S E T"));
    EXPECT_NE(std::string::npos, out.getOutput().find("2TSET"));
    EXPECT_NE(std::string::npos, out.getOutput().find("4TSET"));
}