#include <iostream>

#include "geometry/SegmentIntersection.h"

void printResult(const IntersectionResult &result)
{
    if (result.type == IntersectionType::None)
    {
        std::cout << "None\n";
    }
    else if (result.type == IntersectionType::Point)
    {
        std::cout << "Point: "
                  << result.point.x << ", "
                  << result.point.y
                  << "\n";
    }
    else if (result.type == IntersectionType::Overlap)
    {
        std::cout << "Overlap: "
                  << result.start.x << ", "
                  << result.start.y
                  << " -> "
                  << result.end.x << ", "
                  << result.end.y
                  << "\n";
    }
}

int main()
{
    Point2D A{0, 0};
    Point2D B{10, 10};

    Point2D C{0, 20};
    Point2D D{10, 20};

    IntersectionResult result =
        segmentIntersection(A, B, C, D);

    printResult(result);

    return 0;
}