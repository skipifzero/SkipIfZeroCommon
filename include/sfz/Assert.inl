#include "sfz/MSVC12HackON.hpp"


#if !defined(SFZ_NO_DEBUG) && !defined(SFZ_NO_ASSERTIONS)

	inline void sfz_assert_debug(bool condition) noexcept
	{
		assert(condition);
	}

	inline void sfz_assert_debug(bool condition, const std::string& message) noexcept
	{
		if (!condition) {
			std::cerr << message << std::endl;
			assert(condition);
		}
	}

#else
	inline void sfz_assert_debug(bool) noexcept { }
	inline void sfz_assert_debug(bool, const std::string&) noexcept { }
#endif



#if !defined(SFZ_NO_ASSERTIONS)

	inline void sfz_assert_release(bool condition) noexcept
	{
		assert(condition);	
	}

	inline void sfz_assert_release(bool condition, const std::string& message) noexcept
	{
		if (!condition) {
			std::cerr << message << std::endl;
			assert(condition);
		}
	}

#else
	inline void sfz_assert_release(bool) noexcept {}
	inline void sfz_assert_release(bool, const std::string&) noexcept {}
#endif



#if !defined(SFZ_DISABLE_ERRORS)

	inline void sfz_error(const std::string& message) noexcept
	{
		std::cerr << message << std::endl;
		std::terminate();
	}

#else
	inline void sfz_error(const std::string&) noexcept {}
#endif


#include "sfz/MSVC12HackOFF.hpp"