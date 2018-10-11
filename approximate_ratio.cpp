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

#include "approximate_ratio.h"

#ifdef __cplusplus
extern "C"
#endif
Ratio approxRatio(double num, const intmax_t max)
{
    const bool isNegative = num < 0.0;
    if(isNegative)
        num = -num;

    if(num > 1.0)
    {
        Ratio best = approxRatio(1.0 / num, max);
        if(isNegative)
            return {-best.denominator, best.numerator};
        return {best.denominator, best.numerator};
    }

    uintmax_t lowerNumerator = 0;
    uintmax_t lowerDenominator = 1;
    uintmax_t upperNumerator = 1;
    uintmax_t upperDenominator = 1;
    while(lowerDenominator <= max && upperDenominator <= max)
    {
        if(num > static_cast<double>(lowerNumerator + upperNumerator) / static_cast<double>(lowerDenominator + upperDenominator))
        {
            lowerNumerator = lowerNumerator + upperNumerator;
            lowerDenominator = lowerDenominator + upperDenominator;
        }
        else
        {
            upperNumerator = lowerNumerator + upperNumerator;
            upperDenominator = lowerDenominator + upperDenominator;
        }
    }

    if(lowerDenominator > max)
    {
        if(isNegative)
            return {-static_cast<intmax_t>(upperNumerator), static_cast<intmax_t>(upperDenominator)};
        return {static_cast<intmax_t>(upperNumerator), static_cast<intmax_t>(upperDenominator)};
    }
    if(isNegative)
        return {-static_cast<intmax_t>(lowerNumerator), static_cast<intmax_t>(lowerDenominator)};
    return {static_cast<intmax_t>(lowerNumerator), static_cast<intmax_t>(lowerDenominator)};
}
