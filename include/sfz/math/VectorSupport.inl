namespace sfz {

template<typename T>
Vector<T,3> cross(const Vector<T,3>& vectorA, const Vector<T,3>& vectorB) noexcept
{
	sfz::Vector<T,3> result;
	result[0] = vectorA[1]*vectorB[2] - vectorA[2]*vectorB[1];
	result[1] = vectorA[2]*vectorB[0] - vectorA[0]*vectorB[2];
	result[2] = vectorA[0]*vectorB[1] - vectorA[1]*vectorB[0];
	return result;
}

template<typename T, size_t N>
T angle(const Vector<T,N>& vectorA, const Vector<T,N>& vectorB) noexcept
{
	auto squaredLengthA = squaredLength(vectorA);
	sfz_assert_debug(squaredLengthA != 0);
	auto squaredLengthB = squaredLength(vectorB);
	sfz_assert_debug(squaredLengthB != 0);
	return std::acos(dot(vectorA, vectorB)/(std::sqrt(squaredLengthA*squaredLengthB)));
}

template<typename T>
T angle(const Vector<T,2>& vector) noexcept
{
	sfz_assert_debug(!(vector[0] == 0 && vector[1] == 0));
	T angle = std::atan2(vector[1], vector[0]);
	if (angle < 0) {
		angle += T(2)*PI<T>();
	}
	return angle;
}

template<typename T>
Vector<T,2> rotate(const Vector<T,2>& vector, const T angle) noexcept
{
	T cos = std::cos(angle);
	T sin = std::sin(angle);	
	return Vector<T,2>{vector[0]*cos - vector[1]*sin, vector[0]*sin + vector[1]*cos};
}

template<typename T, size_t N>
Vector<T,N> projectOnto(const Vector<T,N>& toProject, const Vector<T,N>& target) noexcept {
	T targetSquaredLength = squaredLength(target);
	if (targetSquaredLength == 0) return target; // Returns 0 vector, target == 0 vector.
	return target * (dot(toProject, target)/targetSquaredLength);
}

} // namespace sfz