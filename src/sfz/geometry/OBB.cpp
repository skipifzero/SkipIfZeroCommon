#include "sfz/geometry/OBB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

// Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

OBB::OBB(const vec3f& center, const std::array<vec3f,3>& axes, const vec3f& extents) noexcept
:
	mCenter{center},
	mHalfExtents{extents/2.0f}
{
	mAxes = axes;
	ensureCorrectAxes();
	ensureCorrectExtents();
}

OBB::OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
         const vec3f& extents) noexcept
:
	mCenter{center},
	mHalfExtents{extents/2.0f}
{
	mAxes[0] = xAxis;
	mAxes[1] = yAxis;
	mAxes[2] = zAxis;
	ensureCorrectAxes();
	ensureCorrectExtents();
}

OBB::OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
         float xExtent, float yExtent, float zExtent) noexcept
:
	OBB(center, xAxis, yAxis, zAxis, vec3f{xExtent, yExtent, zExtent})
{
	// Initialization done.
}

OBB::OBB(const AABB& aabb) noexcept
:
	OBB(aabb.position(), vec3f{1, 0, 0}, vec3f{0, 1, 0}, vec3f{0, 0, 1},
        aabb.xExtent(), aabb.yExtent(), aabb.zExtent())
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool OBB::intersects(const OBB& other) const noexcept
{
	const OBB& a = *this;
	const std::array<vec3f,3>& aU = a.mAxes;
	const vec3f& aE = a.mHalfExtents;
	const OBB& b = other;
	const std::array<vec3f,3>& bU = b.mAxes;
	const vec3f& bE = b.mHalfExtents;

	// Compute the rotation matrix from b to a
	mat3f R;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			R.set(i, j, aU[i].dot(bU[j]));
		}
	}

	// Compute common subexpressions, epsilon term to counteract arithmetic errors
	static const float EPSILON = 0.000001f;
	mat3f AbsR;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			AbsR.set(i, j, std::abs(R.at(i, j)) + EPSILON);
		}
	}

	// Calculate translation vector from a to b and bring it into a's frame of reference
	vec3f t = b.mCenter - a.mCenter;
	t = vec3f{t.dot(aU[0]), t.dot(aU[1]), t.dot(aU[2])};

	float ra, rb;

	// Test axes L = aU[0], aU[1], aU[2]
	for (size_t i = 0; i < 3; i++) {
		ra = aE[i];
		rb = bE[0]*AbsR.at(i,0) + bE[1]*AbsR.at(i,1) + bE[2]*AbsR.at(i,2);
		if (std::abs(t[i]) > ra + rb) return false;
	}

	// Test axes L = bU[0], bU[1], bU[2]
	for (size_t i = 0; i < 3; i++) {
		ra = aE[0]*AbsR.at(0,i) + aE[1]*AbsR.at(1,i) + aE[2]*AbsR.at(2,i);
		rb = bE[i];
		if (std::abs(t[0]*R.at(0,i) + t[1]*R.at(1,i) + t[2]*R.at(2,i)) > ra + rb) return false;
	}

	// If no separating axis can be found then the OBBs must be intersecting.
	return true;
}

std::array<vec3f,8> OBB::corners() const noexcept
{
	std::array<vec3f,8> result;
	this->corners(&result[0]);
	return result;
}

void OBB::corners(vec3f* arrayOut) const noexcept
{
	vec3f halfXExtVec = mAxes[0]*mHalfExtents[0];
	vec3f halfYExtVec = mAxes[1]*mHalfExtents[1];
	vec3f halfZExtVec = mAxes[2]*mHalfExtents[2];
	arrayOut[0] = mCenter - halfXExtVec - halfYExtVec - halfZExtVec; // Back-bottom-left
	arrayOut[1] = mCenter - halfXExtVec - halfYExtVec + halfZExtVec; // Front-bottom-left
	arrayOut[2] = mCenter - halfXExtVec + halfYExtVec - halfZExtVec; // Back-top-left
	arrayOut[3] = mCenter - halfXExtVec + halfYExtVec + halfZExtVec; // Front-top-left
	arrayOut[4] = mCenter + halfXExtVec - halfYExtVec - halfZExtVec; // Back-bottom-right
	arrayOut[5] = mCenter + halfXExtVec - halfYExtVec + halfZExtVec; // Front-bottom-right
	arrayOut[6] = mCenter + halfXExtVec + halfYExtVec - halfZExtVec; // Back-top-right
	arrayOut[7] = mCenter + halfXExtVec + halfYExtVec + halfZExtVec; // Front-top-right
}

vec3f OBB::closestPoint(const vec3f& point) const noexcept
{
	// Algorithm from Real-Time Collision Detection (Section 5.1.4)
	const vec3f distToPoint = point - mCenter;
	vec3f res = mCenter;

	float dist;
	for (size_t i = 0; i < 3; i++) {
		dist = distToPoint.dot(mAxes[i]);
		if (dist > mHalfExtents[i]) dist = mHalfExtents[i];
		if (dist < -mHalfExtents[i]) dist = -mHalfExtents[i];
		res += (dist * mAxes[i]);
	}

	return res;
}

OBB OBB::transformOBB(const mat4f& transform) const noexcept
{
	const vec3f newPos = transformPoint(transform, mCenter);
	const vec3f newXHExt = transformDir(transform, mAxes[0] * mHalfExtents[0]);
	const vec3f newYHExt = transformDir(transform, mAxes[1] * mHalfExtents[1]);
	const vec3f newZHExt = transformDir(transform, mAxes[2] * mHalfExtents[2]);
	return OBB{newPos, newXHExt.normalize(), newYHExt.normalize(), newZHExt.normalize(),
	           newXHExt.norm(), newYHExt.norm(), newZHExt.norm()};
}

size_t OBB::hash() const noexcept
{
	std::hash<vec3f> hasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mCenter) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[2]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mHalfExtents) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

std::string OBB::to_string() const noexcept
{
	std::string str{"Center: "};
	str += mCenter.to_string();
	str += "\nX-axis: ";
	str += mAxes[0].to_string();
	str += "\nY-axis: ";
	str += mAxes[1].to_string();
	str += "\nZ-axis: ";
	str += mAxes[2].to_string();
	str += "\nExtents: ";
	str += (mHalfExtents*2.0f).to_string();
	return std::move(str);
}

// Public getters/setters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void OBB::axes(const std::array<vec3f,3>& newAxes) noexcept
{
	mAxes = newAxes;
}

void OBB::xAxis(const vec3f& newXAxis) noexcept
{
	mAxes[0] = newXAxis;
}

void OBB::yAxis(const vec3f& newYAxis) noexcept
{
	mAxes[1] = newYAxis;
}

void OBB::zAxis(const vec3f& newZAxis) noexcept
{
	mAxes[2] = newZAxis;
}

void OBB::extents(const vec3f& newExtents) noexcept
{
	mHalfExtents = newExtents / 2.0f;
	ensureCorrectExtents();
}

void OBB::xExtent(float newXExtent) noexcept
{
	mHalfExtents[0] = newXExtent / 2.0f;
	ensureCorrectExtents();
}

void OBB::yExtent(float newYExtent) noexcept
{
	mHalfExtents[1] = newYExtent / 2.0f;
	ensureCorrectExtents();
}

void OBB::zExtent(float newZExtent) noexcept
{
	mHalfExtents[2] = newZExtent / 2.0f;
	ensureCorrectExtents();
}

void OBB::halfExtents(const vec3f& newHalfExtents) noexcept
{
	mHalfExtents = newHalfExtents;
	ensureCorrectExtents();
}

void OBB::halfXExtent(float newHalfXExtent) noexcept
{
	mHalfExtents[0] = newHalfXExtent;
	ensureCorrectExtents();
}

void OBB::halfYExtent(float newHalfYExtent) noexcept
{
	mHalfExtents[1] = newHalfYExtent;
	ensureCorrectExtents();
}

void OBB::halfZExtent(float newHalfZExtent) noexcept
{
	mHalfExtents[2] = newHalfZExtent;
	ensureCorrectExtents();
}

// Private functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void OBB::ensureCorrectAxes() const noexcept
{
	// Check if axes are orthogonal
	sfz_assert_debug(approxEqual(mAxes[0].dot(mAxes[1]), 0.0f));
	sfz_assert_debug(approxEqual(mAxes[0].dot(mAxes[2]), 0.0f));
	sfz_assert_debug(approxEqual(mAxes[1].dot(mAxes[2]), 0.0f));

	// Check if axes are normalized
	sfz_assert_debug(approxEqual(mAxes[0].norm(), 1.0f));
	sfz_assert_debug(approxEqual(mAxes[1].norm(), 1.0f));
	sfz_assert_debug(approxEqual(mAxes[2].norm(), 1.0f));
}

void OBB::ensureCorrectExtents() const noexcept
{
	// Extents are non-negative
	sfz_assert_debug(0.0f < mHalfExtents[0]);
	sfz_assert_debug(0.0f < mHalfExtents[1]);
	sfz_assert_debug(0.0f < mHalfExtents[2]);
}

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const OBB& obb) noexcept
{
	return ostream << obb.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::OBB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

size_t hash<sfz::OBB>::operator() (const sfz::OBB& obb) const noexcept
{
	return obb.hash();
}

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"