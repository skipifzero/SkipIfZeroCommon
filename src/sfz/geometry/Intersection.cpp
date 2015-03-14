#include "sfz/geometry/Intersection.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool inside(const AABB& box, const vec3f& point) noexcept
{
	return box.min()[0] < point[0] && point[0] < box.max()[0] &&
	       box.min()[1] < point[1] && point[1] < box.max()[1] &&
	       box.min()[2] < point[2] && point[2] < box.max()[2];
}

bool inside(const vec3f& point, const AABB& box) noexcept
{
	return inside(box, point);
}

bool intersects(const AABB& boxA, const AABB& boxB) noexcept
{
	// Boxes intersect if they overlap on all axes.
	if (boxA.max()[0] < boxB.min()[0] || boxA.min()[0] > boxB.max()[0]) return false;
	if (boxA.max()[1] < boxB.min()[1] || boxA.min()[1] > boxB.max()[1]) return false;
	if (boxA.max()[2] < boxB.min()[2] || boxA.min()[2] > boxB.max()[2]) return false;
	return true;
}

bool intersects(const OBB& boxA, const OBB& boxB) noexcept
{
	return boxA.intersects(boxB);
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