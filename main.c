#include <stdint.h>
#include "stdio.h"
#include "approximate_ratio.h"

#define NUM 51.5488361

void main()
{
    struct Ratio ratio = approxRatio(NUM, 1000);
    printf(
            "%f \u2248 %li/%li = %lf\n",
            NUM,
            ratio.numerator,
            ratio.denominator,
            (double)ratio.numerator/(double)ratio.denominator
    );
}