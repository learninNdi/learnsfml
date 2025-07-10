#include <iostream>
#include <cmath>

int main()
{
    int deg = 180;
    double Pi = 3.1415926535897932384626433832795;
    // std::cout << cos(deg * 3.14159 / 180) << std::endl;
    double epsilon = 1e-9;
    double result = cos(deg * Pi / 180);
    // result = cos(Pi);

    if (result > 0 && result < epsilon)
        std::cout << 0 << std::endl;
    else
        std::cout << result << std::endl;

    // std::cout << result << std::endl;

    return 0;
}