#include "sfz/geometry/Plane.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

// Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Plane::Plane(const vec3f& normal, float d) noexcept
:
	mNormal{normal},
	mD{d}
{
	sfz_assert_debug(approxEqual<float>(normal.norm(), 1.0f, 0.025f));
}

Plane::Plane(const vec3f& normal, const vec3f& position) noexcept
:
	mNormal{normal},
	mD{normal.dot(position)}
{
	sfz_assert_debug(approxEqual<float>(normal.norm(), 1.0f, 0.025f));
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

float Plane::signedDistance(const vec3f& point) const noexcept
{
	return mNormal.dot(point) - mD; // mNormal MUST be normalized.
}

vec3f Plane::closestPoint(const vec3f& point) const noexcept
{
	return point - signedDistance(point)*mNormal;
}

size_t Plane::hash() const noexcept
{
	std::hash<float> fHasher;
	std::hash<vec3f> vecHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= fHasher(mD) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= vecHasher(mNormal) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

std::string Plane::to_string() const noexcept
{
	std::string str;
	str += "Normal = ";
	str += mNormal.to_string();
	str += ", d = ";
	str += std::to_string(mD);
	return std::move(str);
}

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const Plane& plane) noexcept
{
	return ostream << plane.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Plane
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

size_t hash<sfz::Plane>::operator() (const sfz::Plane& plane) const noexcept
{
	return plane.hash();
}

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"