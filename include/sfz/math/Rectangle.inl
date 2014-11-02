namespace sfz {

// Static constants
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
const HorizontalAlign Rectangle<T>::s_DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

template<typename T>
const VerticalAlign Rectangle<T>::s_DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
template<typename T2>
Rectangle<T>::Rectangle(const Rectangle<T2>& rect)
:
	mPos{static_cast<vec2<T2>>(rect.mPos)},
	mDimensions{static_cast<vec2<T2>>(rect.mDimensions)},
	mHorizontalAlign{rect.mHorizontalAlign},
	mVerticalAlign{rect.mVerticalAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& rect, HorizontalAlign hAlign, VerticalAlign vAlign)
:
	Rectangle<T>{rect}
{
	changeAlign(hAlign, vAlign);
}

template<typename T>
Rectangle<T>::Rectangle(const vec2<T>& position, const vec2<T>& dimensions, HorizontalAlign hAlign,
                                                                            VerticalAlign vAlign)
:
	mPos{position},
	mDimensions{dimensions},
	mHorizontalAlign{hAlign},
	mVerticalAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(const vec2<T>& position, T width, T height, HorizontalAlign hAlign,
                                                                    VerticalAlign vAlign)
:
	mPos{position},
	mDimensions{width, height},
	mHorizontalAlign{hAlign},
	mVerticalAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(T x, T y, T width, T height, HorizontalAlign hAlign, VerticalAlign vAlign)
:
	mPos{x, y},
	mDimensions{width, height},
	mHorizontalAlign{hAlign},
	mVerticalAlign{vAlign}
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Rectangle<T>::overlap(const vec2<T>& point) const
{
	Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

	T rectXLeft = leftBottomAlignRect.x();
	T rectXRight = rectXLeft + leftBottomAlignRect.width();
	T rectYBottom = leftBottomAlignRect.y();
	T rectYTop = rectYBottom + leftBottomAlignRect.height();
	T vecX = point[0];
	T vecY = point[1];

	return rectXLeft <= vecX && rectXRight >= vecX &&
	       rectYBottom <= vecY && rectYTop>= vecY;
}

template<typename T>
bool Rectangle<T>::overlap(const Rectangle<T>& rect) const
{
	Rectangle<T> leftBottomAlignRectThis{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
	Rectangle<T> leftBottomAlignRectOther{rect, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

	T thisXLeft = leftBottomAlignRectThis.x();
	T thisXRight = thisXLeft + leftBottomAlignRectThis.width();
	T thisYBottom = leftBottomAlignRectThis.y();
	T thisYTop = thisYBottom + leftBottomAlignRectThis.height();

	T otherXLeft = leftBottomAlignRectOther.x();
	T otherXRight = otherXLeft + leftBottomAlignRectOther.width();
	T otherYBottom = leftBottomAlignRectOther.y();
	T otherYTop = otherYBottom + leftBottomAlignRectOther.height();

	return thisXLeft   <= otherXRight &&
	       thisXRight  >= otherXLeft &&
	       thisYBottom <= otherYTop &&
	       thisYTop    >= otherYBottom;
}

template<typename T>
bool Rectangle<T>::overlap(const Circle<T>& circle) const
{
	Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
	Circle<T> centerAlignCircle{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	T rectXLeft = leftBottomAlignRect.x();
	T rectXRight = rectXLeft + leftBottomAlignRect.width();
	T rectYBottom = leftBottomAlignRect.y();
	T rectYTop = rectYBottom + leftBottomAlignRect.height();

	T circleX = centerAlignCircle.x();
	T circleY = centerAlignCircle.y();
	T radius = centerAlignCircle.mRadius;

	// If the length between the center of the circle and the closest point on the rectangle is
	// less than or equal to the circles radius they overlap. Both sides of the equation is 
	// squared to avoid somewhat expensive sqrt() function. 
	T closestX = circleX;
	T closestY = circleY;
	
	if (circleX <= rectXLeft) {
		closestX = rectXLeft;
	} 
	else if (circleX >= rectXRight) {
		closestX = rectXRight;
	}
	
	if (circleY <= rectYBottom) {
		closestY = rectYBottom;
	}
	else if (circleY >= rectYTop) {
		closestY = rectYTop;
	}
	
	return centerAlignCircle.mPos.distance(sfz::vec2<T>{closestX, closestY}).squaredNorm() 
	       <= radius*radius;
}

template<typename T>
T Rectangle<T>::area() const
{
	return width()*height();
}

template<typename T>
T Rectangle<T>::circumference() const
{
	return width()*2 + height()*2;
}

template<typename T>
size_t Rectangle<T>::hash() const
{
	std::hash<T> hasher;
	std::hash<char> enumHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mPos[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mPos[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mDimensions[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mDimensions[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mHorizontalAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mVerticalAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

template<typename T>
std::string Rectangle<T>::to_string() const
{
	std::string str;
	str += "[pos=";
	str += mPos.to_string();
	str += ", dim=";
	str += mDimensions.to_string();
	str += ", align: ";
	str += sfz::to_string(mHorizontalAlign);
	str += ", ";
	str += sfz::to_string(mVerticalAlign);
	str += "]";
	return std::move(str);
}

template<typename T>
void Rectangle<T>::changeHorizontalAlign(HorizontalAlign hAlign)
{
	mPos[0] = calculateNewPosition(mPos[0], std::abs(mDimensions[0]), mHorizontalAlign, hAlign);
	mHorizontalAlign = hAlign;
}

template<typename T>
void Rectangle<T>::changeVerticalAlign(VerticalAlign vAlign)
{
	mPos[1] = calculateNewPosition(mPos[1], std::abs(mDimensions[1]), mVerticalAlign, vAlign);
	mVerticalAlign = vAlign;
}

template<typename T>
void Rectangle<T>::changeAlign(HorizontalAlign hAlign, VerticalAlign vAlign)
{
	changeHorizontalAlign(hAlign);
	changeVerticalAlign(vAlign);
}

// Getters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
T Rectangle<T>::x() const
{
	return mPos[0];
}

template<typename T>
T Rectangle<T>::y() const
{
	return mPos[1];
}

template<typename T>
T Rectangle<T>::width() const
{
	return mDimensions[0];
}

template<typename T>
T Rectangle<T>::height() const
{
	return mDimensions[1];
}

// Comparison operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Rectangle<T>::operator== (const Rectangle<T>& other) const
{
	return mPos == other.mPos &&
	       mDimensions == other.mDimensions &&
	       mHorizontalAlign == other.mHorizontalAlign &&
	       mVerticalAlign == other.mVerticalAlign;
}

template<typename T>
bool Rectangle<T>::operator!= (const Rectangle<T>& other) const
{
	return !((*this) == other);
}

template<typename T>
bool Rectangle<T>::operator< (const Rectangle<T>& other) const
{
	return this->area() < other.area();
}

template<typename T>
bool Rectangle<T>::operator> (const Rectangle<T>& other) const
{
	return this->area() > other.area();
}

template<typename T>
bool Rectangle<T>::operator<= (const Rectangle<T>& other) const
{
	return this->area() <= other.area();
}

template<typename T>
bool Rectangle<T>::operator>= (const Rectangle<T>& other) const
{
	return this->area() >= other.area();
}

// Free (non-member) operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
std::ostream& operator<< (std::ostream& ostream, const Rectangle<T> rect)
{
	return ostream << rect.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Rectangle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {

template<typename T>
size_t hash<sfz::Rectangle<T>>::operator() (const sfz::Rectangle<T>& rect) const
{
	return rect.hash();
}

} // namespace std