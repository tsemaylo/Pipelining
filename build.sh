#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

export CXX="g++"
export CC="gcc"

rm -Rf ./build 
mkdir -p build

cd build 

TESTING_FLAG="Off"
if [ "$DO_TESTING" = "1" ]; then
    TESTING_FLAG="On"
fi

VALGRIND_FLAG="Off"
if [ "$DO_VALGRIND_TEST" = "1" ]; then
    VALGRIND_FLAG="On"
fi

cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/pipelining -DCMAKE_BUILD_TYPE=Debug -DDO_VALGRIND_TEST=$VALGRIND_FLAG -DDO_TESTING=$TESTING_FLAG

make 
if [ "${DO_TESTING}" = "1" ]; then
    make test
fi
make install

cd ..
