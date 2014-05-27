#pragma once
#ifndef SFZ_MATH_VECTOR_HPP
#define SFZ_MATH_VECTOR_HPP

#include <array>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iterator>

namespace sfz {

	template<class T, std::size_t N>
	class Vector {
	public:
		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		
		/**
		 * @brief Default constructor, initializes all elements to 0.
		 */
		Vector();

		/**
		 * @brief Copy constructor.
		 * Copies all elements from specified vector to this vector.
		 * @param vector the vector to copy
		 */
		Vector(const Vector<T,N>& vector);

		/**
		 * @brief Copy cast constructor.
		 * Copies all elements from specified vector and attempts to static_cast them to this vectors type.
		 * @param vector the vector to copy
		 */
		template<class T2>
		explicit Vector(const Vector<T2,N>& vector);

		/**
		 * @brief Initializer list constructor.
		 * @throws std::invalid_argument if vector and initializer list are different sizes
		 * @param list the initializer_list with values to fill the vector with
		 */
		Vector(std::initializer_list<T> list);

		virtual ~Vector() = default;

		// Public functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns the element at the specified index.
		 * @throws std::out_of_range if index is out of range
		 * @param index the index of the element
		 * @return the element at the specified index
		 */
		T get(std::size_t index) const;

		/**
		 * @brief Assigns value to the specified index.
		 * @throws std::out_of_range if index is out of range
		 * @param index the index to assign value to
		 * @param value the value to assign
		 */
		void set(std::size_t index, T value);

		/**
		 * @brief Calculates the norm (length) of the vector.
		 * Note when using discrete types (int, long, etc): This method will square each element of the vector and add
		 * them together before taking the square root. This might result in an overflow if the elements are too
		 * large. In that case the result of this function will be undefined. Also, the return type will still be a
		 * discrete type, meaning that the result will be truncated. If this is a problem you should use the
		 * squaredNorm() function and do the square root yourself.
		 * @return norm of the vector
		 */
		T norm() const;

		/**
		 * @brief Calculates the squared norm (length) of the vector.
		 * Sums the squares of each element in the vector. Take the sqrt of this sum and you get the norm (length).
		 * This function is useful if you only need to compare vectors as you can skip the expensive sqrt operation.
		 * @return squared norm of the vector
		 */
		T squaredNorm() const;

		/**
		 * @brief Normalizes the vector and produces a unit vector.
		 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing in the same
		 * direction with the norm 1.
		 * @return the unit vector
		 */
		Vector<T,N> normalize() const;

		/**
		 * @brief Calculates the dot (scalar) product between this vector and the other vector.
		 * Might overflow and return weird stuff if vector contains many, very large elements.
		 * @param other the other vector
		 * @return the dot product
		 */
		T dot(const Vector<T,N>& other) const;

		// Standard iterator functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		using iterator = typename std::array<T,N>::iterator;
		using const_iterator = typename std::array<T,N>::const_iterator;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		// Internal operators
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns a reference to element at the specified index.
		 * @throws std::out_of_range if index is out of range
		 * @param index the index of the element
		 * @return reference to element at the specified index
		 */
		T& operator [](std::size_t index);

		/**
		 * @brief Returns a const reference to element at the specified index.
		 * @throws std::out_of_range if index is out of range
		 * @param index the index of the element
		 * @return const reference to element at the specified index
		 */
		const T& operator [](std::size_t index) const;

		// Internal operators (Arithmetic & Assignment)
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Assignment addition operator.
		 * Adds the lhs and rhs vectors and saves the result in the lhs operand.
		 * @param right the rhs vector
		 * @return reference to the modified vector
		 */
		Vector<T,N>& operator +=(const Vector<T,N>& right);

		/**
		 * @brief Assignment subtraction operator.
		 * Subtracts the rhs vector from the lhs vector and saves the result in the lhs operand.
		 * @param right the rhs vector
		 * @return reference to the modified vector
		 */
		Vector<T,N>& operator -=(const Vector<T,N>& right);

		/**
		 * @brief Assignment multiplication operator.
		 * Multiplies the lhs vector with the rhs element and saves the result in the lhs operand.
		 * @param right the rhs element
		 * @return reference to the modified vector
		 */
		Vector<T,N>& operator *=(const T& right);

		/**
		 * @brief Assignment division operator.
		 * Divides the lhs vector with the rhs element and saves the result in the lhs operand.
		 * @throws std::domain_error if rhs element is zero
		 * @param right the rhs element
		 * @return reference to the modified vector
		 */
		Vector<T,N>& operator /=(const T& right);

	private:
		std::array<T,N> array;
	};

	// External functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @relates sfz::Vector
	 * @brief Calculates the norm (length) of the vector.
	 * @see sfz::Vector<T,N>::norm()
	 * @param vector the vector to calculate norm of
	 * @return norm of the vector
	 */
	template<class T, std::size_t N>
	T norm(const Vector<T,N>& vector);

	/**
	 * @relates sfz::Vector
	 * @brief Normalizes the vector and produces a unit vector.
	 * Simply divides this vector by it's length to get the unit vector, i.e. the vector pointing in the same
	 * direction with the norm 1.
	 * @param vector the vector to normalize
	 * @return the unit vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> normalize(const Vector<T,N>& vector);


	// External Operators (Arithmetic)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	/**
	 * @relates sfz::Vector
	 * @brief Addition operator.
	 * Adds the lhs and rhs vectors and returns the result in a new vector.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator +(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Subtraction operator.
	 * Subtracts the rhs vector from the lhs vector and returns the result in a new vector.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator -(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Negation operator.
	 * Negates every element in the rhs vector and returns the result in a new vector.
	 * @param right the rhs vector
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator -(const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Multiplication operator.
	 * Multiplies the lhs vector with the rhs element and returns the result in a new vector.
	 * @param left the lhs vector
	 * @param right the rhs element
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator *(const Vector<T,N>& left, const T& right);

	/**
	 * @relates sfz::Vector
	 * @brief Multiplication operator.
	 * Multiplies the rhs vector with the lhs element and returns the result in a new vector.
	 * @param left the lhs element
	 * @param right the rhs vector
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator *(const T& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Division operator.
	 * Divides the lhs vector with the rhs element and returns the result in a new vector.
	 * @throws std::domain_error if rhs element is zero
	 * @param left the lhs vector
	 * @param right the rhs element
	 * @return the resulting vector
	 */
	template<class T, std::size_t N>
	Vector<T,N> operator /(const Vector<T,N>& left, const T& right);

	// External Operators (Comparison)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @relates sfz::Vector
	 * @brief Equality operator.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs and rhs vectors are equal
	 */
	template<class T, std::size_t N>
	bool operator ==(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Inequality operator.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs and rhs vectors aren't equal
	 */
	template<class T, std::size_t N>
	bool operator !=(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Smaller than operator.
	 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs vector is smaller than the rhs vector
	 */	
	template<class T, std::size_t N>
	bool operator <(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Larger than operator.
	 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs vector is larger than the rhs vector
	 */	
	template<class T, std::size_t N>
	bool operator >(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Smaller than or equal operator.
	 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs vector is smaller than or equal to the rhs vector
	 */	
	template<class T, std::size_t N>
	bool operator <=(const Vector<T,N>& left, const Vector<T,N>& right);

	/**
	 * @relates sfz::Vector
	 * @brief Larger than or equal operator.
	 * The size of the vectors is defined by the length() function, which is also what is compared in this function.
	 * @param left the lhs vector
	 * @param right the rhs vector
	 * @return whether the lhs vector is larger than or equal to the rhs vector
	 */	
	template<class T, std::size_t N>
	bool operator >=(const Vector<T,N>& left, const Vector<T,N>& right);	

	// Typedefs
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	using vec2f = Vector<float,2>;
	using vec2d = Vector<double,2>;
	using vec2i = Vector<int,2>;
	using vec2l = Vector<long,2>;
	using vec3f = Vector<float,3>;
	using vec3d = Vector<double,3>;
	using vec3i = Vector<int,3>;
	using vec3l = Vector<long,3>;

	// Element access constants
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	/**
	 * @brief Constant for accessing the x element of a sfz::Vector (x == 0).
	 */
	const std::size_t x = 0;

	/**
	 * @brief Constant for accessing the y element of a sfz::Vector (y == 1).
	 */
	const std::size_t y = 1;

	/**
	 * @brief Constant for accessing the z element of a sfz::Vector (z == 2).
	 */
	const std::size_t z = 2;
}
#include "Vector.inl"
#endif