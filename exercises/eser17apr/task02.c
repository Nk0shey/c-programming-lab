//
// Created by kozch on 01.06.2026.
//

/*2. Implementare un programma che:
 permetta di inserire da tastiera valori interi e di salvarli in memoria mediante una
struttura dati dinamica di tipo lista collegata tramite puntatori
 restituisca il numero attuale di nodi che compongono la lista
 restituisca la somma dei valori pari contenuti nella lista
 permetta di verificare se un determinato valore sia presente nella lista
 restituisca il puntatore al nodo contenente il minimo elemento dispari nella lista
(NULL se non contiene elementi dispari)
Scrivere un opportuno main in cui sia previsto un menu di scelta delle precedenti
operazioni*/

#include <stdlib.h>
#include <stdio.h>

typedef int TipoElemLista;

typedef struct StructLista {
    TipoElemLista info;
    struct StructLista *next;
}TipoNodoLista;

typedef TipoNodoLista *List;

void EmptyList(List *l) {
    *l = NULL;
}

int isEmpty(List l) {
    return l == NULL;
}

int cons(List *l, TipoElemLista elem) {
    List aux;
    aux = (List) malloc(sizeof(TipoNodoLista));
    if (aux == NULL) {
        printf("Erro no memoria");
        return 0;
    }
    aux -> info = elem;
    aux -> next = *l;
    *l = aux;
    return 1;
}

void CancellaLista(List *l) {
    List aux;
    while (l != NULL) {
        aux = *l;
        *l = (*l) -> next;
        free(aux);
    }
}

void stampaLista(List l) {
    while (l != NULL) {
        printf("%d ", l -> info);
        l = l -> next;
    }
}

int contaNodi(List l) {
    int conta = 0;
    while (l != NULL) {
        conta++;
        l = l -> next;
    }
    return conta;
}

int sommaPari(List l) {
    int somma = 0;
    while (l != NULL) {
        if (l -> info % 2 == 0) {
            somma += l -> info;
        }
        l = l -> next;
    }
    return somma;
}

int cercaValore(List l, int valore) {
    while (l != NULL) {
        if (l -> info == valore) {
            return 1;
        }
        l = l -> next;
    }
    return 0;
}
List minimoDispari(List l) {
    List minimo = NULL;
    while (l != NULL) {
        if (minimo == NULL || l -> info < minimo -> info) {
            minimo = l;
        }
        l = l -> next;
    }
    return minimo;
}

int main(void) {
List lista;
    int scelta, valore;
    List nodoMin;

    EmptyList(&lista);

    do {
        printf("\n\n--- MENU ---\n");
        printf("1. Inserisci valore\n");
        printf("2. Conta nodi\n");
        printf("3. Somma valori pari\n");
        printf("4. Cerca valore\n");
        printf("5. Minimo dispari\n");
        printf("6. Stampa lista\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Inserisci un valore intero: ");
                scanf("%d", &valore);

                if (cons(&lista, valore)) {
                    printf("Valore inserito correttamente.\n");
                } else {
                    printf("Errore inserimento.\n");
                }
                break;

            case 2:
                printf("Numero nodi: %d\n", contaNodi(lista));
                break;

            case 3:
                printf("Somma valori pari: %d\n", sommaPari(lista));
                break;

            case 4:
                printf("Inserisci valore da cercare: ");
                scanf("%d", &valore);

                if (cercaValore(lista, valore)) {
                    printf("Valore presente nella lista.\n");
                } else {
                    printf("Valore non presente nella lista.\n");
                }
                break;

            case 5:
                nodoMin = minimoDispari(lista);

                if (nodoMin == NULL) {
                    printf("La lista non contiene elementi dispari.\n");
                } else {
                    printf("Minimo dispari: %d\n", nodoMin->info);
                    printf("Indirizzo nodo: %p\n", (void *)nodoMin);
                }
                break;

            case 6:
                printf("Lista: ");
                stampaLista(lista);
                printf("\n");
                break;

            case 0:
                printf("Uscita...\n");
                break;

            default:
                printf("Scelta non valida.\n");
        }

    } while (scelta != 0);

    CancellaLista(&lista);

    return 0;
}