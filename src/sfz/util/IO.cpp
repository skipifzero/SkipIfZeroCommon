#include "sfz/util/IO.hpp"

#include "sfz/Assert.hpp"

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlobj.h>
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

} // namespace sfz