option(DO_TESTING "Build tests" OFF)
option(DO_VALGRIND_TEST "Build test suite and perform memory checks" OFF)

cmake_minimum_required (VERSION 3.0.2)
project (Pipelining)

include(CheckCXXCompilerFlag)
function(check_and_set_compiler_flag flag_name)
   check_cxx_compiler_flag(${flag_name} isFlagSupported)
   message(STATUS "Support of compiler flag ${flag_name} is ${isFlagSupported}")
   if(${isFlagSupported})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag_name}")
      add_compile_options(${flag_name})
   endif()
endfunction()

# version
set(Pipelining_VERSION_MAJOR 0)
set(Pipelining_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# force essential compiler options if they are supported
check_and_set_compiler_flag("-Wall")
check_and_set_compiler_flag("-Werror")
check_and_set_compiler_flag("-Wextra")
check_and_set_compiler_flag("-pedantic")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_COMPILER_IS_GNUCC) 
        check_and_set_compiler_flag("-O0")
        check_and_set_compiler_flag("--coverage")
    endif()
endif()

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(pipeline
    src/main.cpp
    src/Pipe.cpp
    src/BufferedPipe.cpp 
    src/Branch.cpp 
    src/SyslogOperations/FilterInputDevices.cpp
    src/SyslogOperations/StandardOut.cpp
    src/PipelineException.cpp
    src/SyslogOperations/Reformat.cpp
)

target_link_libraries(pipeline pthread)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_COMPILER_IS_GNUCC) 
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
        target_link_libraries (pipeline gcov)
    endif()
endif()

if(DO_TESTING)
    add_subdirectory(test)
    enable_testing()
endif()

# ---------------------------------

install(TARGETS pipeline DESTINATION bin)
