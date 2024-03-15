#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int memory_matrix_on(int ***matrix, unsigned n, unsigned m);

void matrix_input(int ***matrix, unsigned n, unsigned m, int left, int right);

void matrix_printer(int ***matrix, unsigned n, unsigned m);

void memory_matrix_off(int ***matrix, unsigned n);

int matrix_mult(int ***matrix1, int ***matrix2, int ***matrix_out, int n1, int m1, int n2, int m2);

int nums_from_stdin(unsigned *n, unsigned *m, int *left, int *right);

double find_determinant(int **matrix, int size, int *determinant);

int get_sign(int a) {
    if (a % 2 == 0)return -1;
    return 1;
}

void swap_lines(int ***matrix, int size, int s1, int s2) {
    for (int i = 0; i < size; ++i) {
        int temp;
        temp = (*matrix)[s2][i];
        (*matrix)[s2][i] = (*matrix)[s1][i];
        (*matrix)[s1][i] = temp;
    }
}

void swap(int *num1, int *num2) {
    int tmp = *num2;
    *num2 = *num1;
    *num1 = tmp;
}

void multiply_num(int ***matrix, int size, int num) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            (*matrix)[i][j] = (*matrix)[i][j];
        }
    }
}

double determinant(int ***matrix, int size) {
    int cntSwaps = 1;
    int i, j, k;
    for (i = 0; i < size; ++i) {
        int max_i = i;
        for (j = i + 1; j < size; ++j) {
            if (abs((*matrix)[j][i]) > (*matrix)[max_i][i]) {
                max_i = i;
            }
        }
        if ((*matrix)[max_i][i] == 0) continue;
        for (k = 0; k < size; ++k) {
            swap(&matrix[i][k], &matrix[max_i][k]);
            cntSwaps = -cntSwaps * (i != max_i ? 1 : -1);
        }
        for (j = i + 1; j < size; ++j) {
            double q = -(*matrix)[j][i] / (*matrix)[i][i];
            for (int k = size; k >= i; --k) {
                (*matrix)[j][k] += q * (*matrix)[i][k];
            }
        }
    }
    multiply_num(matrix, size, cntSwaps);
    return 0;
}

int main() {
    int flag_memory;
    int **matrix1, **matrix2, **matrix_out;
    unsigned n1, m1, n2, m2; // количество строк -- n /// количество столбцов -- m
    int left1, right1, left2, right2;
    nums_from_stdin(&n1, &m1, &left1, &right1);
    nums_from_stdin(&n2, &m2, &left2, &right2);

    if (memory_matrix_on(&matrix1, n1, m1) == -1) {
        printf("Ошбика при работе с памятью");
        return -1;
    }
    if (memory_matrix_on(&matrix2, n2, m2) == -1) {
        memory_matrix_off(&matrix1, n1);
        printf("Ошбика при работе с памятью");
        return -1;
    }
    if (memory_matrix_on(&matrix_out, n1, m2) == -1) {
        memory_matrix_off(&matrix1, n1);
        memory_matrix_off(&matrix2, n2);
        printf("Ошбика при работе с памятью");
        return -1;
    }
    printf("\n");
    matrix_input(&matrix1, n1, m1, left1, right1);
    matrix_printer(&matrix1, n1, m1);
    printf("\n");
    matrix_input(&matrix2, n2, m2, left2, right2);
    matrix_printer(&matrix2, n2, m2);
    printf("\n");
    int det1, det2;
    find_determinant(matrix1, n1, &det1);
    printf("%d\n", det1);
    find_determinant(matrix1, n1, &det2);
    printf("%d\n", det2);
    printf("\n");


    memory_matrix_off(&matrix1, n1);
    memory_matrix_off(&matrix2, n2);
    memory_matrix_off(&matrix_out, n1);
}

int memory_matrix_on(int ***matrix, unsigned n, unsigned m) {
    (*matrix) = (int **) malloc(n * sizeof(int *));
    if ((*matrix) == NULL) {
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        (*matrix)[i] = (int *) malloc(m * sizeof(int));
        if ((*matrix)[i] == NULL) {
            return -1;
        }
    }
    return 0;
}

void matrix_input(int ***matrix, unsigned n, unsigned m, int left, int right) {
    int element;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            element = rand() % right - left + 1;
            (*matrix)[i][j] = element;
        }
    }
}

void matrix_printer(int ***matrix, unsigned n, unsigned m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", (*matrix)[i][j]);
        }
        printf("\n");
    }
}

void memory_matrix_off(int ***matrix, unsigned n) {
    for (int i = 0; i < n; ++i) {
        free((*matrix)[i]);
    }
    free(*matrix);
}

int nums_from_stdin(unsigned *n, unsigned *m, int *left, int *right) {
    scanf("%u%u", n, m);
    scanf("%d%d", left, right);
    return 0;
}

int matrix_mult(int ***matrix1, int ***matrix2, int ***matrix_out, int n1, int m1, int n2, int m2) {
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; j++) {
            (*matrix_out)[i][j] = 0;
            for (int k = 0; k < m1; ++k) {
                (*matrix_out)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
            }
        }
    }
}

double find_determinant(int **matrix, int size, int *determinant) {
    if (size == 1) {
        return matrix[0][0];
    }
    if (size == 2) {
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    } else {

        int del;
        for (int row = 0; row < size; ++row) {
            if (matrix[row][row] != 0) {
                for (int j = row + 1; j < size; ++j) {
                    del = matrix[j][row] / matrix[row][row];
                    for (int k = row; k < size; ++k) {
                        matrix[j][k] -= matrix[row][k] * del;
                    }
                }
            } else if (matrix[row][row] == 0) {
                int sdvig = -1;
                for (int z = row; z < size; ++z) {
                    if (matrix[row][z] != 0) {
                        sdvig = z - row;
                        break;
                    }

                }
                if (sdvig == -1) {
                    return 0.0;
                } else {
                    for (int j = row + 1 + sdvig; j < size; ++j) {
                        del = matrix[j][row] / matrix[row][row];
                        for (int k = row; k < size; ++k) {
                            matrix[j][k] -= matrix[row][k] * del;
                        }
                    }
                }
            }
        }
    }
}

int get_low_matrix(int ***matrix, int size) {
    int **matrix_tmp;
    memory_matrix_on(&matrix_tmp, size - 1, size - 1);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {

        }
    }
    memory_matrix_off(&matrix_tmp, size - 1);
}
//[n1, m1] * [n2, m2] --> [n1, m2]
