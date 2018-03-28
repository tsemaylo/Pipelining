#include <iostream>

#include "SyslogOperations/StandardOut.h"
#include "SyslogOperations/FilterInputDevices.h"
#include "SyslogOperations/Reformat.h"
#include "Pipe.h"
#include "BufferedPipe.h"
#include "Branch.h"

int main(const int, const char **) {
    FilterInputDevices filter;
    BufferedPipe stepFilter(filter);

    StandardOut out;
    BufferedPipe stepOutput(out);

    // split the job and do reformating in parllel

    // so we are creating two BUFFERED pipes which execute Reformat operation in 
    // separate execution threads, the results will be piped to the stepOutput
    Reformat reformat;
    BufferedPipe stepReformat1(reformat);
    BufferedPipe stepReformat2(reformat);
    Branch branch(stepReformat1.sink(&stepOutput), stepReformat2.sink(&stepOutput));

    // in order to split the job, the following criterias are used
    // even lines will go to the stepReformat1
    auto evensToFirst = [](const ByteVector &) {
        static unsigned long counter = 1;
        counter++;
        return (counter % 2) == 0;
    };
    branch.setConditionBranch1(evensToFirst);

    // and adds will go to the stepReformat2
    auto oddsToSecond = [](const ByteVector &) {
        static unsigned long counter = 1;
        counter++;
        return (counter % 2) != 0;
    };
    branch.setConditionBranch2(oddsToSecond);

    stepFilter.sink(&branch);

    while (std::cin) {
        std::string line;
        std::getline(std::cin, line);
        ByteVector data(line.begin(), line.end());
        stepFilter.feed(data);
    };

    stepFilter.wait();

    return 0;
}
