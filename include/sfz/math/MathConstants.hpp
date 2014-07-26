#pragma once
#ifndef SFZ_MATH_MATHCONSTANTS_HPP
#define SFZ_MATH_MATHCONSTANTS_HPP

#include <cmath>

namespace sfz {

	const float PI_FLOAT{std::atan(1.0f)*4.0f};
	const double PI_DOUBLE{std::atan(1.0)*4.0};
	
	const double DEG_TO_RAD_DOUBLE = PI_DOUBLE / 180.0;
	const double RAD_TO_DEG_DOUBLE = 180.0 / PI_DOUBLE;

	const float DEG_TO_RAD_FLOAT = PI_FLOAT / 180.0f;
	const float RAD_TO_DEG_FLOAT = 180.0f / PI_FLOAT;
}
#endif