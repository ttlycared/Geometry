#include <iostream>
#include <vector>

#include "geometry/ConvexHull.h"

int main()
{
    std::vector<Point2D> points = {
        {0, 0},
        {4, 0},
        {5, 2},
        {3, 5},
        {0, 4},
        {2, 2},
        {2, 1}};

    std::vector<Point2D> hull = convexHull(points);

    std::cout << "Convex Hull:\n";

    for (const auto &p : hull)
    {
        std::cout << "("
                  << p.x << ", "
                  << p.y << ")\n";
    }

    return 0;
}