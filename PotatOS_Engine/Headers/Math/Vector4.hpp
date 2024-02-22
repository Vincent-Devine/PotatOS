#pragma once

#include <DLLInclude.hpp>
#include <cmath>
#include <string>
#include <iostream>

#include <Math/Vector3.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Vector4.rfkh.h>

namespace Math RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Vector4
	{
		// Attribute
	public:
		float x;
		float y;
		float z;
		float w;

		// Method
	public:
		Vector4(const float p_x = 0.f, const float p_y = 0.f, const float p_z = 0.f, const float p_w = 0.f);
		Vector4(const Vector3& p_vector3, const float p_w = 0.f);
		Vector4(const Vector4& p_copy);

		static const float DotProduct(const Vector4& p_a, const Vector4& p_b);
		static const float Magnitude(const Vector4& p_vector4);
		static const Vector4 Normalize(const Vector4& p_vector4);
		static const Vector4 Homogenize(const Vector4& p_vector4);

		Vector3 ToVector3() const;

		void Display() const;
		std::string ToString() const;

		Vector4 operator+(const Vector4& p_right) const;
		Vector4 operator-(const Vector4& p_right) const;
		Vector4 operator-() const;
		Vector4 operator*(const Vector4& p_right) const;
		Vector4 operator*(const float p_multiplier) const;
		Vector4 operator/(const Vector4& p_right) const;
		Vector4 operator/(const float p_divider) const;

		void operator+=(const Vector4& p_right);
		void operator-=(const Vector4& p_right);
		void operator*=(const Vector4& p_right);
		void operator*=(const float p_multiplier);
		void operator/=(const Vector4& p_right);
		void operator/=(const float p_divider);

		friend Vector4 operator*(const float p_left, const Vector4& p_right);
		friend bool operator==(const Vector4& p_left, const Vector4& p_right);
		friend bool operator!=(const Vector4& p_left, const Vector4& p_right);

		Math_Vector4_GENERATED
	};
}

#include "Vector4.inl"
File_Vector4_GENERATED 