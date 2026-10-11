#pragma once

#include <cmath>
#include "Vector3D.h"

inline double dot(const Vector3D &a, const Vector3D &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline double lengthSquared(const Vector3D &v)
{
    return dot(v, v);
}

inline double length(const Vector3D &v)
{
    return std::sqrt(lengthSquared(v));
}

inline Vector3D cross(const Vector3D &a, const Vector3D &b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

// 计算点 p 相对于平面 ABC 的有向侧向值
inline double signedPlaneSide(
    const Point3D &p,
    const Point3D &a,
    const Point3D &b,
    const Point3D &c)
{
    Vector3D n = cross(b - a, c - a);
    return dot(p - a, n);
}

// 判断三角形 DEF 是否完全位于三角形 ABC 的同一侧
inline bool triangleStrictlyOnOneSide(
    const Point3D &a,
    const Point3D &b,
    const Point3D &c,
    const Point3D &d,
    const Point3D &e,
    const Point3D &f)
{
    double sd = signedPlaneSide(d, a, b, c);
    double se = signedPlaneSide(e, a, b, c);
    double sf = signedPlaneSide(f, a, b, c);

    bool allPositive =
        sd > 0.0 && se > 0.0 && sf > 0.0;

    bool allNegative =
        sd < 0.0 && se < 0.0 && sf < 0.0;

    return allPositive || allNegative;
}