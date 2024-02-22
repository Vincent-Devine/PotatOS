#pragma once

#include <cmath>
#include <corecrt_math_defines.h>

namespace Math
{
	static constexpr float RAD2DEG = 180.f / static_cast<float>(M_PI);
	static constexpr float DEG2RAD = static_cast<float>(M_PI) / 180.f;

	static constexpr float pi = 3.1415926f;
	static constexpr float halfPi = pi / 2.f;
	static constexpr float doublePi = pi * 2.f;
	static constexpr float epsilon = 1e-24f;
	static constexpr float weakEpsilon = 0.00001f;

	template<typename T = float>
	T Max(const T& p_a, const T& p_b);

	template<typename T = float>
	T Min(const T& p_a, const T& p_b);

	template <typename T>
	T Abs(const T& p_a);

	template <typename T>
	T lerp(const T& p_a, const T& p_b, const float p_t);

	template <typename T>
	T Clamp(const T p_value, const T p_min, const T p_max);
}

#include "Utils.inl"