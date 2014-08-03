#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <stdexcept>
#include "sfz/math/Rectangle.hpp"

TEST_CASE("Constructors", "[sfz::Rectangle]") {
	SECTION("Copy constructor") {
		sfz::Rectangle<int> rect1{1, 2, 3, 4};
		sfz::Rectangle<int> rect2{rect1};
		REQUIRE(rect1.getPosition() == rect2.getPosition());
		REQUIRE(rect1.getDimensions() == rect2.getDimensions());
	}
	SECTION("(vec2 position, vec2 dimensions) constructor") {
		sfz::Rectangle<int> rect{sfz::vec2i{1, 2}, sfz::vec2i{3, 4}};
		REQUIRE(rect.getXPosition() == 1);
		REQUIRE(rect.getYPosition() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
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
		REQUIRE(rect.getXPosition() == 1);
		REQUIRE(rect.getYPosition() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
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
		REQUIRE(rect.getXPosition() == 1);
		REQUIRE(rect.getYPosition() == 2);
		REQUIRE(rect.getWidth() == 3);
		REQUIRE(rect.getHeight() == 4);
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

TEST_CASE("Getters", "[sfz::Rectangle]") {
	const sfz::Rectangle<int> rect1{1, 2, 3, 4};
	const sfz::Rectangle<int> rect2{4, 3, 2, 1};

	SECTION("getPosition()") {
		REQUIRE(rect1.getPosition()[0] == 1);
		REQUIRE(rect1.getPosition()[1] == 2);
		REQUIRE(rect2.getPosition()[0] == 4);
		REQUIRE(rect2.getPosition()[1] == 3);
	}
	SECTION("getXPosition() & getYPosition()") {
		REQUIRE(rect1.getXPosition() == 1);
		REQUIRE(rect1.getYPosition() == 2);
		REQUIRE(rect2.getXPosition() == 4);
		REQUIRE(rect2.getYPosition() == 3);
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
}

TEST_CASE("Setters", "[sfz::Rectangle]") {
	sfz::Rectangle<int> rect{0, 0, 0, 0};

	SECTION("setPosition(vec2)") {
		rect.setPosition(sfz::vec2i{-1, 3});
		REQUIRE(rect.getXPosition() == -1);
		REQUIRE(rect.getYPosition() == 3);
		REQUIRE(rect.getWidth() == 0);
		REQUIRE(rect.getHeight() == 0);
	}
	SECTION("setPosition(x,y)") {
		rect.setPosition(9, 1);
		REQUIRE(rect.getXPosition() == 9);
		REQUIRE(rect.getYPosition() == 1);
		REQUIRE(rect.getWidth() == 0);
		REQUIRE(rect.getHeight() == 0);
	}
	SECTION("setXPosition() & setYPosition()") {
		rect.setXPosition(44);
		rect.setYPosition(-220);
		REQUIRE(rect.getXPosition() == 44);
		REQUIRE(rect.getYPosition() == -220);
		REQUIRE(rect.getWidth() == 0);
		REQUIRE(rect.getHeight() == 0);
	}
	SECTION("setDimensions(vec2)") {
		rect.setDimensions(sfz::vec2i{4, 2});
		REQUIRE(rect.getXPosition() == 0);
		REQUIRE(rect.getYPosition() == 0);
		REQUIRE(rect.getWidth() == 4);
		REQUIRE(rect.getHeight() == 2);
		REQUIRE_THROWS_AS(rect.setDimensions(sfz::vec2i{-1, 0}), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setDimensions(sfz::vec2i{0, -1}), std::invalid_argument);
	}
	SECTION("setDimensions(x,y)") {
		rect.setDimensions(42, 21);
		REQUIRE(rect.getXPosition() == 0);
		REQUIRE(rect.getYPosition() == 0);
		REQUIRE(rect.getWidth() == 42);
		REQUIRE(rect.getHeight() == 21);
		REQUIRE_THROWS_AS(rect.setDimensions(-1, 0), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setDimensions(0, -1), std::invalid_argument);
	}
	SECTION("setWidth() & setHeight()") {
		rect.setWidth(5);
		rect.setHeight(55);
		REQUIRE(rect.getXPosition() == 0);
		REQUIRE(rect.getYPosition() == 0);
		REQUIRE(rect.getWidth() == 5);
		REQUIRE(rect.getHeight() == 55);
		REQUIRE_THROWS_AS(rect.setWidth(-1), std::invalid_argument);
		REQUIRE_THROWS_AS(rect.setHeight(-2), std::invalid_argument);
	}
}