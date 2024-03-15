#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printer(int len, int* arr);
void finder(int MAX_SIZE, int* arr, int* maxi, int* mini);
int random_array(int n, int m, int len, int** arr);

int main(int argc, char* argv) {
    int MAX_SIZE = 10;
    int* arr;
    int flag;
    int maxi, mini;
    int left, right;
    char c;
    if(!(scanf("%d%d%c", &left, &right, &c) == 3 && c == '\n') ){
        printf("Введите два целых числа\n");
        return -1;
    }
    if(right < left){
            printf("Неправильные границы\n");
            return -1;
        }
    flag = random_array(left, right, MAX_SIZE, &arr);
    if(flag == -1){
        printf("Ошибка выделения памяти");
        return -1;
    }
    printer(MAX_SIZE, arr);
    finder(MAX_SIZE, arr, &maxi, &mini);
    printf("Максимальный элемент %d\n", maxi);
    printf("Минимальный элемент %d\n", mini);
    for(int i = 0; i < MAX_SIZE - 1; ++i){
        if(arr[i] == maxi){
            arr[i] = mini;
            continue;
        }
        if(arr[i] == mini){
            arr[i] = maxi;
        }
    }
    printer(MAX_SIZE, arr);
    free(arr);
    return 0;
}

void printer(int len, int* arr) {
    for(int i = 0; i < len - 1; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void finder(int MAX_SIZE, int* arr, int* maxi, int* mini){
    *maxi = arr[0];
    *mini = arr[0];
    for(int i = 1; i < MAX_SIZE; ++i){
        if(*maxi < arr[i]){
            *maxi = arr[i];
        }
        if(*mini > arr[i]){
            *mini = arr[i];
        }
    }

}
int random_array(int n, int m, int len, int** arr) { 
    *arr =(int*)malloc(len * sizeof(int));
    if(arr == NULL){
        return -1;
    }
    if(n < m){
        return -1;
    }
    for(int i = 0; i < len - 1; ++i){
        (*arr)[i] = n + rand()%(m + 1 - n);
    }
    return 0;
}
