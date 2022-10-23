# Assuming this your tests/CMakeLists.txt (and your libs are setup in a root config)
# Just make sure to include(CTest) in your *root* cmake config.

# 3.9 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
cmake_minimum_required(VERSION 3.9)

find_package(Threads REQUIRED)

# Configure google-test as a downloadable library.
include(external_gtest)

add_executable(myTests
    main.cpp)


# This will automatically handle all of the lib linkage and include dirs
message("GTEST_LIBRARY ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY}, path ${GTEST_INCLUDE_DIRS}")
if(NOT TARGET ${GTEST_LIBRARY})
message(FATAL_ERROR "no valid gtest")
endif()

target_link_libraries(myTests
    PUBLIC
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
)

target_include_directories(myTests PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# # Tell ctest about my tests
# include(GoogleTest)

# gtest_add_tests(
#     TARGET      myTests
#     TEST_LIST   myTests_targets
# )

# # set each target to timeout if not finished within 10 sec
# set_tests_properties(${myTests_targets} PROPERTIES TIMEOUT 10)