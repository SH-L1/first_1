#pragma once

template<typename T = float>
class Vector2
{
public:
    Vector2() : x(0), y(0) {}
    Vector2(const T& x, const T& y) : x(x), y(y) {}

    // 전역함수로 오버로딩 해도 되지만 예외가 있다.
    // +연산자 오버로딩
    // a + b : 임시값을 만들고 a + b 연산을 임시값에 대입하고 임시값을 반환한다.
    Vector2<T> operator+(const Vector2<T>& other) const // const & : 읽기 전용
    {
        Vector2<T> result;
        result.x = x + other.x;
        result.y = y + other.y;

        return result;
    }
    Vector2<T> operator-(const Vector2<T>& other) const
    {
        Vector2<T> result;
        result.x = x - other.x;
        result.y = y - other.y;

        return result;
    }
    Vector2<T> operator*(const float& value) const
    {
        Vector2 result;
        result.x = x * value;
        result.y = y * value;

        return result;
    }
    Vector2<T>& operator=(const Vector2<T>& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }
    Vector2<T>& operator+=(const Vector2<T>& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
    Vector2<T>& operator-=(const Vector2<T>& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }
    bool operator>(const Vector2<T>& other)
    {
        if (x > other.x && y > other.y)
            return true;

        return false;
    }
    bool operator<(const Vector2<T>& other)
    {
        if (x < other.x && y < other.y)
            return true;

        return false;
    }

    // 내적 연산 : 벡터 * 벡터 => 스칼라(힘)
    float DotProduct(const Vector2<T>& other) const
    {
        return x * other.x + y * other.y;
    }
    // 외적 연산 => 벡터
    float Cross(const Vector2<T>& other) const
    {
        // sin(x) * |A| * |B|

        // x1   y1 
        // x2   y2 

        return x * other.y - y * other.x;
    }
    float Length() const { return sqrtf(x * x + y * y); }
    Vector2<T> NormalVector()
    {
        float length = Length();

        Vector2<T> result;
        result.x = x / length;
        result.y = y / length;

        return result;
    }

    // 대입연산자
    // a = b : a에다가 b를 대입하고 원본을 반환한다.

    T x;
    T y;
};
