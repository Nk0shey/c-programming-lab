#include "../../../common/console.h"
//
// Created by kozch on 07.06.2026.
//

/* Esercizio 3.
 * Date due code c1 e c2 di interi non negativi (acquisite da tastiera) creare una coda c3 dove gli
 * elementi di c1 e c2 vengano inseriti in modo alternato (prima un elemento da c1, poi uno da
 * c2, ecc.), finché entrambe le code non sono vuote (se una delle due code finisce prima,
 * inserire in c3 tutti gli elementi rimanenti dell’altra coda).
 */

#include <stdio.h>
#include <stdlib.h>
#include "CodaCoollegata.h"

void visita_coda(TipoCoda);
void dealloca_coda(TipoCoda*);

int main(void) {
    int elem;
    TipoCoda c1, c2, c3;
    InitCoda(&c1);
    InitCoda(&c2);
    InitCoda(&c3);

    printf("** coda_1 **\n");
    do {
        printf("Inserire un numero: ");
        lab_scanf("%d", &elem);
        if ((elem < 0) || (InCoda(&c1, elem) == -1)) {
            break;
        }
    } while (elem >= 0);

    printf("** coda_2 **\n");
    do {
        printf("Inserire un numero: ");
        lab_scanf("%d", &elem);
        if ((elem < 0) || (InCoda(&c2, elem) == -1)) {
            break;
        }
    } while (elem >= 0);

    while (!CodaVuota(c1) && !CodaVuota(c2)) {
        OutCoda(&c1, &elem);
        if (InCoda(&c3, elem) == -1) break;
        OutCoda(&c2, &elem);
        if (InCoda(&c3, elem) == -1) break;
    }

    while (!CodaVuota(c1)) {
        OutCoda(&c1, &elem);
        if (InCoda(&c3, elem) == -1) break;
    }

    while (!CodaVuota(c2)) {
        OutCoda(&c2, &elem);
        if (InCoda(&c3, elem) == -1) break;
    }

    //stampa coda 3
    printf("\n coda_3: ");
    visita_coda(c3);
    dealloca_coda(&c1);
    dealloca_coda(&c2);
    dealloca_coda(&c3);
    return 0;
}

void visita_coda(TipoCoda c) {
    TipoNodoCoda *nodo = c.primo;
    while (nodo != NULL) {
        printf("%d", nodo->info);
        nodo = nodo->next;
    }
}

void dealloca_coda(TipoCoda *c) {
    TipoNodoCoda *nodo;
    while (c->primo != NULL) {
        nodo = c->primo;
        c->primo = c->primo->next;
        free(nodo);
    }
    c->primo = c->ultimo = NULL;
}

