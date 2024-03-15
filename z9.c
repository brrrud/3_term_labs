#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int get_string_from_stdin(int* len, char** string);
int string_to_num(char** string_num, int* num);
int n_to_dec(int notation, char** string_num);
int check(char** all, char** string, int notation);
int dec_to_n(int notation, int num, char** ans_num);
void reverse(char** ans_num);

int main() {
    char* all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";         
    int notation, num, len, res, k;
    int flag_dec = 0;
    char* string_num;
    char c;
    int maximum = -10000000;
    int dec_max;
    if((!scanf("%d%c", &notation, &c) == 2 && c == '\n') || (notation < 2 || notation > 36)){
        printf("Система счисления в диапазоне: [2;36]");
        return -2;
    }
    while(1) {
        k = get_string_from_stdin(&len, &string_num);
        if(k == -1){
            printf("Возникла ошибка при работе с памятью");
            return -1;
        }
        if(strcmp(string_num, "Stop") == 0){
            free(string_num);
            break;
        }
        int check_flag = check(&all, &string_num, notation);
        if(check_flag == -1){
            printf("Некорректный ввод\n");
            free(string_num);
            continue;
        }
        else if(check_flag == 1){
            int sz = strlen(string_num);
            memmove(string_num, string_num + 1, sz - 1);
            string_num[sz - 1] = 0;
        }
        int t = n_to_dec(notation, &string_num);
        if(t > maximum){
            maximum = t;
        }
        free(string_num); 
    } 
    printf("%d\n", maximum);
    char* ans_num;

    flag_dec = dec_to_n(9, maximum, &ans_num);
    if(flag_dec == -1){
        printf("Возникла ошибка при работе с памятью");
        return -1;
    }
    printf("Максимум с основанием 9: %s\n", ans_num);
    free(ans_num);

    flag_dec = dec_to_n(18, maximum, &ans_num);
    if(flag_dec == -1){
        printf("Возникла ошибка при работе с памятью");
        return -1;
    }
    printf("Максимум с основанием 18: %s\n", ans_num);
    free(ans_num);

    flag_dec = dec_to_n(27, maximum, &ans_num);
    if(flag_dec == -1){
        printf("Возникла ошибка при работе с памятью");
        return -1;
    }
    printf("Максимум с основанием 27: %s\n", ans_num);
    free(ans_num);

    flag_dec = dec_to_n(36, maximum, &ans_num);
    if(flag_dec == -1){
        printf("Возникла ошибка при работе с памятью");
        return -1;
    }
    printf("Максимум с основанием 36: %s\n", ans_num);
    free(ans_num);
}

int get_string_from_stdin(int* len, char** string){
    *len = 0; 
    int capacity = 1; 
    (*string) = (char*)malloc(capacity*sizeof(char));
    if(string == NULL) return -1; 
    char c = getchar(); 
    while (c != '\n') {
        (*string)[(*len)++] = c; 
        if (*len >= capacity) {
            capacity *= 2; 
            *string = (char*)realloc(*string, capacity * sizeof(char)); 
            if(string == NULL) return -1;
        }
        c = getchar();        
    }
    (*string)[*len] = '\0';
    return 0;
}

int check(char** all, char** string, int notation){
    int minus_cmp = 0;
    for(int i = 0; i <= strlen(*string) - 1; ++i){
        if(!isdigit((*string)[i]) && !isalpha((*string)[i]) && (*string)[i] != '-') return -1;
        if((*string)[i] == '-') minus_cmp++;
        if(((*string)[i] > (*all)[notation - 1]) && (*string)[i] != '-') return -1;
        
    }      
    if(minus_cmp > 1) return -1;
    else if(minus_cmp == 1 && (*string)[0] == '-') return 1;
    return 0;
}

int n_to_dec(int notation, char** string_num){
    int base = 1;
    int dec = 0;
    int length = strlen(*string_num);
    for(int i = length--; i >= 0; i--){
        if((*string_num)[i] >= '0' && (*string_num)[i] <= '9'){
            dec += ((*string_num)[i] - 48) * base;
            base *= notation;
        }
        if((*string_num)[i] >= 'A' && (*string_num)[i] <= 'Z'){
            dec += ((*string_num)[i] - 55) * base;
            base *= notation;
        }
    }
    return dec;
}

int dec_to_n(int base, int num, char** ans_num){
    int element;
    int i = 0;
    unsigned size = 10;
    (*ans_num) = (char*)malloc(size * sizeof(char));
    if(*ans_num == NULL){
        return -1;
    }
    if(num == 0) (*ans_num)[i++] = '0';
    while(num != 0){
        if(i >= size-1){
            size *= 2;
            (*ans_num) = realloc((*ans_num), size * sizeof(char));
            if(*ans_num == NULL){
                return -1;
            }
        }
        
        element = num % base + '0';
        if(element > '9') element += 7;
        (*ans_num)[i] = element;
        i++;
        num /= base;
    }
    (*ans_num)[i++] = '\0';
    reverse(ans_num);
    return 0;
}

void reverse(char** ans_num){
    for (int i = 0, j = strlen(*ans_num) - 1; i < j; i++, j--) {
        char z = (*ans_num)[i];
        (*ans_num)[i] = (*ans_num)[j];
        (*ans_num)[j] = z;
    }
}
