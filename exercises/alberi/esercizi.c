//
// Created by kozch on 28.05.2026.
//

#include <stdio.h>
#include <stdlib.h>
#define DIM_MAX 100

typedef int TipoInfoAlbero;

typedef struct nodoAlbero {
    TipoInfoAlbero info;
    struct nodoAlbero *destro, *sinistro;
}NodoAlbero;

typedef NodoAlbero *Albero;

typedef struct nodoLista {
    TipoInfoAlbero info;
    struct nodoLista *next;
} NodoLista;

typedef NodoLista * Lista;

void initLista(Lista *l) {
    *l = NULL;
}

int listaVuota(Lista l) {
    return l == NULL;
}

void inserisciInCoda(Lista *l, TipoInfoAlbero elem) {
    NodoLista *nuovo;
    NodoLista *corrente;

    nuovo = (NodoLista *) malloc(sizeof(NodoLista));
    if (nuovo == NULL) {
        printf("Errore allocazione\n");
        exit(-1);
    }

    nuovo -> info = elem;
    nuovo -> next = NULL;

    if (*l == NULL) {
        *l = nuovo;
    } else {
        corrente = *l;

        while (corrente -> next != NULL) {
            corrente = corrente -> next;
        }

        corrente -> next = nuovo;
    }
}

void stampaLista(Lista l) {
    while (l != NULL) {
        printf("%d ", l -> info);
        l = l -> next;
    }
}

void initAlbero(Albero *a) {
    *a = NULL;
}

int isEmpty(Albero a) {
    return a == NULL;
}

void analizza(TipoInfoAlbero info) {
    printf("%d ", info);
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

Albero creaAlberoEsemplaro(void) {
    Albero a;

    a = costruisciAlbero(
        49,
        costruisciAlbero(
            22,
            costruisciAlbero(
                17,
                costruisciAlbero(85, NULL, NULL),
                costruisciAlbero(8, NULL, NULL)
                ),
                NULL
            ),
            costruisciAlbero(
                82,
                costruisciAlbero(
                    88,
                    costruisciAlbero(57, NULL, NULL),
                        costruisciAlbero(
                            94,
                            costruisciAlbero(91, NULL, NULL),
                            NULL
                        )
                    ),
                    costruisciAlbero(34, NULL, NULL)
                )
            );
    return a;
}

Albero ricercaAlbero(Albero a, TipoInfoAlbero elem) {
    Albero pila[DIM_MAX];
    int top = -1;
    Albero corrente;

    if (isEmpty(a)) {
        return NULL;
    }

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

void VisitaRicorsiva(Albero a) {
    if (!isEmpty(a)) {
        analizza(a->info);
        VisitaRicorsiva(a->sinistro);
        VisitaRicorsiva(a->destro);
    }
}

void visualizzaFoglie(Albero a) {
    if (!isEmpty(a)) {
        if (a -> sinistro == NULL && a -> destro == NULL) {
            analizza(a->info);
        }

        visualizzaFoglie(a->sinistro);
        visualizzaFoglie(a->destro);
    }
}

int sommaNodi(Albero a) {
    if (isEmpty(a)) {
        return 0;
    }

    return a->info + sommaNodi(a->sinistro) + sommaNodi(a->destro);
}

int sommaFoglie(Albero a) {
    if (isEmpty(a)) {
        return 0;
    }
    if (a->sinistro == NULL && a->destro == NULL) {
        return a->info;
    }

    return sommaFoglie(a->sinistro) + sommaFoglie(a->destro);
}

int sommaLivello(Albero a, int livello) {
    if (isEmpty(a)) {
        return 0;
    }

    if (livello == 0) return a->info;
    return sommaLivello(a->sinistro, livello - 1) + sommaLivello(a->destro, livello - 1);
}

int sommaSottoAlbero(Albero a, TipoInfoAlbero elem) {
    Albero sottoalbero;

    sottoalbero = ricercaAlbero(a, elem);

    if (sottoalbero == NULL) {
        return 0;
    }

    return sommaNodi(sottoalbero);
}

void costruisciListaPreordine(Albero a, Lista *l) {
    if (!isEmpty(a)) {
        inserisciInCoda(l, a->info);
        costruisciListaPreordine(a->sinistro, l);
        costruisciListaPreordine(a->destro, l);
    }
}

void costruisciListaPostordine(Albero a, Lista *l) {
    if (!isEmpty(a)) {
        costruisciListaPostordine(a->sinistro, l);
        costruisciListaPostordine(a->destro, l);
        inserisciInCoda(l, a->info);
    }
}

void costruisciListaPerLivelli(Albero a, Lista *l) {
    Albero coda[DIM_MAX];
    int primo = 0;
    int ultimo = -1;
    Albero corrente;

    if (isEmpty(a)) {
        return;
    }

    coda[++ultimo] = a;

    while (primo <= ultimo) {
        corrente = coda[primo++];

        inserisciInCoda(l, corrente->info);

        if (corrente->sinistro != NULL) {
            coda[++ultimo] = corrente->sinistro;
        }

        if (corrente->destro != NULL) {
            coda[++ultimo] = corrente->destro;
        }
    }
}

void costruisciListaFoglie(Albero a, Lista *l) {
    if (!isEmpty(a)) {
        if (a->sinistro == NULL && a->destro == NULL) {
            inserisciInCoda(l, a->info);
        }

        costruisciListaFoglie(a->sinistro, l);
        costruisciListaFoglie(a->destro, l);
    }
}

void costruisciListaLivello(Albero a, int livello, Lista *l) {
    if (isEmpty(a) || livello < 0) {
        return;
    }

    if (livello == 0) {
        inserisciInCoda(l, a->info);
    } else {
        costruisciListaLivello(a->sinistro, livello - 1, l);
        costruisciListaLivello(a->destro, livello - 1, l);
    }
}

int main (void) {
    Albero a;
    int somma_nodi;
    int somma_foglie;
    initAlbero(&a);
    a = creaAlberoEsemplaro();
    printf("Visita preordine: ");
    VisitaRicorsiva(a);

    printf("\nFoglie: ");
    visualizzaFoglie(a);

    somma_nodi = sommaNodi(a);
    printf("\nSomma di tutti i nodi: %d\n", somma_nodi);

    somma_foglie = sommaFoglie(a);
    printf("\nSomma di foglie: %d\n", somma_foglie);

    int livello;
    int somma_livello;

    printf("\nInserisci il livello: ");
    scanf("%d", &livello);

    somma_livello = sommaLivello(a, livello);

    printf("Somma dei nodi al livello %d: %d\n", livello, somma_livello);

    int etichetta;
    int somma_sottoalbero;

    printf("Inserisci l'etichetta radice sottoalbero: ");
    scanf("%d", &etichetta);

    somma_sottoalbero = sommaSottoAlbero(a, etichetta);
    printf("Somma del sottoalbero con radice %d: %d\n", etichetta, somma_sottoalbero);

    Lista lista_preordine;

    initLista(&lista_preordine);
    costruisciListaPreordine(a, &lista_preordine);

    printf("\nLista preordine: ");
    stampaLista(lista_preordine);

    Lista lista_postordine;

    initLista(&lista_postordine);
    costruisciListaPostordine(a, &lista_postordine);

    printf("\nLista postordine: ");
    stampaLista(lista_postordine);

    Lista lista_livelli;

    initLista(&lista_livelli);
    costruisciListaPerLivelli(a, &lista_livelli);

    printf("\nLista per livelli: ");
    stampaLista(lista_livelli);

    Lista lista_foglie;

    initLista(&lista_foglie);
    costruisciListaFoglie(a, &lista_foglie);

    printf("\nLista foglie: ");
    stampaLista(lista_foglie);

    Lista lista_livello1;

    printf("\nInserisci livello: ");
    scanf("%d", &livello);

    initLista(&lista_livello1);
    costruisciListaLivello(a, livello, &lista_livello1);

    printf("Lista nodi al livello %d: ", livello);
    stampaLista(lista_livello1);
}
