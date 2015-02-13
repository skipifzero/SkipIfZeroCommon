#pragma once
#ifndef SFZ_GEOMETRY_COLLISION_DETECTION_HPP
#define SFZ_GEOMETRY_COLLISION_DETECTION_HPP

#include "sfz/math/Vector.hpp"
#include "sfz/math/Matrix.hpp"
#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/OBB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool intersects(const AABB& boxA, const AABB& boxB) noexcept;

bool intersects(const OBB& boxA, const OBB& boxB) noexcept;

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"

#endif