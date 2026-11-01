#include <stdio.h>
#define R1 2
#define C1 3
#define R2 3
#define C2 2

int main(void) {
    int A[R1][C1] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int B[R2][C2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    int R[R1][C2];

    if (C1 != R2) {
        printf("Prodotto non possibile: dimensioni incompatibili.\n");
        return 1;
    }

    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            R[i][j] = 0;

            for (int k = 0; k < C1; k++) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("The result is: \n");
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }
    return 0;
}