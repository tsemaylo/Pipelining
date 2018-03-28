#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "ByteVector.h"
#include "SyslogOperations/Reformat.h"

TEST(ReformatTest, apply_SubstringFound){
    std::unique_ptr<Operation> op = std::make_unique<Reformat>();
    std::string str = "[    4.724189] input: RAPOO RAPOO 5G Wireless Device as /devices/pci0000:00/0000:00:14.0/usb2/2-3/2-3:1.1/0003:24AE:2003.0002/input/input12";
    ByteVector data(str.begin(), str.end());
    
    ByteVector res = op->apply(data);
    std::string resStr(res.begin(), res.end());
    ASSERT_EQ("RAPOO RAPOO 5G Wireless Device | /devices/pci0000:00/0000:00:14.0/usb2/2-3/2-3:1.1/0003:24AE:2003.0002/input/input12", resStr);
}

TEST(ReformatTest, apply_SubstringNotFound){
    
}