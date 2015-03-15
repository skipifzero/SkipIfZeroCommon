#pragma once
#ifndef SFZ_GEOMETRY_COLLISION_DETECTION_HPP
#define SFZ_GEOMETRY_COLLISION_DETECTION_HPP

#include "sfz/geometry/AABB.hpp"
#include "sfz/geometry/OBB.hpp"
#include "sfz/geometry/Sphere.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool pointInside(const AABB& box, const vec3f& point) noexcept;
bool pointInside(const OBB& box, const vec3f& point) noexcept;
bool pointInside(const Sphere& sphere, const vec3f& point) noexcept;

bool intersects(const AABB& boxA, const AABB& boxB) noexcept;
bool intersects(const OBB& boxA, const OBB& boxB) noexcept;
bool intersects(const Sphere& sphereA, const Sphere& sphereB) noexcept;

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"

#endif