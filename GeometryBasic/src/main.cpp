
#include <iostream>
#include <cmath>

double orientation(
    double ax, double ay,
    double bx, double by,
    double cx, double cy)
{
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

int main()
{
    // A、B、C 的数学位置共线
    double scales[] = {1.0, 1000.0, 1000000.0};

    for (double s : scales)
    {
        double cross = orientation(
            0.0, 0.0,
            1.0 * s, 1.0 * s,
            2.0 * s, 2.0 * s);

        std::cout << "scale = " << s
                  << ", cross = " << cross
                  << ", cross == 0: "
                  << (cross == 0.0)
                  << '\n';
    }

    return 0;
}
