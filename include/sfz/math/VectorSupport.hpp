#pragma once
#ifndef SFZ_MATH_VECTOR_SUPPORT_HPP
#define SFZ_MATH_VECTOR_SUPPORT_HPP

#include <cmath>
#include "sfz/math/Vector.hpp"

namespace sfz {

/**
 * This header includes support functions for the Vector class.
 *
 * @author Peter Hillerström
 */

/**
 * @relates sfz::Vector
 * @brief Calculates the cross product of the vectors.
 * @return the resulting vector
 */
template<typename T>
Vector<T,3> cross(const Vector<T,3>& vectorA, const Vector<T,3>& vectorB) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the positive angle between two vectors.
 * The angle will be in range [0, Pi] and will always be the smallest possible angle between the
 * vectors.
 * @assert norm of vectorA or B != 0
 * @return the angle between the two vectors
 */
template<typename T, size_t N>
T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept;

/**
 * @relates sfz::Vector
 * @brief Calculates the positive angle between the specified vector and the x-axis in radians.
 * The angle will be in the range [0, 2*Pi).
 * @assert norm of vector != 0
 * @return the angle between the vector and the x-axis
 */
template<typename T>
T angle(const Vector<T,2>& vector) noexcept;

/**
 * @relates sfz::Vector
 * @brief Rotates a 2-dimensional vector with the specified angle around origo.
 * @return the resulting vector
 */
template<typename T>
Vector<T,2> rotate(const Vector<T,2>& vector, const T angle) noexcept;

} // namespace sfz

#include "sfz/math/VectorSupport.inl"
#endif