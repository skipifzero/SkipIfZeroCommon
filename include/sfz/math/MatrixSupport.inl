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

template<typename T>
Matrix<T,4,4> glPerspectiveProjectionMatrix(T left, T bottom, T zNear,
                                            T right, T top, T zFar) noexcept
{
	T zNear2 = 2*zNear;
	T rightMLeft = right-left;
	T topMBottom = top-bottom;
	T zFarMzNear = zFar-zNear;
	return Matrix<T,4,4>{{zNear2/rightMLeft, 0, (right+left)/rightMLeft, 0},
	                     {0, zNear2/topMBottom, (top+bottom)/topMBottom, 0},
	                     {0, 0, -(zFar+zNear)/zFarMzNear, -(zNear2*zFar)/zFarMzNear},
	                     {0, 0, -1, 0}};
}

Matrix<float,4,4> glPerspectiveProjectionMatrix(float yFovDeg, float aspectRatio,
                                                float zNear, float zFar) noexcept
{
	assert(0 < zNear);
	assert(zNear < zFar);
	float yMax = zNear * tanf(yFovDeg * (g_PI_FLOAT/360.f));
	float xMax = yMax * aspectRatio;
	return glPerspectiveProjectionMatrix(-xMax, -yMax, zNear, xMax, yMax, zFar);
}

} // namespace sfz