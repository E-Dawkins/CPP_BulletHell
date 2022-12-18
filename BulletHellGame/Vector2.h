#pragma once
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
        Vector2 diff = _end - _start;
    
        float time = _time;
    
        if (time < 0) time = 0;
        if (time > 1) time = 1;
        
        return _start + (diff * time);
    }

    static float Distance(const Vector2 _a, const Vector2 _b)
    {
        return (float)sqrt(pow((double)(_b.x - _a.x), 2) + pow((double)(_b.y - _a.y), 2));
    }
    
    void operator +=(const Vector2 _b)
    {
        x += _b.x;
        y += _b.y;
    }

    Vector2 operator *(const float _b)
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
