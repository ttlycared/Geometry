#pragma once

#include <cmath>

#include "Point2D.h"
#include "Vector2D.h"

struct PointSegmentDistanceResult
{
    Point2D closestPoint;
    double distance;
    double t;
};

inline PointSegmentDistanceResult pointSegmentDistance(
    const Point2D &p,
    const Point2D &a,
    const Point2D &b)
{
    // 线段方向向量
    Vector2D v = b - a;

    // 从 A 指向 P 的向量
    Vector2D w = p - a;

    // 线段长度的平方
    double lengthSquared =
        v.x * v.x + v.y * v.y;

    // 处理退化线段：A 和 B 是同一个点
    if (lengthSquared == 0.0)
    {
        double dx = p.x - a.x;
        double dy = p.y - a.y;

        return {
            a,
            std::sqrt(dx * dx + dy * dy),
            0.0};
    }

    // 计算投影参数
    double t =
        (w.x * v.x + w.y * v.y) / lengthSquared;

    // 限制在 [0, 1]，确保最近点在线段上
    if (t < 0.0)
        t = 0.0;
    else if (t > 1.0)
        t = 1.0;

    // 计算最近点 Q
    Point2D q = {
        a.x + t * v.x,
        a.y + t * v.y};

    // 计算 P 到 Q 的距离
    double dx = p.x - q.x;
    double dy = p.y - q.y;

    double distance = std::sqrt(dx * dx + dy * dy);

    return {q, distance, t};
}