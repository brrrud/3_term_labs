#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdarg.h>

char *all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int correct(char **str1, char **str2);

void cycle_shift(char **str, int n);

int correct_launch(char **str1, char **str2);

//в функция попадают два числа, меньшее по длине регулируем нулями до длины большего
// складываем поразрядно, например пусть str1[i]==A тогда i+str2[i]==
int calculation(int r, int n, ...) {
    va_list ap;
    char *value;
    if (n == 1) {
        return -1;
    }
    va_start(ap, n);
    for (int i = 0; i < n; ++i) {
        value = va_arg(ap,
        char*);

        printf("%s\n", value);
    }
    va_end(ap);
}

int sum_res(char *s1, char *s2, int notation) {
    int flag = 0;
    int res_add = 0;
    int tmp;
    char *sum = (char *) malloc(sizeof(char) * (strlen(s1) + 1));
    if (sum == NULL) {
        return -1;
    }
    for (int i = strlen(s1) - 1; i >= 0; --i) {
        int tmp_s1 = (s1[i] > 47 && s1[i] < 58) ? s1[i] - '0' : s1[i] - 55;
        int tmp_s2 = (s2[i] > 47 && s2[i] < 58) ? s2[i] - '0' : s2[i] - 55;
        res_add = tmp_s1 + tmp_s2 + flag;
        if (res_add >= notation) {
            tmp = res_add - notation;
            flag++;
            sum[i] = all[tmp];
        } else {

        }
    }
}

int sum_res1(char **num, char **ans, int *count, int notation) {
    if (*count == 0) {
        *ans = (char *) malloc(sizeof(char) * strlen(*num) + 1);
        if (ans == NULL) {
            return 1;
        }
        memcpy(*ans, *num, sizeof(char) * strlen(*num) + 1);
    } else {
        int res = 0;
        correct_launch(num, ans);
        int tmp;
        int flag = 0;
        for (int i = strlen(*num); i >= 0; --i) {
            int tmp_num = ((*num)[i] > 47 && (*num)[i] < 58) ? (*num)[i] - '0' : (*num)[i] - 55;
            int tmp_ans = ((*ans)[i] > 47 && (*ans)[i] < 58) ? (*ans)[i] - '0' : (*ans)[i] - 55;
            res = tmp_ans + tmp_num + flag;
            if (res >= notation) {
                tmp = res - notation;
                flag++;
                (*ans)[i] = all[tmp];
            } else {
                flag = 0;
                (*ans)[i] = all[res];
            }
        }
        if (flag > 0) {
            (*ans)[0] = '1';
        } else {
            (*ans)[0] = '0';
        }

    }
    printf("%s", *ans);

    return 0;
}

int main() {

    //printf("%d\n", tmp);
    //printf("%d",tmp_s1);
    int count = 2;
    char *ans = "A13A4";
    char *num = "187AB";
    sum_res1(&ans, &num, &count, 12);


}

void cycle_shift(char **str, int n) {
    int tmp = (*str)[n - 1];
    for (int i = n - 1; i > 0; --i) {
        (*str)[i] = (*str)[i - 1];
    }
    (*str)[0] = tmp;
}

int correct_launch(char **str1, char **str2) {
    if (strlen(*str1) > strlen(*str2)) {
        if (correct(str2, str1) != 0) {
            return -1;
        }
    } else if (strlen(*str2) > strlen(*str1)) {
        if (correct(str1, str2) != 0) {
            return -1;
        }
    } else if (strlen(*str2) == strlen(*str1)) {
        return -1;
    }
    return 0;
}

int correct(char **str1, char **str2) {//len(str1) < len(str2)
    int min_tmp = strlen(*str1);
    int max_tmp = strlen(*str2);
    int k = 0;
    *str1 = realloc(*str1, sizeof(char) * max_tmp);
    if (*str1 == NULL) {
        return -1;
    }
    for (int i = min_tmp; i < max_tmp; ++i) {
        (*str1)[i] = '0';
        k++;
    }
    (*str1)[max_tmp] = '\0';
    for (int i = 0; i < max_tmp - min_tmp; ++i) {
        cycle_shift(str1, max_tmp);
    }
    printf("%s\n", *str1);
    return 0;

}

int right_realloc(char **str, int new_size) {
    char *temp = (char *) realloc(*str, sizeof(char) * new_size);
    if (!temp) {
        free(*str);
        *str = NULL;
        return -1;
    }
    *str = temp;
    return 0;
}

