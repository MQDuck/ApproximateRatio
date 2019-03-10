#include <iostream>
#include <cmath>
#include <chrono>
#include "approximate_ratio.h"

int main()
{
    const double num = sqrt(2);
    //const intmax_t max = 9000000000000000000;
    const intmax_t max = 10000;

    auto begin = std::chrono::steady_clock::now();
    Ratio ratio = approxRatio(num, max);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    std::cout.precision(12);
    std::cout << num << " \u2248 " << ratio << " = " << ratio.value() << "\n"
              << "duration: " << duration << std::endl;
    return 0;
}
