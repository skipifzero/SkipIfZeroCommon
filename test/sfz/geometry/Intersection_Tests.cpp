#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <vector>

#include "sfz/geometry/Intersection.hpp"
#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/OBB.hpp"

TEST_CASE("AABB & AABB test", "[sfz::Intersection]")
{
	using namespace sfz;

	AABB boxMid{vec3f{-1.0f, -1.0f, -1.0f}, vec3f{1.0f, 1.0f, 1.0f}};
	AABB boxMidSmall{vec3f{-0.5f, -0.5f, -0.5f}, vec3f{0.5f, 0.5f, 0.5f}};

	AABB boxFrontSmall{vec3f{-0.5f, -0.5f, 0.75f}, vec3f{0.5f, 0.5f, 1.75f}};
	AABB boxBackSmall{vec3f{-0.5f, -0.5f, -1.75f}, vec3f{0.5f, 0.5f, -0.75f}};

	AABB boxUpSmall{vec3f{-0.5f, 0.75f, -0.5f}, vec3f{0.5f, 1.75f, 0.5f}};
	AABB boxDownSmall{vec3f{-0.5f, -1.75f, -0.5f}, vec3f{0.5f, -0.75f, 0.5f}};

	AABB boxLeftSmall{vec3f{-1.75f, -0.5f, -0.5f}, vec3f{-0.75f, 0.5f, 0.5f}};
	AABB boxRightSMall{vec3f{0.75f, -0.5f, -0.5f}, vec3f{1.75f, 0.5f, 0.5f}};

	std::vector<AABB*> smallSurroundingBoxes;
	smallSurroundingBoxes.push_back(&boxFrontSmall);
	smallSurroundingBoxes.push_back(&boxBackSmall);
	smallSurroundingBoxes.push_back(&boxUpSmall);
	smallSurroundingBoxes.push_back(&boxDownSmall);
	smallSurroundingBoxes.push_back(&boxLeftSmall);
	smallSurroundingBoxes.push_back(&boxRightSMall);

	REQUIRE(sfz::intersects(boxMidSmall, boxMid));

	for (AABB* boxPtr : smallSurroundingBoxes) {
		REQUIRE(sfz::intersects(boxMid, *boxPtr));
	}

	for (AABB* boxPtr : smallSurroundingBoxes) {
		REQUIRE(!sfz::intersects(boxMidSmall, *boxPtr));
	}

	for (AABB* boxPtr1 : smallSurroundingBoxes) {
		for (AABB* boxPtr2 : smallSurroundingBoxes) {
			if (boxPtr1 == boxPtr2) REQUIRE(sfz::intersects(*boxPtr1, *boxPtr2));
			else REQUIRE(!sfz::intersects(*boxPtr1, *boxPtr2));
		}
	}
}