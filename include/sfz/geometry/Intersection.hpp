#pragma once
#ifndef SFZ_GEOMETRY_COLLISION_DETECTION_HPP
#define SFZ_GEOMETRY_COLLISION_DETECTION_HPP

#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/OBB.hpp"
#include "sfz/geometry/Sphere.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool inside(const AABB& box, const vec3f& point) noexcept;
bool inside(const vec3f& point, const AABB& box) noexcept;

bool intersects(const AABB& boxA, const AABB& boxB) noexcept;

bool intersects(const Sphere& sphereA, const Sphere& sphereB) noexcept;

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"

#endif