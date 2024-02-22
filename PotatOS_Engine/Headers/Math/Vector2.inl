#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace Math
{
    inline Vector2::Vector2(const float p_x, const float p_y)
        : x(p_x)
        , y(p_y)
    {}

    inline Vector2::Vector2(const Vector2& p_copy)
        : x(p_copy.x)
        , y(p_copy.y)
    {}

    inline const float Vector2::DotProduct(const Vector2& p_a, const Vector2& p_b)
    {
        return p_a.x * p_b.x + p_a.y * p_b.y;
    }

    inline const float Vector2::Magnitude(const Vector2& p_vector)
    {
        return sqrt(p_vector.x * p_vector.x + p_vector.y * p_vector.y);
    }

    inline const Vector2& Vector2::Normalize(const Vector2& p_vector)
    {
        float magnitude = Magnitude(p_vector);
        Vector2 vectorNormalize = p_vector;
        if(magnitude != 0.f)
        {
            vectorNormalize.x /= magnitude;
            vectorNormalize.y /= magnitude;
        }
        return vectorNormalize;
    }

    inline void Vector2::Display() const
    {
        std::cout << "[ " << x << ", " << y << " ]" << std::endl;
    }

    inline std::string Vector2::ToString() const
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
    }

    inline Vector2 Vector2::operator+(const Vector2& p_right) const { return Vector2(x + p_right.x, y + p_right.y); }

    inline Vector2 Vector2::operator-(const Vector2& p_right) const { return Vector2(x - p_right.x, y - p_right.y); }

    inline Vector2 Vector2::operator-() const { return Vector2(-x, -y); }

    inline Vector2 Vector2::operator*(const Vector2& p_right) const { return Vector2(x * p_right.x, y * p_right.y); }

    inline Vector2 Vector2::operator*(const float p_multiplier) const { return Vector2(x * p_multiplier, y * p_multiplier); }

    inline Vector2 Vector2::operator/(const Vector2& p_right) const { return Vector2(x / p_right.x, y / p_right.y); }

    inline Vector2 Vector2::operator/(const float p_divider) const { return Vector2(x / p_divider, y / p_divider); }

    inline void Vector2::operator+=(const Vector2& p_right) { *this = *this + p_right; }

    inline void Vector2::operator-=(const Vector2& p_right) { *this = *this - p_right; }

    inline void Vector2::operator*=(const Vector2& p_right) { *this = *this * p_right; }

    inline void Vector2::operator*=(const float p_multiplier) { *this = *this * p_multiplier; }

    inline void Vector2::operator/=(const Vector2& p_right) { *this = *this / p_right; }

    inline void Vector2::operator/=(const float p_divider) { *this = *this / p_divider; }

    inline Vector2 operator*(const float p_left, const Vector2& p_right) { return p_right * p_left; }

    inline bool operator==(const Vector2& p_left, const Vector2& p_right)
    {
        if (p_left.x <= p_right.x + 0.001f && p_left.x >= p_right.x - 0.001f &&
            p_left.y <= p_right.y + 0.001f && p_left.y >= p_right.y - 0.001f)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool operator!=(const Vector2& p_left, const Vector2& p_right) { return !(p_left == p_right); }
}