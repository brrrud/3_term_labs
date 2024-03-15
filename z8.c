#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int num_read(FILE* file, int array[]);

int flag_a(int array[], int len, int new_array[]);
int flag_b(int array[], int len, int new_array[]);
int flag_c(int array[], int len, int ind);
int flag_d(int array[], int len, int ind);
int flag_e(int array[], int len, int ind);
void printer(int array[], int len);

int main(int argc, char* argv[]){
    FILE* file;
    int array[128];
    file = fopen("text.txt", "r");
    if(file == NULL){
        printf("Ошибка открытия");
        return -1;
    }
    int len = num_read(file, array) - 1;
    fclose(file);

    int new_array[128];
    printer(array, len);

    if(strcmp(argv[1], "-a") == 0){
        int len_new_a = flag_a(array, len, new_array);
        printer(new_array, len_new_a);
    }
    else if(strcmp(argv[1], "-b") == 0){
        int len_new_b = flag_b(array, len, new_array);
        printer(new_array, len_new_b);
    }
    else if(strcmp(argv[1], "-c") == 0){
        int num;
        scanf("%d", &num);
        printf("%d\n", flag_c(array, len, num));
    }
    else if(strcmp(argv[1], "-d") == 0){
        int num;
        scanf("%d", &num);
        printf("%d\n", flag_d(array, len, num));
    }
    else if(strcmp(argv[1], "-e") == 0){
        int num;
        scanf("%d", &num);
        printf("%d\n", flag_e(array, len, num));
    }
    else{
        printf("некорректность флага\n");
    }
    return 0;    
}

int num_read(FILE* file, int array[]){
    char sym;
    int i = 0;
    int tab_cnt = 0;
    while (!feof(file))
    {
        fscanf(file, "%d", &(array)[i]/*array + i*/);
        i++;
    }
    return i;
}
int flag_a(int array[], int len, int new_array[]){
    int j = 0;
    for(int i = 0; i < len; i += 2){
        new_array[j] = array[i];
        j++;
    }
    return j;
}
int flag_b(int array[], int len, int new_array[]){
    int j = 0;
    for(int i = 0; i < len; i++){
        if(array[i] % 2 == 0){
            new_array[j] = array[i];
            j++;
        }
    }
    return j;
}
int flag_c(int array[], int len, int ind){
    int k = 0;
    int m = 0;
    for(int i = 0; i < len; i++){
        int tmp = abs(array[ind] - array[i]);
        if (tmp > m){
            m = tmp;
            k = i;
        }
    }
    return array[k];
}
int flag_d(int array[], int len, int ind){
    int sum = 0;
    for(int i = 0; i < ind; i++){
        sum += array[i];
    }
    return sum;
}

int flag_e(int array[], int len, int ind){
    int sum = 0;
    for(int i = 0; i < len; ++i){
        if(array[i]<array[ind]){
            sum+=array[i];
        }
    }
    return sum;
}
void printer(int array[], int len){
    for(int i = 0; i < len; ++i){
        printf("%d ", array[i]);
    }
    printf("\n");
}
