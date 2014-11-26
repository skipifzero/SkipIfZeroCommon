#pragma once
#ifndef SFZ_MATH_MATRIX_HPP
#define SFZ_MATH_MATRIX_HPP

#include <initializer_list>
#include <string>
#include <iostream> // std::ostream

#include "sfz/math/Vector.hpp"

namespace sfz {

using std::size_t;

/**
 * @brief A mathematical Matrix POD class that imitates a built-in primitive.
 * 
 * It's important to note that the implementation of this Matrix is column-major order (and
 * publically accessable). The reason for this is that this seems to be the most natural way to
 * interact with OpenGL. What might be confusing is that some parts of the interface (most notably
 * the initalizer_list constructor) uses row-major order as it's more natural to write matrices
 * in code that way. Be extra careful when accesing or setting specific values in a matrix.
 *
 * The template is designed to be used with floating point types in first hand. It's possible that
 * using integer types might lead to truncation in some instances.
 *
 * Satisfies the conditions of std::is_pod, std::is_trivial and std::is_standard_layout if used
 * with standard primitives.
 *
 * @param T the element type
 * @param M the amount of rows in the Matrix
 * @param N the amount of columns in the Matrix
 *
 * @author Peter Hillerström
 */
template<typename T, size_t M, size_t N>
struct Matrix final {

	// Public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief The internal COLUMN-MAJOR order array of this Matrix.
	 * This is column-major order (i.e. N columns of size M), so the pointer can be supplied to
	 * OpenGL directly with the transpose flag set to GL_FALSE.
	 */
	Vector<T,M> mElements[N];

	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Default constructor, value of elements is undefined.
	 */
	Matrix() = default;

	Matrix(const Matrix<T,M,N>&) = default;

	/**
	 * @brief Constructs a matrix with the given elements given in ROW-MAJOR order.
	 * The elements are given in row-major order because it's more natural to write and read a
	 * matrix that way in source. This is however not how the elements will be saved as the
	 * internal representation uses column-major order. Any unspecified elements will be set to 0.
	 * @assert if any of the lists are larger than the row or column it's trying to fill
	 * @param list the (column) initializer list of (row) initializer lists
	 */
	Matrix(std::initializer_list<std::initializer_list<T>> list) noexcept;

	~Matrix() = default;

	// Member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Returns a reference to element at the specified location.
	 * No range checking is done, zero-indexing is used.
	 * @param i the i:th row
	 * @param j the j:th column
	 * @return reference to element at the specified location
	 */
	T& get(size_t i, size_t j) noexcept;

	/**
	 * @brief Returns the element at the specified location.
	 * No range checking is done, zero-indexing is used.
	 * @param i the i:th row
	 * @param j the j:th column
	 * @return the element at the specified location
	 */
	T get(size_t i, size_t j) const noexcept;

	size_t rows() const noexcept { return M; }

	size_t cols() const noexcept { return N; }

	/**
	 * @brief Element-wise multiplication
	 * @return the resulting matrix
	 */
	Matrix<T,M,N> elemMult(const Matrix<T,M,N>& other) const noexcept;

	Matrix<T,N,M> transpose() const noexcept;

	size_t hash() const noexcept;

	std::string to_string() const noexcept;

	// Operators (arithmetic & assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Matrix<T,M,N>& operator= (const Matrix<T,M,N>&) = default;

	Matrix<T,M,N>& operator+= (const Matrix<T,M,N>& other) noexcept;

	Matrix<T,M,N>& operator-= (const Matrix<T,M,N>& other) noexcept;

	Matrix<T,M,N>& operator*= (const T& other) noexcept;

	// Operators (arithmetic)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Matrix<T,M,N> operator+ (const Matrix<T,M,N>& other) const noexcept;

	Matrix<T,M,N> operator- (const Matrix<T,M,N>& other) const noexcept;

	template<size_t P>
	Matrix<T,M,P> operator* (const Matrix<T,N,P>& other) const noexcept;

	Matrix<T,M,N> operator* (const T& other) const noexcept;

	// Operators (comparison)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	bool operator== (const Matrix<T,M,N>& other) const noexcept;

	bool operator!= (const Matrix<T,M,N>& other) const noexcept;
};

// Non-member operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t M, size_t N>
Matrix<T,M,N> operator* (const T& lhs, const Matrix<T,M,N>& rhs) noexcept;

// Non-member operators (others)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t M, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Matrix<T,M,N>& matrix) noexcept;

// Standard typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
using Matrix2 = Matrix<T, 2, 2>;
using Matrix2f = Matrix2<float>;
using Matrix2d = Matrix2<double>;
using Matrix2i = Matrix2<int>;
using Matrix2l = Matrix2<long>;

template<typename T>
using Matrix3 = Matrix<T, 3, 3>;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;
using Matrix3i = Matrix3<int>;
using Matrix3l = Matrix3<long>;

template<typename T>
using Matrix4 = Matrix<T, 4, 4>;
using Matrix4f = Matrix4<float>;
using Matrix4d = Matrix4<double>;
using Matrix4i = Matrix4<int>;
using Matrix4l = Matrix4<long>;

template<typename T, size_t M, size_t N>
using mat = Matrix<T, M, N>;

template<typename T>
using mat2 = mat<T, 2, 2>;
using mat2f = mat2<float>;
using mat2d = mat2<double>;
using mat2i = mat2<int>;
using mat2l = mat2<long>;

template<typename T>
using mat3 = mat<T, 3, 3>;
using mat3f = mat3<float>;
using mat3d = mat3<double>;
using mat3i = mat3<int>;
using mat3l = mat3<long>;

template<typename T>
using mat4 = mat<T, 4, 4>;
using mat4f = mat4<float>;
using mat4d = mat4<double>;
using mat4i = mat4<int>;
using mat4l = mat4<long>;

} // namespace sfz

// Specializations of standard library for sfz::Matrix
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t M, size_t N>
struct hash<sfz::Matrix<T,M,N>> {
	size_t operator() (const sfz::Matrix<T,M,N>& matrix) const noexcept;
};

} // namespace std

#include "sfz/math/Matrix.inl"
#endif