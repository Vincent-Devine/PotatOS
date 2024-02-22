#pragma once
#include <Math/Quaternion.hpp>

#include <iostream>
#include <string>

#include <Math/Utils.hpp>

namespace Math
{
    inline Quaternion::Quaternion(const float p_x, const float p_y, const float p_z, const float p_w)
        : x(p_x)
        , y(p_y)
        , z(p_z)
        , w(p_w)
    {}

    inline Quaternion::Quaternion(const Vector3 & p_vector, const float p_scalar) 
        : x(p_vector.x)
        , y(p_vector.y)
        , z(p_vector.z)
        , w(p_scalar)
    {
    }

    inline Quaternion::Quaternion(const Quaternion& p_other)
        : x(p_other.x)
        , y(p_other.y)
        , z(p_other.z)
        , w(p_other.w)
    {
    }
  
    inline Quaternion Quaternion::operator+(const Quaternion& p_q) const
    {
        return 
        {
                x + p_q.x,
                y + p_q.y,
                z + p_q.z,
                w + p_q.w
        };
    }

    inline Quaternion Quaternion::operator-(const Quaternion& p_q) const
    {
        return 
        {
                x - p_q.x,
                y - p_q.y,
                z - p_q.z,
                w - p_q.w
        };
    }

    inline Quaternion Quaternion::operator-() const
    {
        return Quaternion(-x, -y, -z, -w);
    }

    inline Quaternion Quaternion::operator*(const Quaternion& p_q) const
    {
        return 
        {
                w* p_q.x + x * p_q.w + y * p_q.z - z * p_q.y,
                w* p_q.y + y * p_q.w + z * p_q.x - x * p_q.z,
                w* p_q.z + z * p_q.w + x * p_q.y - y * p_q.x,
                w* p_q.w - x * p_q.x - y * p_q.y - z * p_q.z
        };
    }

    inline Quaternion Quaternion::operator*(const float p_s) const
    {
        return Quaternion(x * p_s, y * p_s, z * p_s, w * p_s);
    }

    inline Quaternion Quaternion::operator/(const float p_s) const
    {
        return Quaternion(x / p_s, y / p_s, z / p_s, w / p_s);
    }

    inline void Quaternion::operator+=(const Quaternion& p_q)
    {
        *this = *this + p_q;
    }

    inline void Quaternion::operator-=(const Quaternion& p_q)
    {
        *this = *this - p_q;
    }

    inline void Quaternion::operator*=(const Quaternion& q)
    {
        *this = *this * q;
    }

    inline void Quaternion::operator*=(const float p_s)
    {
        *this = *this * p_s;
    }

    inline void Quaternion::operator/=(const float p_s)
    {
        *this = *this / p_s;
    }

    inline std::string Quaternion::ToString()
    {
        return std::string("x: "+ std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z) + ", w: " + std::to_string(w));
    }

    inline bool operator==(const Quaternion& p_q, const Quaternion& p_right)
    {
        return (
            Math::Abs(p_q.x - p_right.x) <= Math::weakEpsilon &&
            Math::Abs(p_q.y - p_right.y) <= Math::weakEpsilon &&
            Math::Abs(p_q.z - p_right.z) <= Math::weakEpsilon &&
            Math::Abs(p_q.w - p_right.w) <= Math::weakEpsilon
            );
    }

    inline std::ostream& operator<<(std::ostream& p_o, const Quaternion& p_q)
    {
        return p_o << "x = " << p_q.x << ", y = " << p_q.y << ", z = " << p_q.z << ", w = " << p_q.w;
    }

    //Functions
    inline Quaternion Quaternion::Identity()
    {
        return { 0.f, 0.f, 0.f, 1.f };
    }

    inline Quaternion Quaternion::Normalize() const
    {
        float length = this->Length();

        if (length < Math::weakEpsilon)
        {
            length = 1.0f;
        }

        float ilength = 1.0f / length;

        return {
                x * ilength,
                y * ilength,
                z * ilength,
                w * ilength
        };
    }

    inline float Quaternion::Length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    inline Quaternion Quaternion::Conjugate() const
    {
        return Quaternion(-x, -y, -z, w);
    }

    inline Quaternion Quaternion::Invert() const
    {
        Quaternion result = *this;
        float length = this->Length();
        float lengthSq = length * length;

        if (lengthSq != 0.0)
        {
            float i = 1.0f / lengthSq;

            result.x *= -i;
            result.y *= -i;
            result.z *= -i;
            result.w *= i;
        }

        return result;
    }

    inline Mat4 Quaternion::QuatToMatrix(const Quaternion& p_q)
    {
        p_q.Normalize();

        return {
                2.f * (p_q.w * p_q.w + p_q.x * p_q.x) - 1.f,    2.f * (p_q.x * p_q.y - p_q.z * p_q.w),          2.f * (p_q.x * p_q.z + p_q.y * p_q.w),          0.f,
                2.f * (p_q.x * p_q.y + p_q.z * p_q.w),          2.f * (p_q.w * p_q.w + p_q.y * p_q.y) - 1.f,    2.f * (p_q.y * p_q.z - p_q.x * p_q.w),          0.f,
                2.f * (p_q.x * p_q.z - p_q.y * p_q.w),          2.f * (p_q.y * p_q.z + p_q.x * p_q.w),          2.f * (p_q.w * p_q.w + p_q.z * p_q.z) - 1.f,    0.f,
                0.f,                                            0.f,                                            0.f,                                            1.f
        };
    }


    inline Quaternion Quaternion::QuatFromEuler(const float& p_x, const float& p_y, const float& p_z)
    {
        const float cr = cosf(DEG2RAD * p_x * 0.5f);
        const float sr = sinf(DEG2RAD * p_x * 0.5f);
        const float cp = cosf(DEG2RAD * p_y * 0.5f);
        const float sp = sinf(DEG2RAD * p_y * 0.5f);
        const float cy = cosf(DEG2RAD * p_z * 0.5f);
        const float sy = sinf(DEG2RAD * p_z * 0.5f);

        Quaternion q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = sr * cp * cy - cr * sp * sy;
        q.y = cr * sp * cy + sr * cp * sy;
        q.z = cr * cp * sy - sr * sp * cy;

        return q;
    }

    inline Quaternion Quaternion::QuatFromEuler(const Vector3& p_eulerRadAngles)
    {
        return QuatFromEuler(p_eulerRadAngles.x, p_eulerRadAngles.y, p_eulerRadAngles.z);
    }

    inline Vector3 Quaternion::QuatToEuler() const
    {
        Vector3 euler;

        double sqw = w * w;
        double sqx = x * x;
        double sqy = y * y;
        double sqz = z * z;
        double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
        double test = x * y + z * w;
        if (test > 0.499 * unit) { // singularity at north pole
            euler.y = static_cast<float>(2.0 * atan2(x, w));
            euler.z = static_cast<float>(Math::pi / 2.0);
            euler.x = static_cast<float>(0.0);
            return euler * RAD2DEG;
        }
        if (test < -0.499 * unit) { // singularity at south pole
            euler.y = static_cast<float>(-2.0 * atan2(x, w));
            euler.z = static_cast<float>(-Math::pi / 2.0);
            euler.x = static_cast<float>(0.0);
            return euler * RAD2DEG;
        }
        euler.y = static_cast<float>(atan2(2.0 * y * w - 2.0 * x * z, sqx - sqy - sqz + sqw));
        euler.z = static_cast<float>(asin(2.0 * test / unit));
        euler.x = static_cast<float>(atan2(2.0 * x * w - 2.0 * y * z, -sqx + sqy - sqz + sqw));

        return euler * RAD2DEG;
    }

    inline Quaternion Quaternion::QuatFromAxisAngle(const Vector3& p_axis, float p_radAngle)
    {
        Quaternion result = Identity();

        if (Math::Vector3::Magnitude(p_axis) != 0.0f)
        {
            p_radAngle *= 0.5f;
        }
        Vector3 newAxis = Math::Vector3::Normalize(p_axis);

        float cosres = cos(p_radAngle * DEG2RAD);
        float sinres = sin(p_radAngle * DEG2RAD);

        result.x = newAxis.x * sinres;
        result.y = newAxis.y * sinres;
        result.z = newAxis.z * sinres;
        result.w = cosres;

        return result.Normalize();
    }

    inline void Quaternion::QuatToAxisAngle(Vector3& p_outAxis, float& p_outAngle)
    {
        if (Math::Abs(w) > 1.0f)
        {
            *this = this->Normalize();
        }

        Vector3 resAxis = { 0.0f, 0.0f, 0.0f };
        float resAngle = 2.0f * acos(w);
        float den = sqrt(1.0f - w * w);

        if (den > 0.0001f)
        {
            resAxis.x = x / den;
            resAxis.y = y / den;
            resAxis.z = z / den;
        }
        else
        {
            resAxis.x = x;
            resAxis.y = y;
            resAxis.z = z;
        }

        p_outAxis = resAxis;
        p_outAngle = resAngle;
    }

    inline Quaternion Quaternion::VectorToVector(const Vector3& p_from, const Vector3& p_to)
    {
        Quaternion result = { 0.f, 0.f, 0.f, 0.f };

        float dot = Vector3::DotProduct(p_from, p_to);
        Vector3 cross = Vector3::CrossProduct(p_from, p_to);

        result.x = cross.x;
        result.y = cross.y;
        result.z = cross.z;
        result.w = 1.0f + dot;

        return result.Normalize();
    }

    inline float Quaternion::Angle(const Quaternion& p_q1, const Quaternion& p_q2)
    {
        float innerProd = p_q1.x * p_q2.x + p_q1.y * p_q2.y + p_q1.z * p_q2.z + p_q1.w * p_q2.w;
        return acos((2 * innerProd * innerProd) - 1.f) * Math::RAD2DEG;
    }

    inline Quaternion Quaternion::Lerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor)
    {
        p_factor = Math::Clamp(p_factor, 0.f, 1.f);
        return {
                p_q1.x + p_factor * (p_q2.x - p_q1.x),
                p_q1.y + p_factor * (p_q2.y - p_q1.y),
                p_q1.z + p_factor * (p_q2.z - p_q1.z),
                p_q1.w + p_factor * (p_q2.w - p_q1.w)
        };
    }

    inline Quaternion Quaternion::Nlerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor)
    {
        p_factor = Math::Clamp(p_factor, 0.f, 1.f);

        Quaternion result = Lerp(p_q1, p_q2, p_factor);

        return result.Normalize();
    }

    inline Quaternion Quaternion::Slerp(const Quaternion& p_q1, const Quaternion& p_q2, float p_factor)
    {
        if (p_factor > 1.f)
        {
            return p_q2;
        }
        float cosHalfOmega = p_q1.x * p_q2.x + p_q1.y * p_q2.y + p_q1.z * p_q2.z + p_q1.w * p_q2.w;

        Quaternion tto = p_q2;
        if (cosHalfOmega < 0.f)
        {
            tto = { -tto.x, -tto.y, -tto.z, -tto.w };
            cosHalfOmega = -cosHalfOmega;
        }

        if (Math::Abs(cosHalfOmega) >= 1.0f)
        {
            return p_q1;
        }
        else
        {
            float halfOmega = acos(cosHalfOmega);
            float sinHalfOmega = sqrt(1.f - cosHalfOmega * cosHalfOmega);

            float ratioA = (sin((1.f - p_factor) * halfOmega) / sinHalfOmega);
            float ratioB = (sin(p_factor * halfOmega) / sinHalfOmega);
            return { (p_q1.x * ratioA + tto.x * ratioB),
                (p_q1.y * ratioA + tto.y * ratioB),
                (p_q1.z * ratioA + tto.z * ratioB),
                (p_q1.w * ratioA + tto.w * ratioB) };
        }
    }
}