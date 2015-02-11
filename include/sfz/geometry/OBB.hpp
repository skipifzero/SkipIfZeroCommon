#pragma once
#ifndef SFZ_GEOMETRY_OBB_HPP
#define SFZ_GEOMETRY_OBB_HPP

#include <string>
#include <array>
#include <iostream> // std::ostream
#include <functional> // std::hash
#include <cassert>

#include "sfz/math/Vector.hpp"
#include "sfz/geometry/AABB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Class representing an Oriented Bounding Box.
 * @author Peter Hillerström
 */
class OBB final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	OBB() noexcept = delete;
	OBB(const OBB&) noexcept = default;
	OBB& operator= (const OBB&) noexcept = default;
	~OBB() noexcept = default;

	OBB(const vec3f& center, const std::array<vec3f,3>& axes, const vec3f& extents) noexcept;

	OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
	    const vec3f& extents) noexcept;

	OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
	    float xExtent, float yExtent, float zExtent) noexcept;

	explicit OBB(const AABB& aabb) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	size_t hash() const noexcept;
	std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline vec3f position() const noexcept { return mCenter; }
	inline std::array<vec3f,3> axes() const noexcept { return mAxes; }
	inline vec3f xAxis() const noexcept { return mAxes[0]; }
	inline vec3f yAxis() const noexcept { return mAxes[1]; }
	inline vec3f zAxis() const noexcept { return mAxes[2]; }
	inline vec3f extents() const noexcept { return mHalfExtents * 2.0f; }
	inline float xExtent() const noexcept { return mHalfExtents[0] * 2.0f; }
	inline float yExtent() const noexcept { return mHalfExtents[1] * 2.0f; }
	inline float zExtent() const noexcept { return mHalfExtents[2] * 2.0f; }
	inline vec3f halfExtents() const noexcept { return mHalfExtents; }
	inline float halfXExtent() const noexcept { return mHalfExtents[0]; }
	inline float halfYExtent() const noexcept { return mHalfExtents[1]; }
	inline float halfZExtent() const noexcept { return mHalfExtents[2]; }

	inline void position(const vec3f& newCenterPos) noexcept { mCenter = newCenterPos; }
	void axes(const std::array<vec3f,3>& newAxes) noexcept;
	void xAxis(const vec3f& newXAxis) noexcept;
	void yAxis(const vec3f& newYAxis) noexcept;
	void zAxis(const vec3f& newZAxis) noexcept;
	void extents(const vec3f& newExtents) noexcept;
	void xExtent(float newXExtent) noexcept;
	void yExtent(float newYExtent) noexcept;
	void zExtent(float newZExtent) noexcept;
	void halfExtents(const vec3f& newHalfExtents) noexcept;
	void halfXExtent(float newHalfXExtent) noexcept;
	void halfYExtent(float newHalfYExtent) noexcept;
	void halfZExtent(float newHalfZExtent) noexcept;

private:
	// Private functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	void ensureCorrectAxes() const noexcept;
	void ensureCorrectExtents() const noexcept;

	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mCenter;
	std::array<vec3f,3> mAxes;
	vec3f mHalfExtents;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const OBB& obb) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::OBB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<>
struct hash<sfz::OBB> {
	size_t operator() (const sfz::OBB& obb) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#endif