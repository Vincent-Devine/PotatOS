#pragma once

#include <cmath>
#include <corecrt_math_defines.h>

namespace Math
{
	template<typename T>
	inline T Max(const T& p_a, const T& p_b) { return p_a > p_b ? p_a : p_b; }

	template<typename T>
	inline T Min(const T& p_a, const T& p_b) { return p_a < p_b ? p_a : p_b; }

	template <typename T>
	inline T Abs(const T& p_a) { return p_a < 0 ? -p_a : p_a; }

	template<typename T>
	inline T lerp(const T& p_a, const T& p_b, float p_t) { return p_a + p_t * (p_b - p_a); }

	template <typename T>
	inline T Clamp(const T p_value, const T p_min, const T p_max)
	{
		if (p_value < p_min)
		{
			return p_min;
		}
		if (p_value > p_max)
		{
			return p_max;
		}
		return p_value;
	}
}