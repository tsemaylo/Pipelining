#include <iostream>
#include <string>
#include <algorithm>

/**
 * TI - input type of operation
 * TO - output type of operation
 */
template <typename TI, typename TO>
class Operation {
    public:
        TO apply(const TI &) { return TO(); }
};


/**
 * TI - type of this pipe input
 * TO - type of this pipe output
 */
template <typename TI, typename TO>
class UnbufferedPipe {
    public:
       UnbufferedPipe(Operation<TI, TO> *_operation) : operation(_operation) { }

       void feed(const TI &data) {
           if(this->sink != 0){
               this->sink->feed(this->operation->apply(data));
           }
       }

       UnbufferedPipe *setSink(UnbufferedPipe *_sink) {
           this->sink=_sink;
           return this;
       }

    protected:
       Operation<TI, TO> *operation;
       UnbufferedPipe *sink;
};

class MakeUppercase : public Operation<std::string, std::string> {
    public:
        std::string apply(std::string &data) {
            std::string out(data);
            std::transform(out.begin(), out.end(), out.begin(), toupper);
            return out;
        }
};

class Reverse : public Operation<std::string, std::string> {
    public:
        std::string apply(std::string &data) {
            std::string out;
            for(size_t i=data.length(); i != 0ul; --i){
               out += data[i-1];
            }
            return out;
        }
};

class StandardOut : public Operation<std::string, void> {
    public:
        void apply(std::string &data) {
            std::cout << data << std::endl;
        }
};

int main(int , char **){
    std::string input="test";
    
    MakeUppercase uppercase;
    UnbufferedPipe<std::string, std::string> step1(&uppercase);

    Reverse reverse;
    UnbufferedPipe<std::string, std::string> step2(&reverse);

    StandardOut out;
    UnbufferedPipe<std::string, void> step3(&out);

    step1.setSink(step2.setSink(&step3));
    step1.feed(input);

   return 0;
}
