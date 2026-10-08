#pragma once

#include "Point2D.h"

enum class IntersectionType
{
    None,
    Point,
    Overlap
};

struct IntersectionResult
{
    IntersectionType type;

    // Point 情况
    Point2D point;

    // Overlap 情况
    Point2D start;
    Point2D end;
};