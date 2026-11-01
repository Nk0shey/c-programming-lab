/*
===============================================================================
SIMULAZIONE DI ALLENAMENTO - GESTIONE ADT
Fondamenti di Programmazione - Modulo 2
Allenamento mirato: VETTORI, LISTE, PILE, CODE

OBIETTIVO:
Allenarti esclusivamente sulle operazioni tipiche che possono comparire
nell'esame: inizializzazione, inserimento, estrazione, ricerca, visita,
trasferimento tra ADT e deallocazione.

REGOLE:
- NON cambiare le typedef.
- NON usare variabili globali.
- NON usare array dinamici.
- Usare malloc/free per le strutture collegate.
- Le funzioni devono restituire OK/ERRORE dove previsto.
- Il main e' volutamente solo parzialmente completato.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERRORE 0
#define DIM_MAX 50
#define MAX_CODICE 16
#define MAX_NOME 40

/* ============================================================================
   TIPO BASE
   ========================================================================== */

typedef struct {
    int id;
    char nome[MAX_NOME];
    int priorita;
} Elemento;


/* ============================================================================
   1. VETTORE
   ========================================================================== */

typedef struct {
    Elemento dati[DIM_MAX];
    unsigned n;
} VettoreElementi;


/* ============================================================================
   2. LISTA COLLEGATA
   ========================================================================== */

typedef struct nodo_lista {
    Elemento info;
    struct nodo_lista *next;
} NodoLista;

typedef NodoLista *Lista;


/* ============================================================================
   3. PILA COLLEGATA
   ========================================================================== */

typedef struct nodo_pila {
    Elemento info;
    struct nodo_pila *next;
} NodoPila;

typedef NodoPila *Pila;


/* ============================================================================
   4. CODA COLLEGATA
   ========================================================================== */

typedef struct nodo_coda {
    Elemento info;
    struct nodo_coda *next;
} NodoCoda;

typedef struct {
    NodoCoda *primo;
    NodoCoda *ultimo;
} Coda;


/* ============================================================================
   PROTOTIPI
   ========================================================================== */

/* VETTORE */
void inizializza_vettore(VettoreElementi *v);
int inserisci_fondo_vettore(VettoreElementi *v, Elemento e);
int cerca_id_vettore(const VettoreElementi *v, int id);
int elimina_indice_vettore(VettoreElementi *v, unsigned indice);
void stampa_vettore(const VettoreElementi *v);

/* LISTA */
void inizializza_lista(Lista *lista);
int inserisci_testa_lista(Lista *lista, Elemento e);
int inserisci_ordinato_lista(Lista *lista, Elemento e);
NodoLista *cerca_lista(Lista lista, int id);
int elimina_id_lista(Lista *lista, int id);
void stampa_lista(Lista lista);
void dealloca_lista(Lista *lista);

/* PILA */
void inizializza_pila(Pila *pila);
int push(Pila *pila, Elemento e);
int pop(Pila *pila, Elemento *e);
int top(Pila pila, Elemento *e);
int pila_vuota(Pila pila);
void stampa_pila(Pila pila);
void dealloca_pila(Pila *pila);

/* CODA */
void inizializza_coda(Coda *coda);
int enqueue(Coda *coda, Elemento e);
int dequeue(Coda *coda, Elemento *e);
int front(Coda coda, Elemento *e);
int coda_vuota(Coda coda);
void stampa_coda(Coda coda);
void dealloca_coda(Coda *coda);

/* ESERCIZI MISTI */
unsigned trasferisci_prioritari_lista_pila(
    Lista *lista,
    Pila *pila,
    int priorita_minima
);

unsigned sposta_coda_in_vettore(
    Coda *coda,
    VettoreElementi *v,
    unsigned max_elementi
);

int estrai_massimo_vettore(
    VettoreElementi *v,
    Elemento *estratto
);

void svuota_pila_in_coda(
    Pila *pila,
    Coda *coda
);


/* ============================================================================
   QUESITO 1 - VETTORE
   ========================================================================== */

/*
1A) Inizializzare il vettore impostando il numero di elementi a 0.
*/
void inizializza_vettore(VettoreElementi *v) {
    /* TODO QUESITO 1A */
    v->n = 0;
}


/*
1B) Inserire un elemento in fondo al vettore.
Restituisce ERRORE se:
- v == NULL
- il vettore e' pieno
Altrimenti restituisce OK.
*/
int inserisci_fondo_vettore(VettoreElementi *v, Elemento e) {
    /* TODO QUESITO 1B */
    if (!v) return ERRORE;

    if (v->n == DIM_MAX) return ERRORE;
    v->dati[v->n] = e;
    v->n++;

    return OK;
}


/*
1C) Cercare un elemento per id.
Restituisce l'indice se trovato, -1 altrimenti.
*/
int cerca_id_vettore(const VettoreElementi *v, int id) {
    /* TODO QUESITO 1C */

    if (v == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < v->n; i++) {
        if (v->dati[i].id == id) {
            return i;
        }
    }

    return -1;
}


/*
1D) Eliminare l'elemento in posizione indice.
Gli elementi successivi devono essere spostati a sinistra.
Restituisce ERRORE se indice non valido.
*/
int elimina_indice_vettore(VettoreElementi *v, unsigned indice) {
    /* TODO QUESITO 1D */

    if (v == NULL) {
        return ERRORE;
    }


    if (indice >= v->n) {
        return ERRORE;
    }

    for (unsigned i = indice; i < v->n - 1; i++) {
        v->dati[i] = v->dati[i + 1];
    }
    v->n--;
    return OK;
}


/*
1E) Stampare tutti gli elementi del vettore.
*/
void stampa_vettore(const VettoreElementi *v) {
    /* TODO QUESITO 1E */

    if (v == NULL) {
        return;
    }

    for (unsigned i = 0; i < v->n; i++) {
        printf("ID: %d | Nome: %s | Priorita: %d\n",
               v->dati[i].id,
               v->dati[i].nome,
               v->dati[i].priorita);
    }

}


/* ============================================================================
   QUESITO 2 - LISTA
   ========================================================================== */

/*
2A) Inizializzare la lista vuota.
*/
void inizializza_lista(Lista *lista) {
    /* TODO QUESITO 2A */
    *lista = NULL;
}


/*
2B) Inserire un nuovo nodo in testa.
*/
int inserisci_testa_lista(Lista *lista, Elemento e) {
    /* TODO QUESITO 2B */
    if (!lista) return ERRORE;
    NodoLista *corrente = *lista;

    NodoLista *nuovo = malloc(sizeof(NodoLista));
    if (!nuovo) return ERRORE;

    nuovo->info = e;
    nuovo->next = NULL;

    nuovo->next = corrente;
    *lista = nuovo;

    return OK;
}


/*
2C) Inserire un elemento mantenendo la lista ordinata per id crescente.
Non sono ammessi id duplicati.

Esempio:
10 -> 30 -> 50
inserimento 40
10 -> 30 -> 40 -> 50
*/
int inserisci_ordinato_lista(Lista *lista, Elemento e) {
if (!lista) return ERRORE;
    while (*lista && (*lista)->info.id<e.id) lista=&(*lista)->next;
    if (*lista && (*lista)->info.id==e.id) return ERRORE;
    return inserisci_testa_lista(lista,e);
}


/*
2D) Cercare il nodo con un determinato id.
Restituire il puntatore al nodo oppure NULL.
*/
NodoLista *cerca_lista(Lista lista, int id) {

    if (!lista) return NULL;
    NodoLista *corrente = lista;
    while (corrente != NULL) {
        if (corrente->info.id == id) {
            return corrente;
        }
        corrente = corrente->next;
    }
    return NULL;
}


/*
2E) Eliminare dalla lista il nodo con id indicato.
Gestire correttamente:
- lista vuota
- eliminazione del primo nodo
- eliminazione di un nodo interno
- id assente
*/
int elimina_id_lista(Lista *lista, int id) {
    /* TODO QUESITO 2E */
    if (!lista) return ERRORE;
    NodoLista *trovato = cerca_lista(*lista, id);
    if (!trovato) return ERRORE;

    if (trovato == *lista) {
        *lista = trovato->next;
        free(trovato);
        return OK;
    }

    NodoLista *corrente = *lista;
    while (corrente->next != trovato) {
        corrente = corrente->next;
    }

    corrente->next = trovato->next;
    free(trovato);
    return OK;
}


/*
2F) Stampare la lista senza modificarla.
*/
void stampa_lista(Lista lista) {
    /* TODO QUESITO 2F */
    NodoLista *corrente = lista;
    while (corrente != NULL) {
        printf("ID: %d | Nome: %s | Priorita: %d\n",  corrente->info.id, corrente->info.nome, corrente->info.priorita);
        corrente = corrente->next;
    }
}


/*
2G) Deallocare tutti i nodi della lista.
Al termine *lista deve essere NULL.
*/
void dealloca_lista(Lista *lista) {
while (*lista) { NodoLista *n = *lista; *lista = n->next; free(n); }
}


/* ============================================================================
   QUESITO 3 - PILA
   ========================================================================== */

/*
3A) Inizializzare una pila vuota.
*/
void inizializza_pila(Pila *pila) {
    /* TODO QUESITO 3A */
    *pila = NULL;
}


/*
3B) Push:
inserire e in cima alla pila.
*/
int push(Pila *pila, Elemento e) {
    /* TODO QUESITO 3B */
    if (!pila) return ERRORE;
    NodoPila *nuovo = malloc(sizeof(NodoPila));
    if (!nuovo) return ERRORE;
    nuovo->info = e;
    nuovo->next = *pila;
    *pila = nuovo;

    return OK;
}


/*
3C) Pop:
estrarre l'elemento in cima.
Il nodo deve essere deallocato.
*/
int pop(Pila *pila, Elemento *e) {
    /* TODO QUESITO 3C */
    if (!pila || !*pila) {
        return ERRORE;
    }

    NodoPila *temp = *pila;

    if (e != NULL) {
        *e = temp->info;
    }

    *pila = temp->next;

    free(temp);

    return OK;
}


/*
3D) Top:
leggere l'elemento in cima SENZA rimuoverlo.
*/
int top(Pila pila, Elemento *e) {
    /* TODO QUESITO 3D */
    if (!pila || !e) return ERRORE;

    *e = pila->info;

    return OK;
}


/*
3E) Restituire 1 se la pila e' vuota, 0 altrimenti.
*/
int pila_vuota(Pila pila) {
    /* TODO QUESITO 3E */
    if (pila == NULL) return 1;
    return 0;
}


/*
3F) Stampare la pila dalla cima verso il fondo
SENZA modificarla.
*/
void stampa_pila(Pila pila) {
    /* TODO QUESITO 3F */
    NodoPila *corrente = pila;
    while (corrente != NULL) {
        printf("ID: %d | Nome: %s | Priorita: %d\n", corrente->info.id, corrente->info.nome, corrente->info.priorita);
        corrente = corrente->next;
    }
}


/*
3G) Deallocare completamente la pila.
*/
void dealloca_pila(Pila *pila) {
    /* TODO QUESITO 3G */
    NodoPila *corrente = *pila;
    while (corrente != NULL) {
        NodoPila *temp = corrente;
        corrente = corrente->next;
        free(temp);
    }

    *pila = NULL;
}


/* ============================================================================
   QUESITO 4 - CODA
   ========================================================================== */

/*
4A) Inizializzare una coda vuota.
*/
void inizializza_coda(Coda *coda) {
coda->primo = coda->ultimo = NULL;
}


/*
4B) Enqueue:
inserire un elemento in fondo alla coda.

Attenzione ai due casi:
- coda vuota
- coda non vuota
*/
int enqueue(Coda *coda, Elemento e) {
if (!coda) return ERRORE;
    NodoCoda *n = malloc(sizeof *n); if (!n) return ERRORE;
    n->info = e; n->next = NULL;
    if (coda->ultimo) coda->ultimo->next = n; else coda->primo = n;
    coda->ultimo = n; return OK;
}


/*
4C) Dequeue:
estrarre il primo elemento della coda.

Attenzione:
se viene rimosso l'unico nodo presente,
sia primo sia ultimo devono diventare NULL.
*/
int dequeue(Coda *coda, Elemento *e) {
if (!coda || !coda->primo) return ERRORE;
    NodoCoda *n = coda->primo; if (e) *e = n->info;
    coda->primo = n->next; if (!coda->primo) coda->ultimo = NULL;
    free(n); return OK;
}


/*
4D) Front:
leggere il primo elemento senza rimuoverlo.
*/
int front(Coda coda, Elemento *e) {
if (!coda.primo || !e) { return ERRORE; }
    *e = coda.primo->info;
    return OK;
}


/*
4E) Restituire 1 se la coda e' vuota, 0 altrimenti.
*/
int coda_vuota(Coda coda) {
return coda.primo == NULL;
}


/*
4F) Stampare la coda dal primo all'ultimo
senza modificarla.
*/
void stampa_coda(Coda coda) {
for (NodoCoda *n = coda.primo; n; n = n->next) printf("%d %s %d\n", n->info.id, n->info.nome, n->info.priorita);
}


/*
4G) Deallocare tutti i nodi della coda.
Al termine primo e ultimo devono essere NULL.
*/
void dealloca_coda(Coda *coda) {
while (dequeue(coda, NULL)) { }
}


/* ============================================================================
   QUESITO 5 - OPERAZIONI MISTE TRA ADT
   ========================================================================== */

/*
5A) Trasferire dalla lista alla pila tutti gli elementi con
priorita >= priorita_minima.

Per ogni elemento trasferito:
- deve essere eliminato dalla lista
- deve essere inserito nella pila con push

Restituisce il numero di elementi trasferiti.

ATTENZIONE:
la scansione della lista deve continuare correttamente anche
quando il nodo corrente viene eliminato.
*/
unsigned trasferisci_prioritari_lista_pila(
    Lista *lista,
    Pila *pila,
    int priorita_minima
) {
unsigned count = 0;
    while (*lista) {
        NodoLista *n = *lista;
        if (n->info.priorita >= priorita_minima) {
            if (!push(pila, n->info)) break;
            *lista = n->next; free(n); ++count;
        } else lista = &n->next;
    }
    return count;
}


/*
5B) Estrarre dalla coda al massimo max_elementi elementi e inserirli
in fondo al vettore.

Il trasferimento deve fermarsi se:
- la coda diventa vuota
- sono stati trasferiti max_elementi
- il vettore diventa pieno

Restituisce il numero di elementi realmente trasferiti.
*/
unsigned sposta_coda_in_vettore(
    Coda *coda,
    VettoreElementi *v,
    unsigned max_elementi
) {
unsigned count = 0;
    while (count < max_elementi && v->n < DIM_MAX && coda->primo) {
        Elemento e; dequeue(coda, &e); v->dati[v->n++] = e; ++count;
    }
    return count;
}


/*
5C) Trovare nel vettore l'elemento con priorita massima,
copiarlo in *estratto e rimuoverlo dal vettore.

In caso di parita' scegliere il primo incontrato.

Restituisce ERRORE se il vettore e' vuoto.
*/
int estrai_massimo_vettore(
    VettoreElementi *v,
    Elemento *estratto
) {
if (!v || !estratto || !v->n) return ERRORE;
    unsigned best = 0;
    for (unsigned i = 1; i < v->n; ++i) if (v->dati[i].priorita > v->dati[best].priorita) best = i;
    *estratto = v->dati[best]; return elimina_indice_vettore(v, best);
}


/*
5D) Svuotare completamente la pila trasferendo gli elementi
nella coda.

L'ordine finale nella coda deve corrispondere all'ordine
di estrazione dalla pila.
*/
void svuota_pila_in_coda(
    Pila *pila,
    Coda *coda
) {
while (*pila) {
        if (!enqueue(coda, (*pila)->info)) return;
        pop(pila, NULL);
    }
}


/* ============================================================================
   MAIN - PARZIALMENTE COMPLETATO
   ========================================================================== */

int main(void) {
Lista lista = NULL; Pila pila = NULL; Coda coda = {0}; VettoreElementi v;
    inizializza_vettore(&v);
    Elemento e[] = {{10,"Alpha",2},{20,"Beta",5},{30,"Gamma",1},{40,"Delta",4},{50,"Epsilon",3}};
    for (int i = 0; i < 5; ++i) if (!inserisci_ordinato_lista(&lista, e[i])) goto fail;
    for (int i = 0; i < 3; ++i) if (!enqueue(&coda, e[i])) goto fail;
    if (!push(&pila,e[3]) || !push(&pila,e[4])) goto fail;
    printf("Trasferiti: %u\n", trasferisci_prioritari_lista_pila(&lista,&pila,4));
    printf("Spostati: %u\n", sposta_coda_in_vettore(&coda,&v,2));
    Elemento max;
    if (estrai_massimo_vettore(&v,&max)) printf("Massimo: %d\n",max.id);
    svuota_pila_in_coda(&pila,&coda); stampa_lista(lista); stampa_coda(coda);
    dealloca_lista(&lista); dealloca_pila(&pila); dealloca_coda(&coda); return 0;
fail:
    dealloca_lista(&lista); dealloca_pila(&pila); dealloca_coda(&coda); return 1;
}


/* ============================================================================
   BONUS - DOMANDE DA ESAME ORALE
   ========================================================================== */

/*

1) Perche' la pila e' LIFO?
2) Perche' la coda e' FIFO?
3) Qual e' la differenza strutturale tra una pila collegata e una lista?
4) Perche' in una coda collegata conviene mantenere sia primo che ultimo?
5) Qual e' il costo di push e pop in una pila collegata?
6) Qual e' il costo di enqueue e dequeue nella coda definita sopra?
7) Qual e' il costo della ricerca in una lista collegata?
8) Perche' l'accesso a vettore[i] e' O(1)?
9) Quale problema si verifica se dopo dequeue dell'ultimo nodo
   non si imposta coda->ultimo = NULL?
10) Perche' durante la deallocazione bisogna salvare il puntatore
    al nodo successivo prima di eseguire free()?

===============================================================================
FINE SIMULAZIONE
===============================================================================
*/
