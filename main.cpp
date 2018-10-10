#include <iostream>
#include <cmath>
#include "ApproximateRatio.hpp"

int main()
{
    const double num = 1234.1234;
    Ratio ratio = approxRatio(num, 2500);
    std::cout.precision(12);
    std::cout << num << " \u2248 " << ratio << " = " << ratio.value() << std::endl;
    return 0;
}