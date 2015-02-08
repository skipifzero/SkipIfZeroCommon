#pragma once
#ifndef SFZ_GEOMETRY_OBB_HPP
#define SFZ_GEOMETRY_OBB_HPP

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

struct OBB final {
	vec3f mCenter;
	vec3f mAxes[3];
	vec3f mExtents;
};

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"
#endif