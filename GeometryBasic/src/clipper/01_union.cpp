
#include <iostream>
#include "clipper2/clipper.h"

using namespace Clipper2Lib;

// 计算闭合多边形的周长
double CalculatePerimeter(const Path64 &path)
{
    double perimeter = 0.0;

    if (path.size() < 2)
        return perimeter;

    for (size_t i = 0; i < path.size(); ++i)
    {
        const auto &p1 = path[i];
        const auto &p2 = path[(i + 1) % path.size()];

        double dx = static_cast<double>(p2.x - p1.x);
        double dy = static_cast<double>(p2.y - p1.y);

        perimeter += std::sqrt(dx * dx + dy * dy);
    }

    return perimeter;
}

int main()
{
    // 创建一个 100 x 100 的正方形
    Path64 rect = {
        {0, 0},
        {100, 0},
        {100, 100},
        {0, 100}};

    // 1. 计算面积
    double area = Area(rect);
    std::cout << "Area: " << area << '\n';

    // 2. 计算周长
    double perimeter = CalculatePerimeter(rect);
    std::cout << "Perimeter: " << perimeter << '\n';

    // 3. 计算包围盒
    Rect64 bounds = GetBounds(rect);

    std::cout << "Bounds:\n";
    std::cout << "left   = " << bounds.left << '\n';
    std::cout << "top    = " << bounds.top << '\n';
    std::cout << "right  = " << bounds.right << '\n';
    std::cout << "bottom = " << bounds.bottom << '\n';

    // 4. 判断点与多边形的关系
    Point64 p1(50, 50);
    Point64 p2(150, 50);
    Point64 p3(0, 50);

    auto r1 = PointInPolygon(p1, rect);
    auto r2 = PointInPolygon(p2, rect);
    auto r3 = PointInPolygon(p3, rect);

    std::cout << "Point (50,50): " << static_cast<int>(r1) << '\n';
    std::cout << "Point (150,50): " << static_cast<int>(r2) << '\n';
    std::cout << "Point (0,50): " << static_cast<int>(r3) << '\n';

    return 0;
}
