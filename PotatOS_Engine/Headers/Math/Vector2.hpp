#pragma once

#include <DLLInclude.hpp>

#include <cmath>
#include <iostream>
#include <string>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Vector2.rfkh.h>

namespace Math RFKNamespace()
{
    class RFKClass() POTATOS_ENGINE_API Vector2
    {
        // Attribute
    public:
        float x;
        float y;

        // Method
    public:
        Vector2(const float p_x = 0.f, const float p_y = 0.f);
        Vector2(const Vector2& p_copy);

        static const float DotProduct(const Vector2& p_a, const Vector2& p_b);
        static const float Magnitude(const Vector2& p_vector);
        static const Vector2& Normalize(const Vector2& p_vector);

        void Display() const;
        std::string ToString() const;

        Vector2 operator+(const Vector2& p_right) const;
        Vector2 operator-(const Vector2& p_right) const;
        Vector2 operator-() const;
        Vector2 operator*(const Vector2& p_right) const;
        Vector2 operator*(const float p_multiplier) const;
        Vector2 operator/(const Vector2& p_right) const;
        Vector2 operator/(const float p_divider) const;

        void operator+=(const Vector2& p_right);
        void operator-=(const Vector2& p_right);
        void operator*=(const Vector2& p_right);
        void operator*=(const float p_multiplier);
        void operator/=(const Vector2& p_right);
        void operator/=(const float p_divider);

        friend Vector2 operator*(const float p_left, const Vector2& p_right);
        friend bool operator==(const Vector2& p_left, const Vector2& p_right);
        friend bool operator!=(const Vector2& p_left, const Vector2& p_right);

        Math_Vector2_GENERATED
    };
}
#include "Vector2.inl"
File_Vector2_GENERATED