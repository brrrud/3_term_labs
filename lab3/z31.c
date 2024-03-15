#include<stdio.h>
#include<string.h>
#include<ctype.h>

// (0. путь исполняемого файла) (1. флаг) (2. путь к файлу) (3. ВОЗМОЖНО еще один файл)
int flag_d(FILE **file, FILE **file_out);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("мало аргументов\n");
        return -1;
    }
    if (argc == 3 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (!isalpha(argv[1][1])) {
            printf("Ошибка аргумента");
            return -1;
        }
        FILE *file;
        FILE *file_out;
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fclose(file);
            printf("Ошибка открытия");
            return -2;
        }
        char *path = argv[2];
        strcat(path, "_out.txt");
        file_out = fopen(path, "w");
        if (file_out == NULL) {
            printf("Ошибка открытия");
            fclose(file);
            fclose(file_out);
            return -2;
        }
        if (argv[1][1] == 'd') {
            char c;
            while ((c = fgetc(file)) != EOF) {
                if (c < 48 || c > 57) {
                    fputc(c, file_out);
                }
            }
            fclose(file);
            fclose(file_out);
            return 0;
        }
        if (argv[1][1] == 'i') {

        }
        if (argv[1][1] == 's') {

        }
        if (argv[1][1] == 'a') {

        }


    }
    if (argc == 4 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (argv[1][1] != 'n') {
            printf("Ошибка в аргументе");
            return -1;
        }
        FILE *file, *file_out;

        file = fopen(argv[2], "r");
        if (file == NULL) {
            fclose(file);
            printf("Ошибка открытия");
            return -2;
        }

        file_out = fopen(argv[3], "w");
        if (file_out == NULL) {
            fclose(file);
            fclose(file_out);
            printf("Ошибка открытия");
            return -2;
        }


    }
}


