#pragma once

#include <iostream>
#include <string>
#include <exception> // std::terminate

#ifndef SFZ_EXCEPTIONS_ENABLED

	// GCC
	#ifdef __GNUG__
		// GCC: '__EXCEPTIONS' This macro is defined, with value 1, when compiling a C++ source file with exceptions
		// enabled. If -fno-exceptions was used when compiling the file, then this macro will not be defined. 
		#ifdef __EXCEPTIONS
		#define SFZ_EXCEPTIONS_ENABLED true
		#else
		#define SFZ_EXCEPTIONS_ENABLED false
		#endif
	#endif

	


#endif

template<typename ExceptionType>
void sfz_throw(std::string message)
{
	#if SFZ_EXCEPTIONS_ENABLED == true
		throw ExceptionType{message};
	#elif SFZ_EXCEPTIONS_ENABLED == false
		std::cout << message << std::endl;
		std::terminate();
	#else
	#error SFZ_EXCEPTIONS_ENABLED may only be defined as true or false
	#endif
}