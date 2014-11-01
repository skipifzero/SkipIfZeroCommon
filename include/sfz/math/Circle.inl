namespace sfz {

// Static constants
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
const HorizontalAlign Circle<T>::s_DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

template<typename T>
const VerticalAlign Circle<T>::s_DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
template<typename T2>
Circle<T>::Circle(const Circle<T2>& circle)
:
	mPosition{static_cast<vec2<T2>>(circle.getPosition())},
	mHorizontalAlign{circle.getHorizontalAlign()},
	mVerticalAlign{circle.getVerticalAlign()}
{
	mRadius = static_cast<T2>(circle.getRadius());
}


template<typename T>
Circle<T>::Circle(const Circle<T>& circle, HorizontalAlign hAlign, VerticalAlign vAlign)
:
	Circle<T>{circle}
{
	changeHorizontalAlign(hAlign);
	changeVerticalAlign(vAlign);
}

template<typename T>
Circle<T>::Circle(vec2<T> position, T radius, HorizontalAlign hAlign, VerticalAlign vAlign)
:
	mPosition{position},
	mRadius{requireNonNegative(radius)},
	mHorizontalAlign{hAlign},
	mVerticalAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Circle<T>::Circle(T x, T y, T radius, HorizontalAlign hAlign, VerticalAlign vAlign)
:
	mPosition{x, y},
	mRadius{requireNonNegative(radius)},
	mHorizontalAlign{hAlign},
	mVerticalAlign{vAlign}
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Circle<T>::overlap(const vec2<T>& point) const
{
	Circle<T> centerAlignCircle{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	// If the length from this circles center to the specified point is shorter than or equal to
	// the radius then this Circle overlaps the point. Both sides of the equation is squared to
	// avoid somewhat expensive sqrt() function.
	return centerAlignCircle.mPosition.distance(point).squaredNorm() <= mRadius*mRadius;
}

template<typename T>
bool Circle<T>::overlap(const Circle<T>& circle) const
{
	Circle<T> centerAlignCircleThis{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};
	Circle<T> centerAlignCircleOther{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	// If the length between the center of the two circles is less than or equal to the the sum of
	// the circle's radiuses they overlap. Both sides of the equation is squared to avoid somewhat 
	// expensive sqrt() function.
	T distSquared = centerAlignCircleThis.mPosition.distance(centerAlignCircleOther.mPosition)
	                .squaredNorm();
	T radiusSum = centerAlignCircleThis.mRadius + centerAlignCircleOther.mRadius;
	return distSquared <= radiusSum * radiusSum;
}

template<typename T>
bool Circle<T>::overlap(const Rectangle<T>& rect) const
{
	return rect.overlap(*this);
}

template<typename T>
T Circle<T>::area() const
{
	return static_cast<T>(g_PI_DOUBLE)*mRadius*mRadius;
}

template<typename T>
T Circle<T>::circumference() const
{
	return static_cast<T>(2)*static_cast<T>(g_PI_DOUBLE)*mRadius;
}

template<typename T>
size_t Circle<T>::hash() const
{
	std::hash<T> hasher;
	std::hash<char> enumHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mPosition[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mPosition[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mRadius) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mHorizontalAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mVerticalAlign)) + 
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

template<typename T>
std::string Circle<T>::to_string() const
{
	std::string str;
	str += "[pos=";
	str += mPosition.to_string();
	str += ", r=";
	str += std::to_string(mRadius);
	str += ", align: ";
	str += sfz::to_string(mHorizontalAlign);
	str += ", ";
	str += sfz::to_string(mVerticalAlign);
	str += "]";
	return std::move(str);
}

// Getters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
vec2<T> Circle<T>::getPosition() const
{
	return mPosition;
}

template<typename T>
T Circle<T>::getX() const
{
	return mPosition[0];
}

template<typename T>
T Circle<T>::getY() const
{
	return mPosition[1];
}

template<typename T>
T Circle<T>::getRadius() const
{
	return mRadius;
}

template<typename T>
HorizontalAlign Circle<T>::getHorizontalAlign() const
{
	return mHorizontalAlign;
}

template<typename T>
VerticalAlign Circle<T>::getVerticalAlign() const
{
	return mVerticalAlign;
}

// Setters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
void Circle<T>::setPosition(const vec2<T>& position)
{
	mPosition = position;
}

template<typename T>
void Circle<T>::setPosition(T x, T y)
{
	mPosition[0] = x;
	mPosition[1] = y;
}

template<typename T>
void Circle<T>::setX(T x)
{
	mPosition[0] = x;
}

template<typename T>
void Circle<T>::setY(T y)
{
	mPosition[1] = y;
}

template<typename T>
void Circle<T>::setRadius(T radius)
{
	mRadius = requireNonNegative(radius);
}

template<typename T>
void Circle<T>::setHorizontalAlign(HorizontalAlign horizontalAlign)
{
	mHorizontalAlign = horizontalAlign;
}

template<typename T>
void Circle<T>::setVerticalAlign(VerticalAlign verticalAlign)
{
	mVerticalAlign = verticalAlign;
}

template<typename T>
void Circle<T>::changeHorizontalAlign(HorizontalAlign horizontalAlign)
{
	mPosition[0] = calculateNewPosition(mPosition[0], mRadius*2, mHorizontalAlign, horizontalAlign);
	mHorizontalAlign = horizontalAlign;
}

template<typename T>
void Circle<T>::changeVerticalAlign(VerticalAlign verticalAlign)
{
	mPosition[1] = calculateNewPosition(mPosition[1], mRadius*2, mVerticalAlign, verticalAlign);
	mVerticalAlign = verticalAlign;
}

// Comparison operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Circle<T>::operator== (const Circle<T>& other) const
{
	return mPosition == other.mPosition &&
	       mRadius == other.mRadius &&
	       mHorizontalAlign == other.mHorizontalAlign &&
	       mVerticalAlign == other.mVerticalAlign;
}

template<typename T>
bool Circle<T>::operator!= (const Circle<T>& other) const
{
	return !((*this) == other);
}

template<typename T>
bool Circle<T>::operator< (const Circle<T>& other) const
{
	return this->area() < other.area();
}

template<typename T>
bool Circle<T>::operator> (const Circle<T>& other) const
{
	return this->area() > other.area();
}

template<typename T>
bool Circle<T>::operator<= (const Circle<T>& other) const
{
	return this->area() <= other.area();
}

template<typename T>
bool Circle<T>::operator>= (const Circle<T>& other) const
{
	return this->area() >= other.area();
}

// Private helper functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
T Circle<T>::requireNonNegative(T value)
{
	if (value < 0) {
		throw std::invalid_argument{"Negative radius not allowed."};
	}
	return value;
}

// Free (non-member) operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
std::ostream& operator<< (std::ostream& ostream, const Circle<T> circle)
{
	return ostream << circle.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Circle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {

template<typename T>
size_t hash<sfz::Circle<T>>::operator() (const sfz::Circle<T>& circle) const
{
	return circle.hash();
}

} // namespace std