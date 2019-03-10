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

#ifdef __cplusplus
#include <cstdint>
#include <ostream>
#else
#include <stdint.h>
#endif

struct Ratio
{
    intmax_t numerator, denominator;

#ifdef __cplusplus
    inline double value() const
    {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    friend inline std::ostream& operator<<(std::ostream& os, const Ratio& ratio)
    {
        os << ratio.numerator << "/" << ratio.denominator;
        return os;
    }
#endif
};

#ifdef __cplusplus
extern "C"
#else
struct
#endif
Ratio approxRatio(double num, intmax_t max);

#endif //APPROXIMATERATIO_HPP
