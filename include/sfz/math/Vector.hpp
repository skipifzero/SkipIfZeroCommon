#pragma once
#ifndef SFZ_MATH_VECTOR_HPP
#define SFZ_MATH_VECTOR_HPP

#include <array>
#include <initializer_list>
#include <stdexcept> // std::invalid_argument, std::out_of_range, std::domain_error
#include <algorithm> // std::copy
#include <functional> // std::hash
#include <cmath> // std::sqrt
#include <iterator>
#include <string>
#include <iostream> // std::ostream

#include "sfz/math/MathConstants.hpp"

namespace sfz {

using std::size_t;

/**
 * @brief A mathematical vector POD class that imitates a built-in primitive.
 *
 * The template is designed to be used with float and doubles in first hand, and everything should work as expected
 * with them. Integral types can also be used, but some things will not function as expected due to truncation. Most
 * notably taking the norm will most likely not give the correct result as it involves taking the square root. Another
 * trouble with integral types is the risk of overflow. When calculating the norm you have to square each element in
 * the vector, which might wery well overflow if you have large elements.
 *
 * Satisfies the conditions of std::is_pod, std::is_trivial and std::is_standard_layout if used with standard
 * primitives.
 *
 * @param T the element type
 * @param N the amount of elements in the vector
 *
 * @author Peter Hillerström <peter@hstroem.se>
 */
template<typename T, size_t N>
class Vector final {
public:
	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	/**
	 * @brief Default constructor, value of elements is undefined.
	 */
	Vector() = default;

	/**
	 * @brief Copy constructor.
	 * @param vector the vector to copy
	 */
	Vector(const Vector<T,N>& vector) = default;

	/**
	 * @brief Copy cast constructor.
	 * Copies all elements from specified vector and attempts to static_cast them to this vectors type.
	 * @param vector the vector to copy
	 */
	template<typename T2>
	explicit Vector(const Vector<T2,N>& vector);

	/**
	 * @brief Initializer list constructor.
	 * @throws std::invalid_argument if vector and initializer list are different sizes
	 * @param list the initializer_list with values to fill the vector with
	 */
	Vector(std::initializer_list<T> list);

	~Vector() = default;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Returns the element at the specified index.
	 * @throws std::out_of_range if index is out of range
	 * @param index the index of the element
	 * @return the element at the specified index
	 */
	T get(const size_t index) const;

	/**
	 * @brief Assigns value to the specified index.
	 * @throws std::out_of_range if index is out of range
	 * @param index the index to assign value to
	 * @param value the value to assign
	 */
	void set(const size_t index, const T value);

	/**
	 * @brief Fills the vector with the specified value.
	 * Assigns each elemnt in the vector the specified value
	 * @param value the value to fill vector with
	 */
	void fill(const T value) noexcept;

	/**
	 * @brief Calculates the norm (length) of the vector.
	 * Note when using discrete types (int, long, etc): This method will square each element of the vector and add
	 * them together before taking the square root. This might result in an overflow if the elements are too large. In
	 * that case the result of this function will be undefined. Also, the return type will still be a discrete type,
	 * meaning that the result will be truncated. If this is a problem you should use the squaredNorm() function and
	 * do the square root yourself.
	 * @return norm of the vector
	 */
	T norm() const noexcept;

	/**
	 * @brief Calculates the squared norm (length) of the vector.
	 * Sums the squares of each element in the vector. Take the sqrt of this sum and you get the norm (length).
	 * This function is useful if you only need to compare vectors as you can skip the expensive sqrt operation.
	 * @return squared norm of the vector
	 */
	T squaredNorm() const noexcept;

	/**
	 * @brief Normalizes the vector and produces a unit vector.
	 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing in the same
	 * direction with the norm 1.
	 * @return the unit vector
	 */
	Vector<T,N> normalize() const noexcept;

	/**
	 * @brief Calculates the dot (scalar) product between this vector and the other vector.
	 * Might overflow and return weird stuff if vector contains many, very large elements.
	 * @param other the other vector
	 * @return the dot product
	 */
	T dot(const Vector<T,N>& other) const noexcept;

	/**
	 * @brief Does an element-wise multiplication of two vectors.
	 * @param the other vector
	 * @return the resulting vector
	 */
	Vector<T,N> elemMult(const Vector<T,N>& other) const noexcept;

	/**
	 * @brief Sums the elements in the vector.
	 * @return the sum of all the elements in the vector
	 */
	T sum() const noexcept;

	/**
	 * @brief Projects the vector onto another vector.
	 * Makes a scalar projection of the vector onto the specifed target vector. The resulting vector will be equal to
	 * the target vector times a scalar constant.
	 * @throws std::domain_error if target vector is 0
	 * @param target the vector to project onto
	 * @return the resulting projection in vector form
	 */
	Vector<T,N> projectOnto(const Vector<T,N>& target) const;

	/**
	 * @brief Calculates distance vector from this vector to another vector.
	 * This is the same thing as doing 'other - this'.
	 * @param other the other vector
	 * @return the resulting vector
	 */
	Vector<T,N> distance(const Vector<T,N>& other) const noexcept;

	/**
	 * @brief Hashes the vector.
	 * @return hash of the vector
	 */
	size_t hash() const noexcept;

	/**
	 * @brief Returns string representation of the vector.
	 * @return string representation of the vector
	 */
	std::string to_string() const noexcept;

	// Standard iterator functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	using iterator = typename std::array<T,N>::iterator;
	using const_iterator = typename std::array<T,N>::const_iterator;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	// Member operators (access)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Returns a reference to element at the specified index.
	 * Unlike get() if index is out of range undefined behavior occurs.
	 * @param index the index of the element
	 * @return reference to element at the specified index
	 */
	T& operator[] (const size_t index) noexcept;

	/**
	 * @brief Returns a const reference to element at the specified index.
	 * Unlike get() if index is out of range undefined behavior occurs.
	 * @param index the index of the element
	 * @return const reference to element at the specified index
	 */
	const T& operator[] (const size_t index) const noexcept;

	// Member operators (Arithmetic & Assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Assignment addition operator.
	 * Adds the lhs and rhs vectors and saves the result in the lhs operand.
	 * @param right the rhs vector
	 * @return reference to the modified vector
	 */
	Vector<T,N>& operator+= (const Vector<T,N>& right) noexcept;

	/**
	 * @brief Assignment subtraction operator.
	 * Subtracts the rhs vector from the lhs vector and saves the result in the lhs operand.
	 * @param right the rhs vector
	 * @return reference to the modified vector
	 */
	Vector<T,N>& operator-= (const Vector<T,N>& right) noexcept;

	/**
	 * @brief Assignment multiplication operator.
	 * Multiplies the lhs vector with the rhs element and saves the result in the lhs operand.
	 * @param right the rhs element
	 * @return reference to the modified vector
	 */
	Vector<T,N>& operator*= (const T& right) noexcept;

	/**
	 * @brief Assignment division operator.
	 * Divides the lhs vector with the rhs element and saves the result in the lhs operand.
	 * @throws std::domain_error if rhs element is zero
	 * @param right the rhs element
	 * @return reference to the modified vector
	 */
	Vector<T,N>& operator/= (const T& right);

private:
	std::array<T,N> mElements;
};

// Free (non-member) functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

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
 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing in the same
 * direction with the norm 1.
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
 * @throws std::domain_error if norm of vector is 0
 * @param vector the 2-dimensional vector to calculate angle of
 * @return the angle between the vector and the x-axis
 */
template<typename T>
T angle(const Vector<T,2>& vector);

/**
 * @relates sfz::Vector
 * @brief Calculates the positive angle between two vectors.
 * The angle will be in range [0, Pi] and will always be the smallest possible angle between the vectors.
 * @throws std::domain_error if norm of vectorA or B is 0
 * @param vectorA the first vector
 * @param vectorB the second vector
 * @return the angle between the two vectors
 */
template<typename T, size_t N>
T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB);

/**
 * @relates sfz::Vector
 * @brief Rotates a 2-dimensional vector with the specified angle around origo.
 * @param vector the vector to rotate
 * @param angle the angle to rotate in radians
 * @return the resulting vector
 */
template<typename T>
Vector<T,2> rotate(const Vector<T,2>& vector, const T angle) noexcept;

// Free (non-member) operators (Arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @relates sfz::Vector
 * @brief Addition operator.
 * Adds the lhs and rhs vectors and returns the result in a new vector.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator+ (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Subtraction operator.
 * Subtracts the rhs vector from the lhs vector and returns the result in a new vector.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Negation operator.
 * Negates every element in the rhs vector and returns the result in a new vector.
 * @param right the rhs vector
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Multiplication operator.
 * Multiplies the lhs vector with the rhs element and returns the result in a new vector.
 * @param left the lhs vector
 * @param right the rhs element
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator* (const Vector<T,N>& left, const T& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Multiplication operator.
 * Multiplies the rhs vector with the lhs element and returns the result in a new vector.
 * @param left the lhs element
 * @param right the rhs vector
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator* (const T& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Division operator.
 * Divides the lhs vector with the rhs element and returns the result in a new vector.
 * @throws std::domain_error if rhs element is zero
 * @param left the lhs vector
 * @param right the rhs element
 * @return the resulting vector
 */
template<typename T, size_t N>
Vector<T,N> operator/ (const Vector<T,N>& left, const T& right);

// Free (non-member) operators (Comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @relates sfz::Vector
 * @brief Equality operator.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs and rhs vectors are equal
 */
template<typename T, size_t N>
bool operator== (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Inequality operator.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs and rhs vectors aren't equal
 */
template<typename T, size_t N>
bool operator!= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Smaller than operator.
 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs vector is smaller than the rhs vector
 */	
template<typename T, size_t N>
bool operator< (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Larger than operator.
 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs vector is larger than the rhs vector
 */	
template<typename T, size_t N>
bool operator> (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Smaller than or equal operator.
 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs vector is smaller than or equal to the rhs vector
 */	
template<typename T, size_t N>
bool operator<= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

/**
 * @relates sfz::Vector
 * @brief Larger than or equal operator.
 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
 * @param left the lhs vector
 * @param right the rhs vector
 * @return whether the lhs vector is larger than or equal to the rhs vector
 */	
template<typename T, size_t N>
bool operator>= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept;

// Free (non-member) operators (Other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @relates sfz::Vector
 * @brief Ostream operator
 * The serialization of the vector is defined by its to_string() function.
 * @param ostream the output stream
 * @param vector the vector to serialize
 * @return ostream the output straem
 */	
template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept;

// Standard typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
using Vector2 = Vector<T,2>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;
using Vector2l = Vector2<long>;

template<typename T>
using Vector3 = Vector<T,3>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;
using Vector3l = Vector3<long>;

template<typename T, size_t N>
using vec = Vector<T,N>;

template<typename T>
using vec2 = vec<T,2>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2i = vec2<int>;
using vec2l = vec2<long>;

template<typename T>
using vec3 = vec<T,3>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;
using vec3i = vec3<int>;
using vec3l = vec3<long>;

} // namespace sfz

// Specializations of standard library for sfz::Vector
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t N>
struct hash<sfz::Vector<T,N>> {
	size_t operator() (const sfz::Vector<T,N>& vector) const;
};

} // namespace std

#include "Vector.inl"
#endif