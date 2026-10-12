
#include <iostream>
#include <string>
#include "clipper2/clipper.h"

using namespace Clipper2Lib;

// 打印多边形集合
void PrintPaths(const std::string &name, const Paths64 &paths)
{
    std::cout << "\n========== " << name << " ==========\n";

    std::cout << "Number of polygons: "
              << paths.size() << '\n';

    for (size_t i = 0; i < paths.size(); ++i)
    {
        std::cout << "Polygon " << i << ":\n";

        for (const auto &p : paths[i])
        {
            std::cout << "(" << p.x << ", "
                      << p.y << ")\n";
        }

        std::cout << "Area: "
                  << Area(paths[i]) << '\n';
    }
}

int main()
{
    // 矩形 A：范围 [0,100] x [0,100]
    Path64 rect1 = {
        {0, 0},
        {100, 0},
        {100, 100},
        {0, 100}};

    // 矩形 B：范围 [50,150] x [50,150]
    Path64 rect2 = {
        {50, 50},
        {150, 50},
        {150, 150},
        {50, 150}};

    Paths64 subjects = {rect1};
    Paths64 clips = {rect2};

    // 1. 并集
    Paths64 union_result =
        Union(subjects, clips, FillRule::NonZero);

    PrintPaths("Union", union_result);

    // 2. 交集
    Paths64 intersect_result =
        Intersect(subjects, clips, FillRule::NonZero);

    PrintPaths("Intersect", intersect_result);

    // 3. 差集：A - B
    Paths64 difference_result =
        Difference(subjects, clips, FillRule::NonZero);

    PrintPaths("Difference A - B", difference_result);

    // 4. 异或：只保留不重叠的区域
    Paths64 xor_result =
        Xor(subjects, clips, FillRule::NonZero);

    PrintPaths("Xor", xor_result);

    return 0;
}
