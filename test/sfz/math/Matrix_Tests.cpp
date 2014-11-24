#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "sfz/math/Vector.hpp"
#include "sfz/math/Matrix.hpp"

TEST_CASE("Constructors", "[sfz::Matrix]")
{
	SECTION("Initializer list constructor") {
		sfz::mat3i m1{{1, 2, 3},
		              {4, 5, 6},
		              {7, 8, 9}};

		REQUIRE(m1.get(0, 0) == 1);
		REQUIRE(m1.get(0, 1) == 2);
		REQUIRE(m1.get(0, 2) == 3);
		REQUIRE(m1.get(1, 0) == 4);
		REQUIRE(m1.get(1, 1) == 5);
		REQUIRE(m1.get(1, 2) == 6);
		REQUIRE(m1.get(2, 0) == 7);
		REQUIRE(m1.get(2, 1) == 8);
		REQUIRE(m1.get(2, 2) == 9);

		REQUIRE(m1.mElements[0][0] == 1);
		REQUIRE(m1.mElements[0][1] == 4);
		REQUIRE(m1.mElements[0][2] == 7);
		REQUIRE(m1.mElements[1][0] == 2);
		REQUIRE(m1.mElements[1][1] == 5);
		REQUIRE(m1.mElements[1][2] == 8);
		REQUIRE(m1.mElements[2][0] == 3);
		REQUIRE(m1.mElements[2][1] == 6);
		REQUIRE(m1.mElements[2][2] == 9);

		sfz::mat2i m2{{1}};

		REQUIRE(m2.get(0, 0) == 1);
		REQUIRE(m2.get(0, 1) == 0);
		REQUIRE(m2.get(1, 0) == 0);
		REQUIRE(m2.get(1, 1) == 0);

		REQUIRE(m2.mElements[0][0] == 1);
		REQUIRE(m2.mElements[0][1] == 0);
		REQUIRE(m2.mElements[1][0] == 0);
		REQUIRE(m2.mElements[1][1] == 0);
	}
}

TEST_CASE("Is proper POD", "[sfz::Matrix]")
{
	REQUIRE(std::is_trivially_default_constructible<sfz::mat4f>::value);
	REQUIRE(std::is_trivially_copyable<sfz::mat4f>::value);
	REQUIRE(std::is_trivial<sfz::mat4f>::value);
	REQUIRE(std::is_standard_layout<sfz::mat4f>::value);
	REQUIRE(std::is_pod<sfz::mat4f>::value);
}