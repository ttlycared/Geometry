#pragma once

#include "Point2D.h"

struct Vector2D
{
    double x;
    double y;
};

inline Vector2D operator-(const Point2D &a, const Point2D &b)
{
    return {
        a.x - b.x,
        a.y - b.y};
}