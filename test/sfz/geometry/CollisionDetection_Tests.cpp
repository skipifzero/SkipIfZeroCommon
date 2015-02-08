#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/CollisionDetection.hpp"
#include "sfz/geometry/OBB.hpp"

TEST_CASE("AABB & AABB test", "[sfz::CollisionDetection]")
{
	using namespace sfz;

	AABB boxMid{vec3f{-1, -1, -1}, vec3f{1, 1, 1}};
	AABB boxMidSmall{vec3f{-0.5f, -0.5f, -0.5f}, vec3f{0.5f, 0.5f, 0.5f}};

	REQUIRE(true);
}