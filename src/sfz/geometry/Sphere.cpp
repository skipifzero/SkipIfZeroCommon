#include "sfz/geometry/Sphere.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

// Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Sphere::Sphere(const vec3f& center, float radius) noexcept
:
	mCenter{center},
	mRadius{radius}
{
	assert(radius > 0.0f);
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

size_t Sphere::hash() const noexcept
{
	std::hash<vec3f> vecHasher;
	std::hash<float> floatHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= vecHasher(mCenter) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= floatHasher(mRadius) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

std::string Sphere::to_string() const noexcept
{
	std::string str{"Center: "};
	str += mCenter.to_string();
	str += "\nRadius: ";
	str += std::to_string(mRadius);
	return std::move(str);
}

// Public getters/setters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void Sphere::position(const vec3f& newPosition) noexcept
{
	mCenter = newPosition;
}

void Sphere::radius(float newRadius) noexcept
{
	assert(newRadius > 0.0f);
	mRadius = newRadius;
}

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const Sphere& sphere) noexcept
{
	return ostream << sphere.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Sphere
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

size_t hash<sfz::Sphere>::operator() (const sfz::Sphere& sphere) const noexcept
{
	return sphere.hash();
}

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
