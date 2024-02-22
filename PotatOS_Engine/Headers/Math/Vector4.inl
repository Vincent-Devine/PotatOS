#pragma once

#include <cmath>
#include <string>
#include <iostream>

namespace Math
{
	inline Vector4::Vector4(const float p_x, const float p_y, const float p_z, const float p_w)
		: x(p_x)
		, y(p_y)
		, z(p_z)
		, w(p_w)
	{}

	inline Vector4::Vector4(const Vector3& p_vector3, const float p_w)
		: x(p_vector3.x)
		, y(p_vector3.y)
		, z(p_vector3.z)
		, w(p_w)
	{}

	inline Vector4::Vector4(const Vector4& p_copy)
		: x(p_copy.x)
		, y(p_copy.y)
		, z(p_copy.z)
		, w(p_copy.w)
	{}

	inline const float Vector4::DotProduct(const Vector4& p_a, const Vector4& p_b)
	{
		return p_a.x * p_b.x + p_a.y * p_b.y + p_a.z * p_b.z + p_a.w * p_b.w;
	}

	inline const float Vector4::Magnitude(const Vector4& p_vector4)
	{
		return sqrt(p_vector4.x * p_vector4.x + p_vector4.y * p_vector4.y + p_vector4.z * p_vector4.z + p_vector4.w * p_vector4.w);
	}

	inline const Vector4 Vector4::Normalize(const Vector4& p_vector4)
	{
		float magnitude = Magnitude(p_vector4);
		Vector4 vectorNormalize = p_vector4;
		if (magnitude != 0.f)
		{
			vectorNormalize.x /= magnitude;
			vectorNormalize.y /= magnitude;
			vectorNormalize.z /= magnitude;
			vectorNormalize.w /= magnitude;
		}
		return vectorNormalize;
	}

	inline const Vector4 Vector4::Homogenize(const Vector4& p_vector4)
	{
		Vector4 vectorHomogenize = p_vector4;
		if (vectorHomogenize.w != 0.f)
		{
			vectorHomogenize.x /= vectorHomogenize.w;
			vectorHomogenize.y /= vectorHomogenize.w;
			vectorHomogenize.z /= vectorHomogenize.w;
			vectorHomogenize.w /= vectorHomogenize.w;
		}
		return vectorHomogenize;
	}

	inline Vector3 Vector4::ToVector3() const
	{
		return { x, y, z };
	}

	inline void Vector4::Display() const
	{
		std::cout << "[ " << x << ", " << y << ", " << z << ", " << w << " ]" << std::endl;
	}

	inline std::string Vector4::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + " ]";
	}

	inline Vector4 Vector4::operator+(const Vector4 & p_right) const { return Vector4(x + p_right.x, y + p_right.y, z + p_right.z, w + p_right.w); }

	inline Vector4 Vector4::operator-(const Vector4 & p_right) const { return Vector4(x - p_right.x, y - p_right.y, z - p_right.z, w - p_right.w); }

	inline Vector4 Vector4::operator-() const { return Vector4(-x, -y, -z, -w); }

	inline Vector4 Vector4::operator*(const Vector4& p_right) const { return Vector4(x * p_right.x, y * p_right.y, z * p_right.z, w * p_right.w); }
	
	inline Vector4 Vector4::operator*(const float p_multiplier) const { return Vector4(x * p_multiplier, y * p_multiplier, z * p_multiplier, w * p_multiplier); }

	inline Vector4 Vector4::operator/(const Vector4& p_right) const { return Vector4(x / p_right.x, y / p_right.y, z / p_right.z, w / p_right.w); }
	
	inline Vector4 Vector4::operator/(const float p_divider) const { return Vector4(x / p_divider, y / p_divider, z / p_divider, w / p_divider); }

	inline void Vector4::operator+=(const Vector4& p_right) { *this = *this + p_right; }

	inline void Vector4::operator-=(const Vector4& p_right) { *this = *this - p_right; }

	inline void Vector4::operator*=(const Vector4& p_right) { *this = *this * p_right; }

	inline void Vector4::operator*=(const float p_multiplier) { *this = *this * p_multiplier; }

	inline void Vector4::operator/=(const Vector4& p_right) { *this = *this / p_right; }

	inline void Vector4::operator/=(const float p_divider) { *this = *this / p_divider; }

	inline Vector4 operator*(const float p_left, const Vector4& p_right) { return p_right * p_left; }

	inline bool operator==(const Vector4& p_left, const Vector4& p_right)
	{
		if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
			p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f &&
			p_left.z <= p_right.z + 0.001f && p_left.z >= p_right.z - 0.001f &&
			p_left.w <= p_right.w + 0.001f && p_left.w >= p_right.w - 0.001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool operator!=(const Vector4& p_left, const Vector4& p_right) { return !(p_left == p_right); }
}