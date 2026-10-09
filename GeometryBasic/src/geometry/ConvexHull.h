#pragma once

#include <algorithm>
#include <vector>

#include "Point2D.h"
#include "Geometry2D.h"

inline std::vector<Point2D> buildHalfHull(
    const std::vector<Point2D> &points)
{
    std::vector<Point2D> hull;

    for (const auto &p : points)
    {
        while (hull.size() >= 2 &&
               orientation(
                   hull[hull.size() - 2],
                   hull[hull.size() - 1],
                   p) <= 0)
        {
            hull.pop_back();
        }

        hull.push_back(p);
    }

    return hull;
}

// 计算二维点集的凸包
inline std::vector<Point2D> convexHull(
    std::vector<Point2D> points)
{
    if (points.size() < 3)
    {
        return points;
    }

    // 1. 按照 x 坐标升序排序，如果 x 坐标相同，则按照 y 坐标升序排序
    std::sort(
        points.begin(),
        points.end(),
        [](const Point2D &a, const Point2D &b)
        {
            if (a.x != b.x)
                return a.x < b.x;
            return a.y < b.y;
        });

    // 删除重复点
    points.erase(
        std::unique(
            points.begin(),
            points.end(),
            [](const Point2D &a, const Point2D &b)
            {
                return a.x == b.x && a.y == b.y;
            }),
        points.end());

    std::vector<Point2D> lower =
        buildHalfHull(points);

    std::reverse(points.begin(), points.end());

    std::vector<Point2D> upper =
        buildHalfHull(points);

    // 去掉两部分重复的端点
    lower.pop_back();
    upper.pop_back();

    lower.insert(
        lower.end(),
        upper.begin(),
        upper.end());

    return lower;
}