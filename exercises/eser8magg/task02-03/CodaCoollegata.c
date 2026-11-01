//
// Created by kozch on 07.06.2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "CodaCoollegata.h"

void InitCoda(TipoCoda *c) {
    c->primo = NULL;
    c->ultimo = NULL;
}

int CodaVuota(TipoCoda c) {
    return (c.primo == NULL);
}

int InizioCoda(TipoCoda *c, TipoElemCoda *elem) {
    if (CodaVuota(*c)) {
        printf("Errore");
        return -1;
    }
    *elem = c->primo->info;
    return 1;
}

int InCoda(TipoCoda *c, TipoElemCoda elem) {
    TipoNodoCoda *nuovo_nodo = malloc(sizeof(TipoNodoCoda));
    if (nuovo_nodo == NULL) {
        printf("Errore");
        return -1;
    }
    nuovo_nodo -> info = elem;
    nuovo_nodo -> next = NULL;

    if (CodaVuota(*c)) {
        c->primo = nuovo_nodo;
        c->ultimo = nuovo_nodo;
    }
    else {
        c->ultimo->next = nuovo_nodo;
        c->ultimo = nuovo_nodo;
    }
    return 1;
}

int OutCoda(TipoCoda *c, TipoElemCoda *elem) {
    if (CodaVuota(*c)) {
        printf("Errore");
        return -1;
    }
    TipoNodoCoda *aux = c->primo;
    *elem = aux->info;
    c->primo = c->primo->next;
    free(aux);

    if (c->primo == NULL) {
        c->ultimo = NULL;
    }
    return 1;
}
