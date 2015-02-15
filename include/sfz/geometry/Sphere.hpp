#pragma once
#ifndef SFZ_GEOMETRY_SPHERE_HPP
#define SFZ_GEOMETRY_SPHERE_HPP

#include <string>
#include <iostream> // std::ostream
#include <functional> // std::hash
#include <cassert>

#include "sfz/math/Vector.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Class representing a Sphere.
 * @author Peter Hillerström
 */
class Sphere final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Sphere() noexcept = delete;
	Sphere(const Sphere&) noexcept = default;
	Sphere& operator= (const Sphere&) noexcept = default;
	~Sphere() noexcept = default;

	/**
	 * @assert radius > 0
	 */
	Sphere(const vec3f& center, float radius) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	size_t hash() const noexcept;
	std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline vec3f position() const noexcept { return mCenter; }
	inline float radius() const noexcept { return mRadius; }

	void position(const vec3f& newPosition) noexcept;
	void radius(float newRadius) noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mCenter;
	float mRadius;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const Sphere& sphere) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::Sphere
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<>
struct hash<sfz::Sphere> {
	size_t operator() (const sfz::Sphere& sphere) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#endif