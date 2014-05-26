namespace sfz {
	
	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	template<class T, std::size_t N>
	Vector<T,N>::Vector() {
		array.fill(0);
	}

	template<class T, std::size_t N>
	Vector<T,N>::Vector(const sfz::Vector<T,N>& vector) {
		array = vector.array;
	}

	template<class T, std::size_t N>
	Vector<T,N>::Vector(std::initializer_list<T> list) {
		if(list.size() != N) {
			throw std::invalid_argument{
				std::to_string(list.size()) + " arguments to " + std::to_string(N) + "-dimensional vector"};
		}
		std::copy(list.begin(), list.end(), array.begin());
	}

	// Public functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T Vector<T,N>::get(std::size_t index) const {
		return array.at(index);
	}

	template<class T, std::size_t N>
	void Vector<T,N>::set(std::size_t index, T value) {
		array.at(index) = value;
	}

	template<class T, std::size_t N>
	T Vector<T,N>::length() const {
		return std::sqrt(lengthSquared());
	}

	template<class T, std::size_t N>
	T Vector<T,N>::lengthSquared() const {
		T squaredSum = 0;
		for(auto element : array) {
			squaredSum += element*element;
		}
		return squaredSum;
	}

	template<class T, std::size_t N>
	T Vector<T,N>::dot(const Vector<T,N>& other) const {
		T product = 0;
		auto itr = other.begin();
		for(auto element : array) {
			product += (element*(*itr++));
		}
		return product;
	}

	// Standard iterator functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	typename Vector<T,N>::iterator Vector<T,N>::begin() {
		return array.begin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::begin() const {
		return array.begin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::cbegin() const {
		return array.cbegin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::iterator Vector<T,N>::end() {
		return array.end();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::end() const {
		return array.end();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::cend() const {
		return array.cend();
	}

	// Internal operators
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T& Vector<T,N>::operator [](std::size_t index) {
		return array.at(index);
	}

	template<class T, std::size_t N>
	const T& Vector<T,N>::operator [](std::size_t index) const {
		return array.at(index);
	}

	// Internal operators (Arithmetic & Assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator +=(const Vector<T,N>& right) {
		auto itr = right.begin();
		for(auto& element : array) {
			element += *itr++;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator -=(const Vector<T,N>& right) {
		auto itr = right.begin();
		for(auto& element : array) {
			element -= *itr++;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator *=(const T& right) {
		for(auto& element : array) {
			element *= right;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator /=(const T& right) {
		if(right == 0) {
			throw std::domain_error{"Division by zero"};
		}
		for(auto& element : array) {
			element /= right;
		}
		return *this;
	}

	// External Operators (Arithmetic)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	template<class T, std::size_t N>
	Vector<T,N> operator +(const Vector<T,N>& left, const Vector<T,N>& right) {
		return (Vector<T,N>{left} += right);
	}

	template<class T, std::size_t N>
	Vector<T,N> operator -(const Vector<T,N>& left, const Vector<T,N>& right) {
		return (Vector<T,N>{left} -= right);
	}

	template<class T, std::size_t N>
	Vector<T,N> operator -(const Vector<T,N>& right) {
		return (Vector<T,N>{right} *= -1);
	}

	template<class T, std::size_t N>
	Vector<T,N> operator *(const Vector<T,N>& left, const T& right) {
		return (Vector<T,N>{left} *= right);
	}

	template<class T, std::size_t N>
	Vector<T,N> operator *(const T& left, const Vector<T,N>& right) {
		return (Vector<T,N>{right} *= left);
	}

	template<class T, std::size_t N>
	Vector<T,N> operator /(const Vector<T,N>& left, const T& right) {
		return (Vector<T,N>{left} /= right);
	}

	// External Operators (Comparison)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	bool operator ==(const Vector<T,N>& left, const Vector<T,N>& right) {
		auto itr = right.begin();
		for(auto element : left) {
			if(element != *itr++) {
				return false;
			}
		}
		return true;
	}

	template<class T, std::size_t N>
	bool operator !=(const Vector<T,N>& left, const Vector<T,N>& right) {
		return !(left == right);
	}

	template<class T, std::size_t N>
	bool operator <(const Vector<T,N>& left, const Vector<T,N>& right) {
		return left.lengthSquared() < right.lengthSquared();
	}

	template<class T, std::size_t N>
	bool operator >(const Vector<T,N>& left, const Vector<T,N>& right) {
		return left.lengthSquared() > right.lengthSquared();
	}

	template<class T, std::size_t N>
	bool operator <=(const Vector<T,N>& left, const Vector<T,N>& right) {
		return left.lengthSquared() <= right.lengthSquared();
	}

	template<class T, std::size_t N>
	bool operator >=(const Vector<T,N>& left, const Vector<T,N>& right) {
		return left.lengthSquared() >= right.lengthSquared();
	}
}
