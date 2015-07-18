#include "sfz/util/IO.hpp"
#include "sfz/Assert.hpp"

#include <cstdio>

#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlobj.h>
#include <direct.h>

#elif defined(__APPLE__)
#include <sys/stat.h>

#elif defined(__unix)
#include <sys/stat.h>
#endif

namespace sfz {

const std::string& myDocumentsPath() noexcept
{
	static const std::string path = []() {
#ifdef _WIN32
		char tempPath[MAX_PATH];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, tempPath);
		if (result != S_OK) sfz_error("Could not retrieve MyDocuments path.");
		return std::string{tempPath};
#else
		return std::string{"~"};
#endif
	}();
	return path;
}

const std::string& gameBaseFolderPath() noexcept
{
	static const std::string path = myDocumentsPath() + "/My Games";
	return path;
}

bool directoryExists(const char* path) noexcept
{
#ifdef _WIN32
	std::FILE* file = std::fopen(path, "r");
	if (file == NULL) {
		DWORD ftyp = GetFileAttributesA(path);
		if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
		return false;
	}
	std::fclose(file);
	return true;
#else
	std::FILE* file = std::fopen(path, "r");
	if (file == NULL) return false;
	std::fclose(file);
	return true;
#endif
}

bool createDirectory(const char* path) noexcept
{
#ifdef _WIN32
	int res = _mkdir(path);
	if (res == 0) return true;
	return false;
#else
	int res = mkdir(path, 0775);
	if (res == 0) return true;
	else return false;
#endif
}

} // namespace sfz