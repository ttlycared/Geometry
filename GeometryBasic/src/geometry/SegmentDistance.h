#pragma once

#include <algorithm>

#include "Point2D.h"
#include "PointSegmentDistance.h"
#include "SegmentIntersection.h"

struct SegmentDistanceResult
{
    double distance;
    Point2D pointOnAB;
    Point2D pointOnCD;
};

inline SegmentDistanceResult segmentDistance(
    const Point2D &a,
    const Point2D &b,
    const Point2D &c,
    const Point2D &d)
{
    // 第一步：检查两条线段是否相交
    auto intersection = segmentIntersection(a, b, c, d);

    if (intersection.type != IntersectionType::None)
    {
        // 相交或重叠时，距离为 0
        // 此处先返回交点；重叠时取重叠区间起点
        Point2D p = intersection.type == IntersectionType::Point
                        ? intersection.point
                        : intersection.start;

        return {0.0, p, p};
    }

    // 第二步：计算四个端点到另一条线段的距离
    auto ac = pointSegmentDistance(a, c, d);
    auto bc = pointSegmentDistance(b, c, d);
    auto ca = pointSegmentDistance(c, a, b);
    auto da = pointSegmentDistance(d, a, b);

    // 第三步：找最小距离，并记录对应的两个最近点
    SegmentDistanceResult result{
        ac.distance,
        a,
        ac.closestPoint};

    if (bc.distance < result.distance)
    {
        result = {bc.distance, b, bc.closestPoint};
    }

    if (ca.distance < result.distance)
    {
        result = {ca.distance, ca.closestPoint, c};
    }

    if (da.distance < result.distance)
    {
        result = {da.distance, da.closestPoint, d};
    }

    return result;
}