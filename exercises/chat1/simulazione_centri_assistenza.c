#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODICE 20
#define MAX_DEST 50
#define MAX_CORRIERE 40

#define OK 1
#define ERRORE 0

typedef struct {
    int id_pacco;
    char destinazione[MAX_DEST];
    float peso;
    int priorita;
} Pacco;

typedef struct nodo_pacco {
    Pacco info;
    struct nodo_pacco *next;
} NodoPacco;

typedef struct {
    NodoPacco *primo;
    NodoPacco *ultimo;
} CodaPacchi;

typedef struct {
    char codice[MAX_CODICE];
    CodaPacchi pacchi;
} Centro;

typedef struct nodo_centro {
    Centro info;
    struct nodo_centro *next;
} NodoCentro;

typedef NodoCentro *ListaCentri;

typedef struct {
    Pacco pacco;
    char codice_centro[MAX_CODICE];
    char corriere[MAX_CORRIERE];
} Consegna;

typedef struct nodo_consegna {
    Consegna info;
    struct nodo_consegna *next;
} NodoConsegna;

typedef NodoConsegna *PilaConsegne;

typedef struct {
    char codice_centro[MAX_CODICE];
    unsigned numero_pacchi;
    float peso_totale;
} StatisticaCentro;


/* ============================================================
   PROTOTIPI
   ============================================================ */

void inizializza_coda(CodaPacchi *coda);

void inizializza_strutture(
    ListaCentri *lista,
    PilaConsegne *pila
);

int inserisci_centro_ordinato(
    ListaCentri *lista,
    const char codice[]
);

int enqueue_pacco(
    CodaPacchi *coda,
    Pacco pacco
);

int carica_dati(
    ListaCentri *lista,
    const char nome_file_centri[],
    const char nome_file_pacchi[]
);

int consegna_pacco(
    ListaCentri lista,
    const char codice_centro[],
    const char corriere[],
    PilaConsegne *pila
);

unsigned conta_pacchi_destinazione(
    const ListaCentri lista,
    const char destinazione[]
);

NodoCentro *centro_piu_carico(
    ListaCentri lista
);

unsigned crea_statistiche(
    ListaCentri lista,
    StatisticaCentro v[],
    unsigned max
);

void ordina_statistiche(
    StatisticaCentro v[],
    unsigned n
);

NodoConsegna *cerca_consegna(
    PilaConsegne pila,
    int id_pacco
);

void dealloca_tutto(
    ListaCentri *lista,
    PilaConsegne *pila
);

int rimuovi_centro_vuoto(
    ListaCentri *lista,
    const char codice[]
);


/* ============================================================
   QUESITO 1
   Inizializzazione della coda
   ============================================================ */

void inizializza_coda(CodaPacchi *coda) {
    /* TODO QUESITO 1A */
    coda->primo = NULL;
    coda->ultimo = NULL;
}


/* ============================================================
   QUESITO 1
   Inizializzazione delle strutture principali
   ============================================================ */

void inizializza_strutture(
    ListaCentri *lista,
    PilaConsegne *pila
) {
    /* TODO QUESITO 1B */
    *lista = NULL;
    *pila = NULL;
}


/* ============================================================
   QUESITO 2
   Inserimento ordinato di un centro
   ============================================================ */

int inserisci_centro_ordinato(
    ListaCentri *lista,
    const char codice[]
) {
if (strlen(codice) >= MAX_CODICE) return ERRORE;
    while (*lista && strcmp((*lista)->info.codice, codice) < 0) lista = &(*lista)->next;
    if (*lista && !strcmp((*lista)->info.codice,codice)) return ERRORE;
    NodoCentro *n = malloc(sizeof *n); if (!n) return ERRORE;
    strcpy(n->info.codice,codice); inizializza_coda(&n->info.pacchi);
    n->next = *lista; *lista = n; return OK;
}


/* ============================================================
   QUESITO 3
   Inserimento di un pacco in fondo alla coda
   ============================================================ */

int enqueue_pacco(
    CodaPacchi *coda,
    Pacco pacco
) {
NodoPacco *n = malloc(sizeof *n); if (!n) return ERRORE;
    n->info = pacco; n->next = NULL;
    if (coda->ultimo) coda->ultimo->next = n; else coda->primo = n;
    coda->ultimo = n; return OK;
}


/* ============================================================
   QUESITO 4
   Caricamento dei dati da file
   ============================================================ */

int carica_dati(
    ListaCentri *lista,
    const char nome_file_centri[],
    const char nome_file_pacchi[]
) {
/* Formats: one centre code per record; then code id destination weight priority. */
    FILE *fc = fopen(nome_file_centri,"r"); if (!fc) return ERRORE;
    FILE *fp = fopen(nome_file_pacchi,"r"); if (!fp) { fclose(fc); return ERRORE; }
    ListaCentri temp = NULL; PilaConsegne empty = NULL; char codice[MAX_CODICE]; int n,ok = OK;
    while ((n = fscanf(fc,"%19s",codice)) == 1) if (!inserisci_centro_ordinato(&temp,codice)) { ok = ERRORE; break; }
    if (n != EOF || ferror(fc)) ok = ERRORE;
    Pacco p;
    while (ok && (n = fscanf(fp,"%19s %d %49s %f %d",codice,&p.id_pacco,p.destinazione,&p.peso,&p.priorita)) == 5) {
        NodoCentro *c = temp; while (c && strcmp(c->info.codice,codice)) c = c->next;
        if (!c || p.peso < 0 || !enqueue_pacco(&c->info.pacchi,p)) ok = ERRORE;
    }
    if (n != EOF || ferror(fp)) ok = ERRORE;
    fclose(fc); fclose(fp);
    if (!ok) { dealloca_tutto(&temp,&empty); return ERRORE; }
    dealloca_tutto(lista,&empty); *lista = temp; return OK;
}


/* ============================================================
   QUESITO 5
   Consegna di un pacco:
   - estrazione dalla coda del centro
   - inserimento nella pila globale delle consegne
   ============================================================ */

int consegna_pacco(
    ListaCentri lista,
    const char codice_centro[],
    const char corriere[],
    PilaConsegne *pila
) {
while (lista && strcmp(lista->info.codice,codice_centro)) lista = lista->next;
    if (!lista || !lista->info.pacchi.primo || strlen(corriere) >= MAX_CORRIERE) return ERRORE;
    NodoConsegna *n = malloc(sizeof *n); if (!n) return ERRORE;
    NodoPacco *p = lista->info.pacchi.primo;
    n->info.pacco = p->info; strcpy(n->info.codice_centro,codice_centro); strcpy(n->info.corriere,corriere);
    n->next = *pila; *pila = n;
    lista->info.pacchi.primo = p->next; if (!p->next) lista->info.pacchi.ultimo = NULL;
    free(p); return OK;
}


/* ============================================================
   QUESITO 6
   Conteggio dei pacchi con una certa destinazione
   La struttura non deve essere modificata.
   ============================================================ */

unsigned conta_pacchi_destinazione(
    const ListaCentri lista,
    const char destinazione[]
) {
unsigned count = 0;
    for (NodoCentro *c = lista; c; c = c->next) for (NodoPacco *p = c->info.pacchi.primo; p; p = p->next)
        if (!strcmp(p->info.destinazione,destinazione)) ++count;
    return count;
}


/* ============================================================
   QUESITO 7
   Centro con il maggior numero di pacchi
   In caso di parita', restituire il primo nella lista.
   ============================================================ */

NodoCentro *centro_piu_carico(
    ListaCentri lista
) {
NodoCentro *best = NULL; unsigned maximum = 0;
    for (; lista; lista = lista->next) { unsigned n = 0;
        for (NodoPacco *p = lista->info.pacchi.primo; p; p = p->next) ++n;
        if (!best || n > maximum) { best = lista; maximum = n; }
    } return best;
}


/* ============================================================
   QUESITO 8
   Creazione del vettore delle statistiche
   ============================================================ */

unsigned crea_statistiche(
    ListaCentri lista,
    StatisticaCentro v[],
    unsigned max
) {
unsigned n = 0;
    for (; lista && n < max; lista = lista->next, ++n) {
        strcpy(v[n].codice_centro,lista->info.codice); v[n].numero_pacchi = 0; v[n].peso_totale = 0;
        for (NodoPacco *p = lista->info.pacchi.primo; p; p = p->next) { ++v[n].numero_pacchi; v[n].peso_totale += p->info.peso; }
    } return n;
}


/* ============================================================
   QUESITO 9
   Ordinamento decrescente per peso_totale
   Utilizzare INSERTION SORT.
   ============================================================ */

void ordina_statistiche(
    StatisticaCentro v[],
    unsigned n
) {
for (unsigned i = 1; i < n; ++i) { StatisticaCentro x = v[i]; unsigned j = i;
        while (j && v[j-1].peso_totale < x.peso_totale) { v[j] = v[j-1]; --j; } v[j] = x;
    }
}


/* ============================================================
   QUESITO 10
   Ricerca di una consegna nella pila
   La pila non deve essere modificata.
   ============================================================ */

NodoConsegna *cerca_consegna(
    PilaConsegne pila,
    int id_pacco
) {
for (; pila; pila = pila->next) if (pila->info.pacco.id_pacco == id_pacco) return pila;
    return NULL;
}


/* ============================================================
   QUESITO 11
   Deallocazione completa di:
   - tutte le code dei pacchi
   - lista dei centri
   - pila delle consegne
   ============================================================ */

void dealloca_tutto(
    ListaCentri *lista,
    PilaConsegne *pila
) {
while (*lista) { NodoCentro *c = *lista; *lista = c->next;
        while (c->info.pacchi.primo) { NodoPacco *p = c->info.pacchi.primo; c->info.pacchi.primo = p->next; free(p); } free(c);
    }
    while (*pila) { NodoConsegna *p = *pila; *pila = p->next; free(p); }
}


/* ============================================================
   BONUS
   Rimuove un centro soltanto se la sua coda e' vuota.
   ============================================================ */

int rimuovi_centro_vuoto(
    ListaCentri *lista,
    const char codice[]
) {
while (*lista && strcmp((*lista)->info.codice,codice)) lista = &(*lista)->next;
    if (!*lista || (*lista)->info.pacchi.primo) return ERRORE;
    NodoCentro *n = *lista; *lista = n->next; free(n); return OK;
}


/* ============================================================
   MAIN DI TEST
   Puoi modificarlo liberamente per provare le tue funzioni.
   ============================================================ */

int main(void) {
ListaCentri lista = NULL; PilaConsegne pila = NULL;
    const char *codes[] = {"CT03","MI02","PA01","BO05"};
    for (int i = 0; i < 4; ++i) if (!inserisci_centro_ordinato(&lista,codes[i])) { dealloca_tutto(&lista,&pila); return 1; }
    for (NodoCentro *c = lista; c; c = c->next) printf("%s\n",c->info.codice);
    Pacco p = {1001,"Roma",4.5f,2};
    NodoCentro *c = lista; while (c && strcmp(c->info.codice,"CT03")) c = c->next;
    if (!c || !enqueue_pacco(&c->info.pacchi,p)) { dealloca_tutto(&lista,&pila); return 1; }
    printf("Pacchi Roma: %u\n",conta_pacchi_destinazione(lista,"Roma"));
    if (!consegna_pacco(lista,"CT03","Demo",&pila)) { dealloca_tutto(&lista,&pila); return 1; }
    dealloca_tutto(&lista,&pila); return 0;
}
