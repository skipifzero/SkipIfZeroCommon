namespace sfz {

	// Static constants
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	const HorizontalAlign Rectangle<T>::DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

	template<typename T>
	const VerticalAlign Rectangle<T>::DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& rect) :
		position{rect.position}, 
		dimensions{rect.dimensions},
		horizontalAlign{rect.horizontalAlign},
		verticalAlign{rect.verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& rect, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		Rectangle<T>{rect} {
			changeHorizontalAlign(horizontalAlign);
			changeVerticalAlign(verticalAlign);
	}

	template<typename T>
	Rectangle<T>::Rectangle(const vec2<T>& position, const vec2<T>& dimensions, 
		                    HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{position}, 
		dimensions{requireNonNegative(dimensions[0]), requireNonNegative(dimensions[1])},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}
	
	template<typename T>
	Rectangle<T>::Rectangle(const vec2<T>& position, T width, T height,
		                    HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{position},
		dimensions{requireNonNegative(width), requireNonNegative(height)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Rectangle<T>::Rectangle(T x, T y, T width, T height,
	                        HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{x, y},
		dimensions{requireNonNegative(width), requireNonNegative(height)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	bool Rectangle<T>::overlap(const vec2<T>& point) const {
		Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

		T rectXLeft = leftBottomAlignRect.getX();
		T rectXRight = rectXLeft + leftBottomAlignRect.getWidth();
		T rectYBottom = leftBottomAlignRect.getY();
		T rectYTop = rectYBottom + leftBottomAlignRect.getHeight();
		T vecX = point[0];
		T vecY = point[1];

		return rectXLeft <= vecX && rectXRight >= vecX &&
		       rectYBottom <= vecY && rectYTop>= vecY;
	}

	template<typename T>
	bool Rectangle<T>::overlap(const Rectangle<T>& rect) const {
		Rectangle<T> leftBottomAlignRectThis{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
		Rectangle<T> leftBottomAlignRectOther{rect, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

		T thisXLeft = leftBottomAlignRectThis.getX();
		T thisXRight = thisXLeft + leftBottomAlignRectThis.getWidth();
		T thisYBottom = leftBottomAlignRectThis.getY();
		T thisYTop = thisYBottom + leftBottomAlignRectThis.getHeight();

		T otherXLeft = leftBottomAlignRectOther.getX();
		T otherXRight = otherXLeft + leftBottomAlignRectOther.getWidth();
		T otherYBottom = leftBottomAlignRectOther.getY();
		T otherYTop = otherYBottom + leftBottomAlignRectOther.getHeight();

		return thisXLeft   <= otherXRight &&
		       thisXRight  >= otherXLeft &&
		       thisYBottom <= otherYTop &&
		       thisYTop    >= otherYBottom;
	}

	template<typename T>
	bool Rectangle<T>::overlap(const Circle<T>& circle) const {
		Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
		Circle<T> centerAlignCircle{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

		T rectXLeft = leftBottomAlignRect.getX();
		T rectXRight = rectXLeft + leftBottomAlignRect.getWidth();
		T rectYBottom = leftBottomAlignRect.getY();
		T rectYTop = rectYBottom + leftBottomAlignRect.getHeight();

		T circleX = centerAlignCircle.getX();
		T circleY = centerAlignCircle.getY();
		T radius = centerAlignCircle.getRadius();

		// If the length between the center of the circle and the closest point on the rectangle is less than or equal
		// to the circles radius they overlap. Both sides of the equation is squared to avoid expensive sqrt() 
		// function. 
		T closestX = circleX;
		T closestY = circleY;
		
		if(circleX <= rectXLeft) {
			closestX = rectXLeft;
		} 
		else if(circleX >= rectXRight) {
			closestX = rectXRight;
		}
		
		if(circleY <= rectYBottom) {
			closestY = rectYBottom;
		}
		else if(circleY >= rectYTop) {
			closestY = rectYTop;
		}
		
		return centerAlignCircle.getPosition().distance(sfz::vec2<T>{closestX, closestY}).squaredNorm() 
		       <= radius*radius;
	}

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	vec2<T> Rectangle<T>::getPosition() const {
		return position;
	}

	template<typename T>
	T Rectangle<T>::getX() const {
		return position[0];
	}

	template<typename T>
	T Rectangle<T>::getY() const {
		return position[1];
	}

	template<typename T>
	vec2<T> Rectangle<T>::getDimensions() const {
		return dimensions;
	}

	template<typename T>
	T Rectangle<T>::getWidth() const {
		return dimensions[0];
	}

	template<typename T>
	T Rectangle<T>::getHeight() const {
		return dimensions[1];
	}

	template<typename T>
	HorizontalAlign Rectangle<T>::getHorizontalAlign() const {
		return horizontalAlign;
	}
	
	template<typename T>
	VerticalAlign Rectangle<T>::getVerticalAlign() const {
		return verticalAlign;
	}

	// Setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	void Rectangle<T>::setPosition(const vec2<T>& position) {
		this->position = position;
	}

	template<typename T>
	void Rectangle<T>::setPosition(T x, T y) {
		position[0] = x;
		position[1] = y;
	}

	template<typename T>
	void Rectangle<T>::setX(T x) {
		position[0] = x;
	}

	template<typename T>
	void Rectangle<T>::setY(T y) {
		position[1] = y;
	}

	template<typename T>
	void Rectangle<T>::setDimensions(const vec2<T>& dimensions) {
		this->dimensions[0] = requireNonNegative(dimensions[0]);
		this->dimensions[1] = requireNonNegative(dimensions[1]);
	}

	template<typename T>
	void Rectangle<T>::setDimensions(T width, T height) {
		dimensions[0] = requireNonNegative(width);
		dimensions[1] = requireNonNegative(height);
	}

	template<typename T>
	void Rectangle<T>::setWidth(T width) {
		dimensions[0] = requireNonNegative(width);
	}

	template<typename T>
	void Rectangle<T>::setHeight(T height) {
		dimensions[1] = requireNonNegative(height);
	}

	template<typename T>
	void Rectangle<T>::setHorizontalAlign(HorizontalAlign horizontalAlign) {
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Rectangle<T>::setVerticalAlign(VerticalAlign verticalAlign) {
		this->verticalAlign = verticalAlign;
	}

	template<typename T>
	void Rectangle<T>::changeHorizontalAlign(HorizontalAlign horizontalAlign) {
		position[0] = calculateNewPosition(position[0], dimensions[0], this->horizontalAlign, horizontalAlign);
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Rectangle<T>::changeVerticalAlign(VerticalAlign verticalAlign) {
		position[1] = calculateNewPosition(position[1], dimensions[1], this->verticalAlign, verticalAlign);
		this->verticalAlign = verticalAlign;
	}

	// Private helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	T Rectangle<T>::requireNonNegative(T value) const {
		if(value < 0) {
			throw std::invalid_argument{"Negative dimensions not allowed."};
		}
		return value;
	}
}