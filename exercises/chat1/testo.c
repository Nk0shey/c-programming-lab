#include "../../common/console.h"
/*  ESERCIZIO 2  - Fondamenti di Informatica - Appello del 12/11/2024

Un noleggiatore di monopattini elettrici deve gestire la sua flotta di monopattini elettrici.

 In un file di testo ("monopattini.txt") sono memorizzati l'elenco dei monopattini ed il loro stato corrente.
 Come visibile nel file, per ciascun monopattino, sono memorizzate le seguenti informazioni:
 - codice
 - autonomia residua (in km)
 - stato noleggio (1=noleggiato, 0=disponibile)

 Sviluppare una applicazione ANSI C in cui vengono implementate le seguenti funzioni:

  1. CaricaMonopattini: carica le informazioni presenti nel file in un due liste di monopattini distinte ordinate per codice, una per quelli attualmente in noleggio e l'altra per quelli disponibili.

  2. Noleggia: dato il codice di un monopattino, rimuove tale monopattino dalla lista dei disponibili (se esiste) e lo inserisce nella lista dei noleggiati.

  3. EstraiConAutonomia: seleziona dalla lista dei disponibili i monopattini che hanno una autonomia residua maggiore di un valore soglia inserito dall'utente, e li copia in un apposito vettore di monopattini.
  La funzione deve anche restituire il numero di monopattini copiati nel vettore

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Monopattino {
    char  codice[32];
    float  autonomia;
} TMonopattino;

typedef struct TNodoMonopattino { TMonopattino info; struct TNodoMonopattino *next; } TNodoMonopattino;
typedef TNodoMonopattino* TListaMonopattini;

/* InserisciInTesta: inserisce un elemento in
   testa alla lista passata
*/
int InserisciInTesta(TListaMonopattini* plis, TMonopattino elem) {
    TListaMonopattini paux;

    paux = (TListaMonopattini)malloc(sizeof(TNodoMonopattino));

    if (paux == NULL)
        return 0;

    paux->info = elem;
    paux->next = *plis;

    *plis = paux;

    return 1;
}

//la funzione inserisce in una lista di monopattini in modo ordinato per codice

int InserisciInListaOrdinata(TListaMonopattini *lista, TMonopattino elem){
while (*lista && strcmp((*lista)->info.codice, elem.codice) < 0) lista = &(*lista)->next;
    if (*lista && !strcmp((*lista)->info.codice, elem.codice)) return 0;
    return InserisciInTesta(lista, elem);
}

/*
  1. CaricaMonopattini:
  carica le informazioni presenti nel file in un due liste di monopattini distinte, una per quelli attualmente in noleggio e l'altra per quelli disponibili.
  Parametri di ingresso: nome del file
  Parametri di uscita: listanoleggiati (lista dei monopattini in noleggio), listadisponibili (lista dei monopattini disponibili)
  Valore restituito: numero di elementi totali letti da file
*/
int CaricaMonopattini(char *nomefile, TListaMonopattini* listanoleggiati, TListaMonopattini* listadisponibili ) {
FILE *f = fopen(nomefile, "r"); if (!f) return -1;
    TMonopattino m; int stato, n, count = 0;
    while ((n = fscanf(f, "%31s %f %d", m.codice, &m.autonomia, &stato)) == 3) {
        if ((stato != 0 && stato != 1) || m.autonomia < 0 || !InserisciInListaOrdinata(stato ? listanoleggiati : listadisponibili, m)) { fclose(f); return -1; }
        ++count;
    }
    int ok = n == EOF && !ferror(f); fclose(f); return ok ? count : -1;
}

/*
  2. Noleggia:
  dato il codice di un monopattino, rimuove tale monopattino dalla lista dei disponibili (se esiste) e lo
  inserisce nella lista dei noleggiati.
  Parametri di ingresso: codice monopattino da noleggiare, lista dei monopattini disponibili,
  Parametri di uscita: lista dei monopattini noleggiati
  Valore restituito: 1 se il monopattino richiesto era presente nella lista dei disponibili
  ed è stato spostato in quella dei noleggiati, 0 altrimenti
*/
int Noleggia(char* codice, TListaMonopattini* listadisponibili, TListaMonopattini* listanoleggiati) {
while (*listadisponibili && strcmp((*listadisponibili)->info.codice, codice)) listadisponibili = &(*listadisponibili)->next;
    if (!*listadisponibili) return 0;
    if (!InserisciInListaOrdinata(listanoleggiati, (*listadisponibili)->info)) return 0;
    TListaMonopattini n = *listadisponibili; *listadisponibili = n->next; free(n); return 1;
}

/*
  3. EstraiConAutonomia:
  seleziona dalla lista dei disponibili i monopattini che hanno una autonomia residua maggiore di un valore soglia inserito dall'utente, e li copia in un apposito vettore di monopattini.
  La funzione deve anche restituire il numero di monopattini copiati nel vettore
  Parametri di ingresso: lis - lista di monopattini, valore soglia
  Parametri di uscita: dim - dimensione del vettore restituito
  Valore restituito: TMonopattino* - vettore dei monopattini con autonomia maggiore della soglia
*/
TMonopattino* EstraiConAutonomia(TListaMonopattini lis, float soglia, int* dim) {
*dim = 0;
    for (TListaMonopattini n = lis; n; n = n->next) if (n->info.autonomia > soglia) ++*dim;
    if (!*dim) return NULL;
    TMonopattino *v = malloc((size_t)*dim * sizeof *v);
    if (!v) { *dim = 0; return NULL; }
    int i = 0; for (; lis; lis = lis->next) if (lis->info.autonomia > soglia) v[i++] = lis->info;
    return v;
}

/*
  VisualizzaLista: visualizza le informazioni dei monopattini
  contenuti nella lista passata come parametro
*/
void VisualizzaLista(TListaMonopattini lis) {
    while (lis != NULL){
        printf("%s %.2f\n",
               lis->info.codice,
               lis->info.autonomia);
        lis = lis->next;
    }
}

/*
  VisualizzaVettore: visualizza le informazioni degli studenti
  contenute nel vettore passato come parametro
*/
void VisualizzaVettore(TMonopattino v[], int dim) {
for (int i = 0; i < dim; ++i) printf("%s %.2f\n", v[i].codice, v[i].autonomia);
}

int Menu() {
int scelta = 0; printf("1 Carica | 2 Noleggia | 3 Filtra | 0 Esci: ");
    if (lab_scanf("%d", &scelta) != 1) { return 0; }
    return scelta;
}

void DisallocaLista(TListaMonopattini lista) {
    TListaMonopattini paux;

    while (lista != NULL) {
        paux = lista;
        lista = lista->next;
        free(paux);
    }
}

/******** MAIN **********/
int main(void) {
TListaMonopattini disponibili = NULL, noleggiati = NULL; int scelta;
    while ((scelta = Menu()) != 0) {
        if (scelta == 1) {
            char file[256]; if (lab_scanf("%255s", file) != 1) break;
            printf("Caricati: %d\n", CaricaMonopattini(file, &noleggiati, &disponibili));
            VisualizzaLista(disponibili); VisualizzaLista(noleggiati);
        } else if (scelta == 2) {
            char codice[32]; if (lab_scanf("%31s", codice) != 1) break;
            printf("Noleggio: %d\n", Noleggia(codice, &disponibili, &noleggiati));
        } else if (scelta == 3) {
            float soglia; int dim; if (lab_scanf("%f", &soglia) != 1) break;
            TMonopattino *v = EstraiConAutonomia(disponibili, soglia, &dim);
            VisualizzaVettore(v, dim); free(v);
        }
    }
    DisallocaLista(disponibili); DisallocaLista(noleggiati); return 0;
}
