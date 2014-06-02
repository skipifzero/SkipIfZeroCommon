#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

#include "../../../src/sfz/math/MathConstants.hpp"

TEST_CASE("Pi constants", "[MathConstants]") {
	SECTION("Float version") {
		REQUIRE(3.1415f <= sfz::PI_FLOAT);
		REQUIRE(sfz::PI_FLOAT <= 3.1416f);
	}
	SECTION("Double version") {
		REQUIRE(3.1415 <= sfz::PI_DOUBLE);
		REQUIRE(sfz::PI_DOUBLE <= 3.1416);
	}
}