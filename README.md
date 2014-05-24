# SkipIfZero Common

SkipIfZero Common is a collection of reusable c++11 code used in SkipIfZero projects. It contains math, algorithms, utilities, etc.

## Building

Currently contains a simple makefile that uses Clang for building. If Clang is unavailable the makefile can easily be modified to use GCC instead by modifiying the `CC` variable. The commands available are as follows:

`make all` Builds the project

`make run` Builds and runs the project

`make tests` Builds and runs the tests

`make clean` Cleans the project from built files (removes build dir)

This is (most likely) a temporary solution and a proper build system like CMake or Gradle will be implemented in the future.

## License
What license to use has yet to be decided. In the meantime just contact me if you want to use the code.