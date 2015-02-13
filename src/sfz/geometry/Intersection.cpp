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

bool intersects(const OBB& boxA, const OBB& boxB) noexcept
{
	float radiusA, radiusB;
	mat3f rotation, rotationAbsVals;

	mat3f aToWorldSpace;
	aToWorldSpace.setColumn(0, boxA.xAxis());
	aToWorldSpace.setColumn(1, boxA.yAxis());
	aToWorldSpace.setColumn(2, boxA.zAxis());

	mat3f bToWorldSpace;
	bToWorldSpace.setColumn(0, boxB.xAxis());
	bToWorldSpace.setColumn(1, boxB.yAxis());
	bToWorldSpace.setColumn(2, boxB.zAxis());

	mat3f worldToASpace = inverse(aToWorldSpace);
	mat3f bToASpace = worldToASpace * bToWorldSpace;
	
}

} // namespace sfz

#include "sfz/MSVC12HackOFF.hpp"