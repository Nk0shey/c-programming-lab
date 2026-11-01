//
// Created by kozch on 05.06.2026.
//

#include "PilaCollegata.h"
#include <stdio.h>
#include <stdlib.h>


void InitPila(Pila *p) {
    *p = NULL;
}

int PilaVuota(Pila p) {
    return p == NULL;
}

int Push(Pila *p, TipoElemPila elem) {
    TipoNodoPila *aux = malloc(sizeof(TipoNodoPila));
    if (aux == NULL) {
        printf("No hay memoria");
        return -1;
    }
    aux->info = elem;
    aux->next = *p;
    *p = aux;
    return 1;
}

int Pop(Pila *p, TipoElemPila *elem) {
    if (PilaVuota(*p)) return -1;
    TipoNodoPila *nodo_affiorante;
    nodo_affiorante = *p;
    *p = (*p)->next;
    *elem = nodo_affiorante->info;
    free(nodo_affiorante);
    return 1;
}

int TopPila(Pila p, TipoElemPila *elem) {
    if (!PilaVuota(p)) {
        *elem = p->info;
        return 1;
    }
    return 0;
}

int TerminaPila(Pila *p) {
TipoElemPila e;
    while (Pop(p, &e) == 1) { }
    return 1;
}
