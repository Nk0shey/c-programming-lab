#include "../../../common/console.h"
//
// Created by kozch on 07.06.2026.
//

/* Esercizio_2.
 * Scrivere un programma in C che legga da tastiera una sequenza di numeri interi positivi di
 * lunghezza sconosciuta (la sequenza termina quando viene inserito un numero negativo) e li
 * memorizzi in una coda implementata tramite rappresentazione collegata. Scrivere poi una
 * funzione che conti quanti elementi ci sono nella coda, ma alla fine la coda deve risultare
 * esattamente com’era all’inizio. (è possibile usare una seconda coda di appoggio)
 */

#include <stdio.h>
#include <stdlib.h>
#include "CodaCoollegata.h"

int conta_elementi(TipoCoda);
void dealloca_coda(TipoCoda*);

int main(void) {
    TipoCoda coda;
    InitCoda(&coda);
    int elem;

    do {
        printf("Inserisci elem: ");
        lab_scanf("%d", &elem);

        if ((elem < 0) || (InCoda(&coda, elem)) != -1) {
            break;
        }
    } while (elem >= 0);

    printf("La coda contiene %d elementi", conta_elementi(coda));

    dealloca_coda(&coda);
    return 0;
}

int conta_elementi(TipoCoda c) {
    int count = 0;
    TipoNodoCoda *nodo = c.primo;
    while (nodo != NULL) {
        count += 1;
        nodo = nodo->next;
    }
    return count;
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