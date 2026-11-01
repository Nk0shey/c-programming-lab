#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int dim1;
    int conta_pari = 0;
    int *v, *pari;
    do {printf("Inserisci la dim del vettore 1: ");
        if (scanf("%d", &dim1) != 1) return 1;} while (dim1 <= 0);
    if (dim1 > 1000000) return 1;

    v = (int*) malloc(sizeof(int)*dim1);

    if (v == NULL) {
        printf("Errore in allocazione di memoria");
        return 1;
    }

    for (int i = 0; i < dim1; i++) {
        printf("Inserisci il valore[%d]: ", i);
        if (scanf("%d", &v[i]) != 1) { free(v); return 1; }
    }

    for (int i = 0; i < dim1; i++) {
        if (v[i] % 2 == 0) {
            conta_pari++;
        }
    }

    if (conta_pari == 0) {
        printf("Non ci sono numeri pari nel vettore");
        free(v);
        return 0;
    }

    pari = (int*) malloc(conta_pari * sizeof(int));
    if (pari == NULL) {
        printf("Errore in allocazione di memoria");
        free(v);
        return 1;
    }

    int j = 0;
    for (int i = 0; i < dim1; i++) {
        if (v[i] % 2 == 0) {
            pari[j] = v[i];
            j++;
        }
    }

    printf("Vettore iniziale: ");
    for (int i = 0; i < dim1; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Vettore pari: ");
    for (int i = 0; i < conta_pari; i++) {
        printf("%d ", pari[i]);
    }
    printf("\n");

    free(v);
    free(pari);

    return 0;
}
