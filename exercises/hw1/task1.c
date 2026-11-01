#include <stdio.h>
#define N 5

int main(void) {
    int arr[N], i;
    int conta_magg = 0, conta_uguale = 0, conta_superiori = 0;
    int val_magg, val_uguale, val_sup;

    for (i = 0; i < N; i++) {
        printf("Inserisci array di 5 elementi[%d] : ", i);
        scanf("%d", &arr[i]);
    }

    printf("\nInserisci il valore per contare gli elementi maggiori: ");
    scanf("%d", &val_magg);

    printf("Inserisci il valore per contare gli elementi uguali: ");
    scanf("%d", &val_uguale);

    printf("Inserisci il valore superiore per contare gli elementi > 0 e < di esso: ");
    scanf("%d", &val_sup);

    for (i = 0; i < N; i++) {
        if (arr[i] > val_magg) {
            conta_magg++;
        }

        if (arr[i] == val_uguale) {
            conta_uguale++;
        }

        if (arr[i] > 0 && arr[i] < val_sup) {
            conta_superiori++;
        }
    }

    printf("\nNumero di elementi maggiori di %d: %d\n", val_magg, conta_magg);
    printf("Numero di elementi uguali a %d: %d\n", val_uguale, conta_uguale);
    printf("Numero di elementi > 0 e < %d: %d\n", val_sup, conta_superiori);

    return 0;
}