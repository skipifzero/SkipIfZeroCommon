namespace sfz {

// Public constants
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
const Vector<T,N>& Vector<T,N>::ZERO() noexcept
{
	static const Vector<T,N> zero = []() -> Vector<T,N> {
		Vector<T,N> tmp;
		tmp.fill(T(0));
		return tmp;
	}();
	return zero; 
}

// Constructors and destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>::Vector(std::initializer_list<T> list) noexcept
{
	size_t listSize = list.size();
	sfz_assert_debug(listSize <= N);
	// Sets elements to values from initializer list.
	T* elementItr = mElements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
	// Sets remaining elements to 0.
	for (size_t i = listSize; i < N; i++) {
		mElements[i] = 0;
	}
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T& Vector<T,N>::at(const size_t index) noexcept
{
	sfz_assert_debug(index < N);
	return mElements[index];
}

template<typename T, size_t N>
T Vector<T,N>::at(const size_t index) const noexcept
{
	sfz_assert_debug(index < N);
	return mElements[index];
}

template<typename T, size_t N>
void Vector<T,N>::set(const size_t index, T value) noexcept
{
	sfz_assert_debug(index < N);
	mElements[index] = value;
}

template<typename T, size_t N>
void Vector<T,N>::fill(const T value) noexcept
{
	for (auto& element : mElements) {
		element = value;
	}
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
	auto itr = begin(other);
	for (auto element : mElements) {
		product += (element*(*itr++));
	}
	return product;
}

template<typename T, size_t N>
Vector<T,N> Vector<T,N>::elemMult(const Vector<T,N>& other) const noexcept
{
	Vector<T,N> result = *this;
	auto itr = begin(other);
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

// Operators (access)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T& Vector<T,N>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < N);
	return mElements[index];
}

template<typename T, size_t N>
T Vector<T,N>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < N);
	return mElements[index];
}

// Operators (arithmetic & assignment)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>& operator+= (Vector<T, N>& left, const Vector<T,N>& right) noexcept
{
	for (int i = 0; i < N; ++i) {
		left.mElements[i] += right.mElements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator-= (Vector<T, N>& left, const Vector<T,N>& right) noexcept
{
	for (int i = 0; i < N; ++i) {
		left.mElements[i] -= right.mElements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator*= (Vector<T, N>& left, const T& right) noexcept
{
	for (int i = 0; i < N; ++i) {
		left.mElements[i] *= right;
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator/= (Vector<T, N>& left, const T& right) noexcept
{
	sfz_assert_debug(right != T(0));
	for (int i = 0; i < N; ++i) {
		left.mElements[i] /= right;
	}
	return left;
}

// Operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N> operator+ (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	return (Vector<T,N>{left} += right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	return (Vector<T,N>{left} -= right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T, N>& vector) noexcept
{
	return (Vector<T,N>{vector} *= T(-1));
}

template<typename T, size_t N>
Vector<T,N> operator* (const Vector<T, N>& left, const T& right) noexcept
{
	return (Vector<T,N>{left} *= right);
}

template<typename T, size_t N>
Vector<T, N> operator* (const T& left, const Vector<T, N>& right) noexcept
{
	return right * left;
}

template<typename T, size_t N>
Vector<T,N> operator/ (const Vector<T, N>& left, const T& right) noexcept
{
	return (Vector<T,N>{left} /= right);
}

// Operators (comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
bool operator== (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	for (int i = 0; i < N; ++i) {
		if (left.mElements[i] != right.mElements[i]) return false;
	}
	return true;
}

template<typename T, size_t N>
bool operator!= (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	return !(left == right);
}

// Operators (other)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
std::ostream& operator<< (std::ostream& ostream, const Vector<T,N>& vector) noexcept
{
	return ostream << vector.to_string();
}

// Standard iterator functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T* begin(Vector<T, N>& vector) noexcept
{
	return vector.mElements;
}

template<typename T, size_t N>
const T* begin(const Vector<T, N>& vector) noexcept
{
	return vector.mElements;
}

template<typename T, size_t N>
const T* cbegin(const Vector<T, N>& vector) noexcept
{
	return vector.mElements;
}

template<typename T, size_t N>
T* end(Vector<T, N>& vector) noexcept
{
	return vector.mElements + N;
}

template<typename T, size_t N>
const T* end(const Vector<T, N>& vector) noexcept
{
	return vector.mElements + N;
}

template<typename T, size_t N>
const T* cend(const Vector<T, N>& vector) noexcept
{
	return vector.mElements + N;
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