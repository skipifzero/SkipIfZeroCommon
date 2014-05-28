namespace sfz {
	
	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	template<class T, std::size_t N>
	Vector<T,N>::Vector() {
		elements.fill(0);
	}

	template<class T, std::size_t N>
	Vector<T,N>::Vector(const Vector<T,N>& vector) {
		elements = vector.elements;
	}

	template<class T, std::size_t N>
	template<class T2>
	Vector<T,N>::Vector(const Vector<T2,N>& vector) {
		auto itr = vector.begin();
		for(auto& element : elements) {
			element = static_cast<T>(*itr++);
		}
	}

	template<class T, std::size_t N>
	Vector<T,N>::Vector(std::initializer_list<T> list) {
		if(list.size() != N) {
			throw std::invalid_argument{
				std::to_string(list.size()) + " arguments to " + std::to_string(N) + "-dimensional vector"};
		}
		std::copy(list.begin(), list.end(), elements.begin());
	}

	// Public functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T Vector<T,N>::get(std::size_t index) const {
		return elements.at(index);
	}

	template<class T, std::size_t N>
	void Vector<T,N>::set(std::size_t index, T value) {
		elements.at(index) = value;
	}

	template<class T, std::size_t N>
	void Vector<T,N>::fill(T value) {
		elements.fill(value);
	}

	template<class T, std::size_t N>
	T Vector<T,N>::norm() const {
		return std::sqrt(squaredNorm());
	}

	template<class T, std::size_t N>
	T Vector<T,N>::squaredNorm() const {
		T squaredSum = 0;
		for(auto element : elements) {
			squaredSum += element*element;
		}
		return squaredSum;
	}

	template<class T, std::size_t N>
	Vector<T,N> Vector<T,N>::normalize() const {
		T normTmp = norm();
		if(normTmp == 0) {
			return *this;
		} 
		return (*this)/normTmp;
	}

	template<class T, std::size_t N>
	T Vector<T,N>::dot(const Vector<T,N>& other) const {
		T product = 0;
		auto itr = other.begin();
		for(auto element : elements) {
			product += (element*(*itr++));
		}
		return product;
	}

	// Standard iterator functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	typename Vector<T,N>::iterator Vector<T,N>::begin() {
		return elements.begin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::begin() const {
		return elements.begin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::cbegin() const {
		return elements.cbegin();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::iterator Vector<T,N>::end() {
		return elements.end();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::end() const {
		return elements.end();
	}

	template<class T, std::size_t N>
	typename Vector<T,N>::const_iterator Vector<T,N>::cend() const {
		return elements.cend();
	}

	// Internal operators
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T& Vector<T,N>::operator [](std::size_t index) {
		return elements.at(index);
	}

	template<class T, std::size_t N>
	const T& Vector<T,N>::operator [](std::size_t index) const {
		return elements.at(index);
	}

	// Internal operators (Arithmetic & Assignment)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator +=(const Vector<T,N>& right) {
		auto itr = right.begin();
		for(auto& element : elements) {
			element += *itr++;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator -=(const Vector<T,N>& right) {
		auto itr = right.begin();
		for(auto& element : elements) {
			element -= *itr++;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator *=(const T& right) {
		for(auto& element : elements) {
			element *= right;
		}
		return *this;
	}

	template<class T, std::size_t N>
	Vector<T,N>& Vector<T,N>::operator /=(const T& right) {
		if(right == 0) {
			throw std::domain_error{"Division by zero"};
		}
		for(auto& element : elements) {
			element /= right;
		}
		return *this;
	}

	// External functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T norm(const Vector<T,N>& vector) {
		return vector.norm();
	}

	template<class T, std::size_t N>
	Vector<T,N> normalize(const Vector<T,N>& vector) {
		return vector.normalize();
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
		return left.squaredNorm() < right.squaredNorm();
	}

	template<class T, std::size_t N>
	bool operator >(const Vector<T,N>& left, const Vector<T,N>& right) {
		return right < left;
	}

	template<class T, std::size_t N>
	bool operator <=(const Vector<T,N>& left, const Vector<T,N>& right) {
		return left.squaredNorm() <= right.squaredNorm();
	}

	template<class T, std::size_t N>
	bool operator >=(const Vector<T,N>& left, const Vector<T,N>& right) {
		return right <= left;
	}
}
