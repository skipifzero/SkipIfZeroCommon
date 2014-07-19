cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Project name
project("SkipIfZero Common")

# Huge hack to ensure we always build in release mode.
set(CMAKE_BUILD_TYPE release)

# Compiler flags
if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
  OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
  OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	# GCC and Clang flags
	set(compiler_flags "-Wall -Wextra -Wno-c++11-extensions -std=c++11 -O3")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# MSVC flags
	set(compiler_flags "/Wall /EHsc /O2")
else ()
	# Unknown compiler, sets no flags and prints warning.
	message("WARNING: Unknown compiler \"${CMAKE_CXX_COMPILER_ID}\", no specific flags set.")
endif ()

# Sets the specified compiler flags, will only set the first time cmake configures project.
if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_flags}" 
	    CACHE STRING "Flags used by the compiler during all build types." FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_flags}"
	    CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif ()

# Directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(EXTERNALS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# Set standard include directory
include_directories(${INCLUDE_DIR})


# Main executable
add_executable(SFZCommonMain 
	 ${SOURCE_DIR}/Main.cpp

	${INCLUDE_DIR}/sfz/algo/Sorting.hpp
	${INCLUDE_DIR}/sfz/algo/Sorting.inl
	${INCLUDE_DIR}/sfz/algo/SortingPerfTest.hpp
	 ${SOURCE_DIR}/sfz/algo/SortingPerfTest.cpp

	${INCLUDE_DIR}/sfz/Math.hpp
	${INCLUDE_DIR}/sfz/math/MathConstants.hpp
	${INCLUDE_DIR}/sfz/math/Vector.hpp
	${INCLUDE_DIR}/sfz/math/Vector.inl

	${INCLUDE_DIR}/sfz/util/BlockingQueue.hpp
	${INCLUDE_DIR}/sfz/util/BlockingQueue.inl
	${INCLUDE_DIR}/sfz/util/ScopedThread.hpp
	 ${SOURCE_DIR}/sfz/util/ScopedThread.cpp
	${INCLUDE_DIR}/sfz/util/StopWatch.hpp
	 ${SOURCE_DIR}/sfz/util/StopWatch.cpp
	${INCLUDE_DIR}/sfz/util/ThreadPool.hpp
	${INCLUDE_DIR}/sfz/util/ThreadPool.inl)


# Enables testing and adds catch header to project.
enable_testing(true)
include_directories(${EXTERNALS_DIR}/catch/include)

# Test executables
add_executable(Vector_Tests ${TEST_DIR}/sfz/math/Vector_Tests.cpp)
add_executable(MathConstants_Tests ${TEST_DIR}/sfz/math/MathConstants_Tests.cpp)
add_executable(BlockingQueue_Tests ${TEST_DIR}/sfz/util/BlockingQueue_Tests.cpp)

# Tests to run
add_test(Vector_Tests_Name Vector_Tests)
add_test(MathConstants_Tests_Name MathConstants_Tests)
add_test(BlockingQueue_Tests_Name BlockingQueue_Tests)


# Sets flag that ensures some variables are only set once.
set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")