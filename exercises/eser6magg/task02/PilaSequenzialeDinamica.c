//
// Created by kozch on 04.06.2026.
//

#include "PilaSequenzialeDinamica.h"
#include <stdio.h>
#include <stdlib.h>

void InitPila(Pila *p) {
    p->elementi = malloc(sizeof(TipoElemBase)*DIM_INIZIALE);
    if (p->elementi == NULL) {
        printf("Erro ao alocar memoria");
        exit(-1);
    }
    p->indice = -1;
    p->dimensioneCorrente = DIM_INIZIALE;
}

int PilaVuota(Pila p) {
    return p.indice == -1;
}

int PilaPiena(Pila p) {
    return (p.indice + 1) == p.dimensioneCorrente;
}

int Push(Pila *p, TipoElemBase elem) {
    if (PilaPiena(*p)) {
        TipoElemBase *aux = realloc(p->elementi, sizeof(TipoElemBase)*(p->dimensioneCorrente+DIM_INIZIALE));
        if (aux == NULL) {
            printf("Erro ao alocar memoria");
        }
        p->elementi = aux;
        p->dimensioneCorrente+=DIM_INIZIALE;
    }
    p->elementi[++p->indice] = elem;
    return 1;
}

int Pop(Pila* p, TipoElemBase* elem) {
    if (PilaVuota(*p)) {
        return -1;
    }

    *elem = p->elementi[p->indice--];

    if (p->dimensioneCorrente-(p->indice+1) > DIM_INIZIALE) {
        TipoElemBase *aux = realloc(p->elementi, sizeof(TipoElemBase)*(p->dimensioneCorrente-DIM_INIZIALE));
        if (aux == NULL) {
            printf("Erro ao alocar memoria");
            exit(-1);
        }
        p->elementi = aux;
        p->dimensioneCorrente-=DIM_INIZIALE;
    }
    return 1;
}

int TopPila(Pila p, TipoElemBase* elem) {
    if (PilaVuota(p)) {
        return -1;
    }
    *elem = p.elementi[p.indice];
    return 1;
}

int TerminaPila(Pila *p) {
    free(p->elementi);
    p->indice = -1;
    p->dimensioneCorrente = -1;
    return 1;
}
