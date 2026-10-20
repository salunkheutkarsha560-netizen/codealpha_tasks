#include <stdio.h>

#define MAX 10

void inputMatrix(int matrix[MAX][MAX], int rows, int cols);
void displayMatrix(int matrix[MAX][MAX], int rows, int cols);
void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols);
void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX],
                      int r1, int c1, int c2);
void transposeMatrix(int matrix[MAX][MAX],
                     int result[MAX][MAX], int rows, int cols);

int main(void)
{
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2, choice;

    printf("===== MATRIX OPERATIONS =====\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return 1;
    }

    if (choice == 1 || choice == 2) {
        printf("Enter rows and columns of Matrix A (max %d): ", MAX);
        if (scanf("%d %d", &r1, &c1) != 2 ||
            r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid matrix dimensions.\n");
            return 1;
        }

        if (choice == 1) {
            r2 = r1;
            c2 = c1;
        } else {
            printf("Enter rows and columns of Matrix B (max %d): ", MAX);
            if (scanf("%d %d", &r2, &c2) != 2 ||
                r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX) {
                printf("Invalid matrix dimensions.\n");
                return 1;
            }

            if (c1 != r2) {
                printf("Multiplication not possible: ");
                printf("columns of A must equal rows of B.\n");
                return 1;
            }
        }

        printf("Enter elements of Matrix A:\n");
        inputMatrix(a, r1, c1);

        printf("Enter elements of Matrix B:\n");
        inputMatrix(b, r2, c2);

        if (choice == 1) {
            addMatrices(a, b, result, r1, c1);
            printf("Result of Addition:\n");
            displayMatrix(result, r1, c1);
        } else {
            multiplyMatrices(a, b, result, r1, c1, c2);
            printf("Result of Multiplication:\n");
            displayMatrix(result, r1, c2);
        }
    } else {
        printf("Enter rows and columns of Matrix (max %d): ", MAX);
        if (scanf("%d %d", &r1, &c1) != 2 ||
            r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid matrix dimensions.\n");
            return 1;
        }

        printf("Enter matrix elements:\n");
        inputMatrix(a, r1, c1);
        transposeMatrix(a, result, r1, c1);

        printf("Transpose of Matrix:\n");
        displayMatrix(result, c1, r1);
    }

    return 0;
}

void inputMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);

            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid element input.\n");
                return;
            }
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX],
                      int r1, int c1, int c2)
{
    int i, j, k;

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;

            for (k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[MAX][MAX],
                     int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}