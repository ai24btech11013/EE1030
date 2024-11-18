#include <stdio.h>
#include <math.h>

#define MAX_ITER 1000
#define TOL 1e-6
#define MAX_SIZE 100

void printMatrix(double mat[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", mat[i][j]);
        }
        printf("\n");
    }
}

void matrixMultiply(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], double C[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void transpose(double A[MAX_SIZE][MAX_SIZE], double AT[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AT[j][i] = A[i][j];
        }
    }
}

void gramSchmidt(double A[MAX_SIZE][MAX_SIZE], double Q[MAX_SIZE][MAX_SIZE], double R[MAX_SIZE][MAX_SIZE], int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            R[k][i] = 0;
            for (int j = 0; j < n; j++) {
                R[k][i] += Q[j][k] * A[j][i];
            }
        }
        for (int i = 0; i < n; i++) {
            Q[i][k] = A[i][k];
            for (int j = 0; j < k; j++) {
                Q[i][k] -= R[j][k] * Q[i][j];
            }
        }
        double norm = 0;
        for (int i = 0; i < n; i++) {
            norm += Q[i][k] * Q[i][k];
        }
        norm = sqrt(norm);
        for (int i = 0; i < n; i++) {
            Q[i][k] /= norm;
        }
    }
}

void QRAlgorithm(double A[MAX_SIZE][MAX_SIZE], int n, double eigenvalues[MAX_SIZE]) {
    double Q[MAX_SIZE][MAX_SIZE] = {0};
    double R[MAX_SIZE][MAX_SIZE] = {0};
    double A_next[MAX_SIZE][MAX_SIZE] = {0};

    for (int iter = 0; iter < MAX_ITER; iter++) {
        gramSchmidt(A, Q, R, n);
        matrixMultiply(R, Q, A_next, n);

        double diff = 0;
        for (int i = 0; i < n; i++) {
            diff += fabs(A_next[i][i] - A[i][i]);
        }
        if (diff < TOL) break;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = A_next[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        eigenvalues[i] = A[i][i];
    }
}

int main() {
    int n;
    double A[MAX_SIZE][MAX_SIZE];
    double eigenvalues[MAX_SIZE];

    printf("Enter the size of the matrix (n x n, max size 100): ");
    scanf("%d", &n);

    printf("Enter the elements of the matrix row by row:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    QRAlgorithm(A, n, eigenvalues);

    printf("Eigenvalues:\n");
    for (int i = 0; i < n; i++) {
        printf("%8.4f\n", eigenvalues[i]);
    }

    return 0;
}
