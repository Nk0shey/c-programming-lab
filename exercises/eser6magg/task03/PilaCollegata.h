//
// Created by kozch on 05.06.2026.
//

#ifndef ESER6MAGG_PILACOLLEGATA_H
#define ESER6MAGG_PILACOLLEGATA_H

typedef int TipoElemPila;
typedef struct NodoPila{
    TipoElemPila info;
    struct NodoPila *next;
}TipoNodoPila;

typedef TipoNodoPila *Pila;

void InitPila(Pila *);
int PilaVuota(Pila);
int Push(Pila*, TipoElemPila);
int Pop(Pila*, TipoElemPila*);
int TopPila(Pila, TipoElemPila*);
int TerminaPila(Pila*);

#endif //ESER6MAGG_PILACOLLEGATA_H

