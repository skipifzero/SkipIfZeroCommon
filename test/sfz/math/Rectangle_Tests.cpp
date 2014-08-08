#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <stdexcept>
#include <vector>
#include "sfz/math/Vector.hpp"
#include "sfz/math/Rectangle.hpp"
#include "sfz/math/Circle.hpp"

TEST_CASE("Constructors", "[sfz::Rectangle]") {
	SECTION("Copy constructor") {
		sfz::Rectangle<int> rect1{1, 2, 3, 4, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::TOP};
		sfz::Rectangle<int> rect2{rect1};
		REQUIRE(rect1.getPosition() == rect2.getPosition());
		REQUIRE(rect1.getDimensions() == rect2.getDimensions());
		REQUIRE(rect1.getHorizontalAlign() == rect2.getHorizontalAlign());
		REQUIRE(rect1.getVerticalAlign() == rect2.getVerticalAlign());
	}
	SECTION("(vec2 position, vec2 dimensions) constructor") {
		sfz::Rectangle<int> rect{sfz::vec2i{1, 2}, sfz::vec2i{3, 4}};
		REQUIRE(rect.getX() == 1);
		REQUIRE(rect.getY() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
		REQUIRE(rect.getHorizontalAlign() == sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.getVerticalAlign() == sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN);
		try {
			sfz::Rectangle<int>{sfz::vec2i{0, 0}, sfz::vec2i{-1, 0}};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
		try {
			sfz::Rectangle<int>{sfz::vec2i{0, 0}, sfz::vec2i{0, -1}};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
	}
	SECTION("(vec2 position, width, height) constructor") {
		sfz::Rectangle<int> rect{sfz::vec2i{1, 2}, 3, 4};
		REQUIRE(rect.getX() == 1);
		REQUIRE(rect.getY() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
		REQUIRE(rect.getHorizontalAlign() == sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.getVerticalAlign() == sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN);
		try {
			sfz::Rectangle<int>{sfz::vec2i{0, 0}, -1, 0};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
		try {
			sfz::Rectangle<int>{sfz::vec2i{0, 0}, 0, -1};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
	}
	SECTION("(x, y, width, height) constructor") {
		sfz::Rectangle<int> rect{1, 2, 3, 4};
		REQUIRE(rect.getX() == 1);
		REQUIRE(rect.getY() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
		REQUIRE(rect.getHorizontalAlign() == sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.getVerticalAlign() == sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN);
		try {
			sfz::Rectangle<int>{0, 0, -1, 0};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
		try {
			sfz::Rectangle<int>{0, 0, 0, -1};
			REQUIRE(false);
		} catch (std::invalid_argument e) {
			REQUIRE(true);
		}
	}
}

TEST_CASE("Overlap tests", "[sfz::Rectangle]") {
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
		overlappingRects.emplace_back(0, 0, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(0, 1, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(1, 0, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
		overlappingRects.emplace_back(1, 1, 1, 1, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM);
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

TEST_CASE("Getters", "[sfz::Rectangle]") {
	const sfz::Rectangle<int> rect1{1, 2, 3, 4, sfz::HorizontalAlign::LEFT, sfz::VerticalAlign::BOTTOM};
	const sfz::Rectangle<int> rect2{4, 3, 2, 1};

	SECTION("getPosition()") {
		REQUIRE(rect1.getPosition()[0] == 1);
		REQUIRE(rect1.getPosition()[1] == 2);
		REQUIRE(rect2.getPosition()[0] == 4);
		REQUIRE(rect2.getPosition()[1] == 3);
	}
	SECTION("getX() & getY()") {
		REQUIRE(rect1.getX() == 1);
		REQUIRE(rect1.getY() == 2);
		REQUIRE(rect2.getX() == 4);
		REQUIRE(rect2.getY() == 3);
	}
	SECTION("getDimensions()") {
		REQUIRE(rect1.getDimensions()[0] == 3);
		REQUIRE(rect1.getDimensions()[1] == 4);
		REQUIRE(rect2.getDimensions()[0] == 2);
		REQUIRE(rect2.getDimensions()[1] == 1);
	}
	SECTION("getWidth() & getHeight()") {
		REQUIRE(rect1.getWidth() == 3);
		REQUIRE(rect1.getHeight() == 4);
		REQUIRE(rect2.getWidth() == 2);
		REQUIRE(rect2.getHeight() == 1);
	}
	SECTION("getHorizontalAlign() & getVerticalAlign()") {
		REQUIRE(rect1.getHorizontalAlign() == sfz::HorizontalAlign::LEFT);
		REQUIRE(rect1.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
		REQUIRE(rect2.getHorizontalAlign() == sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect2.getVerticalAlign() == sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN);
	}
}

TEST_CASE("Setters", "[sfz::Rectangle]") {
	sfz::Rectangle<int> rect{0, 0, 2, 2};

	SECTION("setPosition(vec2)") {
		rect.setPosition(sfz::vec2i{-1, 3});
		REQUIRE(rect.getX() == -1);
		REQUIRE(rect.getY() == 3);
		REQUIRE(rect.getWidth() == 2);
		REQUIRE(rect.getHeight() == 2);
	}
	SECTION("setPosition(x,y)") {
		rect.setPosition(9, 1);
		REQUIRE(rect.getX() == 9);
		REQUIRE(rect.getY() == 1);
		REQUIRE(rect.getWidth() == 2);
		REQUIRE(rect.getHeight() == 2);
	}
	SECTION("setX() & setY()") {
		rect.setX(44);
		rect.setY(-220);
		REQUIRE(rect.getX() == 44);
		REQUIRE(rect.getY() == -220);
		REQUIRE(rect.getWidth() == 2);
		REQUIRE(rect.getHeight() == 2);
	}
	SECTION("setDimensions(vec2)") {
		rect.setDimensions(sfz::vec2i{4, 2});
		REQUIRE(rect.getX() == 0);
		REQUIRE(rect.getY() == 0);
		REQUIRE(rect.getWidth() == 4);
		REQUIRE(rect.getHeight() == 2);
		REQUIRE_THROWS_AS(rect.setDimensions(sfz::vec2i{-1, 0}), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setDimensions(sfz::vec2i{0, -1}), std::invalid_argument);
	}
	SECTION("setDimensions(x,y)") {
		rect.setDimensions(42, 21);
		REQUIRE(rect.getX() == 0);
		REQUIRE(rect.getY() == 0);
		REQUIRE(rect.getWidth() == 42);
		REQUIRE(rect.getHeight() == 21);
		REQUIRE_THROWS_AS(rect.setDimensions(-1, 0), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setDimensions(0, -1), std::invalid_argument);
	}
	SECTION("setWidth() & setHeight()") {
		rect.setWidth(5);
		rect.setHeight(55);
		REQUIRE(rect.getX() == 0);
		REQUIRE(rect.getY() == 0);
		REQUIRE(rect.getWidth() == 5);
		REQUIRE(rect.getHeight() == 55);
		REQUIRE_THROWS_AS(rect.setWidth(-1), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setHeight(-2), std::invalid_argument);
	}
	SECTION("setHorizontalAlign() & setVerticalAlign()") {
		REQUIRE(rect.getHorizontalAlign() == sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN);
		REQUIRE(rect.getVerticalAlign() == sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN);
		rect.setHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		rect.setVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(rect.getHorizontalAlign() == sfz::HorizontalAlign::RIGHT);
		REQUIRE(rect.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
	}
	SECTION("changeHorizontalAlign()") {
		REQUIRE(sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		rect.changeHorizontalAlign(sfz::HorizontalAlign::LEFT);
		REQUIRE(rect.getX() == -1);
		REQUIRE(rect.getHorizontalAlign() == sfz::HorizontalAlign::LEFT);
		rect.changeHorizontalAlign(sfz::HorizontalAlign::RIGHT);
		REQUIRE(rect.getX() == 1);
		REQUIRE(rect.getHorizontalAlign() == sfz::HorizontalAlign::RIGHT);
		rect.changeHorizontalAlign(sfz::HorizontalAlign::CENTER);
		REQUIRE(rect.getX() == 0);
		REQUIRE(rect.getHorizontalAlign() == sfz::HorizontalAlign::CENTER);
	}
	SECTION("changeVerticalAlign()") {
		REQUIRE(sfz::Rectangle<int>::DEFAULT_HORIZONTAL_ALIGN == sfz::HorizontalAlign::CENTER);
		REQUIRE(sfz::Rectangle<int>::DEFAULT_VERTICAL_ALIGN == sfz::VerticalAlign::MIDDLE);

		rect.changeVerticalAlign(sfz::VerticalAlign::TOP);
		REQUIRE(rect.getY() == 1);
		REQUIRE(rect.getVerticalAlign() == sfz::VerticalAlign::TOP);
		rect.changeVerticalAlign(sfz::VerticalAlign::BOTTOM);
		REQUIRE(rect.getY() == -1);
		REQUIRE(rect.getVerticalAlign() == sfz::VerticalAlign::BOTTOM);
		rect.changeVerticalAlign(sfz::VerticalAlign::MIDDLE);
		REQUIRE(rect.getY() == 0);
		REQUIRE(rect.getVerticalAlign() == sfz::VerticalAlign::MIDDLE);
	}
}