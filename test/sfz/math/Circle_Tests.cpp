#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <unordered_map>
#include <type_traits>
#include "sfz/math/Circle.hpp"

TEST_CASE("Constructors", "[sfz::Circle]")
{
	SECTION("Copy constructor") {
		sfz::Circle<int> circ1{1, 2, 3, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
		sfz::Circle<int> circ2{circ1};
		REQUIRE(circ1.mPos == circ2.mPos);
		REQUIRE(circ1.mRadius == circ2.mRadius);
		REQUIRE(circ1.mHorizontalAlign == circ2.mHorizontalAlign);
		REQUIRE(circ1.mVerticalAlign == circ2.mVerticalAlign);
	}
	SECTION("Copy cast constructor") {
		sfz::Circle<float> circlef{1.1f, 2.2f, 3.3f};
		sfz::Circle<int> circlei{circlef};
		REQUIRE(circlei.x() == 1);
		REQUIRE(circlei.y() == 2);
		REQUIRE(circlei.mRadius == 3);
		REQUIRE(circlei.mHorizontalAlign == circlef.mHorizontalAlign);
		REQUIRE(circlei.mVerticalAlign == circlef.mVerticalAlign);
	}
	SECTION("Copy constructor with alignment change") {
		sfz::Circle<int> circ1{0, 0, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
		sfz::Circle<int> circ2{circ1, sfz::HorizontalAlign::RIGHT, sfz::VerticalAlign::TOP};
		REQUIRE(circ2.x() == 2);
		REQUIRE(circ2.y() == 2);
		REQUIRE(circ2.mRadius == circ1.mRadius);
		REQUIRE(circ2.mHorizontalAlign == sfz::HorizontalAlign::RIGHT);
		REQUIRE(circ2.mVerticalAlign == sfz::VerticalAlign::TOP);
	}
	SECTION("(vec2, radius) constructor") {
		sfz::Circle<int> circ{sfz::vec2i{-1, 2}, 2};
		REQUIRE(circ.x() == -1);
		REQUIRE(circ.y() == 2);
		REQUIRE(circ.mRadius == 2);
		REQUIRE(circ.mHorizontalAlign == sfz::Circle<int>::s_DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.mVerticalAlign == sfz::Circle<int>::s_DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("(x, y, radius) constructor") {
		sfz::Circle<int> circ{-1, 2, 2};
		REQUIRE(circ.x() == -1);
		REQUIRE(circ.y() == 2);
		REQUIRE(circ.mRadius == 2);
		REQUIRE(circ.mHorizontalAlign == sfz::Circle<int>::s_DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.mVerticalAlign == sfz::Circle<int>::s_DEFAULT_VERTICAL_ALIGN);
	}
}

TEST_CASE("Overlap tests", "[sfz::Circle]")
{
	sfz::Circle<int> circ{1, 1, 1};

	SECTION("overlap(vec2)") {
		std::vector<sfz::vec2i> insideVecs;
		insideVecs.push_back({1, 0});
		insideVecs.push_back({0, 1});
		insideVecs.push_back({1, 1});
		insideVecs.push_back({2, 1});
		insideVecs.push_back({1, 2});

		std::vector<sfz::vec2i> outsideVecs;
		outsideVecs.push_back({-1, -1});
		outsideVecs.push_back({-1, 0});
		outsideVecs.push_back({-1, 1});
		outsideVecs.push_back({-1, 2});
		outsideVecs.push_back({-1, 3});
		outsideVecs.push_back({0, -1});
		outsideVecs.push_back({0, 3});
		outsideVecs.push_back({1, -1});
		outsideVecs.push_back({1, 3});
		outsideVecs.push_back({2, -1});
		outsideVecs.push_back({2, 3});
		outsideVecs.push_back({3, -1});
		outsideVecs.push_back({3, 0});
		outsideVecs.push_back({3, 1});
		outsideVecs.push_back({3, 2});
		outsideVecs.push_back({3, 3});
		outsideVecs.push_back({0, 0});
		outsideVecs.push_back({2, 0});
		outsideVecs.push_back({0, 2});
		outsideVecs.push_back({2, 2});

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				circ.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				circ.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& inVec : insideVecs) {
					REQUIRE(circ.overlap(inVec));
				}
				for(auto& outVec : outsideVecs) {
					REQUIRE(!circ.overlap(outVec));
				}
			}
		}
	}
	SECTION("overlap(Circle)") {
		std::vector<sfz::Circle<int>> overlappingCircles;
		overlappingCircles.emplace_back(1, 1, 1);
		overlappingCircles.emplace_back(0, 0, 1);
		overlappingCircles.emplace_back(1, 0, 1);
		overlappingCircles.emplace_back(2, 0, 1);
		overlappingCircles.emplace_back(0, 1, 1);
		overlappingCircles.emplace_back(2, 1, 1);
		overlappingCircles.emplace_back(0, 2, 1);
		overlappingCircles.emplace_back(2, 2, 1);

		std::vector<sfz::Circle<int>> nonOverlappingCircles;
		nonOverlappingCircles.emplace_back(-2, 1, 1);
		nonOverlappingCircles.emplace_back(4, 1, 1);
		nonOverlappingCircles.emplace_back(1, -2, 1);
		nonOverlappingCircles.emplace_back(1, 4, 1);

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				circ.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				circ.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& overCircle : overlappingCircles) {
					REQUIRE(circ.overlap(overCircle));
					REQUIRE(overCircle.overlap(circ));
				}
				for(auto& nonOverCircle : nonOverlappingCircles) {
					REQUIRE(!circ.overlap(nonOverCircle));
					REQUIRE(!nonOverCircle.overlap(circ));
				}
			}
		}
	}
	SECTION("overlap(Rectangle)") {
		std::vector<sfz::Rectangle<int>> overlapping;
		overlapping.emplace_back(1, 1, 2, 2);
		overlapping.emplace_back(0, 0, 1, 1, sfz::HorizontalAlign::LEFT,
		                                     sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(0, 1, 1, 1, sfz::HorizontalAlign::LEFT,
		                                     sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(1, 0, 1, 1, sfz::HorizontalAlign::LEFT,
		                                     sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(1, 1, 1, 1, sfz::HorizontalAlign::LEFT,
		                                     sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(1, 1, 8, 8);

		std::vector<sfz::Rectangle<int>> nonOverlapping;
		nonOverlapping.emplace_back(-2, -2, 2, 2);
		nonOverlapping.emplace_back(4, 4, 2, 2);
		nonOverlapping.emplace_back(-2, 4, 2, 2);
		nonOverlapping.emplace_back(4, -2, 2, 2);
		nonOverlapping.emplace_back(-2, 1, 2, 2);
		nonOverlapping.emplace_back(4, 1, 2, 2);
		nonOverlapping.emplace_back(1, 4, 2, 2);
		nonOverlapping.emplace_back(1, -4, 2, 2);

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				circ.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				circ.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& rect: overlapping) {
					REQUIRE(circ.overlap(rect));
					REQUIRE(rect.overlap(circ));
				}
				for(auto& rect : nonOverlapping) {
					REQUIRE(!circ.overlap(rect));
					REQUIRE(!rect.overlap(circ));
				}
			}
		}
	}
}

TEST_CASE("Setters", "[sfz::Circle]") {
	sfz::Circle<int> circ{0, 0, 2};
	SECTION("changeHorizontalAlign()") {
		REQUIRE(sfz::Circle<int>::s_DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Circle<int>::s_DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		circ.changeHorizontalAlign(sfz::HorizontalAlign::LEFT);
		REQUIRE(circ.x() == -2);
		REQUIRE(circ.mHorizontalAlign == sfz::HorizontalAlign::LEFT);
		circ.changeHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		REQUIRE(circ.x() == 2);
		REQUIRE(circ.mHorizontalAlign == sfz::HorizontalAlign::RIGHT);
		circ.changeHorizontalAlign(sfz::HorizontalAlign::CENTER);
		REQUIRE(circ.x() == 0);
		REQUIRE(circ.mHorizontalAlign == sfz::HorizontalAlign::CENTER);
	}
	SECTION("changeVerticalAlign()") {
		REQUIRE(sfz::Circle<int>::s_DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Circle<int>::s_DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		circ.changeVerticalAlign(sfz::VerticalAlign::TOP);
		REQUIRE(circ.y() == 2);
		REQUIRE(circ.mVerticalAlign == sfz::VerticalAlign::TOP);
		circ.changeVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(circ.y() == -2);
		REQUIRE(circ.mVerticalAlign == sfz::VerticalAlign::BOTTOM);
		circ.changeVerticalAlign(sfz::VerticalAlign::MIDDLE);
		REQUIRE(circ.y() == 0);
		REQUIRE(circ.mVerticalAlign == sfz::VerticalAlign::MIDDLE);
	}
}

TEST_CASE("Area and circumference", "[sfz::Circle]")
{
	sfz::Circle<int> r1{0, 0, 10};
	sfz::Circle<int> r2{0, 0, 1};
	SECTION("area()") {
		REQUIRE(r1.area() == 300);
		REQUIRE(r2.area() == 3);
	}
	SECTION("circumference()") {
		REQUIRE(r1.circumference() == 60);
		REQUIRE(r2.circumference() == 6);
	}
}

TEST_CASE("Comparison operators", "[sfz::Circle]")
{
	sfz::Circle<int> r1{0, 0, 10};
	sfz::Circle<int> r2{0, 0, 10};
	sfz::Circle<int> r3{0, 0, 1};
	sfz::Circle<int> r4{0, 0, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};

	SECTION("==") {
		REQUIRE(r1 == r2);
		REQUIRE(!(r1 == r3));
		REQUIRE(!(r1 == r4));
		REQUIRE(!(r2 == r3));
		REQUIRE(!(r2 == r4));
		REQUIRE(!(r3 == r4));
	}
	SECTION("!=") {
		REQUIRE(!(r1 != r2));
		REQUIRE(r1 != r3);
		REQUIRE(r1 != r4);
		REQUIRE(r2 != r3);
		REQUIRE(r2 != r4);
		REQUIRE(r3 != r4);
	}
	SECTION("<") {
		REQUIRE(!(r1 < r2));
		REQUIRE(!(r3 < r4));
		REQUIRE(r3 < r1);
		REQUIRE(!(r1 < r3));
	}
	SECTION(">") {
		REQUIRE(!(r1 > r2));
		REQUIRE(!(r3 > r4));
		REQUIRE(r1 > r3);
		REQUIRE(!(r3 > r1));
	}
	SECTION("<=") {
		REQUIRE(r1 <= r2);
		REQUIRE(r3 <= r4);
		REQUIRE(r3 <= r1);
		REQUIRE(!(r1 <= r3));
	}
	SECTION(">=") {
		REQUIRE(r1 >= r2);
		REQUIRE(r3 >= r4);
		REQUIRE(r1 >= r3);
		REQUIRE(!(r3 >= r1));
	}
}

TEST_CASE("Hashing", "[sfz::Circle]")
{
	sfz::Circle<int> r1{-1, 100, 32};
	sfz::Circle<int> r2{-1, 100, 32, sfz::HorizontalAlign::RIGHT, sfz::VerticalAlign::TOP};
	sfz::Circle<int> r3{0, -9, 2};
	
	SECTION("Hash functions") {
		REQUIRE(r1.hash() != r2.hash());
		REQUIRE(r2.hash() != r3.hash());
	}
	SECTION("Hash map") {
		// This test checks if unordered_map works as it should. Not a very good test, but the best
		// I can come up with to test if hashing works as it should at the moment.
		std::unordered_map<sfz::Circle<int>, int> hashMap;
		hashMap[r1] = 1;
		hashMap[r2] = 2;
		hashMap[r3] = 3;
		REQUIRE(hashMap[r1] == 1);
		REQUIRE(hashMap[r2] == 2);
		REQUIRE(hashMap[r3] == 3);
	}
}

TEST_CASE("to_string()", "[sfz::Circle]")
{
	sfz::Circle<int> c{1, 2, 3, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::TOP};
	REQUIRE(c.to_string() == "[pos=[1, 2], r=3, align: LEFT, TOP]");
}

TEST_CASE("Is proper POD", "[sfz::Circle]")
{
	REQUIRE(std::is_trivially_default_constructible<sfz::circf>::value);
	REQUIRE(std::is_trivially_default_constructible<sfz::circd>::value);
	REQUIRE(std::is_trivially_default_constructible<sfz::circi>::value);
	REQUIRE(std::is_trivially_default_constructible<sfz::circl>::value);

	REQUIRE(std::is_trivially_copyable<sfz::circf>::value);
	REQUIRE(std::is_trivially_copyable<sfz::circd>::value);
	REQUIRE(std::is_trivially_copyable<sfz::circi>::value);
	REQUIRE(std::is_trivially_copyable<sfz::circl>::value);

	REQUIRE(std::is_trivial<sfz::circf>::value);
	REQUIRE(std::is_trivial<sfz::circd>::value);
	REQUIRE(std::is_trivial<sfz::circi>::value);
	REQUIRE(std::is_trivial<sfz::circl>::value);

	REQUIRE(std::is_standard_layout<sfz::circf>::value);
	REQUIRE(std::is_standard_layout<sfz::circd>::value);
	REQUIRE(std::is_standard_layout<sfz::circi>::value);
	REQUIRE(std::is_standard_layout<sfz::circl>::value);

	REQUIRE(std::is_pod<sfz::circf>::value);
	REQUIRE(std::is_pod<sfz::circd>::value);
	REQUIRE(std::is_pod<sfz::circi>::value);
	REQUIRE(std::is_pod<sfz::circl>::value);
}