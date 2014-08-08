#pragma once
#ifndef SFZ_MATH_CIRCLE_HPP
#define SFZ_MATH_CIRCLE_HPP

#include "sfz/math/Vector.hpp"
#include "sfz/math/Alignment.hpp"

namespace sfz {
	template<typename T>
	class Rectangle;
}

namespace sfz {

	template<typename T>
	class Circle final {
	public:
		// Static constants
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		static const HorizontalAlign DEFAULT_HORIZONTAL_ALIGN;
		static const VerticalAlign DEFAULT_VERTICAL_ALIGN;

		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		Circle() = delete;
		
		Circle(const Circle<T>& circle);
		
		Circle(vec2<T> position, T radius, 
		       HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		       VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		Circle(T x, T y, T radius,
		       HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		       VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		~Circle() = default;

		// Public member functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		bool overlap(const vec2<T>& point) const;
		bool overlap(const Circle<T>& circle) const;
		bool overlap(const Rectangle<T>& rect) const;

		// Getters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> getPosition() const;
		T getX() const;
		T getY() const;
		T getRadius() const;
		HorizontalAlign getHorizontalAlign() const;
		VerticalAlign getVerticalAlign() const;

		// Settersz
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		void setPosition(const vec2<T>& position);
		void setPosition(T x, T y);
		void setX(T x);
		void setY(T y);
		void setRadius(T radius);
		void setHorizontalAlign(HorizontalAlign horizontalAlign);
		void setVerticalAlign(VerticalAlign verticalAlign);
		void changeHorizontalAlign(HorizontalAlign horizontalAlign);
		void changeVerticalAlign(VerticalAlign verticalAlign);

	private:

		// Members
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> position;
		T radius;
		HorizontalAlign horizontalAlign;
		VerticalAlign verticalAlign;

		// Private helper functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		T requireNonNegative(T value) const;
	};
}
#include "sfz/math/Rectangle.hpp"
#include "Circle.inl"
#endif