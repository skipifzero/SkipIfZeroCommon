#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <vector>

#include "sfz/Geometry.hpp"

TEST_CASE("Point inside AABB test", "[sfz::Intersection]")
{
	using namespace sfz;

	AABB box{vec3f{-1,-1,-1}, vec3f{1,1,1}};

	REQUIRE(inside(box, vec3f{0,0,0}));
	REQUIRE(!inside(box, vec3f{-2,0,0}));
}

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

	REQUIRE(intersects(boxMidSmall, boxMid));

	for (AABB* boxPtr : smallSurroundingBoxes) {
		REQUIRE(intersects(boxMid, *boxPtr));
	}

	for (AABB* boxPtr : smallSurroundingBoxes) {
		REQUIRE(!intersects(boxMidSmall, *boxPtr));
	}

	for (AABB* boxPtr1 : smallSurroundingBoxes) {
		for (AABB* boxPtr2 : smallSurroundingBoxes) {
			if (boxPtr1 == boxPtr2) REQUIRE(intersects(*boxPtr1, *boxPtr2));
			else REQUIRE(!intersects(*boxPtr1, *boxPtr2));
		}
	}
}

TEST_CASE("Sphere & Sphere test", "[sfz::Intersection]")
{
	using namespace sfz;

	Sphere mid{vec3f{0.0f, 0.0f, 0.0f}, 0.5f};
	Sphere midBig{vec3f{0.0f, 0.0f, 0.0f}, 1.0f};
	Sphere aBitOff{vec3f{-1.1f, 0.0f, 0.0f}, 0.5f};

	REQUIRE(intersects(mid, midBig));
	REQUIRE(intersects(midBig, aBitOff));
	REQUIRE(!intersects(mid, aBitOff));
}