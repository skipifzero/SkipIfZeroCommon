#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "sfz/geometry/Intersection.hpp"
#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/OBB.hpp"

TEST_CASE("AABB & AABB test", "[sfz::Intersection]")
{
	using namespace sfz;

	AABB boxMid{vec3f{-1.0f, -1.0f, -1.0f}, vec3f{1.0f, 1.0f, 1.0f}};
	AABB boxMidSmall{vec3f{-0.5f, -0.5f, -0.5f}, vec3f{0.5f, 0.5f, 0.5f}};

	REQUIRE(true);
}