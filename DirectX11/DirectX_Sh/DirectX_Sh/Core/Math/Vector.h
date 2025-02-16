#pragma once

#include "framework.h"

class Vector : public XMFLOAT2
{
public:
    Vector() : XMFLOAT2() {}
    Vector(float x, float y) : XMFLOAT2(x, y) {}

    Vector operator+(const Vector& other) const
    {
        Vector result;
        result.x = x + other.x;
        result.y = y + other.y;

        return result;
    }
    Vector operator-(const Vector& other) const
    {
        Vector result;
        result.x = x - other.x;
        result.y = y - other.y;

        return result;
    }
    Vector operator*(const float& value) const
    {
        Vector result;
        result.x = x * value;
        result.y = y * value;

        return result;
    }
    Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
    Vector& operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }
    bool operator==(const Vector& other) const
    {
        return (x == other.x && y == other.y);
    }
    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }
    bool operator>(const Vector& other)
    {
        if (x > other.x && y > other.y)
            return true;

        return false;
    }
    bool operator<(const Vector& other)
    {
        if (x < other.x && y < other.y)
            return true;

        return false;
    }

    float DotProduct(const Vector& other) const
    {
        return x * other.x + y * other.y;
    }

    float Cross(const Vector& other) const
    {
        // sin(x) * |A| * |B|

        // x1   y1 
        // x2   y2 

        return x * other.y - y * other.x;
    }

    float Length() const { return sqrtf(x * x + y * y); }
    float LengthSq() const { return x * x + y * y; }
    Vector NormalVector()
    {
        float length = Length();

        Vector result;
        result.x = x / length;
        result.y = y / length;

        return result;
    }
    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
    }
    
    float Angle() { return atan2(y, x); }
};