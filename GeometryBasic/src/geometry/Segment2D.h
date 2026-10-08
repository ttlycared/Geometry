#pragma once

#include "Point2D.h"
#include "Geometry2D.h"

// 点 C 是否在线段 AB 的包围范围内
inline bool onSegment(
    const Point2D &A,
    const Point2D &B,
    const Point2D &P)
{
    return P.x >= std::min(A.x, B.x) &&
           P.x <= std::max(A.x, B.x) &&
           P.y >= std::min(A.y, B.y) &&
           P.y <= std::max(A.y, B.y);
}

// 判断线段 AB 和 CD 是否相交
inline bool segmentIntersect(
    const Point2D &A,
    const Point2D &B,
    const Point2D &C,
    const Point2D &D)
{
    double o1 = orientation(A, B, C);
    double o2 = orientation(A, B, D);
    double o3 = orientation(C, D, A);
    double o4 = orientation(C, D, B);

    // 普通相交
    if ((o1 > 0 && o2 < 0 || o1 < 0 && o2 > 0) &&
        (o3 > 0 && o4 < 0 || o3 < 0 && o4 > 0))
    {
        return true;
    }

    // C 在 AB 上
    if (o1 == 0 && onSegment(A, B, C))
        return true;

    // D 在 AB 上
    if (o2 == 0 && onSegment(A, B, D))
        return true;

    // A 在 CD 上
    if (o3 == 0 && onSegment(C, D, A))
        return true;

    // B 在 CD 上
    if (o4 == 0 && onSegment(C, D, B))
        return true;

    return false;
}