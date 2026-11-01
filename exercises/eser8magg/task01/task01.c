#include "../../../common/console.h"
//
// Created by kozch on 07.06.2026.
//

#include <stdio.h>
#include "CodaSequenziale.h"

int main(void) {
    TipoCoda coda;
    InitCoda(&coda);

    int elem;

    do {
        printf("Inserisci il numero:");
        lab_scanf("%d", &elem);

        if ((elem < 0) || (InCoda(&coda, elem) == -1))
            break;
    } while (elem >= 0);

    TipoCoda coda_appoggio;
    InitCoda(&coda_appoggio);
    while (OutCoda(&coda, &elem) != -1) {
        if (elem % 2 == 0) {
            InCoda(&coda_appoggio, elem);
        }
    }
    printf("\n\nCoda:");
    while (OutCoda(&coda_appoggio, &elem) != -1) {
        printf("%d ", elem);
    }
    return 0;
}