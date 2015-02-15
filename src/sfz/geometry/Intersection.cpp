#include "sfz/geometry/Intersection.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool intersects(const AABB& boxA, const AABB& boxB) noexcept
{
	// Boxes intersect if they overlap on all axes.
	if (boxA.max()[0] < boxB.min()[0] || boxA.min()[0] > boxB.max()[0]) return false;
	if (boxA.max()[1] < boxB.min()[1] || boxA.min()[1] > boxB.max()[1]) return false;
	if (boxA.max()[2] < boxB.min()[2] || boxA.min()[2] > boxB.max()[2]) return false;
	return true;
}

bool intersects(const Sphere& sphereA, const Sphere& sphereB) noexcept
{
	const vec3f distVec = sphereA.position() - sphereB.position();
	const float squaredDist = distVec.dot(distVec);
	const float radiusSum = sphereA.radius() + sphereB.radius();
	const float squaredRadiusSum = radiusSum * radiusSum;
	return squaredDist <= squaredRadiusSum;
}

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"