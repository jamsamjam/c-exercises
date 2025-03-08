#include <stdio.h>

#define N 10 // max size for the matrix dimension

typedef struct {
    double array[N][N];
    unsigned int row, col;
} Matrix;

Matrix read_matrix(void);
Matrix multiply(const Matrix a, const Matrix b);
void display_matrix(const Matrix m);

int main(void)
{
    Matrix M1, M2, M = {0};

    M1 = read_matrix();
    display_matrix(M1);

    M2 = read_matrix();
    display_matrix(M2);

    if (M2.col != M1.row) {
        printf("Matrix multiplication impossible!");
        return 1;
    } else {
        M = multiply(M1, M2);
        printf("Result:\n");
        display_matrix(M);
    }

    return 0;
}

Matrix read_matrix(void)
{
    Matrix res = {0};
    unsigned int r, c;

    printf("Entering a matrix:\n");
    printf("Number of rows: ");
    scanf("%d", &r);
    printf("Number of columns: ");
    scanf("%d", &c);

    if (r > N || c > N) {
        printf("Error: Matrix size exceeds maximum limit of %d.\n", N);
        res.row = res.col = 0;
        return res;
    } else {
        res.row = r;
        res.col = c;
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double elem;
            printf("M[%d, %d]=", i + 1, j + 1);
            scanf("%lf", &elem);
            res.array[i][j] = elem;
        }
    }

    return res;
}

Matrix multiply(const Matrix a, const Matrix b)
{
    Matrix res = {0};

    res.row = a.row;
    res.col = b.col;

    for (int i = 0; i < res.row; i++) {
        for (int j = 0; j < res.col; j++) {
            for (int k = 0; k < a.col; k++) {
                res.array[i][j] += a.array[i][k] * b.array[k][j];
            }
        }
    }

    return res;
}

void display_matrix(const Matrix m)
{
    //int len = m.col * m.row;

    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            printf("%.2f ", m.array[i][j]);
        }
        printf("\n");
    }
}