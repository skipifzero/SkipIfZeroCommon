#pragma once

#include <iostream>
#include <string>
#include <exception> // std::terminate

#ifndef SFZ_EXCEPTIONS_ENABLED
// Wip, here we will check compiler specific macros.
#define SFZ_EXCEPTIONS_ENABLED true
#endif

template<typename ExceptionType>
void sfz_throw(std::string message)
{
	#if SFZ_EXCEPTIONS_ENABLED == true
		throw ExceptionType{message};
	#else
		std::cout << message << std::endl;
		std::terminate();
	#endif
}