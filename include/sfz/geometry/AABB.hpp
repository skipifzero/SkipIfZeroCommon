#pragma once
#ifndef SFZ_GEOMETRY_AABB_HPP
#define SFZ_GEOMETRY_AABB_HPP

#include <string>
#include <array>
#include <iostream> // std::ostream
#include <functional> // std::hash

#include "sfz/Assert.hpp"
#include "sfz/math/Vector.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Class representing an Axis-Aligned Bounding Box.
 * @author Peter Hillerström
 */
class AABB final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	AABB() noexcept = delete;
	AABB(const AABB&) noexcept = default;
	AABB& operator= (const AABB&) noexcept = default;
	~AABB() noexcept = default;

	/**
	 * @sfz_debug_assert min is smaller than max in all axes
	 */
	AABB(const vec3f& min, const vec3f& max) noexcept;

	/**
	 * @sfz_debug_assert all extents are larger than 0
	 */
	AABB(const vec3f& centerPos, float xExtent, float yExtent, float zExtent) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	std::array<vec3f,8> corners() const noexcept;
	void corners(vec3f* arrayOut) const noexcept;

	size_t hash() const noexcept;
	std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline vec3f min() const noexcept { return mMin; }
	inline vec3f max() const noexcept { return mMax; }
	vec3f position() const noexcept;
	vec3f extents() const noexcept;
	float xExtent() const noexcept;
	float yExtent() const noexcept;
	float zExtent() const noexcept;

	void min(const vec3f& newMin) noexcept;
	void max(const vec3f& newMax) noexcept;
	void position(const vec3f& newCenterPos) noexcept;
	void extents(const vec3f& newExtents) noexcept;
	void xExtent(float newXExtent) noexcept;
	void yExtent(float newYExtent) noexcept;
	void zExtent(float newZExtent) noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mMin, mMax;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const AABB& aabb) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::AABB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<>
struct hash<sfz::AABB> {
	size_t operator() (const sfz::AABB& aabb) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#endif