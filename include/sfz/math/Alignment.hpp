#pragma once
#ifndef SFZ_MATH_ALIGNMENT_HPP
#define SFZ_MATH_ALIGNMENT_HPP

namespace sfz {

	/**
	 * @brief A simple enum used to determine if something is left, center or right-aligned horizontally.
	 *
	 * The different values are considered to have different distance from each other. The distance from LEFT to
	 * CENTER is one unit, the distance from LEFT to RIGHT is two units. The formula for calculating the distance is
	 * 'destination - origin'. Therefore going from LEFT to RIGHT is the positive direction, going from RIGHT to LEFT
	 * is the negative direction.
	 *
	 * @author Peter Hillerström <peter@hstroem.se>
	 */
	enum class HorizontalAlign : char {
		LEFT = -1, 
		CENTER = 0, 
		RIGHT = 1
	};

	/**
	 * @brief A simple enum used to determine if something is bottom, middle or top-aligned vertically.
	 *
	 * The different values are considered to have different distance from each other. The distance from BOTTOM to
	 * MIDDLE is one unit, the distance from BOTTOM to TOP is two units. The formula for calculating the distance is
	 * 'destination - origin'. Therefore going from BOTTOM to TOP is the positive direction, going from TOP to BOTTOM
	 * is the negative direction.
	 *
	 * author Peter Hillerström <peter@hstroem.se>
	 */
	enum class VerticalAlign : char {
		BOTTOM = -1, 
		MIDDLE = 0, 
		TOP = 1
	};

	/**
	 * @brief Calculates the distance between two HorizontalAlign or VerticalAlign enums.
	 *
	 * Calculates and returns the distance between two enum values as defined by the enums. The answer will be signed
	 * and may have a positive or negative value depending on the 'direction'. 
	 *
	 * The behavior of this function is only defined when using HorizontalAlign or VerticalAlign.
	 *
	 * @param origin the origin enum
	 * @param destination the destination enum
	 * @return the distance between the two enums
	 */
	template<typename Align>
	char calculateAlignDistance(Align origin, Align destination) {
		return static_cast<char>(destination) - static_cast<char>(origin);
	}

	/**
	 * @brief Returns a denominator to divide the width/height of something to adjust for a change of alignment.
	 * 
	 * Assume we have a square with a position and a width. The alignment enums are used to define how the position
	 * relates to the square. If we for some reason want to change the alignment without moving the square we would
	 * need to recalculate the position. This is where this function comes in, to adjust the position you just have
	 * to do the following:
	 *
	 * 'oldPosition += width / alignChangeDenominator(oldAlign, newAlign)'
	 *
	 * WARNING: Will return 0 if origin == destination. If this is something that can occur you should check the 
	 * return value before dividing to avoid division by zero.
	 *
	 * The behavior of this function is only defined when using HorizontalAlign or VerticalAlign.
	 *
	 * @param origin the orign enum
	 * @param destination the destination eum
	 * @return the constant to divide the width/height with when adjusting alignment.
	 */
	template<typename Align>
	char alignChangeDenominator(Align origin, Align destination) {
		switch(calculateAlignDistance(origin, destination)) {
		case 0:
			return 0;
		case -2:
			return -1;
		case -1:
			return -2;
		case 1:
			return 2;
		case 2:
			return 1;
		default:
			throw std::logic_error{"This should not be possible."};
		}
	}

	/**
	 * @brief Calculates the new position when changing alignment.
	 *
	 * Uses the method described in alignChangeDenominator() to calculate the new position.
	 *
	 * @see alignChangeDenominator()
	 * @param oldPosition the old position
	 * @param size the size of the object in the desired axis
	 * @param origin the old alignment
	 * @param destination the new alignment
	 * @return the new position
	 */
	template<typename T, typename Align>
	T changeAlignAdjustPosition(T oldPosition, T size, Align origin, Align destination) {
		char denominator = alignChangeDenominator(origin, destination);
		if(denominator == 0) {
			return oldPosition;
		} 
		return oldPosition + (size / static_cast<T>(denominator));
	}
 }
#endif