#pragma once
#ifndef SFZ_GEOMETRY_COLLISION_DETECTION_HPP
#define SFZ_GEOMETRY_COLLISION_DETECTION_HPP

#include "sfz/geometry/AABB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool intersects(const AABB& a, const AABB& b) noexcept;

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"

#endif