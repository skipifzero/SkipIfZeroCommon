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
		verticalAlign{circle.verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Circle<T>::Circle(const Circle<T>& circle, HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		Circle<T>{circle} {
			changeHorizontalAlign(horizontalAlign);
			changeVerticalAlign(verticalAlign);
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
	bool Circle<T>::overlap(const vec2<T>& point) const {
		Circle<T> centerAlignCircle{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

		// If the length from this circles center to the specified point is shorter than or equal to the radius then
		// this Circle overlaps the point. Both sides of the equation is squared to avoid expensive sqrt() function.
		return centerAlignCircle.position.distance(point).squaredNorm() <= radius*radius;
	}

	template<typename T>
	bool Circle<T>::overlap(const Circle<T>& circle) const {
		Circle<T> centerAlignCircleThis{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};
		Circle<T> centerAlignCircleOther{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

		// If the length between the center of the two circles is less than or equal to the the sum of the circle's
		// radiuses they overlap. Both sides of the equation is squared to avoid expensive sqrt() function.
		T distSquared = centerAlignCircleThis.position.distance(centerAlignCircleOther.position).squaredNorm();
		T radiusSum = centerAlignCircleThis.getRadius() + centerAlignCircleOther.getRadius();
		return distSquared <= radiusSum * radiusSum;
	}
	
	template<typename T>
	bool Circle<T>::overlap(const Rectangle<T>& rect) const {
		return rect.overlap(*this);
	}

	template<typename T>
	T Circle<T>::area() const {
		return static_cast<T>(PI_DOUBLE)*radius*radius;
	}

	template<typename T>
	T Circle<T>::circumference() const {
		return static_cast<T>(2)*static_cast<T>(PI_DOUBLE)*radius;
	}

	template<typename T>
	size_t Circle<T>::hash() const {
		std::hash<T> hasher;
		std::hash<char> enumHasher;
		size_t hash = 0;
		// hash_combine algorithm from boost
		hash ^= hasher(position[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		hash ^= hasher(position[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		hash ^= hasher(radius) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		hash ^= enumHasher(static_cast<char>(horizontalAlign)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		hash ^= enumHasher(static_cast<char>(verticalAlign)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		return hash;
	}

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	vec2<T> Circle<T>::getPosition() const {
		return position;
	}

	template<typename T>
	T Circle<T>::getX() const {
		return position[0];
	}

	template<typename T>
	T Circle<T>::getY() const {
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
	void Circle<T>::setX(T x) {
		this->position[0] = x;
	}

	template<typename T>
	void Circle<T>::setY(T y) {
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