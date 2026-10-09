
#pragma once

#include "Point2D.h"
#include "Vector2D.h"
#include "Geometry2D.h"
#include "SegmentIntersectionResult.h"

#include <algorithm>
#include <cmath>

inline bool useX(const Vector2D &v)
{
    return std::abs(v.x) >= std::abs(v.y);
}

inline double coordinate(
    const Point2D &p,
    bool useXCoordinate)
{
    return useXCoordinate ? p.x : p.y;
}

inline Point2D pointAtCoordinate(
    const Point2D &A,
    const Point2D &B,
    double value,
    bool useXCoordinate)
{
    if (useXCoordinate)
    {
        double t =
            (value - A.x) /
            (B.x - A.x);

        return {
            A.x + t * (B.x - A.x),
            A.y + t * (B.y - A.y)};
    }
    else
    {
        double t =
            (value - A.y) /
            (B.y - A.y);

        return {
            A.x + t * (B.x - A.x),
            A.y + t * (B.y - A.y)};
    }
}

// 交集是一个点
inline bool segmentIntersection(const Point2D &A, const Point2D &B, const Point2D &C, const Point2D &D, Point2D &intersection)
{
    // r = B - A
    Vector2D r = B - A;

    // s = D - C
    Vector2D s = D - C;

    // q = C - A
    Vector2D q = C - A;

    // 分母：cross(r, s)
    double denominator = cross(r, s);

    // 平行或共线
    if (std::abs(denominator) < 1e-12)
    {
        return false;
    }

    // 计算参数 t、u
    double t = cross(q, s) / denominator;
    double u = cross(q, r) / denominator;

    // 判断交点是否同时位于两条线段内部或端点
    if (t < 0.0 || t > 1.0 ||
        u < 0.0 || u > 1.0)
    {
        return false;
    }

    // 计算交点坐标
    intersection.x = A.x + t * r.x;
    intersection.y = A.y + t * r.y;

    return true;
}
// 点是否在AB线段上
inline bool pointOnSegment(const Point2D &A, const Point2D &B, const Point2D &P)
{
    const double eps = 1e-12;

    // 先判断是否共线
    if (std::abs(orientation(A, B, P)) > eps)
        return false;

    // 再判断是否位于包围盒内
    return P.x >= std::min(A.x, B.x) - eps &&
           P.x <= std::max(A.x, B.x) + eps &&
           P.y >= std::min(A.y, B.y) - eps &&
           P.y <= std::max(A.y, B.y) + eps;
}
// 交集是一个点或线段
inline IntersectionResult segmentIntersection(const Point2D &A, const Point2D &B, const Point2D &C, const Point2D &D)
{
    const double eps = 1e-12;

    Vector2D r = B - A;
    Vector2D s = D - C;

    double denominator = cross(r, s);

    // ========================================================
    // 情况 1：两条线段不平行
    // ========================================================
    if (std::abs(denominator) > eps)
    {
        Vector2D q = C - A;

        double t = cross(q, s) / denominator;
        double u = cross(q, r) / denominator;

        // 交点在线段范围内
        if (t >= -eps && t <= 1.0 + eps &&
            u >= -eps && u <= 1.0 + eps)
        {
            Point2D P{
                A.x + t * r.x,
                A.y + t * r.y};

            return {
                IntersectionType::Point,
                P,
                {},
                {}};
        }

        return {
            IntersectionType::None,
            {},
            {},
            {}};
    }

    // ========================================================
    // 情况 2：平行
    // ========================================================

    // 不共线
    if (std::abs(orientation(A, B, C)) > eps)
    {
        return {
            IntersectionType::None,
            {},
            {},
            {}};
    }

    // ========================================================
    // 情况 3：共线
    // ========================================================

    bool xDirection = useX(r);

    double a1 = coordinate(A, xDirection);
    double a2 = coordinate(B, xDirection);

    double c1 = coordinate(C, xDirection);
    double c2 = coordinate(D, xDirection);

    double minAB = std::min(a1, a2);
    double maxAB = std::max(a1, a2);

    double minCD = std::min(c1, c2);
    double maxCD = std::max(c1, c2);

    double overlapMin =
        std::max(minAB, minCD);

    double overlapMax =
        std::min(maxAB, maxCD);

    // 完全没有交集
    if (overlapMin > overlapMax + eps)
    {
        return {
            IntersectionType::None,
            {},
            {},
            {}};
    }

    // 只有一个交点
    if (std::abs(overlapMin - overlapMax) <= eps)
    {
        Point2D P =
            pointAtCoordinate(
                A,
                B,
                overlapMin,
                xDirection);

        return {
            IntersectionType::Point,
            P,
            {},
            {}};
    }

    // 有一段重叠
    Point2D P1 =
        pointAtCoordinate(
            A,
            B,
            overlapMin,
            xDirection);

    Point2D P2 =
        pointAtCoordinate(
            A,
            B,
            overlapMax,
            xDirection);

    return {
        IntersectionType::Overlap,
        {},
        P1,
        P2};
}
