#include "../../common/console.h"
#include <stdio.h>
#define N 5

int main(void) {
    int a[N], b[N];
    int somma[N], differenza[N], prodotto[N], minimo[N];

    printf("Inserisci gli elementi dell'array a:\n");
    for (int i = 0; i < N; i++) {
        printf("a[%d] = ", i);
        lab_scanf("%d", &a[i]);
    }

    printf("Inserisci gli elementi dell'array b:\n");
    for (int i = 0; i < N; i++) {
        printf("b[%d] = ", i);
        lab_scanf("%d", &b[i]);
    }

    for (int i = 0; i < N; i++) {
        somma[i] = a[i] + b[i];
        differenza[i] = a[i] - b[i];
        prodotto[i] = a[i] * b[i];
        if (a[i] < b[i]) {
            minimo[i] = a[i];
        }
        else {
            minimo[i] = b[i];
            }
        }

    printf("\nArray Somma\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", somma[i]);
    }

    printf("\n\nArray Differenza:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", differenza[i]);
    }

    printf("\n\nArray Prodotto:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", prodotto[i]);
    }

    printf("\n\nArray Minimo:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", minimo[i]);
    }

    printf("\n");
    return 0;
}