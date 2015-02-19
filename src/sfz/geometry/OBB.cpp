#include "sfz/geometry/OBB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

// Anonymous functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace {

bool approxEqual(float lhs, float rhs) noexcept
{
	static const float EPSILON = 0.001f;
	return lhs <= rhs + EPSILON && lhs >= rhs - EPSILON;
}

} // anonymous namespace

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