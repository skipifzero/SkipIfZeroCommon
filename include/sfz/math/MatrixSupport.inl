namespace sfz {

// Rotation matrices
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Matrix<T,4,4> xRotationMatrix(T angleRads) noexcept
{
	using std::cos;
	using std::sin;
	return Matrix<T,4,4>{{static_cast<T>(1), 0, 0, 0},
	                     {0, static_cast<T>(cos(angleRads)), static_cast<T>(-sin(angleRads)), 0},
	                     {0, static_cast<T>(sin(angleRads)), static_cast<T>(cos(angleRads)), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

template<typename T>
Matrix<T,4,4> yRotationMatrix(T angleRads) noexcept
{
	using std::cos;
	using std::sin;
	return Matrix<T,4,4>{{static_cast<T>(cos(angleRads)), 0, static_cast<T>(sin(angleRads)), 0},
	                     {0, static_cast<T>(1), 0, 0},
	                     {static_cast<T>(-sin(angleRads)), 0, static_cast<T>(cos(angleRads)), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

template<typename T>
Matrix<T,4,4> zRotationMatrix(T angleRads) noexcept
{
	using std::cos;
	using std::sin;
	return Matrix<T,4,4>{{static_cast<T>(cos(angleRads)), static_cast<T>(-sin(angleRads)), 0, 0},
	                     {static_cast<T>(sin(angleRads)), static_cast<T>(cos(angleRads)), 0, 0},
	                     {0, 0, static_cast<T>(1), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

/*template<typename T>
Matrix<T,4,4> generalRotationMatrix(const Vector<T,3>& point, const Vector<T,3>& axis,
                                    T angleRads) noexcept
{

}*/

// Transformation matrices
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Matrix<T,4,4> identityMatrix() noexcept
{
	return Matrix<T,4,4>{{static_cast<T>(1), 0, 0, 0},
	                     {0, static_cast<T>(1), 0, 0},
	                     {0, 0, static_cast<T>(1), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

template<typename T>
Matrix<T,4,4> scalingMatrix(T scaleFactor) noexcept
{
	return Matrix<T,4,4>{{static_cast<T>(scaleFactor), 0, 0, 0},
	                     {0, static_cast<T>(scaleFactor), 0, 0},
	                     {0, 0, static_cast<T>(scaleFactor), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

template<typename T>
Matrix<T,4,4> scalingMatrix(T scaleX, T scaleY, T scaleZ) noexcept
{
	return Matrix<T,4,4>{{static_cast<T>(scaleX), 0, 0, 0},
	                     {0, static_cast<T>(scaleY), 0, 0},
	                     {0, 0, static_cast<T>(scaleZ), 0},
	                     {0, 0, 0, static_cast<T>(1)}};
}

template<typename T>
Matrix<T,4,4> translationMatrix(T deltaX, T deltaY, T deltaZ) noexcept
{
	return Matrix<T,4,4>{{static_cast<T>(1), 0, 0, static_cast<T>(deltaX)},
	                     {0, static_cast<T>(1), 0, static_cast<T>(deltaY)},
	                     {0, 0, static_cast<T>(1), static_cast<T>(deltaZ)},
	                     {0, 0, 0, static_cast<T>(1)}};
}

// Projection matrices
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

template<typename T>
Matrix<T,4,4> glOrthogonalProjectionMatrix(T left, T bottom, T near,
                                           T right, T top, T far) noexcept
{
	return Matrix<T,4,4>{{2/(right-left), 0, 0, -((right+left)/(right-left))},
	                     {0, 2/(top-bottom), 0, -((top+bottom)/(top-bottom))},
	                     {0, 0, -2/(far-near), -(far+near)/(far-near)},
	                     {0, 0, 0, 1}};
}

template<typename T>
Matrix<T,4,4> glOrthogonalProjectionMatrix(const sfz::Vector<T,3>& leftBottomNear,
                                           const sfz::Vector<T,3>& rightTopFar) noexcept
{
	return glOrthogonalProjectionMatrix(leftBottomNear[0], leftBottomNear[1], leftBottomNear[2],
	                                    rightTopFar[0], rightTopFar[1], rightTopFar[2]);
}

} // namespace sfz