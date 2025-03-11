#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct {
    double *arr;
    size_t row, col;
} Matrix;

Matrix *empty(Matrix *m);
Matrix *read(Matrix *m);
Matrix *resize(Matrix *m, size_t row, size_t col);
Matrix *multiply(const Matrix *a, const Matrix *b, Matrix *res);
void display(const Matrix *m);
void free(Matrix *m);

int main(void)
{
    Matrix M1, M2, M3;

    read(&M1);
    read(&M2);
    empty(&M3);
    
    if (multiply(&M1, &M2, &M3) == NULL) {
        printf("Matrix multiplication is implssible!\n");
    } else {
        printf("Result :\n");
        display(&M3);
    }

    free(&M1);
    free(&M2);
    free(&M3);

    return 0;
}

Matrix *empty(Matrix *m)
{
    if (m != NULL) {
        free(m->arr);
        m->row = 0;
        m->col = 0;
        m->arr = NULL;
    }
    return m;
}

Matrix *read(Matrix *m)
{
    if (m == NULL) return NULL;

    printf("Entering a matrix:\n");
    printf("Number of rows: ");
    scanf("%u", &m->row);
    printf("Number of columns: ");
    scanf("%u", &m->col);

    if (resize(m, m->row, m->col) == NULL) return NULL;

    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            double elem;
            printf("M[%d, %d]=", i + 1, j + 1);
            scanf("%lf", &m->arr[i * m->col + j]);
        }
    }

    return m;
}

Matrix *resize(Matrix *m, size_t row, size_t col)
{
    if (m == NULL) return NULL;

    if (row > N || col > N) return NULL;

    double *new_arr = realloc(m->arr, row * col * sizeof(double));
    if (new_arr == NULL) return NULL;

    m->arr = new_arr;
    m->row = row;
    m->col = col;

    return m; 
}

Matrix *multiply(const Matrix *a, const Matrix *b, Matrix *res)
{
    if (a->col != b->row) return NULL;

    if (res == NULL) return NULL;

    if (res->arr == NULL) {
        if (resize(res, a->row, b->col) == NULL) return NULL;
    }

    for (int i = 0; i < res->row; i++) {
        for (int j = 0; j < res->col; j++) {
            res->arr[i * res->col + j] = 0;
            for (int k = 0; k < a->col; k++) {
                res->arr[i * res->col + j] += a->arr[i * a->col + k] * b->arr[k * b->col + j];
            }
        }
    }

    return res;
}

void display(const Matrix *m)
{
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            printf("%.2f ", m->arr[i * m->col + j]);
        }
        printf("\n");
    }
}

void free(Matrix *m)
{
    if (m != NULL) {
        free(m->arr);
        m->arr = NULL;
        m->row = 0;
        m->col = 0;
    }
}
