#pragma once

namespace Math {
	/**
	 * Convert a value inside a range to a normalized float [0.0,1.0].
	 * For example: rangePosition(15, 10, 20) would return 0.5.
	 */
	template<typename T>
	float rangePosition(T value, T start, T end) {
		float position = ((float)(value-start))/(end-start);
		if(position < 0) position = 0.0;
		if(position > 1) position = 1.0;
		return position;
	}
}
