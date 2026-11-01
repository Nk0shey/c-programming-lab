#include "../../common/console.h"
/******************************************************************************
 Scrivere un programma ANSI C per la gestione di una coda di ordini.
    Ogni ordine è caratterizzato da un codice (intero positivo), da una lista di
    prodotti, la loro quantità e da un importo totale.

    Il programma deve consentire la lettura degli ordini da file e la loro
    memorizzazione in una coda.
    Ogni elemento della coda contiene quindi un ordine, costituito dalla
    lista dei prodotti, il numero totale di elementi nell'ordine e dal numero di ordine.

    Il file di input contiene un numero variabile di ordini, e in particolare per ogni riga
     un prodotto, la sua quantita' e l'ordine di appartenenza identificato tramite numero.
     Es.
      // PRODOTTO QUANTITA' ORDINE
      PRODOTTO_1 10 #20
      PRODOTTO_2 5 #20
      ...
      PRODOTTO_1 1 #21
      PRODOTTO_10 1 #21


    Il programma svolge le seguenti operazioni:
    1. Caricamento dei dati dal file in una coda in memoria centrale,
    2. Stampa a video gli ordini;
    3. Reperimento di tutti gli ordini che contengono un certo prodotto. Il prodotto è letto da console.
       Gli ordini corrispondenti vengono inseriti in una lista.
    4. Riepilogo numero di prodotti totali per ordine

 I dettagli delle funzioni e dei parametri sono specificati nella descrizione puntuale
    delle funzioni.

 Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare
    quello esistente tranne quando espressamente richiesto.

 Si raccomanda di scrivere il codice delle funzioni in modo modulare (scomporre
 il problema in sottoproblemi piu' semplici).

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRLEN 64

typedef struct prodotto_struct {
    char nome[STRLEN];
    int quantita;
    struct prodotto_struct* successivo;
} NodoProdotto;

typedef NodoProdotto* ListaProdotti;

typedef struct {
    char id_ordine[STRLEN];
    int numero_prodotti;
    ListaProdotti lista_elementi;
} Ordine;

typedef struct ordine_struct {
    Ordine ordine;
    struct ordine_struct* successivo;
} NodoOrdine;

typedef struct {
    NodoOrdine* primo_elemento;
    NodoOrdine* ultimo_elemento;
} CodaOrdini;

typedef NodoOrdine* ListaOrdini;


// Funzione che stampa a video il riepilogo di un ordine
void stampa_ordine(Ordine ordine) {
    printf("Ordine %s - numero prodotti %d:\n", ordine.id_ordine, ordine.numero_prodotti);
    ListaProdotti prodotto = ordine.lista_elementi;
    while (prodotto != NULL) {
        printf("\t%s, %d\n", prodotto->nome, prodotto->quantita);
        prodotto = prodotto->successivo;
    }
}


/* Funzione che, data una coda di ordini, aggiunge un nuovo ordine alla coda.
 * La funzione restituisce il puntatore al nuovo ordine inserito.
 *
 * Parametri:
 * - coda: puntatore alla coda di ordini
 * - id_ordine: stringa che rappresenta l'identificativo dell'ordine
 * Return:
 * - puntatore al nuovo ordine inserito
 */
NodoOrdine* coda_ordini_aggiungi(CodaOrdini* coda, char* id_ordine) {
    NodoOrdine* nuovo_nodo = (NodoOrdine*)malloc(sizeof(NodoOrdine));
    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }

    strcpy(nuovo_nodo->ordine.id_ordine, id_ordine);
    nuovo_nodo->ordine.numero_prodotti = 0;
    nuovo_nodo->ordine.lista_elementi = NULL;

    nuovo_nodo->successivo = NULL;
    if (coda->primo_elemento == NULL) {
        coda->primo_elemento = nuovo_nodo;
        coda->ultimo_elemento = nuovo_nodo;
    }
    else {
        coda->ultimo_elemento->successivo = nuovo_nodo;
        coda->ultimo_elemento = nuovo_nodo;
    }

    return nuovo_nodo;
}


/* Funzione che, data una lista di prodotti, aggiunge un nuovo prodotto alla lista.
 *
 * Parametri:
 * - lista: puntatore alla lista di prodotti
 * - nome_prodotto: stringa che rappresenta il nome del prodotto
 * - quantita: quantita' del prodotto
 */
void lista_prodotti_aggiungi(ListaProdotti* lista, char* nome_prodotto, int quantita) {
    NodoProdotto* nuovo_nodo = malloc(sizeof(NodoProdotto));

    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }
    strcpy(nuovo_nodo->nome, nome_prodotto);
    nuovo_nodo->quantita = quantita;
    nuovo_nodo->successivo = *lista;
    *lista = nuovo_nodo;
}

/*
 * Funzione che, data una lista di ordini, aggiunge un nuovo ordine alla lista.
 *
 * Parametri:
 * - lista: puntatore alla lista di ordini
 * - ordine: ordine da aggiungere alla lista
 *
 */
void lista_ordini_aggiungi(ListaOrdini* lista, Ordine ordine) {
    NodoOrdine* nuovo_nodo = malloc(sizeof(NodoOrdine));
    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }
    nuovo_nodo->ordine = ordine;
    nuovo_nodo->successivo = *lista;
    *lista = nuovo_nodo;
}

/*
 * Funzione che, data una lista di ordini, cerca un ordine con un certo identificativo.
 * La funzione restituisce il puntatore al nodo contenente l'ordine, se non trovato
 * restituisce NULL.
 *
 * parametri:
 * - lista_ordini: lista di ordini
 * - id_ordine: identificativo dell'ordine da cercare
 * - ppNodoOrdine: puntatore al puntatore del nodo contenente l'ordine
 *
 */
void trova_ordine(ListaOrdini lista_ordini, char* id_ordine, NodoOrdine** ppNodoOrdine) {
    while (lista_ordini != NULL) {
        if (strcmp(lista_ordini->ordine.id_ordine, id_ordine) == 0) {
            *ppNodoOrdine = lista_ordini;
            return;
        }
        lista_ordini = lista_ordini->successivo;
    }
    *ppNodoOrdine = NULL;
}

/*
 * Funzione che, data una lista di prodotti, cerca un prodotto con un certo nome.
 * Se lo trova, restituisce il puntatore al nodo contenente il prodotto, altrimenti
 * restituisce NULL
 *
 * parametri:
 * - lista_prodotti: lista di prodotti
 * - prodotto: nome del prodotto da cercare
 * - ppNodoProdotto: puntatore al puntatore del nodo contenente il prodotto
 */
void trova_prodotto(ListaProdotti lista_prodotti, char prodotto[STRLEN], NodoProdotto** ppNodoProdotto) {
    while (lista_prodotti != NULL) {
        if (strcmp(lista_prodotti->nome, prodotto) == 0) {
            *ppNodoProdotto = lista_prodotti;
            return;
        }
        lista_prodotti = lista_prodotti->successivo;
    }
    *ppNodoProdotto = NULL;
}



void init_coda(CodaOrdini* c) {

    // TODO: DA IMPLEMENTARE
    c->primo_elemento = NULL;
    c->ultimo_elemento = NULL;
}



/*
 * 1. Funzione carica_file
 * Questa funzione carica i dati presenti nel file in una coda passata come
 * parametro, restituendo 0 in caso di fallimento altrimenti 1
 *
 * Il formato del file e' il seguente:
  // PRODOTTO QUANTITA' ID_ORDINE
  PRODOTTO_1 10 #20
  PRODOTTO_2 5 #20
  ...
  PRODOTTO_1 1 #21
  PRODOTTO_10 1 #21

 * Per ogni riga del file, trovare l'ordine corrispondente (se presente, in caso contrario
 * crearlo tramite la funzione apposita) e aggiungere la quantita' del prodotto nella lista dei
 * prodotti dell'ordine (se presente, in caso contrario aggiungerlo tramite la funzione apposita).
 * Ricordarsi di incrementare il numero di prodotti dell'ordine.
 *
 * NOTA BENE: se la coda esiste, non va sovrascritta. I nuovi ordini vanno aggiunti in coda.

 * Parametri: nome del file, coda di eventi
 * Restituisce: 1 se il caricamento e' andato a buon fine,
                0 in caso di errore durante il caricamento
*/
int carica_file(const char* nomefile, CodaOrdini* pc) {
    char ordinestr[STRLEN];
    char prodottostr[STRLEN];
    int quantita;
    NodoOrdine* pNodoOrdine = NULL;
    NodoProdotto* pNodoProdotto = NULL;

    if (pc == NULL) {
        printf("Errore nella coda\n");
        return 0;
    }

    FILE* fp = fopen(nomefile, "r");

    if (fp == NULL) {
        printf("Errore nell'apertura del file %s. Controllare il nome del file e l'estensione e riprovare\n", nomefile);
        return 0;
    }

    while (fscanf(fp, "%s%d%s", prodottostr, &quantita, ordinestr) == 3) {
        trova_ordine(pc->primo_elemento, ordinestr, &pNodoOrdine);
        if (pNodoOrdine == NULL) {
            pNodoOrdine = coda_ordini_aggiungi(pc, ordinestr);
        }
        trova_prodotto(pNodoOrdine->ordine.lista_elementi, prodottostr, &pNodoProdotto);
        if (pNodoProdotto == NULL) {
            lista_prodotti_aggiungi(&pNodoOrdine->ordine.lista_elementi, prodottostr, quantita);
        }
        else {
            pNodoProdotto->quantita += quantita;
        }
        pNodoOrdine->ordine.numero_prodotti += quantita;

    }
    fclose(fp);
    return 1;
}



/*
 * 2. Funzione che stampa il contenuto della coda degli ordini
 */
void stampa_ordini(ListaOrdini lista_ordini) {
    NodoOrdine* nodo_ordine = lista_ordini;
    while (nodo_ordine != NULL) {
        stampa_ordine(nodo_ordine->ordine);
        nodo_ordine = nodo_ordine->successivo;
    }
}




/*
 * 3. Ordini che contengono prodotto
 * Questa funzione cerca tutti gli ordini che contengono un certo prodotto e ne restituisce
 * una lista. Il prodotto e' passato come parametro.
 *
 * Parametri: coda di ordini, nome del prodotto
 * Restituisce: lista di ordini che contengono il prodotto
 */
ListaOrdini ordini_contenenti_prodotto(CodaOrdini coda, char prodotto[STRLEN]) {
    ListaOrdini lista_ordini = NULL;
    NodoOrdine* pNodoOrdine = coda.primo_elemento;
    NodoProdotto* pNodoProdotto = NULL;

    while (pNodoOrdine != NULL) {
        trova_prodotto(pNodoOrdine->ordine.lista_elementi, prodotto, &pNodoProdotto);

        if (pNodoProdotto != NULL) {
            lista_ordini_aggiungi(&lista_ordini, pNodoOrdine->ordine);
        }
        pNodoOrdine = pNodoOrdine->successivo;
    }

    return lista_ordini;
}



/* 4. Riepilogo numero di prodotti totali per ordine
 * Questa funzione restituisce un vettore contenente
 * il numero di prodotti totali per ogni ordine.
 *
 * Parametri: coda di ordini
 * Restituisce: vettore di interi
 */
int* numero_di_prodotti(CodaOrdini codaOrdini, int* numero_ordini) {

    *numero_ordini = 0;
    for (NodoOrdine* pNodoOrdine = codaOrdini.primo_elemento;
        pNodoOrdine != NULL;
        pNodoOrdine = pNodoOrdine->successivo)
        (*numero_ordini)++;

    int* vettore = (int*)malloc(sizeof(int) * (*numero_ordini));
    if (vettore == NULL) {
        printf("Errore nell'allocazione del vettore\n");
        return NULL;
    }

    int i = 0;
    for (NodoOrdine* pNodoOrdine = codaOrdini.primo_elemento;
        pNodoOrdine != NULL;
        pNodoOrdine = pNodoOrdine->successivo)

        vettore[i++] = pNodoOrdine->ordine.numero_prodotti;

    return vettore;
}

void dealloca_lista_ordini(ListaOrdini lista) {

    // TODO: DA IMPLEMENTARE
    NodoOrdine *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->successivo;
        free(aux);
    }
}


int main(void) {
CodaOrdini c={0}; int scelta=0;
    for (;;) {
        printf("1 Carica | 2 Stampa | 3 Filtra | 4 Quantita | 0 Esci: ");
        if (lab_scanf("%d",&scelta)!=1 || scelta==0) break;
        if (scelta==1) { char file[256]; if (lab_scanf("%255s",file)!=1) break; printf("Caricamento: %d\n",carica_file(file,&c)); }
        else if (scelta==2) stampa_ordini(c.primo_elemento);
        else if (scelta==3) { char prodotto[STRLEN]; if (lab_scanf("%63s",prodotto)!=1) break; ListaOrdini l=ordini_contenenti_prodotto(c,prodotto); stampa_ordini(l); dealloca_lista_ordini(l); }
        else if (scelta==4) { int dim; int *v=numero_di_prodotti(c,&dim); if(v) { for(int i=0;i<dim;++i) printf("%d\n",v[i]); free(v); } }
    }
    while(c.primo_elemento) { NodoOrdine *n=c.primo_elemento; c.primo_elemento=n->successivo;
        while(n->ordine.lista_elementi) { NodoProdotto *p=n->ordine.lista_elementi; n->ordine.lista_elementi=p->successivo; free(p); } free(n);
    }
    return 0;
}