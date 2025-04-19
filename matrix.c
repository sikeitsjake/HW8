#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **data;
    char name[50];
    int rows;
    int cols;
} Matrix;

// Function declarations
Matrix createMatrix(int rows, int cols, const char *name, int value);
void freeMatrix(Matrix *m);
void populateMatrix(Matrix *m);
void printMatrix(const Matrix *m);
Matrix transposeMatrix(const Matrix *m);
Matrix scalarMultiplyMatrix(const Matrix *m, int scalar);
Matrix multiplyMatrix(const Matrix *a, const Matrix *b, int *error);
Matrix addMatrix(const Matrix *a, const Matrix *b, int *error);

int main() {
    Matrix A = createMatrix(2, 2, "A", 0);
    populateMatrix(&A);

    Matrix B = createMatrix(2, 3, "B", 0);
    populateMatrix(&B);

    Matrix C = createMatrix(2, 3, "C", 0);
    populateMatrix(&C);

    Matrix C_T = transposeMatrix(&C);

    int error = 0;
    Matrix result;
    
    Matrix B3 = scalarMultiplyMatrix(&B, 3);
    Matrix B3C = multiplyMatrix(&B3, &C_T, &error);

    if (error) {
        printf("Exception has occurred: Matrix A cannot be multiplied by Matrix B\n");
        goto cleanup;
    }

    result = addMatrix(&A, &B3C, &error);
    if (error) {
        printf("Exception has occurred: Cannot add these matrices\n");
        goto cleanup;
    }

    printMatrix(&result);

cleanup:
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&C_T);
    freeMatrix(&B3);
    if (!error) freeMatrix(&result);
    if (!error) freeMatrix(&B3C);

    return error;
}

// Function implementations

Matrix createMatrix(int rows, int cols, const char *name, int value) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    strncpy(m.name, name, 49);
    m.name[49] = '\0';

    m.data = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        m.data[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            m.data[i][j] = value;
        }
    }

    return m;
}

void freeMatrix(Matrix *m) {
    for (int i = 0; i < m->rows; ++i) {
        free(m->data[i]);
    }
    free(m->data);
}

void populateMatrix(Matrix *m) {
    printf("Populating Matrix: %s\n", m->name);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("Enter element for matrix position (%d, %d): ", i, j);
            scanf("%d", &m->data[i][j]);
        }
    }
    printf("\n");
}

void printMatrix(const Matrix *m) {
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("%d ", m->data[i][j]);
        }
        printf("\n");
    }
}

Matrix transposeMatrix(const Matrix *m) {
    Matrix result = createMatrix(m->cols, m->rows, "Transpose", 0);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            result.data[j][i] = m->data[i][j];
        }
    }
    return result;
}

Matrix scalarMultiplyMatrix(const Matrix *m, int scalar) {
    Matrix result = createMatrix(m->rows, m->cols, "ScalarMul", 0);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            result.data[i][j] = m->data[i][j] * scalar;
        }
    }
    return result;
}

Matrix multiplyMatrix(const Matrix *a, const Matrix *b, int *error) {
    *error = 0;
    if (a->cols != b->rows) {
        *error = 1;
        return createMatrix(0, 0, "Invalid", 0);
    }

    Matrix result = createMatrix(a->rows, b->cols, "Product", 0);
    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < b->cols; ++j) {
            for (int k = 0; k < a->cols; ++k) {
                result.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

Matrix addMatrix(const Matrix *a, const Matrix *b, int *error) {
    *error = 0;
    if (a->rows != b->rows || a->cols != b->cols) {
        *error = 1;
        return createMatrix(0, 0, "Invalid", 0);
    }

    Matrix result = createMatrix(a->rows, a->cols, "Sum", 0);
    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            result.data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}