#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_COD 16
#define MAX_NOME 40
#define MAX_ID 16
#define MAX_DESC 100
#define OK 1
#define ERRORE 0

typedef struct {
    char id[MAX_ID];
    int urgenza;
    int distanza_km;
    char descrizione[MAX_DESC];
} Missione;

typedef struct nodo_missione {
    Missione info;
    struct nodo_missione *next;
} NodoMissione;

typedef NodoMissione *PilaMissioni;

typedef struct {
    char codice[MAX_COD];
    char nome[MAX_NOME];
    PilaMissioni missioni;
} BaseDrone;

typedef struct {
    BaseDrone *elementi;
    unsigned n;
} VettoreBasi;

typedef struct {
    char codice_base[MAX_COD];
    Missione missione;
} MissioneInviata;

typedef struct nodo_inviata {
    MissioneInviata info;
    struct nodo_inviata *next;
} NodoInviata;

typedef struct {
    NodoInviata *primo;
    NodoInviata *ultimo;
} CodaInviate;

typedef struct {
    char codice[MAX_COD];
    char nome[MAX_NOME];
    unsigned pendenti;
    unsigned inviate;
    unsigned km_totali_inviati;
} StatBase;

void inizializza_coda(CodaInviate *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}

int push_missione(PilaMissioni *pila, Missione m) {
    NodoMissione *nuovo = malloc(sizeof(NodoMissione));
    if (!nuovo) return ERRORE;
    nuovo->info = m;
    nuovo->next = *pila;
    *pila = nuovo;
    return OK;
}

int pop_missione(PilaMissioni *pila, Missione *m) {
    if (*pila == NULL) return ERRORE;
    NodoMissione *temp = *pila;
    *m = temp->info;
    *pila = temp->next;
    free(temp);
    return OK;
}

int enqueue_inviata(CodaInviate *coda, MissioneInviata mi) {
    NodoInviata *nuovo = malloc(sizeof(NodoInviata));
    if (!nuovo) return ERRORE;
    nuovo->info = mi;
    nuovo->next = NULL;
    if (coda->ultimo == NULL) {
        coda->primo = nuovo;
        coda->ultimo = nuovo;
    } else {
        coda->ultimo->next = nuovo;
        coda->ultimo = nuovo;
    }
    return OK;
}

int cerca_base(VettoreBasi basi, const char *codice) {
    for (unsigned i = 0; i < basi.n; i++) {
        if (strcmp(basi.elementi[i].codice, codice) == 0)
            return (int)i;
    }
    return -1;
}

int aggiungi_base(VettoreBasi *basi, const char *codice, const char *nome) {
    if (cerca_base(*basi, codice) != -1) return ERRORE;

    BaseDrone *tmp = realloc(basi->elementi, (basi->n + 1) * sizeof(BaseDrone));
    if (!tmp) return ERRORE;

    basi->elementi = tmp;
    strcpy(basi->elementi[basi->n].codice, codice);
    strcpy(basi->elementi[basi->n].nome, nome);
    basi->elementi[basi->n].missioni = NULL;
    basi->n++;
    return OK;
}

unsigned conta_pila(PilaMissioni pila) {
    unsigned count = 0;
    while (pila != NULL) {
        count++;
        pila = pila->next;
    }
    return count;
}

/* QUESITO 1
   File:
   BASE codice nome
   MISSIONE codice_base id urgenza distanza_km descrizione

   - creare dinamicamente il vettore delle basi
   - per ogni BASE usare aggiungi_base()
   - per ogni MISSIONE trovare la base corrispondente
   - inserire la missione nella PILA della base con push_missione()

   La missione letta per ultima per una base diventa la TESTA della pila.
   Restituire 1 successo, 0 errore.
*/
int carica_dati(const char *nome_file, VettoreBasi *basi) {
    /* TODO QUESITO 1 */
    if (!nome_file) return 0;

    FILE *fp = fopen(nome_file, "r");
    if (!fp) return 0;
    char tipo[10];
    BaseDrone base;
    Missione m;

    while (fscanf(fp, "%s", tipo) == 1) {
        if (strcmp(tipo, "BASE") == 0) {
            if (fscanf(fp, "%s %s",
                       base.codice,
                       base.nome) != 2) {
                fclose(fp);
                return 0;
            }

            if (aggiungi_base(basi,
                              base.codice,
                              base.nome) != OK) {
                fclose(fp);
                return 0;
            }
        }
        if (strcmp(tipo, "MISSIONE") == 0) {
            if (fscanf(fp, "%s %s %d %d %s", base.codice, m.id, &m.urgenza, &m.distanza_km, m.descrizione) != 5) {
                fclose(fp);
                return 0;
            }
            int trovato = cerca_base(*basi, base.codice);
            if (trovato == -1) {
                fclose(fp);
                return 0;
            }

            if (push_missione(&basi->elementi[trovato].missioni, m) != OK) {
                fclose(fp);
                return 0;
            }
        }
    }
    fclose(fp);
    return 1;
}

/* QUESITO 2 - LOGICA
   Puoi considerare SOLO la TESTA della pila di ogni base.

   Scegli la missione migliore secondo:
   1. urgenza PIU' ALTA
   2. a parita': distanza_km PIU' BASSA
   3. a parita': codice_base alfabeticamente PIU' PICCOLO

   Poi:
   - pop solo dalla pila vincitrice
   - crea MissioneInviata
   - enqueue nella coda globale

   Se tutte le pile sono vuote -> 0, altrimenti 1.
*/
int invia_missione_migliore(VettoreBasi *basi, CodaInviate *inviate) {
    /* TODO QUESITO 2 */
    if (!basi) return 0;
    NodoMissione *temp = NULL;
    int migliore = -1;
    for (unsigned i = 0; i < basi->n; i++) {
        NodoMissione *nodo = basi->elementi[i].missioni;
        if (nodo != NULL) {
            if (temp == NULL) {
                temp = nodo;
                migliore = i;
            }
            if (nodo->info.urgenza > temp->info.urgenza
                || (nodo->info.urgenza == temp->info.urgenza && nodo->info.distanza_km < temp->info.distanza_km)
                || (nodo->info.urgenza == temp->info.urgenza && nodo->info.distanza_km == temp->info.distanza_km && strcmp(basi->elementi[i].codice, basi->elementi[migliore].codice) < 0)) {
                temp = nodo;
                migliore = i;
            }
        }
    }

    if (migliore == -1) return 0;
    Missione m;
    if (pop_missione(&basi->elementi[migliore].missioni, &m) != OK) {
        return 0;
    }

    MissioneInviata invi;
    strcpy(invi.codice_base, basi->elementi[migliore].codice);
    invi.missione = m;

    if (enqueue_inviata(inviate, invi) != OK) {
        return 0;
    }

    return 1;
}

/* QUESITO 3 - LOGICA + VETTORI
   Creare dinamicamente un vettore ausiliario StatBase.

   Per ogni base:
   - pendenti = numero missioni ancora nella pila
   - inviate = numero elementi nella coda con lo stesso codice_base
   - km_totali_inviati = somma delle distanze_km delle missioni inviate

   Ordinare con INSERTION SORT secondo:
   1. inviate DECRESCENTE
   2. a parita': km_totali_inviati CRESCENTE
   3. a parita': codice CRESCENTE

   Scrivere:
   codice nome inviate pendenti km_totali_inviati

   NON modificare vettore originale o coda.
   Liberare il vettore ausiliario.
*/
int salva_statistiche(const char *nome_file, VettoreBasi basi, CodaInviate inviate) {
    /* TODO QUESITO 3 */
    StatBase *stats = malloc(basi.n * sizeof(StatBase));
    if (!stats) return 0;
    for (unsigned i = 0; i < basi.n; i++) {
        strcpy(stats[i].codice, basi.elementi[i].codice);
        strcpy(stats[i].nome, basi.elementi[i].nome);
        stats[i].pendenti = conta_pila(basi.elementi[i].missioni);
        stats[i].km_totali_inviati = 0;
        stats[i].inviate = 0;

        NodoInviata *corrente = inviate.primo;
        while (corrente != NULL) {
            if (strcmp(corrente->info.codice_base, stats[i].codice) == 0) {
                stats[i].inviate++;

                stats[i].km_totali_inviati += corrente->info.missione.distanza_km;
            }
            corrente = corrente->next;
        }
    }

    for (unsigned i = 1; i < basi.n; i++) {
        StatBase key = stats[i];
        int j = i - 1;
        while (j>=0 && (stats[j].inviate < key.inviate
            || (stats[j].inviate == key.inviate && stats[j].km_totali_inviati > key.km_totali_inviati)
            || (stats[j].inviate == key.inviate && stats[j].km_totali_inviati == key.km_totali_inviati && strcmp(stats[j].codice, key.codice) > 0))) {
            stats[j+1] = stats[j];
            j--;
        }
        stats[j+1] = key;
    }

    FILE *fp = fopen(nome_file, "w");
    if (!fp) {
        free(stats);
        return 0;
    }

    for (unsigned i = 0; i < basi.n; i++) {
        fprintf(fp, "%s %s %u %u %u\n", stats[i].codice, stats[i].nome, stats[i].inviate, stats[i].pendenti, stats[i].km_totali_inviati);
    }

    fclose(fp);
    free(stats);
    return 1;
}

/* QUESITO 4 - DEALLOCAZIONE
   Liberare:
   1. tutte le pile delle basi
   2. basi.elementi
   3. la coda globale

   Al termine:
   basi->elementi == NULL
   basi->n == 0
   inviate->primo == NULL
   inviate->ultimo == NULL
*/
void dealloca_tutto(VettoreBasi *basi, CodaInviate *inviate) {
    /* TODO QUESITO 4 */
    for (unsigned i = 0; i < basi->n; i++) {
        NodoMissione *nodo = basi->elementi[i].missioni;
        while (nodo != NULL) {
            NodoMissione *temp = nodo;
            nodo = nodo->next;
            free(temp);
        }

        basi->elementi[i].missioni = NULL;
    }

    free(basi->elementi);
    basi->elementi = NULL;
    basi->n = 0;

    NodoInviata *corrente = inviate->primo;
    while (corrente != NULL) {
        NodoInviata *temp = corrente;
        corrente = corrente->next;
        free(temp);
    }

    inviate->primo = NULL;
    inviate->ultimo = NULL;
}

int main(void) {
    VettoreBasi basi = {NULL, 0};
    CodaInviate inviate;
    inizializza_coda(&inviate);

    if (!carica_dati("basi_missioni.txt", &basi)) {
        printf("Errore caricamento dati.\n");
        dealloca_tutto(&basi, &inviate);
        return 1;
    }

    printf("Basi caricate: %u\n", basi.n);

    for (int i = 0; i < 7; i++) {
        if (invia_missione_migliore(&basi, &inviate))
            printf("Missione %d inviata correttamente.\n", i + 1);
        else {
            printf("Nessuna missione disponibile.\n");
            break;
        }
    }

    if (!salva_statistiche("classifica_basi.txt", basi, inviate)) {
        printf("Errore salvataggio statistiche.\n");
        dealloca_tutto(&basi, &inviate);
        return 1;
    }

    printf("Statistiche salvate in classifica_basi.txt\n");
    dealloca_tutto(&basi, &inviate);
    return 0;
}
