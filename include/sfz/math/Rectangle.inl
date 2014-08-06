namespace sfz {

	namespace {

		template<typename T>
		T requireNonNegative(T value) {
			if(value < 0) {
				throw std::invalid_argument{"Negative dimensions not allowed."};
			}
			return value;
		}

		// Calculates a constant used to divide the width/height of a rectangle when changing size.
		// See changeHorizonalAlign() or changeVerticalAlign() for mor info.
		template<typename Align>
		char calculateAlignChangeDenominator(Align origin, Align destination) {
			char diff = static_cast<char>(destination) - static_cast<char>(origin);
			switch(diff) {
			case 0:
				return 0;
			case -2:
				return -1;
			case -1:
				return -2;
			case 1:
				return 2;
			case 2:
				return 1;
			default:
				throw std::logic_error{"This should not be possible."};
			}
		}
	}

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
	bool Rectangle<T>::overlap(const Rectangle<T>& rect) const {

	}

	template<typename T>
	bool Rectangle<T>::overlap(const Circle<T>& circle) const {

	}

	template<typename T>
	bool Rectangle<T>::overlap(const vec2<T>& vector) const {

	}

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	vec2<T> Rectangle<T>::getPosition() const {
		return position;
	}

	template<typename T>
	T Rectangle<T>::getXPosition() const {
		return position[0];
	}

	template<typename T>
	T Rectangle<T>::getYPosition() const {
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
	void Rectangle<T>::setXPosition(T x) {
		position[0] = x;
	}

	template<typename T>
	void Rectangle<T>::setYPosition(T y) {
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
		char denominator = calculateAlignChangeDenominator(this->horizontalAlign, horizontalAlign);
		position[0] += dimensions[0]/static_cast<T>(denominator);
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Rectangle<T>::changeVerticalAlign(VerticalAlign verticalAlign) {
		char denominator = calculateAlignChangeDenominator(this->verticalAlign, verticalAlign);
		position[1] += dimensions[1]/static_cast<T>(denominator);
		this->verticalAlign = verticalAlign;
	}
}