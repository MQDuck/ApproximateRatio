#include <iostream>
#include <cmath>
#include "ApproximateRatio.hpp"

int main()
{
    const double num = 1234.1234;

    auto begin = std::chrono::steady_clock::now();
    Ratio ratio = approxRatio(num, 2500000000);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    auto begin_o = std::chrono::steady_clock::now();
    Ratio ratio_o = approxRatio_o(num, 2500000000);
    auto end_o = std::chrono::steady_clock::now();
    auto duration_o = std::chrono::duration_cast<std::chrono::nanoseconds>(end_o - begin_o).count();

    std::cout.precision(12);
    std::cout << num << " \u2248 " << ratio << " = " << ratio.value() << "\n"
              << num << " \u2248 " << ratio_o << " = " << ratio_o.value() << "\n"
              << "duration: " << duration << "\nduration_o: " << duration_o << "\n"
              << "Optimized solution takes " << (double)duration_o / duration << " times as long." << std::endl;
    return 0;
}