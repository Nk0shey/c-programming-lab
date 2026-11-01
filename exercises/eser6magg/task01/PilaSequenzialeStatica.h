//
// Created by kozch on 04.06.2026.
//

#ifndef ESER6MAGG_PILASEQUENZIALESTATICA_H
#define ESER6MAGG_PILASEQUENZIALESTATICA_H

#define DIM_MAX 10
typedef int tipoElemBase;
typedef struct {
    tipoElemBase elementi[DIM_MAX];
    int indice;
}Pila;

void InitPila(Pila *);
int PilaVuota(Pila);
int PilaPiena(Pila);
int Push(Pila *, tipoElemBase);
int Pop(Pila*, tipoElemBase*);
int TopPila(Pila, tipoElemBase*);

#endif //ESER6MAGG_PILASEQUENZIALESTATICA_H

