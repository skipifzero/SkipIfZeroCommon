#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <unordered_map>
#include "sfz/math/Rectangle.hpp"

TEST_CASE("Constructors", "[sfz::Rectangle]")
{
	SECTION("Copy constructor") {
		sfz::Rectangle<int> rect1{1, 2, 3, 4, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::TOP};
		sfz::Rectangle<int> rect2{rect1};
		REQUIRE(rect1.mPos == rect2.mPos);
		REQUIRE(rect1.mDimensions == rect2.mDimensions);
		REQUIRE(rect1.mHorizontalAlign == rect2.mHorizontalAlign);
		REQUIRE(rect1.mVerticalAlign == rect2.mVerticalAlign);
	}
	SECTION("Copy cast constructor") {
		sfz::Rectangle<float> rectf{1.1f, 2.2f, 3.3f, 4.4f};
		sfz::Rectangle<int> recti{rectf};
		REQUIRE(recti.x() == 1);
		REQUIRE(recti.y() == 2);
		REQUIRE(recti.width() == 3);
		REQUIRE(recti.height() == 4);
		REQUIRE(recti.mHorizontalAlign == rectf.mHorizontalAlign);
		REQUIRE(recti.mVerticalAlign == rectf.mVerticalAlign);
	}
	SECTION("Copy constructor with alignment change") {
		sfz::Rectangle<int> rect1{0, 0, 2, 2, sfz::HorizontalAlign::LEFT,
		                                      sfz::VerticalAlign::BOTTOM};
		sfz::Rectangle<int> rect2{rect1, sfz::HorizontalAlign::RIGHT, sfz::VerticalAlign::TOP};
		REQUIRE(rect2.x() == 2);
		REQUIRE(rect2.y() == 2);
		REQUIRE(rect2.mDimensions == rect1.mDimensions);
		REQUIRE(rect2.mHorizontalAlign == sfz::HorizontalAlign::RIGHT);
		REQUIRE(rect2.mVerticalAlign == sfz::VerticalAlign::TOP);
	}
	SECTION("(vec2 position, vec2 dimensions) constructor") {
		sfz::Rectangle<int> rect{sfz::vec2i{1, 2}, sfz::vec2i{3, 4}};
		REQUIRE(rect.x() == 1);
		REQUIRE(rect.y() == 2);
		REQUIRE(rect.width() == 3);
		REQUIRE(rect.height() == 4);
		REQUIRE(rect.mHorizontalAlign == sfz::Rectangle<int>::s_DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.mVerticalAlign == sfz::Rectangle<int>::s_DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("(vec2 position, width, height) constructor") {
		sfz::Rectangle<int> rect{sfz::vec2i{1, 2}, 3, 4};
		REQUIRE(rect.x() == 1);
		REQUIRE(rect.y() == 2);
		REQUIRE(rect.width() == 3);
		REQUIRE(rect.height() == 4);
		REQUIRE(rect.mHorizontalAlign == sfz::Rectangle<int>::s_DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.mVerticalAlign == sfz::Rectangle<int>::s_DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("(x, y, width, height) constructor") {
		sfz::Rectangle<int> rect{1, 2, 3, 4};
		REQUIRE(rect.x() == 1);
		REQUIRE(rect.y() == 2);
		REQUIRE(rect.width() == 3);
		REQUIRE(rect.height() == 4);
		REQUIRE(rect.mHorizontalAlign == sfz::Rectangle<int>::s_DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.mVerticalAlign == sfz::Rectangle<int>::s_DEFAULT_VERTICAL_ALIGN);
	}
}

TEST_CASE("Overlap tests", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> rect{0, 0, 2, 2, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
	
	SECTION("overlap(vec2)") {
		std::vector<sfz::vec2i> insideVecs;
		insideVecs.push_back({0, 0});
		insideVecs.push_back({1, 0});
		insideVecs.push_back({2, 0});
		insideVecs.push_back({0, 1});
		insideVecs.push_back({1, 1});
		insideVecs.push_back({2, 1});
		insideVecs.push_back({0, 2});
		insideVecs.push_back({1, 2});
		insideVecs.push_back({2, 2});

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

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				rect.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				rect.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& inVec : insideVecs) {
					REQUIRE(rect.overlap(inVec));
				}
				for(auto& outVec : outsideVecs) {
					REQUIRE(!rect.overlap(outVec));
				}
			}
		}
	}
	SECTION("overlap(Rectangle)") {
		std::vector<sfz::Rectangle<int>> overlappingRects;
		overlappingRects.emplace_back(1, 1, 2, 2);
		overlappingRects.emplace_back(0, 0, 1, 1, sfz::HorizontalAlign::LEFT,
		                                          sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(0, 1, 1, 1, sfz::HorizontalAlign::LEFT,
		                                          sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(1, 0, 1, 1, sfz::HorizontalAlign::LEFT,
		                                          sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(1, 1, 1, 1, sfz::HorizontalAlign::LEFT,
		                                          sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(1, 1, 8, 8);

		std::vector<sfz::Rectangle<int>> nonOverlappingRects;
		nonOverlappingRects.emplace_back(-2, -2, 2, 2);
		nonOverlappingRects.emplace_back(4, 4, 2, 2);
		nonOverlappingRects.emplace_back(-2, 4, 2, 2);
		nonOverlappingRects.emplace_back(4, -2, 2, 2);
		nonOverlappingRects.emplace_back(-2, 1, 2, 2);
		nonOverlappingRects.emplace_back(4, 1, 2, 2);
		nonOverlappingRects.emplace_back(1, 4, 2, 2);
		nonOverlappingRects.emplace_back(1, -4, 2, 2);

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				rect.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				rect.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& tempRect : overlappingRects) {
					REQUIRE(rect.overlap(tempRect));
					REQUIRE(tempRect.overlap(rect));
				}
				for(auto& tempRect : nonOverlappingRects) {
					REQUIRE(!rect.overlap(tempRect));
					REQUIRE(!tempRect.overlap(rect));
				}
			}
		}
	}
	SECTION("overlap(Circle)") {
		std::vector<sfz::Circle<int>> overlapping;
		overlapping.emplace_back(1, 1, 10);
		overlapping.emplace_back(0, 0, 1);
		overlapping.emplace_back(1, 0, 1);
		overlapping.emplace_back(2, 0, 1);
		overlapping.emplace_back(0, 1, 1);
		overlapping.emplace_back(1, 1, 1);
		overlapping.emplace_back(2, 1, 1);
		overlapping.emplace_back(0, 2, 1);
		overlapping.emplace_back(1, 2, 1);
		overlapping.emplace_back(2, 2, 1);

		std::vector<sfz::Circle<int>> nonOverlapping;
		nonOverlapping.emplace_back(-2, 1, 1);
		nonOverlapping.emplace_back(4, 1, 1);
		nonOverlapping.emplace_back(1, -2, 1);
		nonOverlapping.emplace_back(1, 4, 1);

		for(char horAlignChar = -1; horAlignChar <= 1; horAlignChar++) {
			for(char verAlignChar = -1; verAlignChar <= 1; verAlignChar++) {
				rect.changeHorizontalAlign(static_cast<sfz::HorizontalAlign>(horAlignChar));
				rect.changeVerticalAlign(static_cast<sfz::VerticalAlign>(verAlignChar));

				for(auto& tempCirc : overlapping) {
					REQUIRE(rect.overlap(tempCirc));
					REQUIRE(tempCirc.overlap(rect));
				}
				for(auto& tempCirc : nonOverlapping) {
					REQUIRE(!rect.overlap(tempCirc));
					REQUIRE(!tempCirc.overlap(rect));
				}
			}
		}
	}
}

TEST_CASE("Getters", "[sfz::Rectangle]")
{
	const sfz::Rectangle<int> rect1{1, 2, 3, 4, sfz::HorizontalAlign::LEFT,
	                                            sfz::VerticalAlign::BOTTOM};
	const sfz::Rectangle<int> rect2{4, 3, 2, 1};

	SECTION("x() & y()") {
		REQUIRE(rect1.x() == 1);
		REQUIRE(rect1.y() == 2);
		REQUIRE(rect2.x() == 4);
		REQUIRE(rect2.y() == 3);
	}
	SECTION("width() & height()") {
		REQUIRE(rect1.width() == 3);
		REQUIRE(rect1.height() == 4);
		REQUIRE(rect2.width() == 2);
		REQUIRE(rect2.height() == 1);
	}
}

TEST_CASE("Setters", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> rect{0, 0, 2, 2};

	SECTION("changeHorizontalAlign()") {
		REQUIRE(sfz::Rectangle<int>::s_DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Rectangle<int>::s_DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		rect.changeHorizontalAlign(sfz::HorizontalAlign::LEFT);
		REQUIRE(rect.x() == -1);
		REQUIRE(rect.mHorizontalAlign == sfz::HorizontalAlign::LEFT);
		rect.changeHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		REQUIRE(rect.x() == 1);
		REQUIRE(rect.mHorizontalAlign == sfz::HorizontalAlign::RIGHT);
		rect.changeHorizontalAlign(sfz::HorizontalAlign::CENTER);
		REQUIRE(rect.x() == 0);
		REQUIRE(rect.mHorizontalAlign == sfz::HorizontalAlign::CENTER);
	}
	SECTION("changeVerticalAlign()") {
		REQUIRE(sfz::Rectangle<int>::s_DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Rectangle<int>::s_DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		rect.changeVerticalAlign(sfz::VerticalAlign::TOP);
		REQUIRE(rect.y() == 1);
		REQUIRE(rect.mVerticalAlign == sfz::VerticalAlign::TOP);
		rect.changeVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(rect.y() == -1);
		REQUIRE(rect.mVerticalAlign == sfz::VerticalAlign::BOTTOM);
		rect.changeVerticalAlign(sfz::VerticalAlign::MIDDLE);
		REQUIRE(rect.y() == 0);
		REQUIRE(rect.mVerticalAlign == sfz::VerticalAlign::MIDDLE);
	}
}

TEST_CASE("Area and circumference", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> r1{0, 0, 10, 10};
	sfz::Rectangle<int> r2{0, 0, 1, 10};
	SECTION("area()") {
		REQUIRE(r1.area() == 100);
		REQUIRE(r2.area() == 10);
	}
	SECTION("circumference()") {
		REQUIRE(r1.circumference() == 40);
		REQUIRE(r2.circumference() == 22);
	}
}

TEST_CASE("Comparison operators", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> r1{0, 0, 10, 10};
	sfz::Rectangle<int> r2{0, 0, 10, 10};
	sfz::Rectangle<int> r3{0, 0, 1, 10};
	sfz::Rectangle<int> r4{0, 0, 1, 10, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};

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

TEST_CASE("Hashing", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> r1{-1, 100, 32, 32};
	sfz::Rectangle<int> r2{-1, 100, 32, 32, sfz::HorizontalAlign::RIGHT, sfz::VerticalAlign::TOP};
	sfz::Rectangle<int> r3{0, -9, 14, 2};
	
	SECTION("Hash functions") {
		REQUIRE(r1.hash() != r2.hash());
		REQUIRE(r2.hash() != r3.hash());
	}
	SECTION("Hash map") {
		// This test checks if unordered_map works as it should. Not a very good test, but the best
		// I can come up with to test if hashing works as it should at the moment.
		std::unordered_map<sfz::Rectangle<int>, int> hashMap;
		hashMap[r1] = 1;
		hashMap[r2] = 2;
		hashMap[r3] = 3;
		REQUIRE(hashMap[r1] == 1);
		REQUIRE(hashMap[r2] == 2);
		REQUIRE(hashMap[r3] == 3);
	}
}

TEST_CASE("to_string()", "[sfz::Rectangle]")
{
	sfz::Rectangle<int> r{1, 2, 3, 4, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::TOP};
	REQUIRE(r.to_string() == "[pos=[1, 2], dim=[3, 4], align: LEFT, TOP]");
}