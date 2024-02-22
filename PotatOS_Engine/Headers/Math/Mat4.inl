#pragma once
#include <Math/Mat4.hpp>

#include <cmath>
#include <corecrt_math_defines.h>
#include <string>
#include <iostream>
#include <Math/Quaternion.hpp>
#include <DebugSystem/Log.hpp>

namespace Math
{
	inline Mat4::Mat4(const float p_value)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				data[i][j] = p_value;
			}
		}
	}

	inline Mat4::Mat4(const Mat4& p_other)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				data[i][j] = p_other.data[i][j];
			}
		}
	}

	inline Mat4::Mat4(const float p_f1,  const float p_f2,  const float p_f3,  const float p_f4,
					  const float p_f5,  const float p_f6,  const float p_f7,  const float p_f8,
					  const float p_f9,  const float p_f10, const float p_f11, const float p_f12,
					  const float p_f13, const float p_f14, const float p_f15, const float p_f16)
	{
		data[0][0] = p_f1;  data[0][1] = p_f2;  data[0][2] = p_f3;  data[0][3] = p_f4;
		data[1][0] = p_f5;  data[1][1] = p_f6;  data[1][2] = p_f7;  data[1][3] = p_f8;
		data[2][0] = p_f9;  data[2][1] = p_f10; data[2][2] = p_f11; data[2][3] = p_f12;
		data[3][0] = p_f13; data[3][1] = p_f14; data[3][2] = p_f15; data[3][3] = p_f16;
	}

	inline Mat4 Mat4::Identity()
	{
		Mat4 identity;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
				{
					identity.data[i][j] = 1;
				}
			}
		}
		return identity;
	}

	inline Mat4 Mat4::Transpose()
	{
		Mat4 transpose;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transpose.data[i][j] = data[j][i];
			}
		}
		return transpose;
	}

	inline Mat4 Mat4::GetInverse() const
	{
		Mat4 inverse;
		float determinant = Determinant();
		if (determinant == 0)
		{
			return Mat4::Identity();
		}
		Mat4 cofactorMatrix = CofactorMatrix();
		cofactorMatrix.Transpose();
		cofactorMatrix = cofactorMatrix * (1.f / determinant);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverse.data[i][j] = cofactorMatrix.data[i][j];
			}
		}
		return inverse;
	}

	inline float Mat4::Determinant() const
	{
		return data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]))
			- data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]))
			+ data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[1][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]))
			- data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[1][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
	}

	inline Mat4 Mat4::CofactorMatrix() const
	{
		Mat4 Cof;

		Cof.data[0][0] = data[1][1] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) - data[1][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
		Cof.data[0][1] = -(data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[1][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]));
		Cof.data[0][2] = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[1][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
		Cof.data[0][3] = -(data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[1][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));

		Cof.data[1][0] = -(data[0][1] * (data[2][2] * data[3][3] - data[3][2] * data[2][3]) - data[0][2] * (data[2][1] * data[3][3] - data[3][1] * data[2][3]) + data[0][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]));
		Cof.data[1][1] = data[0][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) - data[0][2] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[0][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);
		Cof.data[1][2] = -(data[0][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) - data[0][1] * (data[2][0] * data[3][3] - data[3][0] * data[2][3]) + data[0][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
		Cof.data[1][3] = data[0][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) - data[0][1] * (data[2][0] * data[3][2] - data[3][0] * data[2][2]) + data[0][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);
		Cof.data[2][0] = data[0][1] * (data[1][2] * data[3][3] - data[3][2] * data[1][3]) - data[0][2] * (data[1][1] * data[3][3] - data[3][1] * data[1][3]) + data[0][3] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]);
		Cof.data[2][1] = -(data[0][0] * (data[1][2] * data[3][3] - data[1][3] * data[3][2]) - data[0][2] * (data[1][0] * data[3][3] - data[3][0] * data[1][3]) + data[0][3] * (data[1][0] * data[3][2] - data[1][2] * data[3][0]));
		Cof.data[2][2] = data[0][0] * (data[1][1] * data[3][3] - data[1][3] * data[3][1]) - data[0][1] * (data[1][0] * data[3][3] - data[3][0] * data[1][3]) + data[0][3] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]);
		Cof.data[2][3] = -(data[0][0] * (data[1][1] * data[3][2] - data[1][2] * data[3][1]) - data[0][1] * (data[1][0] * data[3][2] - data[3][0] * data[1][2]) + data[0][2] * (data[1][0] * data[3][1] - data[1][1] * data[3][0]));

		Cof.data[3][0] = -(data[0][1] * (data[1][2] * data[2][3] - data[2][2] * data[1][3]) - data[0][2] * (data[1][1] * data[2][3] - data[2][1] * data[1][3]) + data[0][3] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]));
		Cof.data[3][1] = data[0][0] * (data[1][2] * data[2][3] - data[1][3] * data[2][2]) - data[0][2] * (data[1][0] * data[2][3] - data[2][0] * data[1][3]) + data[0][3] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]);
		Cof.data[3][2] = -(data[0][0] * (data[1][1] * data[2][3] - data[1][3] * data[2][1]) - data[0][1] * (data[1][0] * data[2][3] - data[2][0] * data[1][3]) + data[0][3] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]));
		Cof.data[3][3] = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) - data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

		return Cof;
	}

	inline Mat4 Mat4::CreateTranslationMatrix(const Vector3& p_translation)
	{
		Mat4 translationMatrix = Mat4::Identity();
		if (p_translation.x != 0.f)
		{
			translationMatrix.data[0][3] = p_translation.x;
		}
		if (p_translation.y != 0.f)
		{
			translationMatrix.data[1][3] = p_translation.y;
		}
		if (p_translation.z != 0.f)
		{
			translationMatrix.data[2][3] = p_translation.z;
		}
		return translationMatrix;
	}

	inline Mat4 Mat4::CreateScaleMatrix(const Vector3& p_scale)
	{
		Mat4 scaleMatrix;
		scaleMatrix.data[0][0] = p_scale.x;
		scaleMatrix.data[1][1] = p_scale.y;
		scaleMatrix.data[2][2] = p_scale.z;
		scaleMatrix.data[3][3] = 1.f;
		return scaleMatrix;
	}

	inline Mat4 Mat4::CreateXRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // To radians
		Mat4 xRotationMatrix = Mat4::Identity();
		xRotationMatrix.data[1][1] = cosf(p_angleDegree);
		xRotationMatrix.data[1][2] = -sinf(p_angleDegree);
		xRotationMatrix.data[2][1] = sinf(p_angleDegree);
		xRotationMatrix.data[2][2] = cosf(p_angleDegree);
		return xRotationMatrix;
	}

	inline Mat4 Mat4::CreateYRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // To radians
		Mat4 yRotationMatrix = Mat4::Identity();
		yRotationMatrix.data[0][0] = cosf(p_angleDegree);
		yRotationMatrix.data[0][2] = sinf(p_angleDegree);
		yRotationMatrix.data[2][0] = -sinf(p_angleDegree);
		yRotationMatrix.data[2][2] = cosf(p_angleDegree);
		return yRotationMatrix;
	}

	inline Mat4 Mat4::CreateZRotationMatrix(float p_angleDegree)
	{
		p_angleDegree *= (float)M_PI / 180.f; // To radians
		Mat4 zRotationMatrix = Mat4::Identity();
		zRotationMatrix.data[0][0] = cosf(p_angleDegree);
		zRotationMatrix.data[0][1] = -sinf(p_angleDegree);
		zRotationMatrix.data[1][0] = sinf(p_angleDegree);
		zRotationMatrix.data[1][1] = cosf(p_angleDegree);
		return zRotationMatrix;
	}

	inline Mat4 Mat4::CreateRotationMatrix(const Vector3& p_angleDegree)
	{
		return CreateYRotationMatrix(p_angleDegree.y) * CreateXRotationMatrix(p_angleDegree.x) * CreateZRotationMatrix(p_angleDegree.z);
	}

	inline Mat4 Mat4::CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Vector3& p_rotationDegree)
	{
		return CreateTranslationMatrix(p_translation) * CreateRotationMatrix(p_rotationDegree) * CreateScaleMatrix(p_scale);
	}

	inline Mat4 Mat4::CreateTransformationMatrix(const Vector3& p_translation, const Vector3& p_scale, const Quaternion& p_rotation)
	{
		return CreateTranslationMatrix(p_translation) * Quaternion::QuatToMatrix(p_rotation) * CreateScaleMatrix(p_scale);
	}

	inline Mat4 Mat4::GetPerspectiveProjection(const float p_aspect, const float p_FOV, const float p_near, const float p_far)
	{
		const float tanHalfFOV = tanf(p_FOV / 2.f);

		Math::Mat4 res;
		res.data[0][0] = 1.f / (p_aspect * tanHalfFOV);
		res.data[1][1] = 1.f / (tanHalfFOV);
		res.data[2][2] = -(p_far + p_near) / (p_far - p_near);
		res.data[3][2] = -1.f;
		res.data[2][3] = -(2.f * p_far * p_near) / (p_far - p_near);

		return res;
	}

	inline Mat4 Mat4::GetOrthographicProjection(const float p_right, const float p_left, const float p_top, const float p_bottom, const float p_near, const float p_far)
	{
		Mat4 res = Identity();
		res.data[0][0] = 2.f / (p_right - p_left);
		res.data[1][1] = 2.f / (p_top - p_bottom);
		res.data[2][2] = -2.f / (p_far - p_near);
		res.data[0][3] = - (p_left + p_right) / (p_right - p_left);
		res.data[1][3] = - (p_top + p_bottom) / (p_top - p_bottom);
		res.data[2][3] = - (p_far + p_near) / (p_far - p_near);
		return res;
	}

	inline Mat4 Mat4::GetOrthographicProjectionWithoutNearFar(const float p_right, const float p_left, const float p_top, const float p_bottom)
	{
		Mat4 res = Identity();
		res.data[0][0] = 2.f / (p_right - p_left);
		res.data[1][1] = 2.f / (p_top - p_bottom);
		res.data[2][2] = -1.f;
		res.data[0][3] = -(p_left + p_right) / (p_right - p_left);
		res.data[1][3] = -(p_top + p_bottom) / (p_top - p_bottom);
		return res;
	}

	inline Mat4 Mat4::LookAt(const Vector3& p_eye, const Vector3& p_center, const Vector3& p_up)
	{
		Vector3 f = Vector3::Normalize(p_center - p_eye);
		Vector3 s = Vector3::Normalize(Vector3::CrossProduct(f, p_up));
		Vector3 u = Vector3::CrossProduct(s, f);

		Mat4 res = Identity();

		res.data[0][0] = s.x;
		res.data[1][0] = s.y;
		res.data[2][0] = s.z;
		res.data[0][1] = u.x;
		res.data[1][1] = u.y;
		res.data[2][1] = u.z;
		res.data[0][2] = -f.x;
		res.data[1][2] = -f.y;
		res.data[2][2] = -f.z;
		res.data[3][0] = -Vector3::DotProduct(s, p_eye);
		res.data[3][1] = -Vector3::DotProduct(u, p_eye);
		res.data[3][2] =  Vector3::DotProduct(f, p_eye);

		res = res.Transpose();
		return res;
	}

	inline void Mat4::Display() const
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			std::cout << "| ";
			for (unsigned int j = 0; j < 4; j++)
			{
				std::cout << data[i][j] << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << std::endl;
	}

	inline const std::string Mat4::ToString() const
	{
		std::string result;
		for (unsigned int i = 0; i < 4; i++)
		{
			result += "| ";
			for (unsigned int j = 0; j < 4; j++)
			{
				result += std::to_string(data[i][j]) + " ";
			}
			result += "|\n";
		}
		return result;
	}

	inline Math::Vector3 Scale(Math::Vector3& p_vector, float p_desiredLenght)
	{
		return p_vector * p_desiredLenght / Math::Vector3::Magnitude(p_vector);
	}

	inline void Mat4::Decompose(const Mat4& p_transform, Math::Vector3& p_translation, Math::Vector3& p_rotation, Math::Vector3& p_scale)
	{
		Mat4 localMatrix(p_transform);
		if (localMatrix.data[3][3] <= 0.001f && localMatrix.data[3][3] >= -0.001f)
		{
			Log::Print("Decompose error", LOG_LEVEL_TYPE::Warning);
			return;
		}

		// Translation
		p_translation = Math::Vector3(localMatrix.data[3][0], localMatrix.data[3][1], localMatrix.data[3][2]);

		// Scale
		Math::Vector3 row[3], pdum3;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				switch(j)
				{
				case 0:
					row[i].x = localMatrix.data[i][j];
					break;
				case 1:
					row[i].y = localMatrix.data[i][j];
					break;
				case 2:
					row[i].z = localMatrix.data[i][j];
					break;
				default:
					break;
				}
			}
		}

		p_scale.x = Math::Vector3::Magnitude(row[0]);
		row[0] = Scale(row[0], 1);
		p_scale.y = Math::Vector3::Magnitude(row[1]);
		row[1] = Scale(row[1], 1);
		p_scale.z = Math::Vector3::Magnitude(row[2]);
		row[2] = Scale(row[2], 1);

		pdum3 = Math::Vector3::CrossProduct(row[1], row[2]);
		if (Math::Vector3::DotProduct(row[0], pdum3) < 0)
		{
			p_scale.x *= -1.f;
			row[0] *= -1.f;
			p_scale.y *= -1.f;
			row[1] *= -1.f;
			p_scale.z *= -1.f;
			row[2] *= -1.f;
		}

		// Rotation
		p_rotation.y = asin(-row[0].z);
		if (cos(p_rotation.y) != 0)
		{
			p_rotation.x = atan2(row[1].z, row[2].z);
			p_rotation.z = atan2(row[0].y, row[0].x);
		}
		else
		{
			p_rotation.x = atan2(-row[2].x, row[1].y);
			p_rotation.z = 0.f;
		}
	}

	inline Mat4 Mat4::operator+(const Mat4& p_right) const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] + p_right.data[i][j];
			}
		}
		return result;
	}


	inline Mat4 Mat4::operator-(const Mat4& p_right) const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] - p_right.data[i][j];
			}
		}
		return result;
	}

	inline Mat4 Mat4::operator-() const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = -data[i][j];
			}
		}
		return result;
	}

	inline Mat4 Mat4::operator*(const Mat4& p_other) const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				for (unsigned int k = 0; k < 4; k++)
				{
					result.data[i][j] += data[i][k] * p_other.data[k][j];
				}
			}
		}
		return result;
	}

	inline Mat4 Mat4::operator*(const float p_right) const
	{
		Mat4 result;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				result.data[i][j] = data[i][j] * p_right;
			}
		}
		return result;
	}

	inline Vector4 Mat4::operator*(const Vector4& p_right) const
	{
		Vector4 result;
		result.x = data[0][0] * p_right.x + data[0][1] * p_right.y + data[0][2] * p_right.z + data[0][3] * p_right.w;
		result.y = data[1][0] * p_right.x + data[1][1] * p_right.y + data[1][2] * p_right.z + data[1][3] * p_right.w;
		result.z = data[2][0] * p_right.x + data[2][1] * p_right.y + data[2][2] * p_right.z + data[2][3] * p_right.w;
		result.w = data[3][0] * p_right.x + data[3][1] * p_right.y + data[3][2] * p_right.z + data[3][3] * p_right.w;
		return result;
	}

	inline void Mat4::operator+=(const Mat4& p_right) { *this = *this + p_right; }

	inline void Mat4::operator-=(const Mat4& p_right) { *this = *this - p_right; }

	inline void Mat4::operator*=(const Mat4& p_other) { *this = *this * p_other; }

	inline void Mat4::operator*=(const float p_right) { *this = *this * p_right; }

	inline Mat4 operator*(const float p_left, const Mat4& p_matrix) { return p_matrix * p_left; }

	inline Vector4 operator*(const Vector4& p_left, const Mat4& p_matrix)
	{
		Vector4 result;
		result.x = p_matrix.data[0][0] * p_left.x + p_matrix.data[1][0] * p_left.y + p_matrix.data[2][0] * p_left.z + p_matrix.data[3][0] * p_left.w;
		result.y = p_matrix.data[0][1] * p_left.x + p_matrix.data[1][1] * p_left.y + p_matrix.data[2][1] * p_left.z + p_matrix.data[3][1] * p_left.w;
		result.z = p_matrix.data[0][2] * p_left.x + p_matrix.data[1][2] * p_left.y + p_matrix.data[2][2] * p_left.z + p_matrix.data[3][2] * p_left.w;
		result.w = p_matrix.data[0][3] * p_left.x + p_matrix.data[1][3] * p_left.y + p_matrix.data[2][3] * p_left.z + p_matrix.data[3][3] * p_left.w;
		return result;
	}

	inline bool operator==(const Mat4& p_left, const Mat4& p_right)
	{
		float margin = 0.000001f;
		bool result = true;

		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4; ++j)
			{
				if (p_left.data[i][j] > p_right.data[i][j] + margin || p_left.data[i][j] < p_right.data[i][j] - margin)
				{
					result = false;
					break;
				}
			}
			if (!result)
			{
				break;
			}
		}
		return result;
	}
}