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

# Main executable
add_executable(SFZCommonMain 
	src/Main.cpp

	src/sfz/algo/Sorting.hpp
	src/sfz/algo/Sorting.inl
	src/sfz/algo/SortingPerfTest.hpp
	src/sfz/algo/SortingPerfTest.cpp

	src/sfz/Math.hpp
	src/sfz/math/MathConstants.hpp
	src/sfz/math/Vector.hpp
	src/sfz/math/Vector.inl

	src/sfz/util/BlockingQueue.hpp
	src/sfz/util/BlockingQueue.inl
	src/sfz/util/ScopedThread.hpp
	src/sfz/util/ScopedThread.cpp
	src/sfz/util/StopWatch.hpp
	src/sfz/util/StopWatch.cpp
	src/sfz/util/ThreadPool.hpp
	src/sfz/util/ThreadPool.inl)

# Enables tests
enable_testing()

# Test executables
add_executable(Vector_Tests tests/sfz/math/Vector_Tests.cpp)
add_executable(MathConstants_Tests tests/sfz/math/MathConstants_Tests.cpp)
add_executable(BlockingQueue_Tests tests/sfz/util/BlockingQueue_Tests.cpp)

# Tests to run
add_test(Vector_Tests_Name Vector_Tests)
add_test(MathConstants_Tests_Name MathConstants_Tests)
add_test(BlockingQueue_Tests_Name BlockingQueue_Tests)


# install(TARGETS SFZCommonMain DESTINATION bin)

# Sets flag that ensures some variables are only set once.
set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")