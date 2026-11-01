//
// Created by kozch on 07.06.2026.
//

#include <stdio.h>
#include "CodaSequenziale.h"

void InitCoda(TipoCoda *c) {
    c->primo = -1;
    c->ultimo = -1;
}

int CodaVuota(TipoCoda c) {
    return c.primo == -1;
}

int CodaPiena(TipoCoda c) {
    if (c.primo == c.ultimo) return 0;
    else if (c.primo < c.ultimo) return ((c.ultimo - c.primo) == (DIM_MAX - 1));
    else return (c.primo - c.ultimo == 1);
}

void InizioCoda(TipoCoda c, TipoElemCoda* v) {
    if (CodaVuota(c)) {
        printf("Errore");
    }
    else
        *v = c.elementi[c.primo];
}

int InCoda(TipoCoda *c, TipoElemCoda v) {
    if (CodaPiena(*c)) {
        printf("Errore");
        return -1;
    }
    if (c->primo ==  -1) {
        c->primo = 0;
        c->ultimo = 0;
    }
    else
        c->ultimo = (c->ultimo + 1) % DIM_MAX;
    c->elementi[c->ultimo] = v;
    return 1;
}

int OutCoda(TipoCoda *c, TipoElemCoda *v) {
if (CodaVuota(*c) || !v) return -1;
    *v=c->elementi[c->primo];
    if (c->primo==c->ultimo) c->primo=c->ultimo=-1;
    else c->primo=(c->primo+1)%DIM_MAX;
    return 1;
}