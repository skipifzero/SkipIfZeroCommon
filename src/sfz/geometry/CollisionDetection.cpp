#include "sfz/geometry/CollisionDetection.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

bool intersects(const AABB& boxA, const AABB& boxB) noexcept
{
	// Boxes intersect if they overlap on all axes.
	if (boxA.mMax[0] < boxB.mMin[0] || boxA.mMin[0] > boxB.mMax[0]) return false;
	if (boxA.mMax[1] < boxB.mMin[1] || boxA.mMin[1] > boxB.mMax[1]) return false;
	if (boxA.mMax[2] < boxB.mMin[2] || boxA.mMin[2] > boxB.mMax[2]) return false;
	return true;
}

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"