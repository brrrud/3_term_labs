#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int string_read(FILE **file, FILE **file_out, int mode);

int cut_token(char **line, FILE **file_out);

int file_read(FILE **file, FILE **file_out, int mode);

int valid(const char *piece);

int copy_valid_string(const char *piece, int valid_flag, FILE **file_out);

int find_base(char *num, char *all);

long long n_to_dec(int notation, char **string_num);

int answer(FILE **file, FILE **file_out, char **line);

int main() {
    FILE *file;
    FILE *file_out;
    file = fopen("nums.txt", "r");
    file_out = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия входного файла");
        return -1;
    }
    if (file_out == NULL) {
        printf("Ошибка открытия файла записи");
        fclose(file);
        return -1;
    }
    file_read(&file, &file_out, 1);
    fclose(file);
    fclose(file_out);

    file = fopen("output.txt", "r");
    file_out = fopen("output1.txt", "w");
    file_read(&file, &file_out, 2);
    fclose(file);


}

//-1 память -3все ок, конец строки
int string_read(FILE **file, FILE **file_out, int mode) {
    char *line;
    unsigned line_size = 10;
    unsigned line_ind = 0;
    //char sym;
    line = (char *) malloc(sizeof(char) * line_size);
    if (line == NULL)return -1;
    char sym = fgetc(*file);
    if (feof(*file)) {
        return -3;
    }
    while (sym != '\n') {
        if (line_ind >= line_size - 1) {
            line_size *= 2;
            line = realloc(line, line_size * sizeof(char));
            if (line == NULL) return -1;
        }
        line[line_ind++] = sym;
        sym = fgetc(*file);
    }
    line[line_ind++] = '\0';
    if (mode == 1) {
        cut_token(&line, file_out);
    }
    if (mode == 2) {
        answer(file, file_out, &line);
    }

}

int answer(FILE **file, FILE **file_out, char **line) {
    char *all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    fprintf(*file_out, " %s ", *line);
    int f = find_base(*line, all);
    fprintf(*file_out, " %d ", f);
    long long dec = n_to_dec(f, line);
    if (*line[0] == '-')fputc('-', *file_out);
    fprintf(*file_out, "%lld ", dec);
    free(*line);
    fputc('\n', *file_out);
}

int cut_token(char **line, FILE **file_out) {
    int valid_flag, cpflag;
    char *piece = strtok(*line, " \t");
    while (piece != NULL) {
        valid_flag = valid(piece);
        if (valid_flag != -1) {
            cpflag = copy_valid_string(piece, valid_flag, file_out);
            if (cpflag < 0) {
                printf("Ошибка очистки данных");
                return -2;
            }
        }
        piece = strtok(NULL, " \t");
    }
    free(*line);
}

int file_read(FILE **file, FILE **file_out, int mode) {
    int k;
    while (1) {
        k = string_read(file, file_out, mode);
        if (k == -3)break;
        if (k == -1)return -1;
    }
}

int valid(const char *piece) {
    int minus_cnt = 0;
    for (int i = 0; i <= strlen(piece) - 1; ++i) {
        if (!isdigit(piece[i]) && !isalpha(piece[i]) && piece[i] != '-') {
            return -1;
        }
        if (piece[i] == '-') {
            minus_cnt++;
        }
    }
    if (minus_cnt > 1) return -1;
    if (minus_cnt == 1 && piece[0] == '-') return 1;
    if (minus_cnt == 1 && piece[0] != '-') return -1;
    return 0;
}

int copy_valid_string(const char *piece, int valid_flag, FILE **file_out) {
    unsigned j = 0;
    int k;
    if (valid_flag == 1) {
        k = fprintf(*file_out, "%c", '-');
        if (k < 0) return k;
    }
    for (int i = valid_flag; i <= strlen(piece) - 1; ++i) {
        if (piece[i] >= 'a' && piece[i] <= 'z') {
            k = fprintf(*file_out, "%c", toupper(piece[i]));
            if (k < 0) return k;
        } else {
            k = fprintf(*file_out, "%c", piece[i]);
            if (k < 0) return k;
        }
    }
    fputc('\n', *file_out);
}

int find_base(char *num, char *all) {
    char max_sym = num[0];
    char tmp_max;
    int ind;
    int flag = 0;
    int mv = 0;
    if (num[0] == '-') {
        mv = 1;
    }
    for (int i = mv; i <= strlen(num) - 1; ++i) {
        for (int j = 0; j <= strlen(all) - 1; ++j) {
            if (num[i] >= all[j]) {
                tmp_max = num[i];
            }
        }
        if (max_sym < tmp_max) {
            max_sym = tmp_max;
        }
        if (!isdigit(num[i])) {
            flag = 1;
        }
    }
    //if(flag == 0) return 10; 
    for (int j = 0; j <= strlen(all) - 1; ++j) {
        if (max_sym == all[j]) {
            ind = j;
            break;
        }
    }
    return ind + 1;
}

long long n_to_dec(int notation, char **string_num) {
    int mv = 0;
    int base = 1;
    long long dec = 0;
    if (*string_num[0] == '-') {
        mv = 1;
    }
    int length = strlen(*string_num);
    for (int i = length--; i >= mv; i--) {
        if ((*string_num)[i] >= '0' && (*string_num)[i] <= '9') {
            dec += ((*string_num)[i] - 48) * base;
            base *= notation;
        }
        if ((*string_num)[i] >= 'A' && (*string_num)[i] <= 'Z') {
            dec += ((*string_num)[i] - 55) * base;
            base *= notation;
        }
    }
    return dec;
}

