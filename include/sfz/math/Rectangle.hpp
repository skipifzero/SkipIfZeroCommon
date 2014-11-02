#pragma once
#ifndef SFZ_MATH_RECTANGLE_HPP
#define SFZ_MATH_RECTANGLE_HPP

#include <functional> // std::hash
#include <string>
#include <iostream> // ostream
#include <cmath> // std::abs
#include "sfz/math/Vector.hpp"
#include "sfz/math/Alignment.hpp"

// Forward declares Circle, is included after complete declaration of Rectangle.
namespace sfz { template<typename T> class Circle; }

namespace sfz {

/**
 * @brief A class representing a Rectangle.
 *
 * All members are public and should be directly accessed, but there are a few convenience getters.
 *
 * The two alignment variables decide how the Rectangle is anchored to the position.
 *
 * Beware if using integral types, some things like changing alignment and overlap checks might
 * mess up due to truncation.
 *
 * Most functions wrap the width and height in std::abs(), so they will treat a negative width or 
 * height as a positive one. But you should still be careful and avoid negative widths and heights
 * if possible, the results might still be a bit unpredictable.
 *
 * @param T the element type
 *
 * @author Peter Hillerström <peter@hstroem.se>
 * @date 2014-08-08
 */
template<typename T>
class Rectangle final {
public:
	// Static constants & public members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	static const HorizontalAlign s_DEFAULT_HORIZONTAL_ALIGN;
	static const VerticalAlign s_DEFAULT_VERTICAL_ALIGN;

	vec2<T> mPos;
	vec2<T> mDimensions;
	HorizontalAlign mHorizontalAlign;
	VerticalAlign mVerticalAlign;

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Rectangle() = delete;

	/**
	 * @brief Basic copy-constructor.
	 * @param rect the Rectangle to copy
	 */
	Rectangle(const Rectangle<T>& rect) = default;

	/**
	 * @brief Copy cast constructor.
	 * Attempts to static_cast all types from specified rectangle to specified type.
	 * @param rect the rectangle to copy
	 */
	template<typename T2>
	explicit Rectangle(const Rectangle<T2>& rect) noexcept;

	/**
	 * @brief Copy constructor that changes alignment.
	 * The alignment is changed as it would be if changeHorizontalAlign() or changeVerticalAlign()
	 * were called.
	 * @param rect the Rectangle to copy
	 * @param hAlign the HorizontalAlign to change to
	 * @param vAlign the VerticalAlign to change to
	 */
	Rectangle(const Rectangle<T>& rect, HorizontalAlign hAlign, VerticalAlign vAlign) noexcept;

	/**
	 * @brief Rectangle constructor.
	 * If you don't specify the alignment variables they will be set to the default values.
	 * @param position the position
	 * @param dimensions the dimensions
	 * @param hAlign the HorizontalAlign
	 * @param vAlign the VerticalAlign
	 */
	Rectangle(const vec2<T>& position, const vec2<T>& dimensions, 
	          HorizontalAlign hAlign = s_DEFAULT_HORIZONTAL_ALIGN, 
	          VerticalAlign vAlign = s_DEFAULT_VERTICAL_ALIGN) noexcept;

	/**
	 * @brief Rectangle constructor.
	 * If you don't specify the alignment variables they will be set to the default values.
	 * @param position the position
	 * @param width the width
	 * @param height the height
	 * @param hAlign the HorizontalAlign
	 * @param vAlign the VerticalAlign
	 */
	Rectangle(const vec2<T>& position, T width, T height, 
	          HorizontalAlign hAlign = s_DEFAULT_HORIZONTAL_ALIGN, 
	          VerticalAlign vAlign = s_DEFAULT_VERTICAL_ALIGN) noexcept;

	/**
	 * @brief Rectangle constructor.
	 * If you don't specify the alignment variables they will be set to the default values.
	 * @param x the x-position
	 * @param y the y-position
	 * @param width the width
	 * @param height the height
	 * @param hAlign the HorizontalAlign
	 * @param vAlign the VerticalAlign
	 */
	Rectangle(T x, T y, T width, T height, 
	          HorizontalAlign hAlign = s_DEFAULT_HORIZONTAL_ALIGN, 
	          VerticalAlign vAlign = s_DEFAULT_VERTICAL_ALIGN) noexcept;

	~Rectangle() = default;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Returns whether the specified vector is inside this Rectangle or not.
	 * It's worth noting that this function uses 
	 * @param point the specified vector
	 * @return whether the specified vector is inside this Rectangle or not
	 */
	bool overlap(const vec2<T>& point) const noexcept;

	/**
	 * @brief Returns whether the specified Rectangle overlaps with this Rectangle or not.
	 * @param rectangle the specified rectangle
	 * @return whether the specified Rectangle overlaps with this Rectangle or not
	 */
	bool overlap(const Rectangle<T>& rect) const noexcept;

	/**
	 * @brief Returns whether the specified Circle overlaps with this Rectangle or not.
	 * @param circle the specified circle
	 * @return whether the specified Circle overlaps with this Rectangle or not
	 */
	bool overlap(const Circle<T>& circle) const noexcept;

	/**
	 * @brief Returns the area of this Rectangle.
	 * @return the area of this Rectangle
	 */
	T area() const noexcept;

	/**
	 * @brief Returns the circumference of this Rectangle.
	 * @return the circumference of this Rectangle
	 */
	T circumference() const noexcept;

	/**
	 * @brief Hashes the rectangle.
	 * @return hash of the rectangle
	 */
	size_t hash() const noexcept;

	/**
	 * @brief Returns string representation of the rectangle.
	 * @return string representation of the rectangle
	 */
	std::string to_string() const noexcept;

	/**
	 * @brief Changes the HorizontalAlign of this Rectangle and updates the position.
	 * The position is updated so the Rectangle's actual position is the same afterwards, i.e. not
	 * shifted. If this is not wanted mHorizontalAlign should be set directly.
	 * Even if the width is negative this function will behave as if it's positive.
	 * @param hAlign the HorizontalAlign to set
	 */
	void changeHorizontalAlign(HorizontalAlign hAlign) noexcept;

	/**
	 * @brief Changes the VerticalAlign of this Rectangle and updates the position.
	 * The position is updated so the Rectangle's actual position is the same afterwards, i.e. not
	 * shifted. If this is not wanted mVeritcalAlign should be set directly.
	 * Even if the height is negative this function will behave as if it's positive.
	 * @param vAlign the VerticalAlign to set
	 */
	void changeVerticalAlign(VerticalAlign vAlign) noexcept;

	/**
	 * @brief Changes the Horizontal and VerticalAlign of this Rectangle and updates position
	 * @see changeHorizontalAlign()
	 * @see changeVerticalAlign()
	 */
	void changeAlign(HorizontalAlign hAlign, VerticalAlign vAlign) noexcept;

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @return x-position of this Rectangle
	 */
	T x() const noexcept;

	/**
	 * @return y-position of this Rectangle
	 */
	T y() const noexcept;

	/**
	 * @return width of this Rectangle
	 */
	T width() const noexcept;

	/**
	 * @return height of this Rectangle
	 */
	T height() const noexcept;

	// Comparison operators
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	/**
	 * @brief Equality operator.
	 * @param other the rhs rectangle
	 * @return whether the lhs and rhs rectangles are equal
	 */
	bool operator== (const Rectangle<T>& other) const noexcept;

	/**
	 * @brief Inequality operator.
	 * @param other the rhs rectangle
	 * @return whether the lhs and rhs rectangles are not equal
	 */
	bool operator!= (const Rectangle<T>& other) const noexcept;

	/**
	 * @brief Smaller than operator.
	 * The size of the Rectangle is defined by the area() function, which is also what is compared
	 * in this function.
	 * @param other the rhs rectangle
	 * @return whether the lhs rectangle is smaller than the rhs rectangle
	 */	
	bool operator< (const Rectangle<T>& other) const noexcept;

	/**
	 * @brief Larger than operator.
	 * The size of the Rectangle is defined by the area() function, which is also what is compared
	 * in this function.
	 * @param other the rhs rectangle
	 * @return whether the lhs rectangle is larger than the rhs rectangle
	 */	
	bool operator> (const Rectangle<T>& other) const noexcept;

	/**
	 * @brief Smaller than or equal operator.
	 * The size of the Rectangle is defined by the area() function, which is also what is compared
	 * in this function.
	 * @param other the rhs rectangle
	 * @return whether the lhs rectangle is smaller than or equal to the rhs rectangle
	 */	
	bool operator<= (const Rectangle<T>& other) const noexcept;

	/**
	 * @brief Larger than or equal operator.
	 * The size of the Rectangle is defined by the area() function, which is also what is compared
	 * in this function.
	 * @param other the rhs rectangle
	 * @return whether the lhs rectangle is larger than or equal to the rhs rectangle
	 */	
	bool operator>= (const Rectangle<T>& other) const noexcept;
};

// Free (non-member) operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/**
 * @relates sfz::Rectangle
 * @brief Ostream operator
 * The serialization of the rectangle is defined by its to_string() function.
 * @param ostream the output stream
 * @param rect the rectangle to serialize
 * @return ostream the output straem
 */	
template<typename T>
std::ostream& operator<< (std::ostream& ostream, const Rectangle<T> rect) noexcept;

// Standard typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
using RectangleF = Rectangle<float>;
using RectangleD = Rectangle<double>;
using RectangleI = Rectangle<int>;
using RectangleL = Rectangle<long>;

template<typename T>
using rect = Rectangle<T>;
using rectf = rect<float>;
using rectd = rect<double>;
using recti = rect<int>;
using rectl = rect<long>;

} // namespace sfz

// Specializations of standard library for sfz::Rectangle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {

template<typename T>
struct hash<sfz::Rectangle<T>> {
	size_t operator() (const sfz::Rectangle<T>& rect) const noexcept;
};

} // namespace std

#include "sfz/math/Circle.hpp"
#include "Rectangle.inl"
#endif