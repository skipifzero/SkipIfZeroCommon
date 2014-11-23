#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "sfz/math/Vector.hpp"
#include "sfz/math/Matrix.hpp"

TEST_CASE("Constructors", "[sfz::Matrix]")
{

}

TEST_CASE("Is proper POD", "[sfz::Matrix]")
{
	REQUIRE(std::is_trivially_default_constructible<sfz::mat4f>::value);
	REQUIRE(std::is_trivially_copyable<sfz::mat4f>::value);
	REQUIRE(std::is_trivial<sfz::mat4f>::value);
	REQUIRE(std::is_standard_layout<sfz::mat4f>::value);
	REQUIRE(std::is_pod<sfz::mat4f>::value);
}