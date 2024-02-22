#pragma once

#include <DLLInclude.hpp>

#include <cmath>
#include <string>
#include <iostream>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Vector3.rfkh.h>

namespace Math RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Vector3 
	{
		// Attribute
	public:
		float x;
		float y;
		float z;

		// Method
	public:
		Vector3(const float p_x = 0, const float p_y = 0, const float p_z = 0);
		Vector3(const Vector3& p_copy);

		static const Vector3 Zero() { return  Vector3(0.f, 0.f, 0.f); };
		static const Vector3 One() { return  Vector3(1.f, 1.f, 1.f); };
		static const float DotProduct(const Vector3& p_a, const Vector3& p_b);
		static const float Magnitude(const Vector3& p_vector3);
		static const Vector3 CrossProduct(const Vector3& p_a, const Vector3& p_b);
		static const Vector3 Normalize(const Vector3& p_vector3);

		void Display() const;
		std::string ToString() const;

		Vector3 operator+(const Vector3& p_right) const;
		Vector3 operator-(const Vector3& p_right) const;
		Vector3 operator-() const;
		Vector3 operator*(const Vector3& p_right) const;
		Vector3 operator*(const float p_multiplier) const;
		Vector3 operator/(const Vector3& p_right) const;
		Vector3 operator/(const float p_divider) const;

		void operator+=(const Vector3& p_right);
		void operator-=(const Vector3& p_right);
		void operator*=(const Vector3& p_right);
		void operator*=(const float p_multiplier);
		void operator/=(const Vector3& p_right);
		void operator/=(const float p_divider);

		friend Vector3 operator*(const float p_left, const Vector3& p_right);
		friend bool operator==(const Vector3& p_left, const Vector3& p_right);
		friend bool operator!=(const Vector3& p_left, const Vector3& p_right);

		Math_Vector3_GENERATED
	};
}

#include "Vector3.inl"
File_Vector3_GENERATED