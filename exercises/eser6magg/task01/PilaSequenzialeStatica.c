//
// Created by kozch on 04.06.2026.
//

#include <stdio.h>
#include "PilaSequenzialeStatica.h"

void InitPila(Pila *p) {
    p->indice = -1;
}

int PilaVuota(Pila p) {
    return p.indice == -1;
}

int PilaPiena(Pila p) {
    return p.indice + 1 == DIM_MAX;
}

int Push(Pila *p, tipoElemBase elem) {
    if (PilaPiena(*p)) {
        printf("Impossibile raggiungere gli altri elementi");
        return -1;
    }
    p->elementi[++p->indice] = elem;
    return 1;
}

int Pop(Pila *p, tipoElemBase *elem) {
    if (PilaVuota(*p)) {
        printf("\nPila vuota");
        return -1;
    }
    *elem = p->elementi[p->indice--];
    return 1;
}

int TopPila(Pila p, tipoElemBase* elem) {
    if (PilaVuota(p)) {
        printf("\nPila vuota");
        return -1;
    }
    *elem = p.elementi[p.indice];
    return 1;
}