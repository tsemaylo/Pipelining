option(DO_TESTING "Build tests" OFF)
option(DO_VALGRIND_TEST "Build test suite and perform memory checks" OFF)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_COMPILER_IS_GNUCC) 
        check_and_set_compiler_flag("-O0")
        check_and_set_compiler_flag("--coverage")
    endif()
endif()

function(add_unit_test_suite) 
   get_filename_component(test_suite_name ${ARGV0} NAME_WE)
   add_executable(${test_suite_name} ${ARGV})
   target_link_libraries(${test_suite_name} gtest_main)

   if(CMAKE_BUILD_TYPE STREQUAL "Debug")
       if(CMAKE_COMPILER_IS_GNUCC) 
           set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
           target_link_libraries (${test_suite_name} gcov)
       endif()
   endif()

   target_include_directories(${test_suite_name} PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
   )

   if(DO_VALGRIND_TEST)
      add_test(NAME "${test_suite_name}_valgrind"
         COMMAND ${memcheck_command} ./${test_suite_name}
      )
      set_tests_properties("${test_suite_name}_valgrind" PROPERTIES LABELS "valgrind")
   endif()

   add_test(NAME ${test_suite_name} COMMAND ${test_suite_name} --gtest_shuffle --gtest_repeat=7)
endfunction()


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
   RESULT_VARIABLE result
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/googletest-download
)
if(result)
   message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
   RESULT_VARIABLE result
   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/googletest-download 
)
if(result)
   message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${PROJECT_BINARY_DIR}/googletest-src
                 ${PROJECT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

if(DO_VALGRIND_TEST)
    find_program(CMAKE_MEMORYCHECK_COMMAND valgrind)
    set(CMAKE_MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --leak-check=full")
    set(memcheck_command "${CMAKE_MEMORYCHECK_COMMAND} ${CMAKE_MEMORYCHECK_COMMAND_OPTIONS}")
    separate_arguments(memcheck_command)
endif()

add_unit_test_suite("UnbufferedPipeTest.cpp" "../src/UnbufferedPipe.cpp" "../src/Pipe.cpp" "../src/PipelineException.cpp")
add_unit_test_suite("BufferedPipeTest.cpp" "../src/BufferedPipe.cpp" "../src/Pipe.cpp" "../src/PipelineException.cpp")
add_unit_test_suite("BranchingTest.cpp" "../src/Branch.cpp" "../src/BufferedPipe.cpp" "../src/Pipe.cpp" "../src/PipelineException.cpp")
add_unit_test_suite("FilterInputDevicesTest.cpp" "../src/SyslogOperations/FilterInputDevices.cpp")
add_unit_test_suite("ReformatTest.cpp" "../src/SyslogOperations/Reformat.cpp")

enable_testing()