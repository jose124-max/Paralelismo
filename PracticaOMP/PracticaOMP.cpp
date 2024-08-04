#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000  // Tamano de la matriz (N x N)

// Funcion para multiplicar matrices sin paralelismo
void multiply_matrices_serial(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Funcion para multiplicar matrices con paralelismo
void multiply_matrices_parallel(int A[N][N], int B[N][N], int C[N][N]) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print_matrix(int mat[N][N]) {
    for (int i = 0; i < 10; i++) {  // Solo imprimir las primeras 10 filas y columnas
        for (int j = 0; j < 10; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    static int A[N][N], B[N][N], C[N][N];  
    //matrices A y B con valores ascendentes y descendentes
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i * N + j + 1;
            B[i][j] = N * N - (i * N + j);
        }
    }

    while (1) {
        int option;
        printf("Selecciona el modo de ejecucion:\n");
        printf("1. Sin paralelismo\n");
        printf("2. Con paralelismo\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf_s("%d", &option);

        if (option == 3) {
            break;
        }

        double start, end;
        double time_taken;

        if (option == 1) {
            start = omp_get_wtime();
            multiply_matrices_serial(A, B, C);
            end = omp_get_wtime();
        }
        else if (option == 2) {
            start = omp_get_wtime();
            multiply_matrices_parallel(A, B, C);
            end = omp_get_wtime();
        }
        else {
            printf("Opcion no valida.\n");
            continue;
        }

        time_taken = end - start;

        // Imprimir matrices (truncado)
        printf("Matriz A (primeras 10x10 elementos):\n");
        print_matrix(A);

        printf("Matriz B (primeras 10x10 elementos):\n");
        print_matrix(B);

        printf("Matriz C (resultado de A * B, primeras 10x10 elementos):\n");
        print_matrix(C);

        printf("Tiempo de ejecucion: %f segundos\n", time_taken);
    }

    return 0;
}
