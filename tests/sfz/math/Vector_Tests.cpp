#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

#include "../../../src/sfz/math/Vector.hpp"

TEST_CASE("Constructors", "[sfz::Vector]") {
	SECTION("Default constructor initializes elements to 0") {
		sfz::Vector<int, 3> vector;
		for(std::size_t i = 0; i < 3; i++) {
			REQUIRE(vector.get(i) == 0);
		}	
	}
	SECTION("Initalizer list constructor assigns correct value to elements") {
		sfz::Vector<int, 4> vector = {-2, 2, 1, 42};
		REQUIRE(vector[sfz::x] == -2);
		REQUIRE(vector[sfz::y] == 2);
		REQUIRE(vector[sfz::z] == 1);
		REQUIRE(vector[3] == 42);
	}
	SECTION("Initializer list constructor throws exception when wrongly sized") {
		bool exceptionSuccess = false;
		try {
			sfz::Vector<int, 10> vector = {-2, 1, 1};
		} catch (std::invalid_argument exc) {
			exceptionSuccess = true;
		}
		REQUIRE(exceptionSuccess);
	}
	SECTION("Copy constructor correctly copies vector") {
		sfz::Vector<int, 4> vector{sfz::Vector<int, 4>{-2, 2, 1, 42}};
		REQUIRE(vector[sfz::x] == -2);
		REQUIRE(vector[sfz::y] == 2);
		REQUIRE(vector[sfz::z] == 1);
		REQUIRE(vector[3] == 42);
	}
	SECTION("Copy cast construcotr correctly copies and casts") {
		sfz::Vector<int, 4> vector{sfz::Vector<float, 4>{-2.1f, 2.1f, 1.1f, 42.1f}};
		REQUIRE(vector[sfz::x] == -2);
		REQUIRE(vector[sfz::y] == 2);
		REQUIRE(vector[sfz::z] == 1);
		REQUIRE(vector[3] == 42);
	}
}

TEST_CASE("Assignment and accessing", "[sfz::Vector]") {
	sfz::Vector<int, 5> vector{-10, 10, 12, 13, -2};
	SECTION("Correct start values") {
		REQUIRE(vector[sfz::x] == -10);
		REQUIRE(vector.get(sfz::y) == 10);
		REQUIRE(vector[2] == 12);
		REQUIRE(vector[3] == 13);
		REQUIRE(vector[4] == -2);
	}
	SECTION("Assignment with set() function") {
		vector.set(0, 2);
		REQUIRE(vector.get(0) == 2);
		vector.set(3, -100);
		REQUIRE(vector.get(3) == -100);
	}
	SECTION("Assignment with [] operator") {
		vector[1] = 4242;
		REQUIRE(vector[1] == 4242);
		vector[4] = 54;
		REQUIRE(vector[4] == 54);
	}
	SECTION("Throws std::out_of_range when accessing invalid index") {
		REQUIRE_THROWS_AS(vector[5], std::out_of_range);
	}
}

TEST_CASE("fill", "[sfz::Vector]") {
	sfz::Vector<int,4> v;
	v.fill(4);
	for(auto e : v) {
		REQUIRE(e == 4);
	}
	v.fill(2);
	for(auto e : v) {
		REQUIRE(e == 2);
	}
}

TEST_CASE("Arithmetic operators", "[sfz::Vector]") {
	sfz::Vector<int, 3> v1{1, -2, 5};
	sfz::Vector<int, 3> v2{0, -2, 1};

	// Integrity check of base vectors
	REQUIRE(v1[sfz::x] == 1);
	REQUIRE(v1[sfz::y] == -2);
	REQUIRE(v1[sfz::z] == 5);
	REQUIRE(v2[sfz::x] == 0);
	REQUIRE(v2[sfz::y] == -2);
	REQUIRE(v2[sfz::z] == 1);

	SECTION("Addition") {
		auto v3 = v1 + v2;
		REQUIRE(v3[sfz::x] == 1);
		REQUIRE(v3[sfz::y] == -4);
		REQUIRE(v3[sfz::z] == 6);
		// Integrity check of base vectors
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -2);
		REQUIRE(v1[sfz::z] == 5);
		REQUIRE(v2[sfz::x] == 0);
		REQUIRE(v2[sfz::y] == -2);
		REQUIRE(v2[sfz::z] == 1);
	}
	SECTION("Subtraction") {
		auto v3 = v1 - v2;
		REQUIRE(v3[sfz::x] == 1);
		REQUIRE(v3[sfz::y] == 0);
		REQUIRE(v3[sfz::z] == 4);
		auto v4 = v2 - v1;
		REQUIRE(v4[sfz::x] == -1);
		REQUIRE(v4[sfz::y] == 0);
		REQUIRE(v4[sfz::z] == -4);
		// Integrity check of base vectors
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -2);
		REQUIRE(v1[sfz::z] == 5);
		REQUIRE(v2[sfz::x] == 0);
		REQUIRE(v2[sfz::y] == -2);
		REQUIRE(v2[sfz::z] == 1);
	}
	SECTION("Negating (-x)") {
		auto v3 = -v1;
		REQUIRE(v3[sfz::x] == -1);
		REQUIRE(v3[sfz::y] == 2);
		REQUIRE(v3[sfz::z] == -5);
		// Integrity check of base vectors
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -2);
		REQUIRE(v1[sfz::z] == 5);
		REQUIRE(v2[sfz::x] == 0);
		REQUIRE(v2[sfz::y] == -2);
		REQUIRE(v2[sfz::z] == 1);
	}
	SECTION("Multiplication by number") {
		auto v3 = v1*3;
		REQUIRE(v3[sfz::x] == 3);
		REQUIRE(v3[sfz::y] == -6);
		REQUIRE(v3[sfz::z] == 15);
		auto v4 = -3*v2;
		REQUIRE(v4[sfz::x] == 0);
		REQUIRE(v4[sfz::y] == 6);
		REQUIRE(v4[sfz::z] == -3);
		// Integrity check of base vectors
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -2);
		REQUIRE(v1[sfz::z] == 5);
		REQUIRE(v2[sfz::x] == 0);
		REQUIRE(v2[sfz::y] == -2);
		REQUIRE(v2[sfz::z] == 1);
	}
	SECTION("Division by number") {
		auto v1 = sfz::Vector<int, 2>{2, -2}/2;
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -1);
		REQUIRE_THROWS_AS(v1/0, std::domain_error);
	}
	SECTION("Addition assignment") {
		v1 += v2;
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == -4);
		REQUIRE(v1[sfz::z] == 6);
	}
	SECTION("Subtraction assignment") {
		v1 -= v2;
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == 0);
		REQUIRE(v1[sfz::z] == 4);
	}
	SECTION("Multiplication by number assignment") {
		v1 *= 3;
		REQUIRE(v1[sfz::x] == 3);
		REQUIRE(v1[sfz::y] == -6);
		REQUIRE(v1[sfz::z] == 15);
	}
	SECTION("Division by number assignment") {
		sfz::Vector<int, 2> v3{2, -2};
		v3 /= 2;
		REQUIRE(v3[sfz::x] == 1);
		REQUIRE(v3[sfz::y] == -1);
		REQUIRE_THROWS_AS(v3 /= 0, std::domain_error);
	}
}

TEST_CASE("Norm (length) of vector", "[sfz::Vector]") {
	sfz::Vector<int, 2> v1{2, 0};
	sfz::Vector<int, 5> v2{-2, 2, 2, -2, 3};

	SECTION("squaredNorm()") {
		REQUIRE(v1.squaredNorm() == 4);
		REQUIRE(v2.squaredNorm() == 25);
	}
	SECTION("v.norm()") {
		REQUIRE(v1.norm() == 2);
		REQUIRE(v2.norm() == 5);
	}
	SECTION("norm(v)") {
		REQUIRE(norm(v1) == 2);
		REQUIRE(norm(v2) == 5);
	}
	SECTION("Rounding down") {
		sfz::Vector<int, 2> v3{2,1};
		REQUIRE(v3.squaredNorm() == 5);
		REQUIRE(v3.norm() == 2);
	}
}

TEST_CASE("Normalizing (making unit vector) vector", "[sfz::Vector]") {
	sfz::Vector<float, 4> v1 = normalize(sfz::Vector<float, 4>{-2.f, 2.f, -2.f, 2.f});
	const float delta = 1e-3f;

	SECTION("Correct answer") {
		const float posLower = 0.5f - delta;
		const float posHigher = 0.5f + delta;
		const float negLower = -0.5f - delta;
		const float negHigher = -0.5f + delta;		

		REQUIRE(negLower <= v1[0]);
		REQUIRE(v1[0] <= negHigher);

		REQUIRE(posLower <= v1[1]);
		REQUIRE(v1[1] <= posHigher);

		REQUIRE(negLower <= v1[2]);
		REQUIRE(v1[2] <= negHigher);

		REQUIRE(posLower <= v1[3]);
		REQUIRE(v1[3] <= posHigher);
	}
}

TEST_CASE("Angle of vectors", "[sfz::Vector]") {
	sfz::Vector<float, 2> vRight{1, 0};
	sfz::Vector<float, 2> vUp{0, 1};
	sfz::Vector<float, 2> vDown{0, -1};

	SECTION("(2D) Angle between y and (implicit) x-axis") {
		auto angle = sfz::angle(vUp);
		REQUIRE((3.1415f/2.f) <= angle);
		REQUIRE(angle <= (3.1416f/2.f));
	}
	SECTION("Angle between y and (explicit) x-axis") {
		auto angle = sfz::angle(vRight, vUp);
		REQUIRE((3.1415f/2.f) <= angle);
		REQUIRE(angle <= (3.1416f/2.f));
	}
	SECTION("Angle between same vectors") {
		auto angle1 = angle(vRight);
		REQUIRE(angle1 == 0);

		auto angle2 = angle(vUp, vUp);
		REQUIRE(angle2 == 0);
	}
	SECTION("(2D) Angle with implicit x-axis should never give negative angles") {
		auto angle = sfz::angle(vDown);
		REQUIRE((3.f*3.1415f/2.f) <= angle);
		REQUIRE(angle <= (3.f*3.1416f/2.f));
	}
	SECTION("Vectors with norm == 0") {
		sfz::Vector<float, 2> vZero{0, 0};
		REQUIRE_THROWS_AS(angle(vZero), std::domain_error);
		REQUIRE_THROWS_AS(angle(vZero, vUp), std::domain_error);
		REQUIRE_THROWS_AS(angle(vRight, vZero), std::domain_error);
		REQUIRE_THROWS_AS(angle(vZero, vZero), std::domain_error);
	}
}

TEST_CASE("Comparison operators", "[sfz::Vector]") {
	sfz::Vector<int, 3> v1{-4, 0, 0};
	sfz::Vector<int, 3> v2{0, 2, 0};
	sfz::Vector<int, 3> v3{0, 2, 0};

	SECTION("== and !=") {
		REQUIRE(v1 == v1);
		REQUIRE(v2 == v2);
		REQUIRE(v3 == v3);	
		REQUIRE(v2 == v3);
		REQUIRE(v3 == v2);
		REQUIRE(v1 != v2);
		REQUIRE(v2 != v1);
	}
	SECTION("< and >") {
		REQUIRE(v2 < v1);
		REQUIRE(!(v2 > v1));
		REQUIRE(v1 > v2);
		REQUIRE(!(v1 < v2));
	}
	SECTION("<= and >=") {
		REQUIRE(v2 <= v1);
		REQUIRE(!(v2 >= v1));
		REQUIRE(v1 >= v2);
		REQUIRE(!(v1 <= v2));
		REQUIRE(v2 <= v3);
		REQUIRE(v2 >= v3);
		REQUIRE(v3 <= v2);
		REQUIRE(v3 >= v2);
	}
}

TEST_CASE("Dot (scalar) product", "[sfz::Vector]") {
	SECTION("Correctness test") {
		sfz::Vector<int, 3> v1{1, 0, -2};
		sfz::Vector<int, 3> v2{6, 2, 2};
		int scalarProduct = v1.dot(v2);
		
		REQUIRE(scalarProduct == 2);
		
		REQUIRE(v1[sfz::x] == 1);
		REQUIRE(v1[sfz::y] == 0);
		REQUIRE(v1[sfz::z] == -2);
		REQUIRE(v2[sfz::x] == 6);
		REQUIRE(v2[sfz::y] == 2);
		REQUIRE(v2[sfz::z] == 2);
	}
	SECTION("Using same vector twice") {	
		sfz::Vector<int, 2> v1{-3, 2};
		int scalarProduct = v1.dot(v1);
		
		REQUIRE(scalarProduct == 13);
		
		REQUIRE(v1[sfz::x] == -3);
		REQUIRE(v1[sfz::y] == 2);	
	}
}

TEST_CASE("Element-wise multiplication", "[sfz::Vector]") {
	sfz::Vector<int, 3> v1{1, 0, -3};
	sfz::Vector<int, 3> v2{2, 0, 2};

	SECTION("Correctness test") {
		auto v3 = v1.elementMultiply(v2);
		REQUIRE(v3[sfz::x] == 2);
		REQUIRE(v3[sfz::y] == 0);
		REQUIRE(v3[sfz::z] == -6);
	}
	SECTION("Same vector") {
		auto v3 = v1.elementMultiply(v1);
		REQUIRE(v3[sfz::x] == 1);
		REQUIRE(v3[sfz::y] == 0);
		REQUIRE(v3[sfz::z] == 9);
	}
}