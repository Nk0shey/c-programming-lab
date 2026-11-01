/*
 * Scrivere un programma C in cui:
 * a) dato un vettore di N interi, sia possibile costruire una lista di interi contenente gli stessi elementi del
 *      vettore, rispettandone l’ordinamento (v[0] primo elemento della lista, v[1] secondo elemento, ecc.);
 * b) leggendo gli elementi direttamente dalla lista, si stampino a video gli elementi della lista in ordine inverso
 * (dall’ultimo elemento al primo)
*/

#include <stdlib.h>
#include <stdio.h>

#define N 10

typedef int tipoElemLista;

typedef struct StructLista {
    tipoElemLista info;
    struct StructLista* next;
}TipoNodoLista;

typedef TipoNodoLista* List;


//inizializza la lista
void emptyList(List* l) {
    //da implementare a cura dello studente
    *l = NULL;
}

int isEmpty(List l) {
    return (l == NULL);
    //da implementare a cura dello studente
}

//inserimento di un nuovo elemento in testa
int cons(List* l, tipoElemLista elem) {
    List aux;
    aux = (List) malloc(sizeof(TipoNodoLista));
    if (aux == NULL) {
        printf("Errore allocazione memoria");
        return 0;
    }

    aux -> info = elem;
    aux -> next = *l;
    *l = aux;
    return 1;
    //da implementare a cura dello studente
}

//cancella tutti gli elementi della lista
void CancellaLista(List* l) {
    //da implementare a cura dello studente
    List paux;
    if (*l != NULL) {
        paux = (*l)->next;
        free(*l);
        CancellaLista(&paux);
        *l = NULL;
    }
}


void stampaLista(List l) {
    //da implementare a cura dello studente
    if (isEmpty(l)) {
        return;
    }
    stampaLista(l -> next);
    printf("%d ", l -> info);
}

int main(void) {

    List l;
    int v[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    emptyList(&l);
    for (int i = N-1; i >= 0; i--) {
        cons(&l, v[i]);
    }

    stampaLista(l);
    CancellaLista(&l);
    printf("\nLa lista cancellata? %d", isEmpty(l));

    //da implementare a cura dello studente

    return 0;
}