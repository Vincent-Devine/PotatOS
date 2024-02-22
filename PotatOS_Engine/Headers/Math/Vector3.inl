#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace Math
{
	inline Vector3::Vector3(const float p_x, const float p_y, const float p_z)
		: x(p_x)
		, y(p_y)
		, z(p_z)
	{}

	inline Vector3::Vector3(const Vector3& p_copy)
		: x(p_copy.x)
		, y(p_copy.y)
		, z(p_copy.z)
	{}

	inline const float Vector3::DotProduct(const Vector3& p_a, const Vector3& p_b)
	{
		return p_a.x * p_b.x + p_a.y * p_b.y + p_a.z * p_b.z;
	}

	inline const float Vector3::Magnitude(const Vector3& p_vector3)
	{
		return sqrt(p_vector3.x * p_vector3.x + p_vector3.y * p_vector3.y + p_vector3.z * p_vector3.z);
	}

	inline const Vector3 Vector3::CrossProduct(const Vector3& p_a, const Vector3& p_b)
	{
		return
		{
			p_a.y * p_b.z - p_a.z * p_b.y,
			p_a.z * p_b.x - p_a.x * p_b.z,
			p_a.x * p_b.y - p_a.y * p_b.x
		};
	}

	inline const Vector3 Vector3::Normalize(const Vector3& p_vector3)
	{
		float magnitude = Magnitude(p_vector3);
		Vector3 vectorNormalize = p_vector3;
		if(magnitude != 0.f)
		{
			vectorNormalize.x /= magnitude;
			vectorNormalize.y /= magnitude;
			vectorNormalize.z /= magnitude;
		}
		return vectorNormalize;
	}

	inline void Vector3::Display() const
	{
		std::cout << "[ " << x << ", " << y << ", " << z << " ]" << std::endl;
	}

	inline std::string Vector3::ToString() const
	{
		return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
	}

	inline Vector3 Vector3::operator+(const Vector3& p_right) const { return Vector3(x + p_right.x, y + p_right.y, z + p_right.z); }

	inline Vector3 Vector3::operator-(const Vector3& p_right) const { return Vector3(x - p_right.x, y - p_right.y, z - p_right.z); }

	inline Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

	inline Vector3 Vector3::operator*(const Vector3& p_right) const { return Vector3(x * p_right.x, y * p_right.y, z * p_right.z); }

	inline Vector3 Vector3::operator*(const float p_multiplier) const { return Vector3(x * p_multiplier, y * p_multiplier, z * p_multiplier); }

	inline Vector3 Vector3::operator/(const Vector3& p_right) const { return Vector3(x / p_right.x, y / p_right.y, z / p_right.z); }

	inline Vector3 Vector3::operator/(const float p_divider) const { return Vector3(x / p_divider, y / p_divider, z / p_divider); }

	inline void Vector3::operator+=(const Vector3& p_right) { *this = *this + p_right; }

	inline void Vector3::operator-=(const Vector3& p_right) { *this = *this - p_right; }

	inline void Vector3::operator*=(const Vector3& p_right) { *this = *this * p_right; }

	inline void Vector3::operator*=(const float p_multiplier) { *this = *this * p_multiplier; }

	inline void Vector3::operator/=(const Vector3& p_right) { *this = *this / p_right; }

	inline void Vector3::operator/=(const float p_divider) { *this = *this / p_divider; }

	inline Vector3 operator*(const float p_left, const Vector3& p_right) { return p_right * p_left; }

	inline bool operator==(const Vector3& p_left, const Vector3& p_right)
	{
		if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
			p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f &&
			p_left.z <= p_right.z + 0.001f && p_left.z >= p_right.z - 0.001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool operator!=(const Vector3& p_left, const Vector3& p_right) { return !(p_left == p_right); }
}