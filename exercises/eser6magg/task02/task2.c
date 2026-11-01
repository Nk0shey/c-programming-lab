#include "../../../common/console.h"
//
// Created by kozch on 04.06.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "PilaSequenzialeDinamica.h"
int main (void) {
    Pila pila;
    InitPila(&pila);
    int numero, x, bit;

    do {
        printf("Inserisci il numero: ");
        lab_scanf("%d", &numero);
    } while(numero < 0);

    x = numero;
    if (x == 0) {
        Push(&pila, x);
    } else {
        while (x > 0) {
            bit = x % 2;
            Push(&pila, bit);
            x = x / 2;
        }
    }
    printf("Il numero %d binario: ", numero);
    while (Pop(&pila, &bit) != -1) {
        printf("%d", bit);
    }
    TerminaPila(&pila);
    return 0;
}