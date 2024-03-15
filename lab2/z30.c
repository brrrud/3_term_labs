#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <limits.h>

#define EPS 0.0001

typedef enum standart_problems {
    INPUT_ERROR,
    MEM_PROBLEM,
    OK
} standart_problems;

int check_finite(double dec, int base) {
    if (base == 10)
        return 1;
    int i = 0;
    double fract = dec - (int) dec;
    while (fract > EPS) {
        fract *= base;
        if (fract >= 1)
            fract -= 1;

        i++;
        if (i > log(INT_MAX) / log(base) + 1)
            return 0;
    }
    return 1;
}

double *has_finite_representation(int base, int count, int *finite_count, ...) {
    va_list fact;
    va_start(fact, finite_count);
    double *finite_num = (double *) malloc(sizeof(double) * count);
    if (finite_num == NULL) {
        return NULL;
    }
    int index = 0;
    double x;
    for (int i = 0; i < count; i++) {
        x = va_arg(fact,
        double);
        if (check_finite(x, base)) {
            finite_num[index] = x;
            index++;
        }
    }
    va_end(fact);
    *finite_count = index;
    return finite_num;
}

int main() {
    int finite_count = 0;
    unsigned int base;
    scanf("%d", &base);
    if (base <= 1 || base > 36) {
        return INPUT_ERROR;
    }

    double *result = has_finite_representation(base, 2, &finite_count, 0.625, 0.1);
    if (result == NULL) {
        return MEM_PROBLEM;
    }
    for (int i = 0; i < finite_count; i++) {
        printf("%lf :  %d\n", result[i], base);
    }
    free(result);
    return OK;
}