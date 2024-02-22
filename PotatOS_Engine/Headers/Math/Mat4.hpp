#pragma once

#include <cmath>
#include <corecrt_math_defines.h>
#include <string>
#include <iostream>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Utils.hpp>

namespace Math
{
	class Quaternion;
	class Mat4 //line then column
	{
	// Attribute
	public:
		float data[4][4];

	// Method
	public:
		Mat4(const float p_value = 0);
		Mat4(const Mat4& p_other);
		Mat4(const float p_f1,  const float p_f2,  const float p_f3,  const float p_f4,
			 const float p_f5,  const float p_f6,  const float p_f7,  const float p_f8,
			 const float p_f9,  const float p_f10, const float p_f11, const float p_f12,
			 const float p_f13, const float p_f14, const float p_f15, const float p_f16);

		static Mat4 Identity();

		Mat4 Transpose();
		Mat4 GetInverse() const;
		float Determinant() const;
		Mat4 CofactorMatrix() const;

		static Mat4 CreateTranslationMatrix(const Vector3& p_translation);
		static Mat4 CreateScaleMatrix(const Vector3& p_scale);
		static Mat4 CreateXRotationMatrix(float p_angleDegree);
		static Mat4 CreateYRotationMatrix(float p_angleDegree);
		static Mat4 CreateZRotationMatrix(float p_angleDegree);

		static Mat4 CreateRotationMatrix(const Vector3& p_angleDegree);
		static Mat4 CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Vector3& p_rotationDegree);
		static Mat4 CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Quaternion& p_rotation);

		static Mat4 GetPerspectiveProjection(const float p_aspect = 1920.f / 1080.f, const float p_FOV = Math::DEG2RAD * 90.f, const float p_near = 0.1f, const float p_far = 1000.f);
		static Mat4 GetOrthographicProjection(const float p_right = 1920.f/2.f, const float p_left = - 1920.f / 2.f, const float p_top = 1080.f / 2.f, const float p_bottom = - 1080.f / 2.f, const float p_near = -500.f, const float p_far = 500.f);
		static Mat4 GetOrthographicProjectionWithoutNearFar(const float p_right = 1920.f / 2.f, const float p_left = -1920.f / 2.f, const float p_top = 1080.f / 2.f, const float p_bottom = -1080.f / 2.f);

		static Mat4 LookAt(const Vector3& p_eye, const Vector3& p_center, const Vector3& p_up);

		void Display() const;
		const std::string ToString() const;

		void Decompose(const Mat4& p_transform, Math::Vector3& p_translation, Math::Vector3& p_rotation, Math::Vector3& p_scale);

		Mat4 operator+(const Mat4& p_right) const;
		Mat4 operator-(const Mat4& p_right) const;
		Mat4 operator-() const;
		Mat4 operator*(const Mat4& p_other) const;
		Mat4 operator*(const float p_right) const;
		Vector4 operator*(const Vector4& p_right) const;

		void operator+=(const Mat4& p_right);
		void operator-=(const Mat4& p_right);
		void operator*=(const Mat4& p_other);
		void operator*=(const float p_right);

		friend Mat4 operator*(const float p_left, const Mat4& p_matrix);
		friend Vector4 operator*(const Vector4& p_left, const Mat4& p_matrix);
		friend bool operator==(const Mat4& p_left, const Mat4& p_right);
	};
}