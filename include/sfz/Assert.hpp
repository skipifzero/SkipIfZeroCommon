#pragma once
#ifndef SFZ_ASSERT_HPP
#define SFZ_ASSERT_HPP

#include <string>
#include <iostream> // std::cerr
#include <exception> // std::terminate()
#include <cassert>

#include "sfz/MSVC12HackON.hpp"

/**
 * This file contains various assert functions to be used for debugging and error checking purposes.
 * They are all defined in the global namespace with the prefix 'sfz', the reason for this is that
 * in the future it might be of interest to replace the functions with macros. Since macros can't
 * reside in namspaces this will make that change less disrupting.
 */

/**
 * @brief Stops program or opens debugger if condition is false.
 * To be used often to catch bugs during debugging progress. Should normally only be enabled in
 * debug builds. Disabled by defining SFZ_NO_DEBUG, but also by defining SFZ_NO_ASSERTIONS.
 */
inline void sfz_assert_debug(bool condition) noexcept;

/**
 * @brief Stops program or opens debugger if condition is false and displays message.
 * To be used often to catch bugs during debugging progress. Should normally only be enabled in
 * debug builds. Disabled by defining SFZ_NO_DEBUG, but also by defining SFZ_NO_ASSERTIONS.
 */
inline void sfz_assert_debug(bool condition, const std::string& message) noexcept;

/**
 * @brief Stops program or opens debugger if condition is false.
 * To be used for more serious things that you want to catch quickly even in a release build.
 * Should normally always be enabled, but can be disabled by defining SFZ_NO_ASSERTIONS.
 */
inline void sfz_assert_release(bool condition) noexcept;

/**
 * @brief Stops program or opens debugger if condition is false and displays message.
 * To be used for more serious things that you want to catch quickly even in a release build.
 * Should normally always be enabled, but can be disabled by defining SFZ_NO_ASSERTIONS.
 */
inline void sfz_assert_release(bool condition, const std::string& message) noexcept;

/**
 * @brief Stops execution of program and displays message.
 * This is meant to be used for errors that can't be recovered from and should crash the program.
 * Should always be enabled, but can be disabled (not recommended) by defining SFZ_DISABLE_ERRORS.
 */
inline void error(const std::string& message) noexcept;

#include "sfz/MSVC12HackOFF.hpp"
#include "sfz/Assert.inl"
#endif