#pragma once

#include <algorithm>
#include <cmath>

#include "Point3D.h"
#include "Vector3D.h"
#include "Geometry3D.h"

// 点到三角形的距离计算结果
struct PointTriangleDistanceResult
{
    Point3D closestPoint;
    double distance;
};

// 计算三维点到三维线段的最短距离
inline PointTriangleDistanceResult pointSegmentDistance3D(
    const Point3D &p,
    const Point3D &a,
    const Point3D &b)
{
    Vector3D ab = b - a;
    Vector3D ap = p - a;

    double len2 = dot(ab, ab);

    // 退化线段：A、B 重合
    if (len2 == 0.0)
    {
        double dx = p.x - a.x;
        double dy = p.y - a.y;
        double dz = p.z - a.z;

        return {
            a,
            std::sqrt(dx * dx + dy * dy + dz * dz)};
    }

    // 投影参数
    double t = dot(ap, ab) / len2;
    t = std::max(0.0, std::min(1.0, t));

    Point3D q = {
        a.x + t * ab.x,
        a.y + t * ab.y,
        a.z + t * ab.z};

    double dx = p.x - q.x;
    double dy = p.y - q.y;
    double dz = p.z - q.z;

    return {
        q,
        std::sqrt(dx * dx + dy * dy + dz * dz)};
}

// 计算三维点到三角形的最短距离
inline PointTriangleDistanceResult pointTriangleDistance(
    const Point3D &p,
    const Point3D &a,
    const Point3D &b,
    const Point3D &c)
{
    // 三角形的两条边
    Vector3D ab = b - a;
    Vector3D ac = c - a;

    // 三角形法向量
    Vector3D n = cross(ab, ac);

    double n2 = dot(n, n);

    // 默认使用 AB 边作为初始结果
    PointTriangleDistanceResult best =
        pointSegmentDistance3D(p, a, b);

    // 比较 BC 边
    auto resultBC = pointSegmentDistance3D(p, b, c);
    if (resultBC.distance < best.distance)
        best = resultBC;

    // 比较 CA 边
    auto resultCA = pointSegmentDistance3D(p, c, a);
    if (resultCA.distance < best.distance)
        best = resultCA;

    // 三角形退化：三个顶点共线或重合
    // 最近点由三条边的距离比较决定
    if (n2 == 0.0)
        return best;

    // 计算 P 在三角形所在平面上的投影 Q
    Vector3D ap = p - a;

    double t = dot(ap, n) / n2;

    Point3D q = {
        p.x - t * n.x,
        p.y - t * n.y,
        p.z - t * n.z};

    // 利用重心坐标判断投影点 Q 是否位于三角形内
    Vector3D aq = q - a;

    double d00 = dot(ab, ab);
    double d01 = dot(ab, ac);
    double d11 = dot(ac, ac);
    double d20 = dot(aq, ab);
    double d21 = dot(aq, ac);

    double denom = d00 * d11 - d01 * d01;

    double beta = (d11 * d20 - d01 * d21) / denom;
    double gamma = (d00 * d21 - d01 * d20) / denom;
    double alpha = 1.0 - beta - gamma;

    // 投影点位于三角形内部或边界
    if (alpha >= 0.0 &&
        beta >= 0.0 &&
        gamma >= 0.0)
    {
        double dx = p.x - q.x;
        double dy = p.y - q.y;
        double dz = p.z - q.z;

        return {
            q,
            std::sqrt(dx * dx + dy * dy + dz * dz)};
    }

    // 投影点在三角形外部，最近点位于某条边上
    return best;
}