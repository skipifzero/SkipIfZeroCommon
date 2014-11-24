#pragma once
#ifndef SFZ_MATH_MATRIX_HPP
#define SFZ_MATH_MATRIX_HPP

#include <initializer_list>
#include <string>

#include "sfz/math/Vector.hpp"

namespace sfz {

using std::size_t;

// m rows, n cols
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

	size_t hash() const noexcept;

	std::string to_string() const noexcept;

	// Operators (Arithmetic & Assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Matrix<T,M,N>& operator= (const Matrix<T,M,N>&) = default;

	Matrix<T,M,N>& operator+= (const Matrix<T,M,N>& other) noexcept;

	Matrix<T,M,N>& operator-= (const Matrix<T,M,N>& other) noexcept;

	// Operators (comparison)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	bool operator== (const Matrix<T,M,N>& other) const noexcept;

	bool operator!= (const Matrix<T,M,N>& other) const noexcept;
};

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

template<typename T>
using mat2 = Matrix<T, 2, 2>;
using mat2f = mat2<float>;
using mat2d = mat2<double>;
using mat2i = mat2<int>;
using mat2l = mat2<long>;

template<typename T>
using mat3 = Matrix<T, 3, 3>;
using mat3f = mat3<float>;
using mat3d = mat3<double>;
using mat3i = mat3<int>;
using mat3l = mat3<long>;

template<typename T>
using mat4 = Matrix<T, 4, 4>;
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