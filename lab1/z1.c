#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

int flag_h(unsigned *num); // вывод всех кратных чисел данному до 100
int flag_p(unsigned *num); // определить, является ли введённое число простым или составным
int flag_e(unsigned *num); //вывести в консоль числа от 1 до 10, возводя их во все степени от 1 до заданного числа
int flag_a(unsigned *num, unsigned *res); //суммирует все числа от 1 до указанного числа включительно
int flag_f(unsigned *num, unsigned *res); //вычисляет факториал введенного числа

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("incorrect input");
        return -1;
    }
    unsigned num;
    for (unsigned i = 0; i < strlen(argv[1]); ++i) {
        if (!isdigit(argv[1][i])) {
            printf("incorrect number");
            return -1;
        }
    }
    num = atoi(argv[1]);
    if (strlen(argv[2]) != 2) {
        printf("incorrect flag");
        return -1;
    }
    if (argv[2][0] != '-' && argv[2][0] != '/') {
        printf("incorrect flag");
        return -1;
    }
    if (!isalpha(argv[2][1])) {
        printf("incorrect flag");
        return -1;
    }
    if (argv[2][1] == 'h') {
        flag_h(&num);
    }
    if (argv[2][1] == 'p') {
        if (flag_p(&num) == 0) {
            printf("не простое");
            return 0;
        }
        printf("простое");
    }
    if (argv[2][1] == 's') {
        unsigned i = 0;
        while (1) {
            if (argv[1][i] == '\0') break;
            printf("%c ", argv[1][i]);
            i++;
        }
    }
    if (argv[2][1] == 'e') {
        if (num >= 10) {
            printf("Допустимы числа от 1 до 10 для этого флага");
            return -1;
        }
        flag_e(&num);

    }
    if (argv[2][1] == 'a') {
        unsigned res = 0;
        flag_a(&num, &res);
        printf("%u", res);
    }
    if (argv[2][1] == 'f') {
        unsigned res = 1;
        flag_f(&num, &res);
        printf("%u", res);
    }
    return 0;
}


int flag_h(unsigned *num) {
    if (*num == 0) return -2;
    if (*num > 100) return -1;
    for (int i = 1; i < (100 / (*num)); ++i) {
        printf("%d ", *num * i);
    }
    return 0;
}

int flag_p(unsigned *num) {
    if ((*num) < 3) return 1;
    for (unsigned i = 2; i < (*num); ++i) {
        if ((*num) % i == 0) return 0;
    }
    return 1;
}

int flag_e(unsigned *num) {
    for (int i = 1; i <= 10; ++i) {
        printf("%d ", (int) pow(i, *num));
    }
    return 0;
}

int flag_a(unsigned *num, unsigned *res) {
    for (unsigned i = 0; i <= *num; ++i) {
        (*res) += i;
    }
    return 0;
}

int flag_f(unsigned *num, unsigned *res) {
    for (*res = 1; *num > 1; (*res) *= ((*num)--));
    return 0;
}