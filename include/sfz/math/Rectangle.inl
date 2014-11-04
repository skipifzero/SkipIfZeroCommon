namespace sfz {

// Static constants & public members
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
const HorizontalAlign Rectangle<T>::s_DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

template<typename T>
const VerticalAlign Rectangle<T>::s_DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
template<typename T2>
Rectangle<T>::Rectangle(const Rectangle<T2>& rect) noexcept
:
	mPos{static_cast<vec2<T2>>(rect.mPos)},
	mDim{static_cast<vec2<T2>>(rect.mDim)},
	mHAlign{rect.mHAlign},
	mVAlign{rect.mVAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& rect,
                        HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	Rectangle<T>{rect}
{
	changeAlign(hAlign, vAlign);
}

template<typename T>
Rectangle<T>::Rectangle(const vec2<T>& position, const vec2<T>& dimensions,
                        HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	mPos{position},
	mDim{dimensions},
	mHAlign{hAlign},
	mVAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(const vec2<T>& position, T width, T height, 
                        HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	mPos{position},
	mDim{width, height},
	mHAlign{hAlign},
	mVAlign{vAlign}
{
	// Initialization done.
}

template<typename T>
Rectangle<T>::Rectangle(T x, T y, T width, T height,
                        HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
:
	mPos{x, y},
	mDim{width, height},
	mHAlign{hAlign},
	mVAlign{vAlign}
{
	// Initialization done.
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Rectangle<T>::overlap(const vec2<T>& point) const noexcept
{
	Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

	T rectXLeft = leftBottomAlignRect.x();
	T rectXRight = rectXLeft + std::abs(leftBottomAlignRect.width());
	T rectYBottom = leftBottomAlignRect.y();
	T rectYTop = rectYBottom + std::abs(leftBottomAlignRect.height());
	T vecX = point[0];
	T vecY = point[1];

	return rectXLeft <= vecX && rectXRight >= vecX &&
	       rectYBottom <= vecY && rectYTop>= vecY;
}

template<typename T>
bool Rectangle<T>::overlap(const Rectangle<T>& rect) const noexcept
{
	Rectangle<T> leftBottomAlignRectThis{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
	Rectangle<T> leftBottomAlignRectOther{rect, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};

	T thisXLeft = leftBottomAlignRectThis.x();
	T thisXRight = thisXLeft + std::abs(leftBottomAlignRectThis.width());
	T thisYBottom = leftBottomAlignRectThis.y();
	T thisYTop = thisYBottom + std::abs(leftBottomAlignRectThis.height());

	T otherXLeft = leftBottomAlignRectOther.x();
	T otherXRight = otherXLeft + std::abs(leftBottomAlignRectOther.width());
	T otherYBottom = leftBottomAlignRectOther.y();
	T otherYTop = otherYBottom + std::abs(leftBottomAlignRectOther.height());

	return thisXLeft   <= otherXRight &&
	       thisXRight  >= otherXLeft &&
	       thisYBottom <= otherYTop &&
	       thisYTop    >= otherYBottom;
}

template<typename T>
bool Rectangle<T>::overlap(const Circle<T>& circle) const noexcept
{
	Rectangle<T> leftBottomAlignRect{*this, HorizontalAlign::LEFT, VerticalAlign::BOTTOM};
	Circle<T> centerAlignCircle{circle, HorizontalAlign::CENTER, VerticalAlign::MIDDLE};

	T rectXLeft = leftBottomAlignRect.x();
	T rectXRight = rectXLeft + std::abs(leftBottomAlignRect.width());
	T rectYBottom = leftBottomAlignRect.y();
	T rectYTop = rectYBottom + std::abs(leftBottomAlignRect.height());

	T circleX = centerAlignCircle.x();
	T circleY = centerAlignCircle.y();
	T radius = std::abs(centerAlignCircle.radius());

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
T Rectangle<T>::area() const noexcept
{
	return std::abs(width())*std::abs(height());
}

template<typename T>
T Rectangle<T>::circumference() const noexcept
{
	return std::abs(width())*2 + std::abs(height())*2;
}

template<typename T>
size_t Rectangle<T>::hash() const noexcept
{
	std::hash<T> hasher;
	std::hash<char> enumHasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mPos[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mPos[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mDim[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mDim[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mHAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= enumHasher(static_cast<char>(mVAlign)) +
	                   0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

template<typename T>
std::string Rectangle<T>::to_string() const noexcept
{
	std::string str;
	str += "[pos=";
	str += mPos.to_string();
	str += ", dim=";
	str += mDim.to_string();
	str += ", align: ";
	str += sfz::to_string(mHAlign);
	str += ", ";
	str += sfz::to_string(mVAlign);
	str += "]";
	return std::move(str);
}

template<typename T>
void Rectangle<T>::changeHorizontalAlign(HorizontalAlign hAlign) noexcept
{
	assert(mHAlign == HorizontalAlign::LEFT ||
	       mHAlign == HorizontalAlign::CENTER ||
	       mHAlign == HorizontalAlign::RIGHT);
	mPos[0] = calculateNewPosition(mPos[0], std::abs(mDim[0]), mHAlign, hAlign);
	mHAlign = hAlign;
}

template<typename T>
void Rectangle<T>::changeVerticalAlign(VerticalAlign vAlign) noexcept
{
	assert(mVAlign == VerticalAlign::BOTTOM ||
	       mVAlign == VerticalAlign::MIDDLE ||
	       mVAlign == VerticalAlign::TOP);
	mPos[1] = calculateNewPosition(mPos[1], std::abs(mDim[1]), mVAlign, vAlign);
	mVAlign = vAlign;
}

template<typename T>
void Rectangle<T>::changeAlign(HorizontalAlign hAlign, VerticalAlign vAlign) noexcept
{
	changeHorizontalAlign(hAlign);
	changeVerticalAlign(vAlign);
}

// Getters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
T Rectangle<T>::x() const noexcept
{
	return mPos[0];
}

template<typename T>
T Rectangle<T>::y() const noexcept
{
	return mPos[1];
}

template<typename T>
T Rectangle<T>::width() const noexcept
{
	return mDim[0];
}

template<typename T>
T Rectangle<T>::height() const noexcept
{
	return mDim[1];
}

// Comparison operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
bool Rectangle<T>::operator== (const Rectangle<T>& other) const noexcept
{
	return mPos == other.mPos &&
	       mDim == other.mDim &&
	       mHAlign == other.mHAlign &&
	       mVAlign == other.mVAlign;
}

template<typename T>
bool Rectangle<T>::operator!= (const Rectangle<T>& other) const noexcept
{
	return !((*this) == other);
}

template<typename T>
bool Rectangle<T>::operator< (const Rectangle<T>& other) const noexcept
{
	return this->area() < other.area();
}

template<typename T>
bool Rectangle<T>::operator> (const Rectangle<T>& other) const noexcept
{
	return this->area() > other.area();
}

template<typename T>
bool Rectangle<T>::operator<= (const Rectangle<T>& other) const noexcept
{
	return this->area() <= other.area();
}

template<typename T>
bool Rectangle<T>::operator>= (const Rectangle<T>& other) const noexcept
{
	return this->area() >= other.area();
}

// Free (non-member) operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
std::ostream& operator<< (std::ostream& ostream, const Rectangle<T> rect) noexcept
{
	return ostream << rect.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Rectangle
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
namespace std {

template<typename T>
size_t hash<sfz::Rectangle<T>>::operator() (const sfz::Rectangle<T>& rect) const noexcept
{
	return rect.hash();
}

} // namespace std