#include <stdio.h>
#include <stdlib.h>
#define DIM_MAX 100

typedef int TipoInfoAlbero;

typedef struct nodoAlbero {
    TipoInfoAlbero info;
    struct nodoAlbero *destro, *sinistro;
} NodoAlbero;

typedef NodoAlbero *Albero;

void initAlbero(Albero *a) {
    *a = NULL;
}

int isEmpty(Albero a) {
    return a == NULL;
}

int Max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int AltezzaAlbero(Albero a) {
    if (isEmpty(a)) {
        return 0;
    }
    return 1 + Max(AltezzaAlbero(a -> sinistro), AltezzaAlbero(a -> destro));
}

Albero costruisciAlbero(TipoInfoAlbero elem, Albero sx, Albero dx) {
    Albero aux;

    aux = (Albero) malloc(sizeof(NodoAlbero));

    if (aux == NULL) {
        printf("Errore allocazione\n");
        exit(-1);
    }

    aux->info = elem;
    aux->sinistro = sx;
    aux->destro = dx;

    return aux;
}

Albero ricercaAlbero(Albero a, TipoInfoAlbero elem) {
    Albero pila[DIM_MAX];
    int top = -1;
    Albero corrente;

    if (isEmpty(a)) return NULL;

    pila[++top] = a;

    while (top != -1) {
        corrente = pila[top--];

        if (corrente -> info == elem) {
            return corrente;
        }

        if (corrente -> destro != NULL) {
            pila[++top] = corrente -> destro;
        }

        if (corrente -> sinistro != NULL) {
            pila[++top] = corrente -> sinistro;
        }
    }
    return NULL;
}

int main(void) {
    Albero a;
    Albero trovato;
    int altezza;
    initAlbero(&a);

    a = costruisciAlbero(
        49,
        costruisciAlbero(
            22,
            costruisciAlbero(17, NULL, NULL),
            costruisciAlbero(8, NULL, NULL)
            ),
            costruisciAlbero(82,
                costruisciAlbero(57, NULL, NULL),
                costruisciAlbero(91, NULL, NULL)
            )
        );

    trovato = ricercaAlbero(a, 57);


    if (trovato != NULL) {
        printf("Elemento trovato: %d\n", trovato -> info);
    } else {
        printf("Elemento non trovato\n");
    }

    altezza = AltezzaAlbero(a);
    printf("Altezza albero: %d\n", altezza);

    return 0;
}