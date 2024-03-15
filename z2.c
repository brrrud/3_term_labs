#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
double eps0 = 0.00000001;
//добавлена реализация atof и atoi 
// теперь сравнение на кратность через %
// atoi -> my_atoi
int find_root(double a, double b, double c, double* x1, double* x2);
int check_cnt_argv(char* argv, double* znach);
int is_triangle(int num1, int num2, int num3);
void printer(int ind, int flag, double x1, double x2);
int check_digit(char* str);

double my_atof(char* num){
    int sign = 1;
    int num_out = 0;
    int flag = 0;
    int power = 0;
    if(num[0] == '-'){
        sign = -1;
        num++;
    }
    while(*num!='\0'){
        if(flag){
            power++;
        }
        if(*num == '.'){
            num++;
            flag = 1;
        }
        else{
            num_out = num_out*10+(*num - '0');
            num++;
        }
    }
    return sign*num_out / pow(10, power);
}

int my_atoi(int* num_out, char* num){
    *num_out = 0;
    unsigned deg = 1;
    for(int i = strlen(num) - 1; i >= 0; --i){
        *num_out += deg*(num[i]-'0');
        deg *= 10;
    }
    return 0;
}

double my_atof(char* num){
    int sign = 1;
    int num_out = 0;
    int flag = 0;
    int power = 0;
    if(num[0] == '-'){
        sign = -1;
        num++;
    }
    while(*num!='\0'){
        if(flag){
            power++;
        }
        if(*num == '.'){
            num++;
            flag = 1;
        }
        else{
            num_out = num_out*10+(*num - '0');
            num++;
        }
    }
    return sign*num_out / pow(10, power);
}

int main(int argc, char* argv[]){
    double eps = 0.000000001;
    if(argc < 4){
        printf("incorrect input");
        return -1;
    }
    if(argv[1][0] != '-' && argv[1][0] != '/'){
        printf("incorrect flag");
        return -1;
    }
    if(!isalpha(argv[1][1])){
        printf("incorrect flag");
        return -1;
    }
    if(argv[1][1] == 'q'){
        if(argc != 5){
            printf("just 3 nums!!!");
            return -2;
        }
        double a = 0.0;
        double b = 0.0;
        double c = 0.0;
        if(check_cnt_argv(argv[2], &a) != 0 || check_cnt_argv(argv[3], &b) != 0 || check_cnt_argv(argv[4], &c) != 0){
            printf("incorrect nums");
            return -3;
        }
        //printf("При коэффициентах: а = %lf, b = %lf, c = %lf возможны случаи:\n", a, b, c);
        //printf("1.abc 2.acb 3.bca 4.bac 5.cba 6.cab\n");
        double x1, x2;
        int flag;
        flag = find_root(a,  b,  c, &x1, &x2);
        printf("%lf %lf %lf\n", a, b, c);
        printer(1, flag, x1, x2);
        // flag = find_root(a,  c,  b, &x1, &x2);
        // printer(2, flag, &x1, &x2);
        // flag = find_root(b,  c,  a, &x1, &x2);
        // printer(3, flag, &x1, &x2);
        // flag = find_root(b,  a,  c, &x1, &x2);
        // printer(4, flag, &x1, &x2);
        // flag = find_root(c,  b,  a, &x1, &x2);
        // printer(5, flag, &x1, &x2);
        // flag = find_root(c,  a,  b, &x1, &x2);
        //printer(6, flag, &x1, &x2);
    }
    if(argv[1][1] == 'm'){
        if(argc != 4){
            printf("just 2 nums!!!");
            return -2;
        }

        if(check_digit(argv[2]) == -1){
            printf("Целое число!");
            return -1;
        }
        int num1;
        my_atoi(&num1, argv[2]);

        if(check_digit(argv[3]) == -1){
            printf("Целое число!");
            return -1;
        }
        int num2;
        my_atoi(&num2, argv[3]);
        if(num1 == 0 || num2 == 0){
            printf("Zero! sos!!!");
            return -3;
        }
        // double res = num1/num2;
        // if(((double)num1/num2 - floor(num1/num2)) < eps){
        //     printf("кратно");
        //     return 0;
        // }
        if(num1 % num2 == 0){
            printf("кратно\n");
            return 0;
        }
        else{
            printf("не кратно\n");
            return 1;
        }

    }
    if(argv[1][1] == 't'){
        int n1, n2, n3, num1, num2, num3;
        if(argc != 5){
            printf("Неверное число аргументов");
            return -1;
        }
        n1 = check_digit(argv[2]);
        n2 = check_digit(argv[3]);
        n3 = check_digit(argv[4]);
        if(n1 == -1 || n2 == -1 || n3 == -1){
            printf("Некорректные значения");
            return -1;
        }

        my_atoi(&num1, argv[2]);
        my_atoi(&num2, argv[3]);
        my_atoi(&num2, argv[4]);
        //printf("%d %d %d", num1, num2, num3);   
        if(is_triangle(num1, num2, num3) == 1) printf("Yea");
        else{
            printf("No");
        }
    }
}

int is_triangle(int num1, int num2, int num3){ 
    if(num2 + num1 > num3 && num2 + num3 > num1 && num1 + num3 > num2){
        double num_01 = pow(num2, 2);
        double num_02 = pow(num1, 2);
        double num_03 = pow(num3, 2);
        if(num_01+num_02-num_03<eps0 || num_01+num_03-num_02<eps0 || num_03+num_02-num_01<eps0){
            return 1;
        }
    }
    else return -1;
}
int check_digit(char* str){
    unsigned i = 0;
    while(1){
        if(str[i] == '\0') break;
        if(!isdigit(str[i])){
            return -1;
        }
        i++;
    }
    return 0;
}
int find_root(double a, double b, double c, double* x1, double* x2){
    double eps = 0.0000001;
    double d; 
    d = (b * b) - (4 * a * c);
    double ed = -1.0;
    if(d > 0.0 && d > eps) {
        *x1 = ((-1*b) + sqrt(d)) / (2 * a);
        *x2 = ((-1*b) - sqrt(d)) / (2 * a);
        return 0;
    }
    if(d < eps) { 
        *x1 = (-b / (2 * a));
        *x2 = *x1;
        return 1;
    }
    if (d < 0.0){
        return -1;
    }
}

int check_cnt_argv(char* argv, double* znach){
    int i = 0;
    int count_point = 0;
    int count_minus = 0;
    while(1){
        if(argv[i] == '\0') break;
        if(!isdigit(argv[i]) && (argv[i] != '.') && argv[i] != '-'){
            return -2;
        }
        if(argv[i] == '.'){
            count_point++;
        }
        if(argv[i] == '-'){
            count_minus++;
        }
        i++;
    }
    if((count_minus == 1 && argv[0] != '-')|| count_minus > 1) {
        return -1;
    }
    if(count_point <= 1 && argv[0] != '.' ){
        *znach = atof(argv);
        return 0;
    }
    return -1;
}

void printer(int ind, int flag, double x1, double x2){
    if(flag == -1){
        printf("%d При таких коэффициентах нет действительных решений\n", ind);
    }
    if(flag == 1){
        printf("%d При таких коэффициентах единственный корень:\n x = %lf",ind, x1);
    }
    if(flag == 0){
        printf("%d При таких коэффициентах два корня:\n x = %lf и x = %lf\n",ind, x1, x2);
    }
}

