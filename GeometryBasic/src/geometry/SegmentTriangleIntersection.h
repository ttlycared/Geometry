
#pragma once

#include <cmath>
#include "Geometry3D.h"

struct STPoint2D
{
    double x;
    double y;
};

// 计算点 P + t * v
inline Point3D pointAt(
    const Point3D &p,
    const Vector3D &v,
    double t)
{
    return {
        p.x + t * v.x,
        p.y + t * v.y,
        p.z + t * v.z};
}

// 删除指定坐标轴，将三维点投影到二维
// dropAxis: 0 删除 x，1 删除 y，2 删除 z
inline STPoint2D projectTo2D(
    const Point3D &p,
    int dropAxis)
{
    if (dropAxis == 0)
        return {p.y, p.z};

    if (dropAxis == 1)
        return {p.x, p.z};

    return {p.x, p.y};
}

// 二维叉积：判断三个点的转向
inline double stOrientation(
    const STPoint2D &a,
    const STPoint2D &b,
    const STPoint2D &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断二维点是否在线段包围盒内
inline bool stInBox(
    const STPoint2D &p,
    const STPoint2D &a,
    const STPoint2D &b,
    double eps = 1e-10)
{
    return p.x >= std::min(a.x, b.x) - eps && p.x <= std::max(a.x, b.x) + eps && p.y >= std::min(a.y, b.y) - eps && p.y <= std::max(a.y, b.y) + eps;
}

// 判断二维线段是否相交，包含端点接触和共线重叠
inline bool stSegmentsIntersect(
    const STPoint2D &a,
    const STPoint2D &b,
    const STPoint2D &c,
    const STPoint2D &d)
{
    const double eps = 1e-10;

    double o1 = stOrientation(a, b, c);
    double o2 = stOrientation(a, b, d);
    double o3 = stOrientation(c, d, a);
    double o4 = stOrientation(c, d, b);

    if (((o1 > eps && o2 < -eps) || (o1 < -eps && o2 > eps)) && ((o3 > eps && o4 < -eps) || (o3 < -eps && o4 > eps)))
        return true;

    if (std::abs(o1) <= eps && stInBox(c, a, b))
        return true;

    if (std::abs(o2) <= eps && stInBox(d, a, b))
        return true;

    if (std::abs(o3) <= eps && stInBox(a, c, d))
        return true;

    if (std::abs(o4) <= eps && stInBox(b, c, d))
        return true;

    return false;
}

// 判断二维点是否在三角形内或边界上
inline bool stPointInTriangle(
    const STPoint2D &p,
    const STPoint2D &a,
    const STPoint2D &b,
    const STPoint2D &c)
{
    const double eps = 1e-10;

    double o1 = stOrientation(a, b, p);
    double o2 = stOrientation(b, c, p);
    double o3 = stOrientation(c, a, p);

    bool hasPositive =
        o1 > eps || o2 > eps || o3 > eps;

    bool hasNegative =
        o1 < -eps || o2 < -eps || o3 < -eps;

    return !(hasPositive && hasNegative);
}

// 判断共面线段是否与三角形有交集
inline bool coplanarSegmentIntersectsTriangle(
    const Point3D &p,
    const Point3D &q,
    const Point3D &a,
    const Point3D &b,
    const Point3D &c,
    const Vector3D &n)
{
    // 删除法向量绝对值最大的轴
    int dropAxis = 0;

    if (std::abs(n.y) > std::abs(n.x))
        dropAxis = 1;

    double largest =
        dropAxis == 0 ? std::abs(n.x) : std::abs(n.y);

    if (std::abs(n.z) > largest)
        dropAxis = 2;

    STPoint2D P = projectTo2D(p, dropAxis);
    STPoint2D Q = projectTo2D(q, dropAxis);
    STPoint2D A = projectTo2D(a, dropAxis);
    STPoint2D B = projectTo2D(b, dropAxis);
    STPoint2D C = projectTo2D(c, dropAxis);

    // 任意端点在三角形内，就存在交集
    if (stPointInTriangle(P, A, B, C) || stPointInTriangle(Q, A, B, C))
        return true;

    // 否则检查线段是否穿过三角形的三条边
    return stSegmentsIntersect(P, Q, A, B) || stSegmentsIntersect(P, Q, B, C) || stSegmentsIntersect(P, Q, C, A);
}

// 判断三维线段 PQ 是否与三角形 ABC 相交
// 相交时将交点写入 intersection
inline bool segmentTriangleIntersection(
    const Point3D &p,
    const Point3D &q,
    const Point3D &a,
    const Point3D &b,
    const Point3D &c,
    Point3D &intersection)
{
    const double eps = 1e-10;

    Vector3D direction = q - p;
    Vector3D ab = b - a;
    Vector3D ac = c - a;

    // 三角形法向量
    Vector3D n = cross(ab, ac);

    // 线段与平面的方向关系
    double denominator = dot(direction, n);

    if (std::abs(denominator) < eps)
    {
        // 线段与平面平行。
        // 进一步判断线段是否位于该平面上。
        if (std::abs(signedPlaneSide(p, a, b, c)) > eps)
            return false;

        // 共面情况下，判断线段与三角形是否有交集。
        return coplanarSegmentIntersectsTriangle(
            p, q, a, b, c, n);
    }

    // 求交点参数 t
    double t = dot(a - p, n) / denominator;

    // 交点必须在线段范围内
    if (t < -eps || t > 1.0 + eps)
        return false;

    Point3D x = pointAt(p, direction, t);

    // 用重心坐标判断交点是否在三角形内
    Vector3D ap = x - a;

    double d00 = dot(ab, ab);
    double d01 = dot(ab, ac);
    double d11 = dot(ac, ac);
    double d20 = dot(ap, ab);
    double d21 = dot(ap, ac);

    double denom = d00 * d11 - d01 * d01;

    // 退化三角形
    if (std::abs(denom) < eps)
        return false;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    // 允许微小浮点误差，并包含三角形边界
    if (u < -eps || v < -eps || w < -eps)
        return false;

    intersection = x;
    return true;
}
