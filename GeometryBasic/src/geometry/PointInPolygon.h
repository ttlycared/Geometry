#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "Point2D.h"
#include "Geometry2D.h"

enum class PointLocation
{
    Outside,
    Inside,
    Boundary
};

inline bool pointOnSegment(
    const Point2D &p,
    const Point2D &a,
    const Point2D &b)
{
    constexpr double eps = 1e-12;

    // 判断三点是否近似共线
    if (std::abs(orientation(a, b, p)) > eps)
        return false;

    // 共线还不够，点还必须位于线段范围内
    return p.x >= std::min(a.x, b.x) - eps &&
           p.x <= std::max(a.x, b.x) + eps &&
           p.y >= std::min(a.y, b.y) - eps &&
           p.y <= std::max(a.y, b.y) + eps;
}

inline PointLocation pointInPolygon(
    const std::vector<Point2D> &polygon,
    const Point2D &p)
{
    const std::size_t n = polygon.size();

    if (n < 3)
        return PointLocation::Outside;

    bool inside = false;

    for (std::size_t i = 0, j = n - 1;
         i < n;
         j = i++)
    {
        const Point2D &a = polygon[j];
        const Point2D &b = polygon[i];

        // 先判断点是否位于当前边界上
        if (pointOnSegment(p, a, b))
            return PointLocation::Boundary;

        // 当前边是否跨过点 P 所在的水平线
        if ((a.y > p.y) != (b.y > p.y))
        {
            // 计算边与水平射线所在直线的交点 x 坐标
            double xCross =
                a.x + (p.y - a.y) *
                          (b.x - a.x) / (b.y - a.y);

            // 交点在 P 的右侧，射线穿过一条边
            if (xCross > p.x)
                inside = !inside;
        }
    }

    return inside
               ? PointLocation::Inside
               : PointLocation::Outside;
}