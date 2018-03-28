#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "ByteVector.h"
#include "SyslogOperations/FilterInputDevices.h"

TEST(FilterInputDevicesTest, apply_SubstringFound) {
    std::unique_ptr<Operation> op = std::make_unique<FilterInputDevices>();
    std::string str = "something input: something else";
    ByteVector data(str.begin(), str.end());

    ByteVector res = op->apply(data);
    std::string resStr(res.begin(), res.end());
    ASSERT_EQ(str, resStr);
}

TEST(FilterInputDevicesTest, apply_SubstringNotFound) {
    std::unique_ptr<Operation> op = std::make_unique<FilterInputDevices>();
    std::string str = "something else";
    ByteVector data(str.begin(), str.end());

    ByteVector res = op->apply(data);
    ASSERT_EQ(0u, res.size());
}