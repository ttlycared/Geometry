#pragma once

#include "Point3D.h"

struct Vector3D
{
    double x;
    double y;
    double z;
};

// 两点相减，得到向量
inline Vector3D operator-(const Point3D &a, const Point3D &b)
{
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z};
}

// 向量相加
inline Vector3D operator+(const Vector3D &a, const Vector3D &b)
{
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z};
}

// 向量数乘
inline Vector3D operator*(const Vector3D &v, double s)
{
    return {
        v.x * s,
        v.y * s,
        v.z * s};
}