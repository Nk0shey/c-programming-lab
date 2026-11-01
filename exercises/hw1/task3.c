#include <stdio.h>
#define N 5


int main(void) {
    int a[N], b[N], c[N];
    int scalare = 0;

    printf("Inserisci gli elementi dell'array a:\n");
    for (int i = 0; i < N; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("Inserisci gli elementi dell'array b:\n");
    for (int i = 0; i < N; i++) {
        printf("b[%d] = ", i);
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < N; i++) {
        c[i] = a[i] * b[i];
    }

    for (int i = 0; i < N; i++) {
        scalare += c[i];
    }

    printf("Scalare dei vettori [a] e [b] = %d", scalare);
}