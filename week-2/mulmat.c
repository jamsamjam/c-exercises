#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct {
    double array[N][N];
    unsigned int row, col;
} Matrix;

Matrix *read_matrix(void);
Matrix *multiply(const Matrix *a, const Matrix *b);
void display_matrix(const Matrix *m);
void free_matrix(Matrix **m);

int main(void)
{
    Matrix *M1, *M2, *M = NULL;

    M1 = read_matrix();
    display_matrix(M1);

    M2 = read_matrix();
    display_matrix(M2);

    M = multiply(M1, M2);
    if (M == NULL) {
        printf("Matrix multiplication impossible!");
        return 1;
    } else {
        printf("Result:\n");
        display_matrix(M);
    }

    free_matrix(&M1);
    free_matrix(&M2);
    free_matrix(&M);

    return 0;
}

Matrix *read_matrix()
{
    Matrix *res = malloc(sizeof(Matrix));

    if (res == NULL) return NULL;

    printf("Entering a matrix:\n");
    printf("Number of rows: ");
    scanf("%u", &res->row);
    printf("Number of columns: ");
    scanf("%u", &res->col);

    if (res->row > N || res->col > N) {
        printf("Error: Matrix size exceeds maximum limit of %d.\n", N);
        free(res);
        return NULL;
    }

    for (int i = 0; i < res->row; i++) {
        for (int j = 0; j < res->col; j++) {
            double elem;
            printf("M[%d, %d]=", i + 1, j + 1);
            scanf("%lf", &res->array[i][j]);
        }
    }

    return res;
}

Matrix *multiply(const Matrix *a, const Matrix *b)
{
    Matrix *res = malloc(sizeof(Matrix));

    if (res == NULL) return NULL;

    res->row = a->row;
    res->col = b->col;

    for (int i = 0; i < res->row; i++) {
        for (int j = 0; j < res->col; j++) {
            res->array[i][j] = 0;
            for (int k = 0; k < a->col; k++) {
                res->array[i][j] += a->array[i][k] * b->array[k][j];
            }
        }
    }

    return res;
}

void display_matrix(const Matrix *m)
{
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            printf("%.2f ", m->array[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix **m)
{
    if (*m != NULL) {
        free(*m);
        *m = NULL;
    }
}