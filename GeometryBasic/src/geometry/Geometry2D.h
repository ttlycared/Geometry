#pragma once
#include <algorithm>

#include "Point2D.h"
#include "Vector2D.h"

// 计算向量叉积
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

inline int orientationSign(
    const Point2D &A,
    const Point2D &B,
    const Point2D &C)
{
    constexpr double eps = 1e-12;

    double value = orientation(A, B, C);

    if (value > eps)
        return 1;

    if (value < -eps)
        return -1;

    return 0;
}