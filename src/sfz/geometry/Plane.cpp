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
	// Initialization done.
}

Plane::Plane(const vec3f& position, const vec3f& normal) noexcept
:
	mNormal{normal},
	mD{normal.dot(position)}
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


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