#include "../../../common/console.h"
#include <stdio.h>
#include "PilaSequenzialeStatica.h"

int main(void) {
    Pila pila;
    InitPila(&pila);
    int nuovo_input,  estrazione;

    do {
        printf("Inserire un numero[negativo per terminare]: ");
        lab_scanf("%d", &nuovo_input);
        if (Push(&pila, nuovo_input) == -1) {
            printf("Pila piena");
            return -1;
        }
    }
            while (nuovo_input >= 0);
                printf("\n\n Inversione di sequenza: ");

                while (Pop(&pila, &estrazione) != -1) {
                    printf(" %d", estrazione);
                }

    return 0;
}