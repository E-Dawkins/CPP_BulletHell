#pragma once
#include <cmath>
struct Vector2
{
    float x;
    float y;

    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(const float _x, const float _y)
    {
        x = _x;
        y = _y;
    }

    static Vector2 Lerp(const Vector2 _start, const Vector2 _end, const float _time)
    {
        const Vector2 diff = _end - _start;
    
        float time = _time;
    
        if (time < 0) time = 0;
        if (time > 1) time = 1;
        
        return _start + (diff * time);
    }

    float Distance(const Vector2 _b) const
    {
        return sqrtf(powf(_b.x - x, 2) + powf(_b.y - y, 2));
    }

    static float Distance(const Vector2 _a, const Vector2 _b)
    {
        return sqrtf(powf(_b.x - _a.x, 2) + powf(_b.y - _a.y, 2));
    }

    Vector2 Normalize() const
    {
        return Vector2{x / Magnitude(), y / Magnitude()};
    }

    static Vector2 Normalize(const Vector2 _a)
    {
        return Vector2{_a.x / _a.Magnitude(), _a.y / _a.Magnitude()};
    }

    float Magnitude() const
    {
        return sqrtf(x*x + y*y);
    }

    static float Magnitude(const Vector2 _a)
    {
        return sqrtf(_a.x*_a.x + _a.y*_a.y);
    }
    
    void operator +=(const Vector2 _b)
    {
        x += _b.x;
        y += _b.y;
    }

    void operator -=(const Vector2 _b)
    {
        x -= _b.x;
        y -= _b.y;
    }

    Vector2 operator *(const float _b) const
    {
        return {x * _b, y * _b};
    }

    Vector2 operator -(const Vector2 _b) const
    {
        return {x - _b.x, y - _b.y};
    }

    Vector2 operator +(const Vector2 _b) const
    {
        return {x + _b.x, y + _b.y};
    }

    bool operator ==(const Vector2 _b) const
    {
        return (x == _b.x && y == _b.y);
    }
};
