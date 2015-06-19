#pragma once
#ifndef SFZ_MATH_VECTOR_HPP
#define SFZ_MATH_VECTOR_HPP

#include <cstddef> // std::size_t
#include <cstdint> // std::int32_t
#include <initializer_list>
#include <functional> // std::hash
#include <cmath> // std::sqrt
#include <string>
#include <iostream> // std::ostream

#include "sfz/Assert.hpp"
#include "sfz/math/MathConstants.hpp"

namespace sfz {

using std::size_t;
using std::int32_t;

// Vector struct declaration
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

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
 * Additional vector operations available in the VectorSupport.hpp header.
 *
 * @param T the element type
 * @param N the amount of elements in the vector
 *
 * @author Peter Hillerström <peter@hstroem.se>
 */
template<typename T, size_t N>
struct Vector final {

	T elements[N];

	constexpr Vector() noexcept = default;
	constexpr Vector(const Vector<T, N>&) noexcept = default;
	Vector<T, N>& operator= (const Vector<T, N>&) noexcept = default;
	~Vector() noexcept = default;

	explicit Vector(T value) noexcept;
	Vector(std::initializer_list<T> list) noexcept;

	T& operator[] (const size_t index) noexcept;
	T operator[] (const size_t index) const noexcept;
};

template<typename T>
struct Vector<T, 2> final {

	T elements[2];

	constexpr Vector() noexcept = default;
	constexpr Vector(const Vector<T, 2>&) noexcept = default;
	Vector<T, 2>& operator= (const Vector<T, 2>&) noexcept = default;
	~Vector() noexcept = default;

	explicit Vector(T value) noexcept;
	Vector(std::initializer_list<T> list) noexcept;

	T& operator[] (const size_t index) noexcept;
	T operator[] (const size_t index) const noexcept;
};

template<typename T>
struct Vector<T, 3> final {

	T elements[3];

	constexpr Vector() noexcept = default;
	constexpr Vector(const Vector<T, 3>&) noexcept = default;
	Vector<T, 3>& operator= (const Vector<T, 3>&) noexcept = default;
	~Vector() noexcept = default;

	explicit Vector(T value) noexcept;
	Vector(std::initializer_list<T> list) noexcept;

	T& operator[] (const size_t index) noexcept;
	T operator[] (const size_t index) const noexcept;
};

template<typename T>
struct Vector<T, 4> final {

	T elements[4];

	constexpr Vector() noexcept = default;
	constexpr Vector(const Vector<T, 4>&) noexcept = default;
	Vector<T, 4>& operator= (const Vector<T, 4>&) noexcept = default;
	~Vector() noexcept = default;

	explicit Vector(T value) noexcept;
	Vector(std::initializer_list<T> list) noexcept;

	T& operator[] (const size_t index) noexcept;
	T operator[] (const size_t index) const noexcept;
};

// Vector functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

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
template<typename T, size_t N>
T length(const Vector<T,N>& vector) noexcept;

/**
 * @brief Sums the squares of each element in the vector (squared norm, i.e. squared length).
 * @return squared norm of the vector
 */
template<typename T, size_t N>
T squaredLength(const Vector<T,N>& vector) noexcept;

/**
 * @brief Normalizes the vector and produces a unit vector.
 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing
 * in the same direction with the norm 1. Returns 0-vector if the norm is 0.
 * @return the unit vector
 */
template<typename T, size_t N>
Vector<T,N> normalize(const Vector<T,N>& vector) noexcept;

template<typename T, size_t N>
T dot(const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @brief Does an element-wise multiplication of two vectors.
 * @param the other vector
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> elemMult(const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @return the sum of all the elements in the vector
 */
template<typename T, size_t N>
T sum(const Vector<T,N>& vector) noexcept;

template<typename T, size_t N>
size_t hash(const Vector<T,N>& vector) noexcept;

template<typename T, size_t N>
std::string to_string(const Vector<T,N>& vector) noexcept;

// Operators (arithmetic & assignment)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T, N>& operator+= (Vector<T, N>& left, const Vector<T, N>& right) noexcept;

template<typename T, size_t N>
Vector<T, N>& operator-= (Vector<T, N>& left, const Vector<T, N>& right) noexcept;

template<typename T, size_t N>
Vector<T, N>& operator*= (Vector<T, N>& left, const T& right) noexcept;

/** @sfz_assert_debug rhs element != 0 */
template<typename T, size_t N>
Vector<T, N>& operator/= (Vector<T, N>& left, const T& right) noexcept;

// Operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T, N> operator+ (const Vector<T, N>& left, const Vector<T, N>& right) noexcept;

template<typename T, size_t N>
Vector<T, N> operator- (const Vector<T, N>& left, const Vector<T, N>& right) noexcept;

template<typename T, size_t N>
Vector<T, N> operator- (const Vector<T, N>& vector) noexcept;

template<typename T, size_t N>
Vector<T, N> operator* (const Vector<T, N>& left, const T& right) noexcept;

template<typename T, size_t N>
Vector<T, N> operator* (const T& left, const Vector<T, N>& right) noexcept;

/** @sfz_assert_debug rhs element != 0 */
template<typename T, size_t N>
Vector<T, N> operator/ (const Vector<T, N>& left, const T& right) noexcept;

// Operators (comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
bool operator== (const Vector<T, N>& left, const Vector<T, N>& right) noexcept;

template<typename T, size_t N>
bool operator!= (const Vector<T, N>& left, const Vector<T, N>& right) noexcept;

// Operators (other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept;

// Standard iterator functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T* begin(Vector<T,N>& vector) noexcept;

template<typename T, size_t N>
const T* begin(const Vector<T, N>& vector) noexcept;

template<typename T, size_t N>
const T* cbegin(const Vector<T, N>& vector) noexcept;

template<typename T, size_t N>
T* end(Vector<T, N>& vector) noexcept;

template<typename T, size_t N>
const T* end(const Vector<T, N>& vector) noexcept;

template<typename T, size_t N>
const T* cend(const Vector<T, N>& vector) noexcept;

// Standard typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;

using vec2i = Vector<int32_t, 2>;
using vec3i = Vector<int32_t, 3>;
using vec4i = Vector<int32_t, 4>;

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
#include "VectorSupport.hpp"
#endif