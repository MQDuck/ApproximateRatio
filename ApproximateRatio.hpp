/* Copyright 2018 Jeffrey Thomas Piercy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef APPROXIMATERATIO_HPP
#define APPROXIMATERATIO_HPP


#include <limits>
#include <cmath>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <cstdlib>
#include <cstring>

struct Ratio
{
    intmax_t numerator, denominator;

    inline double value() const
    {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    friend inline std::ostream& operator<<(std::ostream& os, const Ratio ratio)
    {
        os << ratio.numerator << "/" << ratio.denominator;
        return os;
    }
};

void approxRatioThread(double num, const intmax_t min, const intmax_t max, Ratio& best, bool printProgress)
{
    const bool isNegative = num < 0.0;
    if(isNegative)
        num = -num;

    if(num > 1.0)
    {
        approxRatioThread(1.0 / num, min, max, best, printProgress);
        if(isNegative)
            best = {-best.denominator, best.numerator};
        else
            best = {best.denominator, best.numerator};
    }

    double bestError = std::numeric_limits<double>::infinity();
    double bestNumerator = 0;
    intmax_t bestDenominator = 0;
    for(intmax_t denom = min; denom < max; ++denom) // NOLINT(cert-flp30-c)
    {
        const double numer = std::round(static_cast<double>(denom) * num);
        const double error = std::abs(num - (numer / static_cast<double>(denom)));
        if(error < bestError)
        {
            bestError = error;
            bestNumerator = numer;
            bestDenominator = denom;
        }
    }

    if(isNegative)
        best.numerator = static_cast<intmax_t>(-bestNumerator);
    else
        best.numerator = static_cast<intmax_t>(bestNumerator);
    best.denominator = bestDenominator;
}

Ratio approxRatio(double num, const intmax_t max)
{
    static const int numThreads = std::thread::hardware_concurrency();

    intmax_t quarter = max / numThreads;
    intmax_t min = 1;
    Ratio bests[numThreads];
    std::vector<std::thread> threads;
    for(int i = 0; i < numThreads - 1; ++i)
    {
        threads.emplace_back(approxRatioThread, num, min, min + quarter, std::ref(bests[i]), false);
        min += quarter;
    }
    threads.emplace_back(approxRatioThread, num, min, max, std::ref(bests[numThreads-1]), true);

    for(auto& thread : threads)
        thread.join();
    int best = 0;
    for(int i = 1; i < numThreads; ++i)
        if(std::abs(num - bests[i].value()) < std::abs(num - bests[best].value()))
            best = i;

    return bests[best];
}


#endif //APPROXIMATERATIO_HPP
