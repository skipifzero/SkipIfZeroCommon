namespace sfz {
	
// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
template<typename T2>
Vector<T,N>::Vector(const Vector<T2,N>& vector) noexcept
{
	auto itr = vector.begin();
	for (auto& element : mElements) {
		element = static_cast<T>(*itr++);
	}
}

template<typename T, size_t N>
Vector<T,N>::Vector(std::initializer_list<T> list) noexcept
{
	assert(list.size() == N);
	T* elementItr = mElements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T Vector<T,N>::get(const size_t index) const noexcept
{
	assert(index < N);
	return mElements[index];
}

template<typename T, size_t N>
void Vector<T,N>::set(const size_t index, T value)
{
	assert(index < N);
	mElements[index] = value;
}

template<typename T, size_t N>
void Vector<T,N>::fill(const T value) noexcept
{
	for (auto& element : mElements) {
		element = value;
	}
	//mElements.fill(value);
}

template<typename T, size_t N>
T Vector<T,N>::norm() const noexcept
{
	return std::sqrt(squaredNorm());
}

template<typename T, size_t N>
T Vector<T,N>::squaredNorm() const noexcept
{
	T squaredSum = 0;
	for (auto element : mElements) {
		squaredSum += element*element;
	}
	return squaredSum;
}

template<typename T, size_t N>
Vector<T,N> Vector<T,N>::normalize() const noexcept
{
	T normTmp = norm();
	if (normTmp == 0) return *this;
	return (*this)/normTmp;
}

template<typename T, size_t N>
T Vector<T,N>::dot(const Vector<T,N>& other) const noexcept
{
	T product = 0;
	auto itr = other.begin();
	for (auto element : mElements) {
		product += (element*(*itr++));
	}
	return product;
}

template<typename T, size_t N>
Vector<T,N> Vector<T,N>::elemMult(const Vector<T,N>& other) const noexcept
{
	Vector<T,N> result = *this;
	auto itr = other.begin();
	for (auto& element : result) {
		element *= *itr++;
	}
	return result;
}

template<typename T, size_t N>
T Vector<T,N>::sum() const noexcept
{
	T result = 0;
	for (auto element : mElements) {
		result += element;
	}
	return result;
}

template<typename T, size_t N>
Vector<T,N> Vector<T,N>::projectOnto(const Vector<T,N>& target) const noexcept {
	auto targetSquaredNorm = target.squaredNorm();
	if (targetSquaredNorm == 0) return target; // Returns 0 vector, target == 0 vector.
	return target * (this->dot(target)/targetSquaredNorm);
}

template<typename T, size_t N>
Vector<T,N> Vector<T,N>::distance(const Vector<T,N>& other) const noexcept
{
	return other - *this;
}

template<typename T, size_t N>
size_t Vector<T,N>::hash() const noexcept
{
	std::hash<T> hasher;
	size_t hash = 0;
	for (auto element : mElements) {
		// hash_combine algorithm from boost
		hash ^= hasher(element) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}
	return hash;
}

template<typename T, size_t N>
std::string Vector<T,N>::to_string() const noexcept
{
	std::string str;
	str += "[";
	for (auto element : mElements) {
		str += std::to_string(element);
		str += ", ";
	}
	str.erase(str.length()-2);
	str += "]";
	return std::move(str);
}

// Standard iterator functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
typename Vector<T,N>::iterator Vector<T,N>::begin() noexcept
{
	return mElements;
	//return mElements.begin();
}

template<typename T, size_t N>
typename Vector<T,N>::const_iterator Vector<T,N>::begin() const noexcept
{
	return mElements;
	//return mElements.begin();
}

template<typename T, size_t N>
typename Vector<T,N>::const_iterator Vector<T,N>::cbegin() const noexcept
{
	return mElements;
	//return mElements.cbegin();
}

template<typename T, size_t N>
typename Vector<T,N>::iterator Vector<T,N>::end() noexcept
{
	return mElements + N;
	//return mElements.end();
}

template<typename T, size_t N>
typename Vector<T,N>::const_iterator Vector<T,N>::end() const noexcept
{
	return mElements + N;
	//return mElements.end();
}

template<typename T, size_t N>
typename Vector<T,N>::const_iterator Vector<T,N>::cend() const noexcept
{
	return mElements + N;
	//return mElements.cend();
}

// Member operators (access)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T& Vector<T,N>::operator[] (const size_t index) noexcept
{
	return mElements[index];
}

template<typename T, size_t N>
const T& Vector<T,N>::operator[] (const size_t index) const noexcept
{
	return mElements[index];
}

// Member operators (Arithmetic & Assignment)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>& Vector<T,N>::operator+= (const Vector<T,N>& right) noexcept
{
	auto itr = right.begin();
	for (auto& element : mElements) {
		element += *itr++;
	}
	return *this;
}

template<typename T, size_t N>
Vector<T,N>& Vector<T,N>::operator-= (const Vector<T,N>& right) noexcept
{
	auto itr = right.begin();
	for (auto& element : mElements) {
		element -= *itr++;
	}
	return *this;
}

template<typename T, size_t N>
Vector<T,N>& Vector<T,N>::operator*= (const T& right) noexcept
{
	for (auto& element : mElements) {
		element *= right;
	}
	return *this;
}

template<typename T, size_t N>
Vector<T,N>& Vector<T,N>::operator/= (const T& right) noexcept
{
	assert(right != 0);
	for (auto& element : mElements) {
		element /= right;
	}
	return *this;
}

// Free (non-member) functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T norm(const Vector<T,N>& vector) noexcept
{
	return vector.norm();
}

template<typename T, size_t N>
Vector<T,N> normalize(const Vector<T,N>& vector) noexcept
{
	return vector.normalize();
}

template<typename T, size_t N>
T dot(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept
{
	return vectorA.dot(vectorB);
}

template<typename T>
Vector<T,3> cross(const Vector<T,3>& vectorA, const Vector<T,3>& vectorB) noexcept
{
	sfz::Vector<T,3> result;
	result[0] = vectorA[1]*vectorB[2] - vectorA[2]*vectorB[1];
	result[1] = vectorA[2]*vectorB[0] - vectorA[0]*vectorB[2];
	result[2] = vectorA[0]*vectorB[1] - vectorA[1]*vectorB[0];
	return result;
}

template<typename T>
T angle(const Vector<T,2>& vector) noexcept
{
	assert(!(vector[0] == 0 && vector[1] == 0));
	T angle = std::atan2(vector[1], vector[0]);
	if (angle < 0) {
		angle += static_cast<T>(2)*static_cast<T>(g_PI_DOUBLE);
	}
	return angle;
}

template<typename T, size_t N>
T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept
{
	auto squaredNormA = vectorA.squaredNorm();
	assert(squaredNormA != 0);
	auto squaredNormB = vectorB.squaredNorm();
	assert(squaredNormB != 0);
	return std::acos(vectorA.dot(vectorB)/(std::sqrt(squaredNormA*squaredNormB)));
}

template<typename T>
Vector<T,2> rotate(const Vector<T,2>& vector, const T angle) noexcept
{
	T cos = std::cos(angle);
	T sin = std::sin(angle);	
	return Vector<T,2>{vector[0]*cos - vector[1]*sin, vector[0]*sin + vector[1]*cos};
}

// Free (non-member) operators (Arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N> operator+ (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return (Vector<T,N>{left} += right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return (Vector<T,N>{left} -= right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T,N>& right) noexcept
{
	return (Vector<T,N>{right} *= -1);
}

template<typename T, size_t N>
Vector<T,N> operator* (const Vector<T,N>& left, const T& right) noexcept
{
	return (Vector<T,N>{left} *= right);
}

template<typename T, size_t N>
Vector<T,N> operator* (const T& left, const Vector<T,N>& right) noexcept
{
	return (Vector<T,N>{right} *= left);
}

template<typename T, size_t N>
Vector<T,N> operator/ (const Vector<T,N>& left, const T& right) noexcept
{
	return (Vector<T,N>{left} /= right);
}

// Free (non-member) operators (Comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
bool operator== (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	auto itr = right.begin();
	for (auto element : left) {
		if(element != *itr++) {
			return false;
		}
	}
	return true;
}

template<typename T, size_t N>
bool operator!= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return !(left == right);
}

template<typename T, size_t N>
bool operator< (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return left.squaredNorm() < right.squaredNorm();
}

template<typename T, size_t N>
bool operator> (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return right < left;
}

template<typename T, size_t N>
bool operator<= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return left.squaredNorm() <= right.squaredNorm();
}

template<typename T, size_t N>
bool operator>= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return right <= left;
}

// Free (non-member) operators (Other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept
{
	return ostream << vector.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::Vector
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t N>
size_t hash<sfz::Vector<T,N>>::operator() (const sfz::Vector<T,N>& vector) const noexcept
{
	return vector.hash();
}

} // namespace std
