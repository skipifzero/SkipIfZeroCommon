#pragma once
#ifndef SFZ_GEOMETRY_OBB_HPP
#define SFZ_GEOMETRY_OBB_HPP

#include <string>
#include <iostream> // std::ostream
#include <functional> // std::hash
#include <cassert>

#include "sfz/math/Vector.hpp"

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

	OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
	    float xExtent, float yExtent, float zExtent) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	size_t hash() const noexcept;
	std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

private:
	// Private functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	void ensureCorrectState() noexcept;

	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mCenter;
	vec3f mAxes[3];
	vec3f mExtents;
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