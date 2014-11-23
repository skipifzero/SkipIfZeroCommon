#pragma once
#ifndef SFZ_MATH_MATRIX_HPP
#define SFZ_MATH_MATRIX_HPP

#include "sfz/math/Vector.hpp"

namespace sfz {

using std::size_t;

// m rows, n cols
template<typename T, size_t M, size_t N>
struct Matrix final {

	// Public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief The internal array of N columns of size M representing this Matrix.
	 * This is column-major order, so the 'mElements' pointer can be supplied to OpenGL directly
	 * with the transpose flag set to GL_FALSE.
	 */
	Vector<T,M> mElements[N];

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Default constructor, value of elements is undefined.
	 */
	Matrix() = default;
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

#include "sfz/math/Matrix.inl"
#endif