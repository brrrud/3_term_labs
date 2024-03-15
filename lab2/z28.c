#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdarg.h>

typedef struct token_info {
    char *file_name;
    char *token;
    int line_number;
    int token_house;
} token_info;

int get_string_from_stdin(int *len, char **string) {
    *len = 0;
    int capacity = 1;
    (*string) = (char *) malloc(sizeof(char));
    if (string == NULL) return -1;
    char c = getchar();
    while (c != '\n') {
        (*string)[(*len)++] = c;
        if (*len >= capacity) {
            capacity *= 2;
            *string = (char *) realloc(*string, capacity * sizeof(char));
            if (string == NULL) return -1;
        }
        c = getchar();
    }
    (*string)[*len] = '\0';
    return 0;
}

int file_read(int array_index, FILE **file, char *token, token_info *about_tokens) {
    while (1) {
        int indi;
        indi = string_read(array_index, file, token, about_tokens);
        if (indi == -3) break;
        if (indi == -1) return -1;
        if (indi == -4) return -4;
    }
    return 0;
}

int string_read(int array_index, FILE **file, char *token, token_info *about_tokens) {
    unsigned line_size = 15;
    unsigned line_ind = 0;
    char *line = (char *) malloc(sizeof(char) * line_size);
    if (line == NULL) return -2;
    char sym = fgetc(*file);
    if (feof(*file)) return -3;
    while (sym != '\n') {
        if (line_ind >= line_size - 1) {
            line_size *= 2;
            line = realloc(line, line_size * sizeof(char));
            if (line == NULL) return -2;
        }
        line[line_ind++] = sym;
        sym = fgetc(*file);
    }
    line[line_ind++] = '\0';
    if (step_by_line(array_index, token, line, about_tokens) == 1) {
        about_tokens[array_index].
    }
    free(line);
    return 0;
}

int step_by_line(int array_index, char *token, char *line, token_info *about_tokens) {
    int flag = 1;
    char ind_flag = token[0];
    int token_size = strlen(token);
    int line_size = strlen(line);
    for (int i = 0; i < line_size; ++i) {
        if (token_size > line_size - i) {
            break;
        }
        if (line[i] == ind_flag) {
            char *mstart = line + i;
            char *mend = mstart + token_size - 1;
            int major_len = mend - mstart + 1;
            char major[major_len + 1];
            memcpy(major, mstart, major_len);
            major[major_len] = '\0';
            if (strcmp(token, major) == 0) {
                flag = 0;
                about_tokens[array_index].token_house = i;
            }
        }
    }
    if (flag != 1) {
        return 1;
    }
    return 0;
}

int find_substr(token_info **about_tokens, char *token, int count, char *file_name, ...) {
    int read_bad = 0;
    int array_index;
    FILE *fp;
    va_list ap;
    va_start(ap, file_name);
    for (int i = 0; i < count; ++i) {
        char *file_name_arg = va_arg(ap,
        char*);
        fp = fopen(file_name_arg, "r");
        if (fp == NULL) {
            read_bad++;
            continue;
        }
        about_tokens[array_index]->file_name = strdup(file_name_arg);
        about_tokens[array_index]->token = strdup(token);

        fclose(fp);

    }
    va_end(ap);
}

int main() {
    token_info *about_tokens;
    about_tokens = (token_info *) malloc(sizeof(token_info) * 10);

    return 0;
}