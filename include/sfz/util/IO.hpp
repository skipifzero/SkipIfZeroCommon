#pragma once
#ifndef SFZ_UTIL_IO_HPP
#define SFZ_UTIL_IO_HPP

#include <string>

namespace sfz {

/** @brief Returns path to MyDocuments on Windows, user root (~) on Unix. */
const std::string& myDocumentsPath() noexcept;

/** @brief Returns path to where game folders with saves should be placed. */
const std::string& gameBaseFolderPath() noexcept;

} // namespace sfz

#endif