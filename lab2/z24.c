#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>

double eps = 0.00000001;

double geom(int n, ...) {
    double res = 1;
    va_list num;
    va_start(num, n);
    for (int i = 0; i < n; i++) {
        res *= va_arg(num,
        double);
    }
    va_end(num);
    if (res < -eps && n & 1 == 0) return -1;

    return pow(res, 1.0 / n);
}


double fastpow(double num, int n) {

    if (fabs(num) < eps) {
        return 0.0;
    }
    if (n == 0) {
        return 1.0;
    }
    if (n == 1) {
        return num;
    }
    if (n % 2 == 0) {
        return fastpow(num * num, n / 2);
    }
    return num * fastpow(num, n - 1);
}


int main() {
    printf("%lf\n", geom(4, (double) 1.0, (double) 1.0, (double) 1.0, (double) -1.0));
    double num = 1.0;
    double deg = 2.0;
    if (fabs(num) < eps) {
        if (deg >= 0) {
            printf("%lf\n", fastpow(num, deg));
        }
        if (deg < 0) {
            printf("Деление на ноль\n");
            return 0;
        }
    }
    if (num > eps) {
        if (deg >= 0) {
            printf("%lf\n", fastpow(num, deg));
        }
        if (deg < 0) {
            double result = fastpow(num, abs(deg));
            printf("%lf\n", 1.0 / result);
        }
    }
    if (num < eps && fabs(num) > eps) {
        if (deg >= 0) {
            printf("%lf\n", fastpow(fabs(num), deg));
        }
        if (deg < 0) {
            double result = fastpow(fabs(num), abs(deg));
            printf("%lf\n", -1.0 / result);
        }
    }

    return 0;

}
