#include<stdio.h>
#include<string.h>
#include<ctype.h>

// (0. путь исполняемого файла) (1. флаг) (2. путь к файлу) (3. ВОЗМОЖНО еще один файл)
void flag_d(FILE **file, FILE **file_out);

void flag_i(FILE **file, FILE **file_out);

void flag_s(FILE **file, FILE **file_out);

void flag_a(FILE **file, FILE **file_out);

void flag_f(FILE **file, FILE **file_out);

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        printf("некорректное количество аргументов\n");
        return -1;
    }
    FILE *file, *file_out;
    int ind = 0;
    if (argc == 3 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (!isalpha(argv[1][1])) {
            printf("Ошибка аргумента");
            return -1;
        }
        file = fopen(argv[2], "r");
        if (file == NULL) {
            fclose(file);
            printf("Ошибка открытия");
            return -2;
        }
        char *dst = argv[2];
        char path[100] = "out_";
        strcat(path, dst);

        file_out = fopen(path, "w");
        if (file_out == NULL) {
            printf("Ошибка открытия");
            fclose(file);
            return -2;
        }
        ind = 1;
    } else if (argc == 4 && (argv[1][0] == '-' || argv[1][0] == '/')) {
        if (argv[1][1] != 'n') {
            printf("Ошибка в аргументе");
            return -1;
        }

        file = fopen(argv[2], "r");
        if (file == NULL) {
            fclose(file);
            printf("Ошибка открытия");
            return -2;
        }

        file_out = fopen(argv[3], "w");

        if (file_out == NULL) {
            fclose(file);
            printf("Ошибка открытия");
            return -2;
        }
        ind = 2;
    }
    if (argv[1][ind] == 'd') {
        flag_d(&file, &file_out);
        fclose(file);
        fclose(file_out);
        return 0;
    } else if (argv[1][ind] == 'i') {
        flag_i(&file, &file_out);
        fclose(file);
        fclose(file_out);
        return 0;
    } else if (argv[1][ind] == 's') {
        flag_s(&file, &file_out);
        fclose(file);
        fclose(file_out);
        return 0;
    } else if (argv[1][ind] == 'a') {
        flag_a(&file, &file_out);
        fclose(file);
        fclose(file_out);
        return 0;
    } else if (argv[1][ind] == 'f') {
        flag_f(&file, &file_out);
        fclose(file);
        fclose(file_out);
        return 0;
    } else {
        printf("Некорректность флага");
        return -1;
    }

}


void flag_d(FILE **file, FILE **file_out) {
    char sym;
    while ((sym = fgetc(*file)) != EOF) {
        if (!isdigit(sym)) {
            fprintf(*file_out, "%c", sym);
        }
    }
}

void flag_i(FILE **file, FILE **file_out) {
    char sym;
    int cnt = 0;
    while ((sym = fgetc(*file)) != EOF) {
        if (isalpha(sym)) {
            cnt++;
        } else if (sym == '\n') {
            fprintf(*file_out, "%d\n", cnt);
            cnt = 0;
        }
    }
}

void flag_s(FILE **file, FILE **file_out) {
    char sym;
    int cnt = 0;
    while ((sym = fgetc(*file)) != EOF) {
        if (!isalpha(sym) && !isdigit(sym) && sym != ' ' && sym != '\n') {
            cnt++;
        } else if (sym == '\n') {
            fprintf(*file_out, "%d\n", cnt);
            cnt = 0;
        }
    }
}

void flag_a(FILE **file, FILE **file_out) {
    char sym;
    while ((sym = fgetc(*file)) != EOF) {
        if (!isdigit(sym)) {
            fprintf(*file_out, "%d", sym);
        } else {
            fprintf(*file_out, "%c", sym);
        }
    }
}

void flag_f(FILE **file, FILE **file_out) {
    char sym;
    int cnt = 0;
    while ((sym = fgetc(*file)) != EOF) {
        char c = sym;
        while (sym == ' ' || sym == '\n') {
            fprintf(*file_out, "%c", sym);
            sym = fgetc(*file);
        }
        cnt++;
        if (sym == EOF) {
            break;
        }
        while (sym != ' ' && sym != '\n') {
            sym = fgetc(*file);
            if (cnt % 2 == 0 && sym >= 65 && sym <= 90) {
                fprintf(*file_out, "%c", sym + 32);
            } else if (cnt % 5 == 0) {
                fprintf(*file_out, "%d", sym);
            } else {
                fprintf(*file_out, "%c", sym);
            }
        }
    }
}