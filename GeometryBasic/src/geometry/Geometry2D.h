#pragma once
#include <algorithm>

#include "Point2D.h"
#include "Vector2D.h"

inline double cross(
    const Vector2D &a,
    const Vector2D &b)
{
    return a.x * b.y - a.y * b.x;
}

/*
> 0    C 在 AB 左侧
< 0    C 在 AB 右侧
= 0    A、B、C 共线
*/
inline double orientation(
    const Point2D &a,
    const Point2D &b,
    const Point2D &c)
{
    return cross(b - a, c - a);
}