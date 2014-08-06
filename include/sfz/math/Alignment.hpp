#pragma once
#ifndef SFZ_MATH_ALIGNMENT_HPP
#define SFZ_MATH_ALIGNMENT_HPP

namespace sfz {

	/**
	 * @brief A simple enum used to determine if something is left, center or right-aligned horizontally.
	 * @author Peter Hillerström <peter@hstroem.se>
	 */
	enum class HorizontalAlign : char {
		LEFT = -1, 
		CENTER = 0, 
		RIGHT = 1
	};

	/**
	 * @brief A simple enum used to determine if something is bottom, middle or top-aligned vertically.
	 * author Peter Hillerström <peter@hstroem.se>
	 */
	enum class VerticalAlign : char {
		BOTTOM = -1, 
		MIDDLE = 0, 
		TOP = 1
	};
}
#endif