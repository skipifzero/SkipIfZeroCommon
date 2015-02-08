#pragma once
#ifndef SFZ_GEOMETRY_AABB_HPP
#define SFZ_GEOMETRY_AABB_HPP

#include <string>
#include <iostream> // std::ostream
#include <functional> // std::hash
#include <cassert>

#include "sfz/math/Vector.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Axis-Aligned Bounding Box POD struct.
 * @author Peter Hillerström
 */
struct AABB final {

	// Public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/** The front bottom left corner of this AABB. */
	vec3f mMin

	/** The back top right corner of this AABB. */
	vec3f mMax;

	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	constexpr AABB() noexcept = default;
	constexpr AABB(const AABB&) noexcept = default;
	AABB& operator= (const AABB&) noexcept = default;
	~AABB() noexcept = default;

	/**
	 * @assert min is smaller than max in all axes
	 */
	AABB(const vec3f& min, const vec3f& max) noexcept;

	/**
	 * @assert all extents are larger than 0
	 */
	AABB(const vec3f& centerPos, float xExtent, float yExtent, float zExtent) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	size_t hash() const noexcept;
	std::string to_string() const noexcept;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const AABB& aabb) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::AABB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

struct hash<sfz::AABB> {
	size_t operator() (const sfz::AABB& aabb) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#endif