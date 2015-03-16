#pragma once
#ifndef SFZ_GEOMETRY_PLANE_HPP
#define SFZ_GEOMETRY_PLANE_HPP

#include <string>
#include <iostream> // std::ostream
#include <functional> // std::hash

#include "sfz/Assert.hpp"
#include "sfz/math/Vector.hpp"
#include "sfz/math/MathHelpers.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Class representing a Plane.
 *
 * Mathematical definition (plane normal = n, position on plane = p, position to test = x):
 * f(x) = dot(n, x - p) = dot(n, q) - d
 * d = dot(n, p)
 * 
 * @author Peter Hillerström
 */
class Plane final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Plane() noexcept = delete;
	Plane(const Plane&) noexcept = default;
	Plane& operator= (const Plane&) noexcept = default;
	~Plane() noexcept = default;

	/** @brief dot(normal, x) - d = 0 */
	Plane(const vec3f& normal, float d) noexcept;
	/** @brief dot(normal, x - position) = 0 */
	Plane(const vec3f& normal, const vec3f& position) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/** @brief Returns the signed distance to the plane. Positive if above, negative if below. */
	float signedDistance(const vec3f& point) const noexcept;
	vec3f closestPoint(const vec3f& point) const noexcept;
	size_t hash() const noexcept;
	std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline vec3f normal() const noexcept { return mNormal; }
	inline float d() const noexcept { return mD; }

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mNormal;
	float mD;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const Plane& plane) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::Plane
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<>
struct hash<sfz::Plane> {
	size_t operator() (const sfz::Plane& plane) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#endif