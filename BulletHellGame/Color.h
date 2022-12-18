#pragma once

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() = default;

    Color(const float _r, const float _g, const float _b, const float _a)
    {
        r =_r;
        g = _g;
        b = _b;
        a = _a;
    }
};
