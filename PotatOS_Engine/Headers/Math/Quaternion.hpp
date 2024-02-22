#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <Math/Mat4.hpp>
#include <Math/Vector3.hpp>

namespace Math
{
    class Quaternion
    {
    // Attribute
    public:
        float x; 
        float y; 
        float z; 
        float w;

    // Method
    public:
        Quaternion(const float p_x = 0.f, const float p_y = 0.f, const float p_z = 0.f, const float p_w = 1.f);
        Quaternion(const Vector3& p_vector, const float p_scalar);
        Quaternion(const Quaternion& p_other);

        // Operators 
        Quaternion operator+(const Quaternion& p_q) const;
        Quaternion operator-(const Quaternion& p_q) const;
        Quaternion operator-() const;
        Quaternion operator*(const Quaternion& p_q) const;
        Quaternion operator*(const float p_s) const;
        //Vector3 operator*(const Vector3& p_v) const;
        Quaternion operator/(const float p_s) const;
        void operator+=(const Quaternion& p_q);
        void operator-=(const Quaternion& p_q);
        void operator*=(const Quaternion& p_q);
        void operator*=(const float p_s);
        void operator/=(const float p_s);
        friend bool operator==(const Quaternion& p_q, const Quaternion& p_right);

        std::string ToString();

        // Functions 
        static Quaternion Identity();

        //Normalize quaternion
        Quaternion Normalize() const;

        //Give quaternion lenght 
        float Length() const;

        Quaternion Conjugate() const;

        //Give quaternion 's inverse if it exist
        Quaternion Invert() const;

        static Mat4 QuatToMatrix(const Quaternion& p_q);

        //Create a quaternion from traditional radian angles
        // yaw Rotation around X axis, in radian
        // pitch Rotation around Y axis, in radian
        // roll Rotation around Z axis, in radian
        static Quaternion QuatFromEuler(const float& p_yaw, const float& p_pitch, const float& p_roll);

        //Create a quaternion from traditional degree angles To recheck
        static Quaternion QuatFromEuler(const Vector3& p_eulerRadAngles);

        //  Give the Euler angles equivalent to quaternion (yaw, pitch, roll)
        Vector3 QuatToEuler() const;

        // Create a quaternion given an angle, in degree, and a rotation axis
        static Quaternion QuatFromAxisAngle(const Vector3& p_axis, float p_radAngle);

        // Give the axis and angle of rotation from a quaternion
        void QuatToAxisAngle(Vector3& p_outAxis, float& p_outAngle);

        //Give rotation quaternion from a vector to another
        static Quaternion VectorToVector(const Vector3& p_from, const Vector3& p_to);

        static float Angle(const Quaternion& p_q1, const Quaternion& p_q2);

        //Calculate linear interpolation between two quaternions (normalize before)
        static Quaternion Lerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor);

        //Calculate slerp-optimized interpolation between two quaternions (normalize before)
        static Quaternion Nlerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor);

        //Calculates spherical linear interpolation between two quaternions (normalize before)
        static Quaternion Slerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor);
    };

    std::ostream& operator<<(std::ostream& p_o, const Quaternion& p_q);
};