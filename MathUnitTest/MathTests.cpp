#include "pch.h"
#include <cmath>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Mat4.inl>
#include <Math/Quaternion.inl>

using namespace Math;

#pragma region Vector2
	TEST(Vector2Test, Equal)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(vec2Test1);

		EXPECT_EQ(vec2Test1, vec2Test2);

		EXPECT_EQ(vec2Test2, vec2Test1);

		Vector2 vec2Test3 = vec2Test2;

		EXPECT_EQ(vec2Test3, vec2Test2);

		EXPECT_EQ(vec2Test2 == vec2Test3, true);

		EXPECT_EQ(vec2Test1 != vec2Test3, false);
	}

	TEST(Vector2Test, Sum)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(2.f, 3.f);

		EXPECT_EQ(vec2Test1 + vec2Test2, Vector2(3.f, 5.f));
		EXPECT_EQ(vec2Test1 + vec2Test2, vec2Test2 + vec2Test1);

		Vector2 vec2Test3 = vec2Test1;
		vec2Test3 += vec2Test2;

		EXPECT_EQ(vec2Test3, Vector2(3.f, 5.f));
	}

	TEST(Vector2Test, Difference)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(2.f, 3.f);

		EXPECT_EQ(-vec2Test1, Vector2(-1.f, -2.f));

		EXPECT_EQ(vec2Test1 - vec2Test2, Vector2(-1.f, -1.f));

		EXPECT_EQ(vec2Test2 - vec2Test1, Vector2(1.f, 1.f));

		Vector2 vec2Test3 = vec2Test1;
		vec2Test3 -= vec2Test2;

		EXPECT_EQ(vec2Test3, Vector2(-1.f, -1.f));
	}

	TEST(Vector2Test, Product)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(2.f, 3.f);

		EXPECT_EQ(vec2Test1 * vec2Test2, Vector2(2.f, 6.f));

		EXPECT_EQ(vec2Test2 * vec2Test1, Vector2(2.f, 6.f));

		EXPECT_EQ(2.f * vec2Test1, Vector2(2.f, 4.f));
		EXPECT_EQ(vec2Test1 * 2.f, Vector2(2.f, 4.f));

		Vector2 vec2Test3 = vec2Test1;
		vec2Test3 *= vec2Test2;

		EXPECT_EQ(vec2Test3, Vector2(2.f, 6.f));

		Vector2 vec2Test4 = vec2Test1;
		vec2Test4 *= 2.f;

		EXPECT_EQ(vec2Test4, Vector2(2.f, 4.f));
	}

	TEST(Vector2Test, Quotient)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(2.f, 3.f);

		EXPECT_EQ(vec2Test1 / vec2Test2, Vector2(0.5f, 2.f / 3.f));

		EXPECT_EQ(vec2Test2 / vec2Test1, Vector2(2.f, 1.5f));

		EXPECT_EQ(vec2Test1 / 2.f, Vector2(0.5f, 1.f));

		Vector2 vec2Test3 = vec2Test1;
		vec2Test3 /= vec2Test2;

		EXPECT_EQ(vec2Test3, Vector2(0.5f, 2.f / 3.f));

		Vector2 vec2Test4 = vec2Test1;
		vec2Test4 /= 2.f;

		EXPECT_EQ(vec2Test4, Vector2(0.5f, 1.f));
	}

	TEST(Vector2Test, SpecialOperator)
	{
		Vector2 vec2Test1 = Vector2(1.f, 2.f);

		Vector2 vec2Test2 = Vector2(2.f, 3.f);

		EXPECT_EQ(Vector2::DotProduct(vec2Test1, vec2Test2), 8.f);

		EXPECT_EQ(Vector2::Magnitude(vec2Test1), sqrtf(5.f));

		EXPECT_EQ(Vector2::Normalize(vec2Test1), Vector2(1.f, 2.f) / sqrtf(5.f));
	}
#pragma endregion Vector2

#pragma region Vector3
	TEST(Vector3Test, Equal)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(vec3Test1);

		EXPECT_EQ(vec3Test1, vec3Test2);

		EXPECT_EQ(vec3Test2, vec3Test1);

		Vector3 vec3Test3 = vec3Test2;

		EXPECT_EQ(vec3Test3, vec3Test2);

		EXPECT_EQ(vec3Test2 == vec3Test3, true);

		EXPECT_EQ(vec3Test1 != vec3Test3, false);
	}

	TEST(Vector3Test, Sum)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(2.f, 3.f, 4.f);

		EXPECT_EQ(vec3Test1 + vec3Test2, Vector3(3.f, 5.f, 7.f));
		EXPECT_EQ(vec3Test1 + vec3Test2, vec3Test2 + vec3Test1);

		Vector3 vec3Test3 = vec3Test1;
		vec3Test3 += vec3Test2;

		EXPECT_EQ(vec3Test3, Vector3(3.f, 5.f, 7.f));
	}

	TEST(Vector3Test, Difference)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(2.f, 3.f, 4.f);

		EXPECT_EQ(-vec3Test1, Vector3(-1.f, -2.f, -3.f));

		EXPECT_EQ(vec3Test1 - vec3Test2, Vector3(-1.f, -1.f, -1.f));

		EXPECT_EQ(vec3Test2 - vec3Test1, Vector3(1.f, 1.f, 1.f));

		Vector3 vec3Test3 = vec3Test1;
		vec3Test3 -= vec3Test2;

		EXPECT_EQ(vec3Test3, Vector3(-1.f, -1.f, -1.f));
	}

	TEST(Vector3Test, Product)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(2.f, 3.f, 4.f);

		EXPECT_EQ(vec3Test1 * vec3Test2, Vector3(2.f, 6.f, 12.f));

		EXPECT_EQ(vec3Test2 * vec3Test1, Vector3(2.f, 6.f, 12.f));

		EXPECT_EQ(2.f * vec3Test1, Vector3(2.f, 4.f, 6.f));
		EXPECT_EQ(vec3Test1 * 2.f, Vector3(2.f, 4.f, 6.f));

		Vector3 vec3Test3 = vec3Test1;
		vec3Test3 *= vec3Test2;

		EXPECT_EQ(vec3Test3, Vector3(2.f, 6.f, 12.f));

		Vector3 vec3Test4 = vec3Test1;
		vec3Test4 *= 2.f;

		EXPECT_EQ(vec3Test4, Vector3(2.f, 4.f, 6.f));
	}

	TEST(Vector3Test, Quotient)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(2.f, 3.f, 4.f);

		EXPECT_EQ(vec3Test1 / vec3Test2, Vector3(0.5f, 2.f / 3.f, 0.75f));

		EXPECT_EQ(vec3Test2 / vec3Test1, Vector3(2.f, 1.5f, 4.f / 3.f));

		EXPECT_EQ(vec3Test1 / 2.f, Vector3(0.5f, 1.f, 1.5f));

		Vector3 vec3Test3 = vec3Test1;
		vec3Test3 /= vec3Test2;

		EXPECT_EQ(vec3Test3, Vector3(0.5f, 2.f / 3.f, 0.75f));

		Vector3 vec3Test4 = vec3Test1;
		vec3Test4 /= 2.f;

		EXPECT_EQ(vec3Test4, Vector3(0.5f, 1.f, 1.5f));
	}

	TEST(Vector3Test, SpecialOperator)
	{
		Vector3 vec3Test1 = Vector3(1.f, 2.f, 3.f);

		Vector3 vec3Test2 = Vector3(2.f, 3.f, 4.f);

		EXPECT_EQ(Vector3::DotProduct(vec3Test1, vec3Test2), 20.f);

		EXPECT_EQ(Vector3::CrossProduct(vec3Test1, vec3Test2), Vector3(-1.f, 2.f, -1.f));

		EXPECT_EQ(Vector3::Magnitude(vec3Test1), sqrtf(14.f));

		EXPECT_EQ(Vector3::Normalize(vec3Test1), Vector3(1.f, 2.f, 3.f) / sqrtf(14.f));
	}
#pragma endregion Vector3

#pragma region Vector4
	TEST(Vector4Test, Equal)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(vec4Test1);

		EXPECT_EQ(vec4Test1, vec4Test2);

		EXPECT_EQ(vec4Test2, vec4Test1);

		Vector4 vec4Test3 = vec4Test2;

		EXPECT_EQ(vec4Test3, vec4Test2);

		EXPECT_EQ(vec4Test2 == vec4Test3, true);

		EXPECT_EQ(vec4Test1 != vec4Test3, false);
	}

	TEST(Vector4Test, Sum)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(2.f, 3.f, 4.f, 5.f);

		EXPECT_EQ(vec4Test1 + vec4Test2, Vector4(3.f, 5.f, 7.f, 9.f));
		EXPECT_EQ(vec4Test1 + vec4Test2, vec4Test2 + vec4Test1);

		Vector4 vec4Test3 = vec4Test1;
		vec4Test3 += vec4Test2;

		EXPECT_EQ(vec4Test3, Vector4(3.f, 5.f, 7.f, 9.f));
	}

	TEST(Vector4Test, Difference)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(2.f, 3.f, 4.f, 5.f);

		EXPECT_EQ(-vec4Test1, Vector4(-1.f, -2.f, -3.f, -4.f));

		EXPECT_EQ(vec4Test1 - vec4Test2, Vector4(-1.f, -1.f, -1.f, -1.f));

		EXPECT_EQ(vec4Test2 - vec4Test1, Vector4(1.f, 1.f, 1.f, 1.f));

		Vector4 vec4Test3 = vec4Test1;
		vec4Test3 -= vec4Test2;

		EXPECT_EQ(vec4Test3, Vector4(-1.f, -1.f, -1.f, -1.f));
	}

	TEST(Vector4Test, Product)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(2.f, 3.f, 4.f, 5.f);

		EXPECT_EQ(vec4Test1 * vec4Test2, Vector4(2.f, 6.f, 12.f, 20.f));

		EXPECT_EQ(vec4Test2 * vec4Test1, Vector4(2.f, 6.f, 12.f, 20.f));

		EXPECT_EQ(2.f * vec4Test1, Vector4(2.f, 4.f, 6.f, 8.f));
		EXPECT_EQ(vec4Test1 * 2.f, Vector4(2.f, 4.f, 6.f, 8.f));

		Vector4 vec4Test3 = vec4Test1;
		vec4Test3 *= vec4Test2;

		EXPECT_EQ(vec4Test3, Vector4(2.f, 6.f, 12.f, 20.f));

		Vector4 vec4Test4 = vec4Test1;
		vec4Test4 *= 2.f;

		EXPECT_EQ(vec4Test4, Vector4(2.f, 4.f, 6.f, 8.f));
	}

	TEST(Vector4Test, Quotient)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(2.f, 3.f, 4.f, 5.f);

		EXPECT_EQ(vec4Test1 / vec4Test2, Vector4(0.5f, 2.f / 3.f, 0.75f, 0.8f));

		EXPECT_EQ(vec4Test2 / vec4Test1, Vector4(2.f, 1.5f, 4.f / 3.f, 1.25f));

		EXPECT_EQ(vec4Test1 / 2.f, Vector4(0.5f, 1.f, 1.5f, 2.f));

		Vector4 vec4Test3 = vec4Test1;
		vec4Test3 /= vec4Test2;

		EXPECT_EQ(vec4Test3, Vector4(0.5f, 2.f / 3.f, 0.75f, 0.8f));

		Vector4 vec4Test4 = vec4Test1;
		vec4Test4 /= 2.f;

		EXPECT_EQ(vec4Test4, Vector4(0.5f, 1.f, 1.5f, 2.f));
	}

	TEST(Vector4Test, SpecialOperator)
	{
		Vector4 vec4Test1 = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 vec4Test2 = Vector4(2.f, 3.f, 4.f, 5.f);

		EXPECT_EQ(Vector4::DotProduct(vec4Test1, vec4Test2), 40.f);

		EXPECT_EQ(Vector4::Magnitude(vec4Test1), sqrtf(30.f));

		EXPECT_EQ(Vector4::Normalize(vec4Test1), Vector4(1.f, 2.f, 3.f, 4.f) / sqrtf(30.f));

		EXPECT_EQ(Vector4::Homogenize(vec4Test1), Vector4(0.25f, 0.5f, 0.75f, 1.f));

		EXPECT_EQ(vec4Test1.ToVector3(), Vector3(1.f, 2.f, 3.f));
	}
#pragma endregion Vector4

#pragma region Matrix
	TEST(MatrixTests, Equal)
	{
		Mat4 matTest1 = Mat4(
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f
		);

		Mat4 matTest2 = Mat4(matTest1);

		EXPECT_EQ(matTest1, matTest2);

		EXPECT_EQ(matTest2, matTest1);

		Mat4 matTest3 = matTest2;

		EXPECT_EQ(matTest3, matTest2);

		EXPECT_EQ(matTest2 == matTest3, true);
	}

	TEST(MatrixTests, Sum)
	{
		Mat4 matTest1 = Mat4(
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f
		);

		Mat4 matTest2 = Mat4(
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f
		);

		Mat4 matRes = Mat4(
			3.f, 5.f, 7.f, 9.f,
			3.f, 5.f, 7.f, 9.f,
			3.f, 5.f, 7.f, 9.f,
			3.f, 5.f, 7.f, 9.f
		);

		EXPECT_EQ(matTest1 + matTest2, matRes);
		EXPECT_EQ(matTest1 + matTest2, matTest2 + matTest1);

		Mat4 matTest3 = matTest1;
		matTest3 += matTest2;

		EXPECT_EQ(matTest3, matRes);
	}

	TEST(MatrixTests, Difference)
	{
		Mat4 matTest1 = Mat4(
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f
		);

		Mat4 matTest2 = Mat4(
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f
		);

		Mat4 matRes1 = Mat4(
			-1.f, -2.f, -3.f, -4.f,
			-1.f, -2.f, -3.f, -4.f,
			-1.f, -2.f, -3.f, -4.f,
			-1.f, -2.f, -3.f, -4.f
		);

		EXPECT_EQ(-matTest1, matRes1);

		Mat4 matRes2 = Mat4(
			-1.f, -1.f, -1.f, -1.f,
			-1.f, -1.f, -1.f, -1.f,
			-1.f, -1.f, -1.f, -1.f,
			-1.f, -1.f, -1.f, -1.f
		);

		EXPECT_EQ(matTest1 - matTest2, matRes2);

		Mat4 matRes3 = Mat4(
			1.f, 1.f, 1.f, 1.f,
			1.f, 1.f, 1.f, 1.f,
			1.f, 1.f, 1.f, 1.f,
			1.f, 1.f, 1.f, 1.f
		);

		EXPECT_EQ(matTest2 - matTest1, matRes3);

		Mat4 matTest3 = matTest1;
		matTest3 -= matTest2;

		EXPECT_EQ(matTest3, matRes2);
	}

	TEST(MatrixTests, Product)
	{
		Mat4 matTest1 = Mat4(
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f,
			1.f, 2.f, 3.f, 4.f
		);

		Mat4 matTest2 = Mat4(
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f,
			2.f, 3.f, 4.f, 5.f
		);

		Mat4 matRes1 = Mat4(
			20.f, 30.f, 40.f, 50.f,
			20.f, 30.f, 40.f, 50.f,
			20.f, 30.f, 40.f, 50.f,
			20.f, 30.f, 40.f, 50.f
		);

		EXPECT_EQ(matTest1 * matTest2, matRes1);

		Mat4 matRes2 = Mat4(
			14.f, 28.f, 42.f, 56.f,
			14.f, 28.f, 42.f, 56.f,
			14.f, 28.f, 42.f, 56.f,
			14.f, 28.f, 42.f, 56.f
		);

		EXPECT_EQ(matTest2 * matTest1, matRes2);

		Mat4 matRes3 = Mat4(
			2.f, 4.f, 6.f, 8.f,
			2.f, 4.f, 6.f, 8.f,
			2.f, 4.f, 6.f, 8.f,
			2.f, 4.f, 6.f, 8.f
		);

		EXPECT_EQ(2.f * matTest1, matRes3);
		EXPECT_EQ(matTest1 * 2.f, matRes3);

		Mat4 matTest3 = matTest1;
		matTest3 *= matTest2;

		EXPECT_EQ(matTest3, matRes1);

		Mat4 matTest4 = matTest1;
		matTest4 *= 2.f;

		EXPECT_EQ(matTest4, matRes3);

		Vector4 VecTest = Vector4(1.f, 2.f, 3.f, 4.f);

		Vector4 VecRes1 = Vector4(30.f, 30.f, 30.f, 30.f);

		EXPECT_EQ(matTest1 * VecTest, VecRes1);

		Vector4 VecRes2 = Vector4(10.f, 20.f, 30.f, 40.f);

		EXPECT_EQ(VecTest * matTest1, VecRes2);
	}

	TEST(MatrixTests, SpecialOperator)
	{
		Mat4 matTest1 = Mat4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);

		EXPECT_EQ(matTest1, Mat4::Identity());

		Mat4 matTest2 = Mat4(
			1.f, 0.f, 3.f, 7.f,
			0.f, 9.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 5.f,
			0.f, 0.f, 0.f, 1.f
		);

		Mat4 matRes1 = Mat4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 9.f, 0.f, 0.f,
			3.f, 0.f, 1.f, 0.f,
			7.f, 0.f, 5.f, 1.f
		);

		EXPECT_EQ(matTest2.Transpose(), matRes1);

		Mat4 matTest3 = Mat4(
			1.f, 2.f, 3.f, 4.f,
			2.f, 3.f, 4.f, 1.f,
			3.f, 4.f, 1.f, 2.f,
			4.f, 1.f, 2.f, 3.f
		);

		EXPECT_EQ(matTest3.Determinant(), 160.f);

		Mat4 matRes2 = (1.f / 40.f) * 
		Mat4(
			-9.f,  1.f,  1.f, 11.f,
			 1.f,  1.f, 11.f, -9.f,
			 1.f, 11.f, -9.f,  1.f,
			11.f, -9.f,  1.f,  1.f
		);

		EXPECT_EQ(matTest3.GetInverse(), matRes2);

		EXPECT_EQ(matTest3.GetInverse() * matTest3, Mat4::Identity());

		EXPECT_EQ(matTest3 * matTest3.GetInverse(), Mat4::Identity());
	}

	TEST(MatrixTests, Transformation)
	{
		Mat4 matTest1 = Mat4::CreateTranslationMatrix(Vector3(1.f, 2.f, -5.f));

		Vector4 vecTest = Vector4(1.f, 2.f, 3.f, 1.f);

		EXPECT_EQ((matTest1 * vecTest).ToVector3(), Vector3(2.f, 4.f, -2.f));

		Mat4 matTest2 = Mat4::CreateRotationMatrix(Vector3(0.f, 180.f, 0.f));

		EXPECT_EQ((matTest2 * vecTest).ToVector3(), Vector3(-1.f, 2.f, -3.f));

		Mat4 matTest3 = Mat4::CreateScaleMatrix(Vector3(1.f, 2.f, 3.f));

		EXPECT_EQ((matTest3 * vecTest).ToVector3(), Vector3(1.f, 4.f, 9.f));

		Mat4 matTest4 = Mat4::CreateTransformationMatrix(Vector3(1.f, 2.f, -5.f), Vector3(1.f, 2.f, 3.f), Vector3(0.f, 180.f, 0.f));

		Mat4 matTest5 = matTest1 * matTest2 * matTest3;

		EXPECT_EQ(matTest4 * vecTest, matTest5 * vecTest);


	}
#pragma endregion Matrix

#pragma region Quaternion
	TEST(QuaternionTests, Equal)
	{
		Quaternion quatTest1 = Quaternion(1.f, 2.f, 3.f, 4.f);

		Quaternion quatTest2 = Quaternion(quatTest1);

		EXPECT_EQ(quatTest1, quatTest2);

		EXPECT_EQ(quatTest2, quatTest1);

		Quaternion quatTest3 = quatTest2;

		EXPECT_EQ(quatTest3, quatTest2);

		EXPECT_EQ(quatTest2 == quatTest3, true);
	}

	TEST(QuaternionTests, Sum)
	{
		Quaternion quatTest1 = Quaternion(1.f, 2.f, 3.f, 4.f);

		Quaternion quatTest2 = Quaternion(2.f, 3.f, 4.f, 5.f);

		Quaternion quatRes = Quaternion(3.f, 5.f, 7.f, 9.f);

		EXPECT_EQ(quatTest1 + quatTest2, quatRes);
		EXPECT_EQ(quatTest1 + quatTest2, quatTest2 + quatTest1);

		Quaternion quatTest3 = quatTest1;
		quatTest3 += quatTest2;

		EXPECT_EQ(quatTest3, quatRes);
	}

	TEST(QuaternionTests, Difference)
	{
		Quaternion quatTest1 = Quaternion(1.f, 2.f, 3.f, 4.f);

		Quaternion quatTest2 = Quaternion(2.f, 3.f, 4.f, 5.f);

		Quaternion quatRes1 = Quaternion(-1.f, -2.f, -3.f, -4.f);

		EXPECT_EQ(-quatTest1, quatRes1);

		Quaternion quatRes2 = Quaternion(-1.f, -1.f, -1.f, -1.f);

		EXPECT_EQ(quatTest1 - quatTest2, quatRes2);

		Quaternion quatRes3 = Quaternion(1.f, 1.f, 1.f, 1.f);

		EXPECT_EQ(quatTest2 - quatTest1, quatRes3);

		Quaternion quatTest3 = quatTest1;
		quatTest3 -= quatTest2;

		EXPECT_EQ(quatTest3, quatRes2);
	}

	TEST(QuaternionTests, Product)
	{
		Quaternion quatTest1 = Quaternion(1.f, 2.f, 3.f, 4.f);

		Quaternion quatTest2 = Quaternion(2.f, 3.f, 4.f, 5.f);

		Quaternion quatRes1 = Quaternion(12.f, 24.f, 30.f, 0.f);

		EXPECT_EQ(quatTest1 * quatTest2, quatRes1);

		Quaternion quatRes2 = Quaternion(14.f, 20.f, 32.f, 0.f);

		EXPECT_EQ(quatTest2 * quatTest1, quatRes2);

		Quaternion quatRes3 = Quaternion(2.f, 4.f, 6.f, 8.f);

		EXPECT_EQ(quatTest1 * 2.f, quatRes3);

		Quaternion quatTest3 = quatTest1;
		quatTest3 *= quatTest2;

		EXPECT_EQ(quatTest3, quatRes1);

		Quaternion quatTest4 = quatTest1;
		quatTest4 *= 2.f;

		EXPECT_EQ(quatTest4, quatRes3);
	}

	TEST(QuaternionTests, Quotient)
	{
		Quaternion quatTest1 = Quaternion(1.f, 2.f, 3.f, 4.f);

		Quaternion quatRes = Quaternion(0.5f, 1.f, 1.5f, 2.f);

		EXPECT_EQ(quatTest1 / 2.f, quatRes);

		Quaternion quatTest2 = quatTest1;
		quatTest2 /= 2.f;

		EXPECT_EQ(quatTest2, quatRes);
	}

	TEST(QuaternionTests, SpecialOperator)
	{
		Quaternion quatTest1 = Quaternion(0.f, 0.f, 0.f, 1.f);

		EXPECT_EQ(quatTest1, Quaternion::Identity());

		Quaternion quatTest2 = Quaternion(1.f, 2.f, 3.f, 4.f);

		EXPECT_EQ(quatTest2.Conjugate(), Quaternion(-1.f, -2.f, -3.f, 4.f));

		EXPECT_EQ(quatTest2.Length(), sqrtf(30.f));

		EXPECT_EQ(quatTest2.Normalize(), quatTest2 / sqrtf(30.f));

		EXPECT_EQ(quatTest2.Invert() * quatTest2, Quaternion::Identity());

		EXPECT_EQ(quatTest2 * quatTest2.Invert(), Quaternion::Identity());

		EXPECT_EQ(Quaternion::QuatFromAxisAngle(Vector3(1.f, 0.f, 1.f), 45.f), Quaternion(0.270598f, 0.f, 0.270598f, 0.92388f));

		EXPECT_EQ(Quaternion::QuatFromEuler(0.f, 90.f, 0.f), Quaternion(0.f, 0.707107f, 0.f, 0.707107f));

		EXPECT_EQ(Quaternion(0.f, 0.707107f, 0.f, 0.707107f).QuatToEuler(), Quaternion::QuatFromEuler(0.f, 90.f, 0.f));

		Mat4 matRes =  Mat4(
		   -1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f,-1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);

		EXPECT_EQ(Quaternion::QuatToMatrix(Quaternion(0.f, 1.f, 0.f, 0.f)), matRes);
	}
#pragma endregion Quaternion