#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int reader(FILE **file, FILE **file_copy) {
    unsigned name_size = 15;
    unsigned name_ind = 0;
    char *name = (char *) malloc(name_size * sizeof(char));
    if (name == NULL) {
        return -1;
    }
    if (name == NULL) {
        return -1;
    }
    char sym = fgetc(*file);
    if (feof(*file)) {
        return -3;
    }

    while (sym != '\n') {
        if (name_ind >= name_size - 1) {
            name_size *= 2;
            name = realloc(name, name_size * sizeof(char));
            if (name == NULL) {
                return -1;
            }
        }
        name[name_ind++] = sym;
        sym = fgetc(*file);
    }
    name[name_ind++] = '\0';
    char *line1, *line2, *line3, *temp;
    char *piece = strtok(name, " ");
    line1 = piece;
    piece = strtok(NULL, " ");
    line2 = piece;
    piece = strtok(NULL, " ");
    line3 = piece;
    fprintf(*file_copy, "%s %s %s\n", line3, line1, line2);
    free(name);
}

int main() {
    FILE *file, *file_copy;
    file = fopen("testask3.txt", "r");
    file_copy = fopen("test_copy.txt", "w");
    if (file == NULL || file_copy == NULL) {
        return -1;
    }
    int k;
    while (1) {
        k = reader(&file, &file_copy);
        if (k == -3) break;
    }
    fclose(file);
    fclose(file_copy);
    if (remove("testask3.txt") == -1) {
        return -2;
    }
    if (rename("test_copy.txt", "testask3.txt") != 0) {
        return -3;
    }
    printf("uspeschno");
    return 0;

}
