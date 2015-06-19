namespace sfz {

// Vector struct declaration: Vector<T,N>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>::Vector(T value) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		elements[i] = value;
	}
}

template<typename T, size_t N>
Vector<T,N>::Vector(std::initializer_list<T> list) noexcept
{
	size_t listSize = list.size();
	sfz_assert_debug(listSize <= N);
	// Sets elements to values from initializer list.
	T* elementItr = elements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
	// Sets remaining elements to 0.
	for (size_t i = listSize; i < N; i++) {
		elements[i] = 0;
	}
}

template<typename T, size_t N>
T& Vector<T,N>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

template<typename T, size_t N>
T Vector<T,N>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

// Vector struct declaration: Vector<T,2>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,2>::Vector(T value) noexcept
{
	for (size_t i = 0; i < 2; ++i) {
		elements[i] = value;
	}
}

template<typename T>
Vector<T,2>::Vector(std::initializer_list<T> list) noexcept
{
	size_t listSize = list.size();
	sfz_assert_debug(listSize <= 2);
	// Sets elements to values from initializer list.
	T* elementItr = elements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
	// Sets remaining elements to 0.
	for (size_t i = listSize; i < 2; i++) {
		elements[i] = 0;
	}
}

template<typename T>
T& Vector<T,2>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 2);
	return elements[index];
}

template<typename T>
T Vector<T,2>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 2);
	return elements[index];
}

// Vector struct declaration: Vector<T,3>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,3>::Vector(T value) noexcept
{
	for (size_t i = 0; i < 3; ++i) {
		elements[i] = value;
	}
}

template<typename T>
Vector<T,3>::Vector(std::initializer_list<T> list) noexcept
{
	size_t listSize = list.size();
	sfz_assert_debug(listSize <= 3);
	// Sets elements to values from initializer list.
	T* elementItr = elements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
	// Sets remaining elements to 0.
	for (size_t i = listSize; i < 3; i++) {
		elements[i] = 0;
	}
}

template<typename T>
T& Vector<T,3>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 3);
	return elements[index];
}

template<typename T>
T Vector<T,3>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 3);
	return elements[index];
}

// Vector struct declaration: Vector<T,4>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Vector<T,4>::Vector(T value) noexcept
{
	for (size_t i = 0; i < 4; ++i) {
		elements[i] = value;
	}
}

template<typename T>
Vector<T,4>::Vector(std::initializer_list<T> list) noexcept
{
	size_t listSize = list.size();
	sfz_assert_debug(listSize <= 4);
	// Sets elements to values from initializer list.
	T* elementItr = elements;
	for (auto listElement : list) {
		*elementItr++ = listElement;
	}
	// Sets remaining elements to 0.
	for (size_t i = listSize; i < 4; i++) {
		elements[i] = 0;
	}
}

template<typename T>
T& Vector<T,4>::operator[] (const size_t index) noexcept
{
	sfz_assert_debug(index < 4);
	return elements[index];
}

template<typename T>
T Vector<T,4>::operator[] (const size_t index) const noexcept
{
	sfz_assert_debug(index < 4);
	return elements[index];
}

// Vector functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T length(const Vector<T,N>& vector) noexcept
{
	return std::sqrt(squaredLength(vector));
}

template<typename T, size_t N>
T squaredLength(const Vector<T,N>& vector) noexcept
{
	T squaredSum = 0;
	for (size_t i = 0; i < N; ++i) {
		squaredSum += vector.elements[i]*vector.elements[i];
	}
	return squaredSum;
}

template<typename T, size_t N>
Vector<T,N> normalize(const Vector<T,N>& vector) noexcept
{
	T lengthTmp = length(vector);
	if (lengthTmp == 0) return vector;
	return vector/lengthTmp;
}

template<typename T, size_t N>
T dot(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	T product = T(0);
	for (size_t i = 0; i < N; ++i) {
		product += (left.elements[i]*right.elements[i]);
	}
	return product;
}

template<typename T, size_t N>
Vector<T,N> elemMult(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> result = left;
	for (size_t i = 0; i < N; ++i) {
		result.elements[i] *= right.elements[i];
	}
	return result;
}

template<typename T, size_t N>
T sum(const Vector<T,N>& vector) noexcept
{
	T result = T(0);
	for (size_t i = 0; i < N; ++i) {
		result += vector.elements[i];
	}
	return result;
}

template<typename T, size_t N>
size_t hash(const Vector<T,N>& vector) noexcept
{
	std::hash<T> hasher;
	size_t hash = 0;
	for (size_t i = 0; i < N; ++i) {
		// hash_combine algorithm from boost
		hash ^= hasher(vector.elements[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}
	return hash;
}

template<typename T, size_t N>
std::string to_string(const Vector<T,N>& vector) noexcept
{
	std::string str;
	str += "[";
	for (size_t i = 0; i < N; ++i) {
		str += std::to_string(vector.elements[i]);
		str += ", ";
	}
	str.erase(str.length()-2);
	str += "]";
	return std::move(str);
}

// Operators (arithmetic & assignment)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N>& operator+= (Vector<T, N>& left, const Vector<T,N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] += right.elements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator-= (Vector<T, N>& left, const Vector<T,N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] -= right.elements[i];
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator*= (Vector<T, N>& left, const T& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] *= right;
	}
	return left;
}

template<typename T, size_t N>
Vector<T,N>& operator/= (Vector<T, N>& left, const T& right) noexcept
{
	sfz_assert_debug(right != T(0));
	for (size_t i = 0; i < N; ++i) {
		left.elements[i] /= right;
	}
	return left;
}

// Operators (arithmetic)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
Vector<T,N> operator+ (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp += right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp -= right);
}

template<typename T, size_t N>
Vector<T,N> operator- (const Vector<T, N>& vector) noexcept
{
	Vector<T,N> temp = vector;
	return (temp *= T(-1));
}

template<typename T, size_t N>
Vector<T,N> operator* (const Vector<T, N>& left, const T& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp *= right);
}

template<typename T, size_t N>
Vector<T, N> operator* (const T& left, const Vector<T, N>& right) noexcept
{
	return right * left;
}

template<typename T, size_t N>
Vector<T,N> operator/ (const Vector<T, N>& left, const T& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp /= right);
}

// Operators (comparison)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
bool operator== (const Vector<T, N>& left, const Vector<T, N>& right) noexcept
{
	for (size_t i = 0; i < N; ++i) {
		if (left.elements[i] != right.elements[i]) return false;
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
	return ostream << sfz::to_string(vector);
}

// Standard iterator functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t N>
T* begin(Vector<T, N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
const T* begin(const Vector<T, N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
const T* cbegin(const Vector<T, N>& vector) noexcept
{
	return vector.elements;
}

template<typename T, size_t N>
T* end(Vector<T, N>& vector) noexcept
{
	return vector.elements + N;
}

template<typename T, size_t N>
const T* end(const Vector<T, N>& vector) noexcept
{
	return vector.elements + N;
}

template<typename T, size_t N>
const T* cend(const Vector<T, N>& vector) noexcept
{
	return vector.elements + N;
}

} // namespace sfz

// Specializations of standard library for sfz::Vector
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<typename T, size_t N>
size_t hash<sfz::Vector<T,N>>::operator() (const sfz::Vector<T,N>& vector) const noexcept
{
	return sfz::hash(vector);
}

} // namespace std