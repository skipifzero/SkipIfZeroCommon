# SkipIfZero Common

SkipIfZero Common is a collection of reusable c++11 code used in SkipIfZero projects. It contains math, algorithms, utilities, etc.


## Building
SkipIfZero Common uses CMake for building and requires at least CMake 3.0. It is advisable to let cmake generate the wanted build solution in a directory called `build` inside the project folder as that folder is ignored by git. Many c++11 features are used, so the newest possible versions of your c++ compiler is recommended. Mostly tested using Clang, but also GCC and MSVC sporadically.

### Linux and Mac OS X
The following commands will generate the standard makefile build solution on Linux and Mac OS X.

`mkdir build`

`cd build`

`cmake ..`

You then have the following options:

`make` Builds the project

`make test` Builds and runs the tests

`make help` Shows available options

#### Xcode
On Mac OS X you might also want to generate an Xcode project, you can do this using the following commands.

`mkdir build`

`cd build`

`cmake .. -GXcode`

### Windows

Not yet tested, presumably cmake will generate a Visual Studio solution by default. 


## License
What license to use has yet to be decided. In the meantime just contact me if you want to use the code.