namespace sfz {

// Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t M, size_t N>
Matrix<T,M,N>::Matrix(std::initializer_list<std::initializer_list<T>> list) noexcept
{
	assert(list.size() <= N);
	size_t i = 0;
	for (auto& rowList : list) {
		assert(rowList.size() <= M);
		size_t j = 0;
		for (auto element : rowList) {
			mElements[j][i] = element;
			j++;
		}
		while (j < N) {
			mElements[j][i] = 0;
			j++;
		}
		i++;
	}
	while (i < M) {
		for (size_t j = 0; j < N; j++) {
			mElements[j][i] = 0;
		}
		i++;
	}
}

// Member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T, size_t M, size_t N>
T& Matrix<T,M,N>::get(size_t i, size_t j) noexcept
{
	return mElements[j][i];
}

template<typename T, size_t M, size_t N>
T Matrix<T,M,N>::get(size_t i, size_t j) const noexcept
{
	return mElements[j][i];
}

template<typename T, size_t M, size_t N>
std::string Matrix<T,M,N>::to_string() const noexcept
{
	using std::to_string;
	std::string str;
	for (size_t i = 0; i < M; i++) {
		str += "Row ";
		str += to_string(i);
		str += ": ";
		for (size_t j = 0; j < N; j++) {
			str += to_string(get(i, j));
			str += ", ";
		}
		str += "\n";
	}
	return std::move(str);
}

// Operators (access)
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

} // namespace sfz