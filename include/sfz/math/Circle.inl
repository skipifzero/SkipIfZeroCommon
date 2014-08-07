namespace sfz {

	// Static constants
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	const HorizontalAlign Circle<T>::DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

	template<typename T>
	const VerticalAlign Circle<T>::DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	Circle<T>::Circle(const Circle<T>& circle) :
		position{circle.position},
		radius{circle.radius},
		horizontalAlign{circle.horizontalAlign},
		verticalAlign{circle.verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Circle<T>::Circle(vec2<T> position, T radius, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{position},
		radius{requireNonNegative(radius)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Circle<T>::Circle(T x, T y, T radius, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{x, y},
		radius{requireNonNegative(radius)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	bool Circle<T>::overlap(const vec2<T>& vector) const {
		Circle<T> centerAlignCircle{*this};
		centerAlignCircle.changeHorizontalAlign(HorizontalAlign::CENTER);
		centerAlignCircle.changeVerticalAlign(VerticalAlign::MIDDLE);
		return (centerAlignCircle.position - vector).squaredNorm() <= radius*radius;
	}

	template<typename T>
	bool Circle<T>::overlap(const Circle<T>& circle) const {

	}
	
	//template<typename T>
	//bool Circle<T>::overlap(const Rectangle<T>& rect) const {
	//}

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	vec2<T> Circle<T>::getPosition() const {
		return position;
	}

	template<typename T>
	T Circle<T>::getXPosition() const {
		return position[0];
	}

	template<typename T>
	T Circle<T>::getYPosition() const {
		return position[1];
	}

	template<typename T>
	T Circle<T>::getRadius() const {
		return radius;
	}

	template<typename T>
	HorizontalAlign Circle<T>::getHorizontalAlign() const {
		return horizontalAlign;
	}

	template<typename T>
	VerticalAlign Circle<T>::getVerticalAlign() const {
		return verticalAlign;
	}

	// Setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	void Circle<T>::setPosition(const vec2<T>& position) {
		this->position = position;
	}

	template<typename T>
	void Circle<T>::setPosition(T x, T y) {
		position[0] = x;
		position[1] = y;
	}

	template<typename T>
	void Circle<T>::setXPosition(T x) {
		this->position[0] = x;
	}

	template<typename T>
	void Circle<T>::setYPosition(T y) {
		this->position[1] = y;
	}

	template<typename T>
	void Circle<T>::setRadius(T radius) {
		this->radius = requireNonNegative(radius);
	}

	template<typename T>
	void Circle<T>::setHorizontalAlign(HorizontalAlign horizontalAlign) {
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Circle<T>::setVerticalAlign(VerticalAlign verticalAlign) {
		this->verticalAlign = verticalAlign;
	}

	template<typename T>
	void Circle<T>::changeHorizontalAlign(HorizontalAlign horizontalAlign) {
		position[0] = calculateNewPosition(position[0], radius*2, this->horizontalAlign, horizontalAlign);
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Circle<T>::changeVerticalAlign(VerticalAlign verticalAlign) {
		position[1] = calculateNewPosition(position[1], radius*2, this->verticalAlign, verticalAlign);
		this->verticalAlign = verticalAlign;
	}

	// Private helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	T Circle<T>::requireNonNegative(T value) const {
		if(value < 0) {
			throw std::invalid_argument{"Negative radius not allowed."};
		}
		return value;
	}
}