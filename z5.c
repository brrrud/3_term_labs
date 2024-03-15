//-fi file_name
//-cin --> stdin
// -arg --> аргументами командной строки 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int string_read(FILE** file, FILE** file_out);
int file_read(FILE** file, FILE** file_out);
int writnwrite(FILE** file, FILE** file_out);
int get_string_from_stdin(int* len, char** string);

int main(int argc, char* argv[]){
    FILE* file_out;
    FILE* file;
    char* file0name;
    int file0name_len;
    get_string_from_stdin(&file0name_len, &file0name);
    file_out = fopen(file0name, "w");
    if(file_out == NULL){
        printf("ошибка открытия F!");
        return -1;
    } 
    if(argc == 3 && strcmp(argv[1], "-fi") == 0){
        int value;
        int ind_sos;
        if(strcmp(file0name, argv[2])==0){
            printf("Всё плохо. имена совпали\n");
            fclose(file_out);
            return -1;
        }
        file = fopen(argv[2], "r");
        if(file == NULL){
            fclose(file_out);
            printf("ошибка открытия 2");
            return -1;
        }
        ind_sos = file_read(&file, &file_out);
        if(ind_sos == -1){
            printf("Ошибка открытия. Неправильное имя файла в списке файлов");
            fclose(file_out);
            return -1;
        }
        if(ind_sos == -4){
            printf("Ошибка записи в файл");
            fclose(file_out);
            return -1;
        }
        if(ind_sos == -2){
            printf("Ошибка памяти");
            fclose(file_out);
            return -1;
        }
        fclose(file);
        fclose(file_out);
        printf("OK!");
        return 0;
    }
    else if(argc == 2 && strcmp(argv[1], "-cin") == 0){
        int n;
        char c;
        if(!(scanf("%d%c", &n, &c) == 2 && c == '\n') || n < 0){
            printf("Введите целое неотрицательное число - количество файлов");
            fclose(file_out);
            return -1;
        }
        for(long i = 0; i < n; ++i){
            int ind_read;
            int len = 0;
            char* file_name;
            int ind_write;
            ind_read = get_string_from_stdin(&len, &file_name);
            if(ind_read == -1){
                printf("Ошибка при считывании имени файла");
                fclose(file_out);
                return -1;
            }
            if(strcmp(file0name, file_name)==0){
                printf("Всё плохо. имена совпали\n");
                fclose(file_out);
                return -1;
            }
            file = fopen(file_name, "r");
            if(file == NULL){
                printf("Ошибка открытия 1");    
                fclose(file_out);
                return -1;
            } 
            ind_write = writnwrite(&file, &file_out);
            if(ind_write < 0){
                printf("Ошибка при записи");
                fclose(file_out);
                return -1;
            }
            free(file_name);
            fclose (file);
        }
        fclose(file_out);
        printf("OK!");
        return 0;
    }
    else if(argc > 2 && strcmp(argv[1], "-arg") == 0){
        int ind_write;
        for(int i = 2; i < argc; ++i){
            if(strcmp(file0name, argv[i])==0){
                printf("Всё плохо. имена совпали\n");
                fclose(file_out);
                return -1;
            }
            file = fopen(argv[i], "r");
            if(file == NULL){
                printf("Ошибка открытия 1");    
                fclose(file_out);
                return -1;
            }
            ind_write = writnwrite(&file, &file_out);
            if(ind_write < 0){
                printf("Ошибка при записи");
                fclose(file_out);
                return -1;
            }
            fclose(file);
        }
        fclose(file_out);
        printf("OK!");
        return 0;
    }
    else{
        printf("Некорректная работа с флагом");
        return -1;
    }

}
// -2 SEGSEV /// -3 индикатор конца строки/// -1 ошибка открыьтя /// -4 ошибка записи
int string_read(FILE** file, FILE** file_out){
    FILE* fd;
    unsigned line_size = 15;
    unsigned line_ind = 0;
    char* line = (char*)malloc(sizeof(char) * line_size);
    if(line == NULL) return -2;
    char sym = fgetc(*file);
    if(feof(*file)) return -3;
    while (sym != '\n') {
        if(line_ind >= line_size - 1){
            line_size *= 2;
            line = realloc(line, line_size * sizeof(char));
            if(line == NULL) return -2;
        }
        line[line_ind++] = sym;
        sym = fgetc(*file);
    }
    line[line_ind++] = '\0';
    fd = fopen(line, "r");
    if(fd == NULL) return -1;
    if(writnwrite(&fd, file_out) != 1) return -4;
    free(line);
    fclose(fd);
    return 0;
}

int file_read(FILE** file, FILE** file_out){
    while (1) {
        int indi;
        indi = string_read(file, file_out);
        if(indi == -3) break;
        if(indi == -1) return -1;
        if(indi == -4) return -4;
    }
    return 0;
}

int writnwrite(FILE** file, FILE** file_out){
    char sym;
    int cnt = 0;
    int indi;
    while((sym = fgetc(*file)) != EOF){
        indi = fprintf(*file_out, "%c", sym);
        if(indi < 0) return indi;
    }
    return 1;
}

int get_string_from_stdin(int* len, char** string){
    *len = 0; 
    int capacity = 1; 
    (*string) = (char*)malloc(sizeof(char));
    if(string == NULL) return -1; 
    char c = getchar(); 
    while (c != '\n') {
        (*string)[(*len)++] = c; 
        if (*len >= capacity) {
            capacity *= 2; 
            *string = (char*) realloc(*string, capacity * sizeof(char)); 
            if(string == NULL) return -1;
        }
        c = getchar();        
    }
    (*string)[*len] = '\0';
    return 0;
}
