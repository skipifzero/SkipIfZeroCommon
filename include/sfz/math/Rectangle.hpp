#pragma once
#ifndef SFZ_MATH_RECTANGLE_HPP
#define SFZ_MATH_RECTANGLE_HPP

#include <stdexcept>
#include "sfz/math/Vector.hpp"

namespace sfz {

	template<typename T>
	class Circle;

	template<typename T>
	class Rectangle final {
	public:
		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		Rectangle() = delete;
		Rectangle(const Rectangle<T>& rect);
		Rectangle(const vec2<T>& position, const vec2<T>& dimensions);
		Rectangle(const vec2<T>& position, T width, T height);
		Rectangle(T x, T y, T width, T height);
		~Rectangle() = default;

		// Public member functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		bool overlap(const Rectangle<T>& rect) const;
		bool overlap(const Circle<T>& circle) const;
		bool overlap(const vec2<T>& vector) const;

		// Getters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> getPosition() const;
		T getXPosition() const;
		T getYPosition() const;
		vec2<T> getDimensions() const;
		T getWidth() const;
		T getHeight() const;

		// Setters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		void setPosition(const vec2<T>& position);
		void setPosition(T x, T y);
		void setXPosition(T x);
		void setYPosition(T y);
		void setDimensions(const vec2<T>& dimensions);
		void setDimensions(T width, T height);
		void setWidth(T width);
		void setHeight(T height);

	private:
		vec2<T> position;
		vec2<T> dimensions;
	};
}
#include "Rectangle.inl"
#endif