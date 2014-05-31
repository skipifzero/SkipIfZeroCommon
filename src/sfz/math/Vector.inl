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

	// Public member functions
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

	template<class T, std::size_t N>
	Vector<T,N> Vector<T,N>::elementMultiply(const Vector<T,N>& other) const {
		Vector<T,N> result = *this;
		auto itr = other.begin();
		for(auto& element : result) {
			element *= *itr++;
		}
		return result;
	}

	template<class T, std::size_t N>
	T Vector<T,N>::sum() const {
		T result = 0;
		for(auto element : elements) {
			result += element;
		}
		return result;
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

	// Member operators (access)
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T& Vector<T,N>::operator [](std::size_t index) {
		return elements.at(index);
	}

	template<class T, std::size_t N>
	const T& Vector<T,N>::operator [](std::size_t index) const {
		return elements.at(index);
	}

	// Member operators (Arithmetic & Assignment)
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

	// Free (non-member) functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<class T, std::size_t N>
	T norm(const Vector<T,N>& vector) {
		return vector.norm();
	}

	template<class T, std::size_t N>
	Vector<T,N> normalize(const Vector<T,N>& vector) {
		return vector.normalize();
	}

	template<class T>
	T angle(const Vector<T,2>& vector) {
		if(vector[x] == 0 && vector[y] == 0) {
			throw std::domain_error("Norm of vector is 0");
		}
		T angle = std::atan2(vector[y], vector[x]);
		if(angle < 0) {
			angle += 2.f*static_cast<T>(PI_DOUBLE);
		}
		return angle;
	}

	template<class T, std::size_t N>
	T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) {
		T normA = norm(vectorA);
		T normB = norm(vectorB);
		if(normA == 0) {
			throw std::domain_error("Norm of vectorA is 0");
		}
		if(normB == 0) {
			throw std::domain_error("Norm of vectorB is 0");
		}
		return std::acos(vectorA.dot(vectorB)/(std::sqrt(vectorA.squaredNorm()*vectorB.squaredNorm())));
	}

	// Free (non-member) operators (Arithmetic)
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

	// Free (non-member) operators (Comparison)
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
