//
// Created by kozch on 04.06.2026.
//

#ifndef ESER6MAGG_PILASEQUENZIALEDINAMICA_H
#define ESER6MAGG_PILASEQUENZIALEDINAMICA_H
#define DIM_INIZIALE 10

typedef int TipoElemBase;
typedef struct {
    TipoElemBase *elementi;
    int indice;
    int dimensioneCorrente;
}Pila;

void InitPila(Pila* );
int PilaVuota(Pila );
int PilaPiena(Pila );
int Push(Pila *, TipoElemBase);
int Pop(Pila *, TipoElemBase*);
int TopPila(Pila, TipoElemBase*);
int TerminaPila(Pila *);


#endif //ESER6MAGG_PILASEQUENZIALEDINAMICA_H