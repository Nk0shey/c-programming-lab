#include "../../common/console.h"
#include <stdio.h>
#define N 5

int main(void) {
    int arr[N];
    int i, el_cercato;
    int trovato = 0;
    printf("Inserisci un array di [%d] elementi: " , N);
    for (i = 0; i < N; i++) {
        printf("Inserisci elemento [%d]: ", i);
        lab_scanf("%d", &arr[i]);
    }

    printf("Digita elemento che vorresti cercare: ");
    lab_scanf("%d", &el_cercato);
    for (i = 0; i < N; i++) {
        if (el_cercato == arr[i]) {
            trovato = 1;
            break;
        }
    }

    if (trovato == 1) {
        printf("Il numero [%d] trovato\n", el_cercato);
    } else {
        printf("Il numero [%d] non trovato\n", el_cercato);
    }
}
