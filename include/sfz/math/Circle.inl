namespace sfz {

// Static constants & public members
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
const HorizontalAlign Circle<T>::s_DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

template<typename T>
const VerticalAlign Circle<T>::s_DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
template<typename T2>
Circle<T>::Circle(const Circle<T2>& circle) noexcept
:
	mPos{static_cast<vec2<T2>>(circle.mPos)},
	mHAlign{circle.mHAlign},
	mVAlign{circle.mVAlign}
{
	mRad = static_cast<T2>(circle.mRad);
}


template<typename T>
Circle<T>::Circle(const Circle<T>& circle, HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	Circle<T>{circle}
{
	changeHorizontalAlign(hAlign);
	changeVerticalAlign(vAlign);
}

template<typename T>
Circle<T>::Circle(vec2<T> position, T radius, HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	mPos{position},
	mRad{radius},
	mHAlign{hAlign},
	mVAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Circle<T>::Circle(T x, T y, T radius, HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	mPos{x, y},
	mRad{radius},
	mHAlign{hAlign},
	mVAlign{vAlign}
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Circle<T>::overlap(const vec2<T>& point) const noexcept
{
	Circle<T> centerAlignCircle{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	// If the length from this circles center to the specified point is shorter than or equal to
	// the radius then this Circle overlaps the point. Both sides of the equation is squared to
	// avoid somewhat expensive sqrt() function.
	return centerAlignCircle.mPos.distance(point).squaredNorm() <= mRad*mRad;
}

template<typename T>
bool Circle<T>::overlap(const Circle<T>& circle) const noexcept
{
	Circle<T> centerAlignCircleThis{*this, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};
	Circle<T> centerAlignCircleOther{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	// If the length between the center of the two circles is less than or equal to the the sum of
	// the circle's radiuses they overlap. Both sides of the equation is squared to avoid somewhat 
	// expensive sqrt() function.
	T distSquared = centerAlignCircleThis.mPos.distance(centerAlignCircleOther.mPos).squaredNorm();
	T radiusSum = std::abs(centerAlignCircleThis.mRad) + std::abs(centerAlignCircleOther.mRad);
	return distSquared <= radiusSum * radiusSum;
}

template<typename T>
bool Circle<T>::overlap(const Rectangle<T>& rect) const noexcept
{
	return rect.overlap(*this);
}

template<typename T>
T Circle<T>::area() const noexcept
{
	return static_cast<T>(g_PI_DOUBLE)*mRad*mRad;
}

template<typename T>
T Circle<T>::circumference() const noexcept
{
	return static_cast<T>(2)*static_cast<T>(g_PI_DOUBLE)*std::abs(mRad);
}

template<typename T>
size_t Circle<T>::hash() const noexcept
{
	std::hash<T> hasher;
	std::hash<char> enumHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mPos[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mPos[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mRad) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mHAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mVAlign)) + 
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

template<typename T>
std::string Circle<T>::to_string() const noexcept
{
	std::string str;
	str += "[pos=";
	str += mPos.to_string();
	str += ", r=";
	str += std::to_string(mRad);
	str += ", align: ";
	str += sfz::to_string(mHAlign);
	str += ", ";
	str += sfz::to_string(mVAlign);
	str += "]";
	return std::move(str);
}

template<typename T>
void Circle<T>::changeHorizontalAlign(HorizontalAlign hAlign) noexcept
{
	assert(mHAlign == HorizontalAlign::LEFT ||
	       mHAlign == HorizontalAlign::CENTER ||
	       mHAlign == HorizontalAlign::RIGHT);
	mPos[0] = calculateNewPosition(mPos[0], mRad*2, mHAlign, hAlign);
	mHAlign = hAlign;
}

template<typename T>
void Circle<T>::changeVerticalAlign(VerticalAlign vAlign) noexcept
{
	assert(mVAlign == VerticalAlign::BOTTOM ||
	       mVAlign == VerticalAlign::MIDDLE ||
	       mVAlign == VerticalAlign::TOP);
	mPos[1] = calculateNewPosition(mPos[1], mRad*2, mVAlign, vAlign);
	mVAlign = vAlign;
}

template<typename T>
void Circle<T>::changeAlign(HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
{
	changeHorizontalAlign(hAlign);
	changeVerticalAlign(vAlign);
}

// Getters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
T Circle<T>::x() const noexcept
{
	return mPos[0];
}

template<typename T>
T Circle<T>::y() const noexcept
{
	return mPos[1];
}

template<typename T>
T Circle<T>::radius() const noexcept
{
	return mRad;
}

// Comparison operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Circle<T>::operator== (const Circle<T>& other) const noexcept
{
	return mPos == other.mPos &&
	       mRad == other.mRad &&
	       mHAlign == other.mHAlign &&
	       mVAlign == other.mVAlign;
}

template<typename T>
bool Circle<T>::operator!= (const Circle<T>& other) const noexcept
{
	return !((*this) == other);
}

template<typename T>
bool Circle<T>::operator< (const Circle<T>& other) const noexcept
{
	return this->area() < other.area();
}

template<typename T>
bool Circle<T>::operator> (const Circle<T>& other) const noexcept
{
	return this->area() > other.area();
}

template<typename T>
bool Circle<T>::operator<= (const Circle<T>& other) const noexcept
{
	return this->area() <= other.area();
}

template<typename T>
bool Circle<T>::operator>= (const Circle<T>& other) const noexcept
{
	return this->area() >= other.area();
}

// Free (non-member) operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

template<typename T>
std::ostream& operator<< (std::ostream& ostream, const Circle<T> circle) noexcept
{
	return ostream << circle.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Circle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {

template<typename T>
size_t hash<sfz::Circle<T>>::operator() (const sfz::Circle<T>& circle) const noexcept
{
	return circle.hash();
}

} // namespace std