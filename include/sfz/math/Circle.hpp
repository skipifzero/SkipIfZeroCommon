#pragma once
#ifndef SFZ_MATH_CIRCLE_HPP
#define SFZ_MATH_CIRCLE_HPP

#include <stdexcept> // std::invalid_argument
#include <functional> // std::hash
#include <string>
#include "sfz/math/MathConstants.hpp"
#include "sfz/math/Vector.hpp"
#include "sfz/math/Alignment.hpp"

// Forward declares Rectangle, is included after complete declaration of Circle.
namespace sfz {
	template<typename T>
	class Rectangle;
}

namespace sfz {

	/**
	 * @brief A class representing a Circle.
	 *
	 * The two alignment variables decide how the Circle is anchored to the position. Basically imagine an invsible
	 * square around the circle, BOTTOM LEFT is the bottom left corner on that square, etc.
	 *
	 * Beware if using integral types, some things like changing alignment and overlap checks might mess up due to
	 * truncation.
	 *
	 * @param T the element type
	 *
	 * @author Peter Hillerström <peter@hstroem.se>
	 * @date 2014-08-08
	 */
	template<typename T>
	class Circle final {
	public:
		// Static constants
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief The default HorizontalAlign.
		 */
		static const HorizontalAlign DEFAULT_HORIZONTAL_ALIGN;

		/**
		 * @brief The default VerticalAlign.
		 */
		static const VerticalAlign DEFAULT_VERTICAL_ALIGN;

		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		// No default constructor.
		Circle() = delete;
		
		/**
		 * @brief Basic copy-constructor.
		 * @param circle the Circle to copy
		 */
		Circle(const Circle<T>& circle) = default;
		
		/**
		 * @brief Copy cast constructor.
		 * Attempts to static_cast all types from specified circle to specified type.
		 * @param circle the circle to copy
		 */
		template<typename T2>
		explicit Circle(const Circle<T2>& circle);

		/**
		 * @brief Copy constructor that changes alignment.
		 * The alignment is changed as it would be if changeHorizontalAlign() or changeVerticalAlign() were called.
		 * @param circle the Circle to copy
		 * @param horizontalAlign the HorizontalAlign to change to
		 * @param verticalAlign the VerticalAlign to change to
		 */
		Circle(const Circle<T>& circle, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign);

		/**
		 * @brief Circle constructor.
		 * If you don't specify the alignment variables they will be set to the default values.
		 * @throw std::invalid_argument if radius < 0
		 * @param position the position
		 * @param radius the radius
		 * @param horizontalAlign the HorizontalAlign
		 * @param verticalAlign the VerticalAlign
		 */
		Circle(vec2<T> position, T radius, 
		       HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		       VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		/**
		 * @brief Circle constructor.
		 * If you don't specify the alignment variables they will be set to the default values.
		 * @throw std::invalid_argument if radius < 0
		 * @param x the x-position
		 * @param y the y-position
		 * @param radius the radius
		 * @param horizontalAlign the HorizontalAlign
		 * @param verticalAlign the VerticalAlign
		 */
		Circle(T x, T y, T radius,
		       HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		       VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		~Circle() = default;

		// Public member functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns whether the specified vector is inside this Circle or not.
		 * It's worth noting that this function uses 
		 * @param point the specified vector
		 * @return whether the specified vector is inside this Circle or not
		 */
		bool overlap(const vec2<T>& point) const;

		/**
		 * @brief Returns whether the specified Circle overlaps with this Circle or not.
		 * @param circle the specified circle
		 * @return whether the specified Circle overlaps with this Circle or not
		 */
		bool overlap(const Circle<T>& circle) const;

		/**
		 * @brief Returns whether the specified Rectangle overlaps with this Circle or not.
		 * @param rectangle the specified rectangle
		 * @return whether the specified Rectangle overlaps with this Circle or not
		 */
		bool overlap(const Rectangle<T>& rect) const;

		/**
		 * @brief Returns the area of this Circle.
		 * @return the area of this Circle
		 */
		T area() const;

		/**
		 * @brief Returns the circumference of this Circle.
		 * @return the circumference of this Circle
		 */
		T circumference() const;

		/**
		 * @brief Hashes the rectangle.
		 * @return hash of rectangle
		 */
		size_t hash() const;

		/**
		 * @brief Returns string representation of the circle.
		 * @return string representation of the circle
		 */
		std::string to_string() const;

		// Getters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Returns the position of this Circle.
		 * @return position of this Circle
		 */
		vec2<T> getPosition() const;

		/**
		 * @brief Returns the x-position of this Circle.
		 * @return x-position of this Circle
		 */
		T getX() const;
		
		/**
		 * @brief Returns the y-position of this Circle.
		 * @return y-position of this Circle
		 */
		T getY() const;

		/**
		 * @brief Returns the radius of this Circle.
		 * @return radius of this Circle
		 */
		T getRadius() const;

		/**
		 * @brief Returns the HorizontalAlign of this Circle.
		 * @return HorizontalAlign of this Circle
		 */
		HorizontalAlign getHorizontalAlign() const;

		/**
		 * @brief Returns the VerticalAlign of this Circle.
		 * @return VerticalAlign of this Circle
		 */
		VerticalAlign getVerticalAlign() const;

		// Setters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Sets the position.
		 * @param position the position to set
		 */
		void setPosition(const vec2<T>& position);

		/**
		 * @brief Sets the position.
		 * @param x the x-position to set
		 * @param y the y-position to set
		 */
		void setPosition(T x, T y);

		/**
		 * @brief Sets the x-position.
		 * @param x the x-position to set
		 */
		void setX(T x);

		/**
		 * @brief Sets the y-position.
		 * @param y the y-position to set
		 */
		void setY(T y);

		/**
		 * @brief Sets the radius.
		 * @throw std::invalid_argument if radius < 0
		 * @param radius the radius to set
		 */
		void setRadius(T radius);

		/**
		 * @brief Simply sets the HorizontalAlign wihout doing anything else.
		 * Doesn't update the position, so the Circle is actually shifted slightly by this function. If this is
		 * unintended you should call changeHorizontalAlign() instead which also updates the position.
		 * @see changeHorizontalAlign()
		 * @param horizontalAlign the HorizontalAlign to set
		 */
		void setHorizontalAlign(HorizontalAlign horizontalAlign);

		/**
		 * @brief Simply sets the VerticalAlign wihout doing anything else.
		 * Doesn't update the position, so the Circle is actually shifted slightly by this function. If this is
		 * unintended you should call changeVerticalAlign() instead which also updates the position.
		 * @see changeVerticalAlign()
		 * @param verticalAlign the VerticalAlign to set
		 */
		void setVerticalAlign(VerticalAlign verticalAlign);

		/**
		 * @brief Changes the HorizontalAlign of this Circle and updates the internal position reflecting this.
		 * The position is updated so the Circle's actual position is the same afterwards, i.e. not shifted. If this
		 * is not wanted setHorizontalAlign() should be used.
		 * @see setHorizontalAlign()
		 * @param horizontalAlign the HorizontalAlign to set
		 */
		void changeHorizontalAlign(HorizontalAlign horizontalAlign);

		/**
		 * @brief Changes the VerticalAlign of this Circle and updates the internal position reflecting this.
		 * The position is updated so the Circle's actual position is the same afterwards, i.e. not shifted. If this
		 * is not wanted setVerticalAlign() should be used.
		 * @see setVerticalAlign()
		 * @param verticalAlign the VerticalAlign to set
		 */
		void changeVerticalAlign(VerticalAlign verticalAlign);

		// Comparison operators
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		/**
		 * @brief Equality operator.
		 * @param other the rhs circle
		 * @return whether the lhs and rhs circles are equal
		 */
		bool operator== (const Circle<T>& other) const;

		/**
		 * @brief Inequality operator.
		 * @param other the rhs circle
		 * @return whether the lhs and rhs circles are not equal
		 */
		bool operator!= (const Circle<T>& other) const;

		/**
		 * @brief Smaller than operator.
		 * The size of the Circle is defined by the area() function, which is also what is compared in this function.
		 * @param other the rhs circle
		 * @return whether the lhs circle is smaller than the rhs circle
		 */	
		bool operator< (const Circle<T>& other) const;

		/**
		 * @brief Larger than operator.
		 * The size of the Circle is defined by the area() function, which is also what is compared in this function.
		 * @param other the rhs circle
		 * @return whether the lhs circle is larger than the rhs circle
		 */	
		bool operator> (const Circle<T>& other) const;

		/**
		 * @brief Smaller than or equal operator.
		 * The size of the Circle is defined by the area() function, which is also what is compared in this function.
		 * @param other the rhs circle
		 * @return whether the lhs circle is smaller than or equal to the rhs circle
		 */	
		bool operator<= (const Circle<T>& other) const;

		/**
		 * @brief Larger than or equal operator.
		 * The size of the Circle is defined by the area() function, which is also what is compared in this function.
		 * @param other the rhs circle
		 * @return whether the lhs circle is larger than or equal to the rhs circle
		 */
		bool operator>= (const Circle<T>& other) const;

	private:

		// Members
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> position;
		T radius;
		HorizontalAlign horizontalAlign;
		VerticalAlign verticalAlign;

		// Private helper functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		static T requireNonNegative(T value);
	};

	// Free (non-member) operators
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @relates sfz::Circle
	 * @brief Ostream operator
	 * The serialization of the circle is defined by its to_string() function.
	 * @param ostream the output stream
	 * @param circle the circle to serialize
	 * @return ostream the output straem
	 */	
	template<typename T>
	std::ostream& operator<< (std::ostream& ostream, const Circle<T> circle);
}

// Specializations of standard library for sfz::Circle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {
	template<typename T>
	struct hash<sfz::Circle<T>> {
		size_t operator() (const sfz::Circle<T>& circle) const;
	};
}

#include "sfz/math/Rectangle.hpp"
#include "Circle.inl"
#endif