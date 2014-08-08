#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <stdexcept>
#include <vector>
#include "sfz/math/Circle.hpp"

TEST_CASE("Constructors", "[sfz::Circle]") {
	SECTION("Copy constructor") {
		sfz::Circle<int> circ1{1, 2, 3, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
		sfz::Circle<int> circ2{circ1};
		REQUIRE(circ1.getPosition() == circ2.getPosition());
		REQUIRE(circ1.getRadius() == circ2.getRadius());
		REQUIRE(circ1.getHorizontalAlign() == circ2.getHorizontalAlign());
		REQUIRE(circ1.getVerticalAlign() == circ2.getVerticalAlign());
	}
	SECTION("(vec2, radius) constructor") {
		sfz::Circle<int> circ{sfz::vec2i{-1, 2}, 2};
		REQUIRE(circ.getX() == -1);
		REQUIRE(circ.getY() == 2);
		REQUIRE(circ.getRadius() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
		try {
			sfz::Circle<int>{sfz::vec2i{0, 0}, -1};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
	}
	SECTION("(x, y, radius) constructor") {
		sfz::Circle<int> circ{-1, 2, 2};
		REQUIRE(circ.getX() == -1);
		REQUIRE(circ.getY() == 2);
		REQUIRE(circ.getRadius() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
		try {
			sfz::Circle<int>{0, 0, -1};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
	}
}

TEST_CASE("Overlap tests", "[sfz::Circle]") {
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
		overlapping.emplace_back(0, 0, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(0, 1, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(1, 0, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlapping.emplace_back(1, 1, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
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

TEST_CASE("Getters", "[sfz::Circle]") {
	const sfz::Circle<int> circ1{1, 2, 3, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
	const sfz::Circle<int> circ2{3, 2, 1};

	SECTION("getPosition()") {
		REQUIRE(circ1.getPosition()[0] == 1);
		REQUIRE(circ1.getPosition()[1] == 2);
		REQUIRE(circ2.getPosition()[0] == 3);
		REQUIRE(circ2.getPosition()[1] == 2);
	}
	SECTION("getX() & getY()") {
		REQUIRE(circ1.getX() == 1);
		REQUIRE(circ1.getY() == 2);
		REQUIRE(circ2.getX() == 3);
		REQUIRE(circ2.getY() == 2);
	}
	SECTION("getRadius()") {
		REQUIRE(circ1.getRadius() == 3);
		REQUIRE(circ2.getRadius() == 1);
	}
	SECTION("getHorizontalAlign() & getVerticalAlign()") {
		REQUIRE(circ1.getHorizontalAlign() == sfz::HorizontalAlign::LEFT);
		REQUIRE(circ1.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
		REQUIRE(circ2.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ2.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
	}
}

TEST_CASE("Setters", "[sfz::Circle]") {
	sfz::Circle<int> circ{0, 0, 2};

	SECTION("setPosition(vec2)") {
		circ.setPosition(sfz::vec2i{-1, 3});
		REQUIRE(circ.getX() == -1);
		REQUIRE(circ.getY() == 3);
		REQUIRE(circ.getRadius() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("setPosition(x,y)") {
		circ.setPosition(9, 1);
		REQUIRE(circ.getX() == 9);
		REQUIRE(circ.getY() == 1);
		REQUIRE(circ.getRadius() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("setX() & setY()") {
		circ.setX(44);
		circ.setY(-220);
		REQUIRE(circ.getX() == 44);
		REQUIRE(circ.getY() == -220);
		REQUIRE(circ.getRadius() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
	}
	SECTION("setRadius()") {
		circ.setRadius(5);
		REQUIRE(circ.getX() == 0);
		REQUIRE(circ.getY() == 0);
		REQUIRE(circ.getRadius() == 5);
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
		REQUIRE_THROWS_AS(circ.setRadius(-1), std::invalid_argument);
	}
	SECTION("setHorizontalAlign() & setVerticalAlign()") {
		REQUIRE(circ.getHorizontalAlign() == sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(circ.getVerticalAlign() == sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN);
		circ.setHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		circ.setVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(circ.getHorizontalAlign() == sfz::HorizontalAlign::RIGHT);
		REQUIRE(circ.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
	}
	SECTION("changeHorizontalAlign()") {
		REQUIRE(sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		circ.changeHorizontalAlign(sfz::HorizontalAlign::LEFT);
		REQUIRE(circ.getX() == -2);
		REQUIRE(circ.getHorizontalAlign() == sfz::HorizontalAlign::LEFT);
		circ.changeHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		REQUIRE(circ.getX() == 2);
		REQUIRE(circ.getHorizontalAlign() == sfz::HorizontalAlign::RIGHT);
		circ.changeHorizontalAlign(sfz::HorizontalAlign::CENTER);
		REQUIRE(circ.getX() == 0);
		REQUIRE(circ.getHorizontalAlign() == sfz::HorizontalAlign::CENTER);
	}
	SECTION("changeVerticalAlign()") {
		REQUIRE(sfz::Circle<int>::DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Circle<int>::DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		circ.changeVerticalAlign(sfz::VerticalAlign::TOP);
		REQUIRE(circ.getY() == 2);
		REQUIRE(circ.getVerticalAlign() == sfz::VerticalAlign::TOP);
		circ.changeVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(circ.getY() == -2);
		REQUIRE(circ.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
		circ.changeVerticalAlign(sfz::VerticalAlign::MIDDLE);
		REQUIRE(circ.getY() == 0);
		REQUIRE(circ.getVerticalAlign() == sfz::VerticalAlign::MIDDLE);
	}
}