#pragma once
#ifndef SFZ_MATH_VECTOR_HPP
#define SFZ_MATH_VECTOR_HPP

#include <initializer_list>
#include <cassert>
#include <functional> // std::hash
#include <cmath> // std::sqrt
#include <string>
#include <iostream> // std::ostream

#include "sfz/math/MathConstants.hpp"

namespace sfz {

using std::size_t;

/**
 * @brief A mathematical vector POD class that imitates a built-in primitive.
 *
 * The template is designed to be used with float and doubles in first hand, and everything should
 * work as expected with them. Integral types can also be used, but some things will not function
 * as expected due to truncation. Most notably taking the norm will most likely not give the
 * correct result as it involves taking the square root. Another trouble with integral types is the
 * risk of overflow. When calculating the norm you have to square each element in the vector, which
 * might wery well overflow if you have large elements.
 *
 * Satisfies the conditions of std::is_pod, std::is_trivial and std::is_standard_layout if used
 * with standard primitives.
 *
 * Comparison operators are also overloaded, in practice this means that the vectors norm is
 * compared.
 *
 * @param T the element type
 * @param N the amount of elements in the vector
 *
 * @author Peter Hillerström <peter@hstroem.se>
 */
template<typename T, size_t N>
struct Vector final {
	
	// Public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/** 
	 * @brief The internal array holding the elements of this Vector.
	 * Provided for compatibility with c-style API's like OpenGL.
	 */
	T mElements[N];

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	Vector() = default;

	Vector(const Vector<T,N>& vector) = default;

	/**
	 * @brief Copy cast constructor.
	 * Copies all elements from specified vector and attempts to static_cast them to this vectors
	 * type.
	 * @param vector the vector to copy
	 */
	template<typename T2>
	explicit Vector(const Vector<T2,N>& vector) noexcept;

	/**
	 * @brief Initializer list constructor.
	 * If the initializer list contains less element than the size of the vector the remaining
	 * elements will be set to 0.
	 * @assert vector and initializer list must fit in the vector
	 * @param list the initializer_list with values to fill the vector with
	 */
	Vector(std::initializer_list<T> list) noexcept;

	~Vector() = default;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	/**
	 * @brief General accessor returning the reference to element at the specified location.
	 * @assert index must be in range
	 * @param index the index of the element
	 * @return reference to the element at the specified index
	 */
	T& at(const size_t index) noexcept;

	/**
	 * @brief Returns the element at the specified index.
	 * @assert index must be in range
	 * @param index the index of the element
	 * @return the element at the specified index
	 */
	T at(const size_t index) const noexcept;

	/**
	 * @brief Assigns value to the specified index.
	 * @assert index must be in range
	 * @param index the index to assign value to
	 * @param value the value to assign
	 */
	void set(const size_t index, const T value) noexcept;

	/**
	 * @brief Assigns each element in the vector with the specified value
	 * @param value the value to fill vector with
	 */
	void fill(const T value) noexcept;

	/**
	 * @brief Calculates the norm (length) of the vector.
	 * Note when using discrete types (int, long, etc): This method will square each element of the
	 * vector and add them together before taking the square root. This might result in an overflow
	 * if the elements are too large. In that case the result of this function will be undefined.
	 * Also, the return type will still be a discrete type, meaning that the result will be
	 * truncated. If this is a problem you should use the squaredNorm() function and do the square
	 * root operation yourself.
	 * @return norm of the vector
	 */
	T norm() const noexcept;

	/**
	 * @brief Sums the squares of each element in the vector (squared norm, i.e. squared length).
	 * @return squared norm of the vector
	 */
	T squaredNorm() const noexcept;

	/**
	 * @brief Normalizes the vector and produces a unit vector.
	 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing
	 * in the same direction with the norm 1.
	 * @return the unit vector
	 */
	Vector<T,N> normalize() const noexcept;

	T dot(const Vector<T,N>& other) const noexcept;

	/**
	 * @brief Does an element-wise multiplication of two vectors.
	 * @param the other vector
	 * @return the resulting vector
	 */
	Vector<T,N> elemMult(const Vector<T,N>& other) const noexcept;

	/**
	 * @return the sum of all the elements in the vector
	 */
	T sum() const noexcept;

	/**
	 * @brief Projects the vector onto another vector.
	 * Makes a scalar projection of the vector onto the specifed target vector. The resulting
	 * vector will be equal to the target vector times a scalar constant. If the target vector is
	 * 0 the 0 vector will be returned.
	 * @param target the vector to project onto
	 * @return the resulting projection in vector form
	 */
	Vector<T,N> projectOnto(const Vector<T,N>& target) const noexcept;

	/**
	 * @brief Calculates distance vector from this vector to another vector.
	 * This is the same thing as doing 'other - this'.
	 * @param other the other vector
	 * @return the resulting vector
	 */
	Vector<T,N> distance(const Vector<T,N>& other) const noexcept;

	size_t hash() const noexcept;

	std::string to_string() const noexcept;

	// Standard iterator functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	T* begin() noexcept;
	const T* begin() const noexcept;
	const T* cbegin() const noexcept;

	T* end() noexcept;
	const T* end() const noexcept;
	const T* cend() const noexcept;

	// Operators (access)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Returns a reference to element at the specified index.
	 * No range checking, index is out of range is undefined behavior.
	 * @param index the index of the element
	 * @return reference to element at the specified index
	 */
	T& operator[] (const size_t index) noexcept;

	/**
	 * @brief Returns a const reference to element at the specified index.
	 * No range checking, index is out of range is undefined behavior.
	 * @param index the index of the element
	 * @return const reference to element at the specified index
	 */
	const T& operator[] (const size_t index) const noexcept;

	// Operators (arithmetic & assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Vector<T,N>& operator= (const Vector<T,N>&) = default;

	Vector<T,N>& operator+= (const Vector<T,N>& right) noexcept;

	Vector<T,N>& operator-= (const Vector<T,N>& right) noexcept;

	Vector<T,N>& operator*= (const T& right) noexcept;

	/**
	 * @assert rhs != 0
	 */
	Vector<T,N>& operator/= (const T& right) noexcept;

	// Operators (arithmetic)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Vector<T,N> operator+ (const Vector<T,N>& other) const noexcept;

	Vector<T,N> operator- (const Vector<T,N>& other) const noexcept;

	Vector<T,N> operator- () const noexcept;

	Vector<T,N> operator* (const T& scalar) const noexcept;

	/**
	 * @assert rhs element != 0
	 */
	Vector<T,N> operator/ (const T& scalar) const noexcept;

	// Operators (comparison)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	bool operator== (const Vector<T,N>& other) const noexcept;

	bool operator!= (const Vector<T,N>& other) const noexcept;

	bool operator< (const Vector<T,N>& other) const noexcept;

	bool operator> (const Vector<T,N>& other) const noexcept;

	bool operator<= (const Vector<T,N>& other) const noexcept;

	bool operator>= (const Vector<T,N>& other) const noexcept;
};

// Non-member operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N> operator* (const T& left, const Vector<T,N>& right) noexcept;

// Non-member operators (other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept;

// Non-member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @relates sfz::Vector
 * @brief Calculates the norm (length) of the vector.
 * @see sfz::Vector<T,N>::norm()
 * @param vector the vector to calculate norm of
 * @return norm of the vector
 */
template<typename T, size_t N>
T norm(const Vector<T,N>& vector) noexcept;

/**
 * @relates sfz::Vector
 * @brief Normalizes the vector and produces a unit vector.
 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing in
 * the same direction with the norm 1.
 * @param vector the vector to normalize
 * @return the unit vector
 */
template<typename T, size_t N>
Vector<T,N> normalize(const Vector<T,N>& vector) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the dot (scalar) product of the vectors.
 * @param vectorA the first vector
 * @param vectorB the second vector
 * @return the dot product
 */
template<typename T, size_t N>
T dot(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the cross product of the vectors.
 * More specifically this function calculates: vectorA x vectorB.
 * @param vectorA the first vector
 * @param vectorB the second vector
 * @return the resulting vector
 */
template<typename T>
Vector<T,3> cross(const Vector<T,3>& vectorA, const Vector<T,3>& vectorB) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the positive angle between the specified vector and the x-axis in radians.
 * The angle will be in the range [0, 2*Pi).
 * @assert norm of vector != 0
 * @param vector the 2-dimensional vector to calculate angle of
 * @return the angle between the vector and the x-axis
 */
template<typename T>
T angle(const Vector<T,2>& vector) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the positive angle between two vectors.
 * The angle will be in range [0, Pi] and will always be the smallest possible angle between the
 * vectors.
 * @assert norm of vectorA or B != 0
 * @param vectorA the first vector
 * @param vectorB the second vector
 * @return the angle between the two vectors
 */
template<typename T, size_t N>
T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept;

/**
 * @relates sfz::Vector
 * @brief Rotates a 2-dimensional vector with the specified angle around origo.
 * @param vector the vector to rotate
 * @param angle the angle to rotate in radians
 * @return the resulting vector
 */
template<typename T>
Vector<T,2> rotate(const Vector<T,2>& vector, const T angle) noexcept;

// Standard typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
using vec2 = Vector<T,2>;
using vec2f = Vector<float,2>;
using vec2i = Vector<int,2>;

template<typename T>
using vec3 = Vector<T,3>;
using vec3f = Vector<float,3>;
using vec3i = Vector<int,3>;

template<typename T>
using vec4 = Vector<T,4>;
using vec4f = Vector<float,4>;
using vec4i = Vector<int,4>;

} // namespace sfz

// Specializations of standard library for sfz::Vector
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t N>
struct hash<sfz::Vector<T,N>> {
	size_t operator() (const sfz::Vector<T,N>& vector) const noexcept;
};

} // namespace std

#include "Vector.inl"
#endif