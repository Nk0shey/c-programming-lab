/******************************************************************************
 * ===== MODULO 2 =====
 *
 *  Implementare in ANSI C un programma che permetta la gestione dei treni
 *  di una compagnia ferroviaria.
 *
 *  I treni sono caratterizzati da un codice univoco, dalla stazione di partenza,
 *  dalla stazione di arrivo, dal numero di posti totali, dal numero di posti occupati,
 *  e dall'orario di partenza e di arrivo.
 *
 *  Le stazioni sono caratterizzate da un nome e da una coda di treni in partenza.
 *
 *  La struttura dati principale del programma è una lista di stazioni di partenza.
 *
 * Il programma esegue le seguenti operazioni:
 *
 * 2a. Caricare il file Modulo2.txt in una lista di stazioni di partenza (T_stazione).
 *      Ogni stazione contiene una coda di treni di passaggio.
 *
 *
 * 2b. Calcolo del numero di posti disponibili per una data stazione di partenza
 *
 * 2c. Restituzione del tempo di percorrenza per tutti i treni che partono da
 *     una data stazione di partenza
 *
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOME_FILE "Modulo2.txt"

#define STR_LEN 50

/* Struttura dati treno */
typedef struct {
    char codice_treno[STR_LEN];
    char stazione_arrivo[STR_LEN];
    unsigned posti_totali;
    unsigned posti_occupati;
    char orario_partenza[6];
    char orario_arrivo[6];
} T_treno;

/* Struttura dati stazione (coda di treni + altre info sulla stazione) */
typedef struct nodo_coda_treni {
    T_treno treno;
    struct nodo_coda_treni *next;
} NodoCodaTreni;

typedef struct {
    char stazione_partenza[STR_LEN];
    unsigned numero_treni;
    NodoCodaTreni *primo, *ultimo;
} T_stazione;

typedef struct nodo_lista_stazioni {
    T_stazione stazione;
    struct nodo_lista_stazioni *next;
} NodoListaStazioni, *ListaStazioni;

/* Aggiunge in testa alla lista di stazioni una
 * nuova stazione di partenza
 *
 * Parametri in ingresso:
 * - lista_stazioni: puntatore alla lista di stazioni
 * - nome_stazione: nome della stazione da aggiungere
 *
 * Valore di ritorno:
 * - puntatore alla stazione appena aggiunta
 * */
NodoListaStazioni *aggiungi_stazione(ListaStazioni *lista_stazioni, const char *nome_stazione) {
    NodoListaStazioni *nodo = (NodoListaStazioni *) malloc(sizeof(NodoListaStazioni));
    if (nodo == NULL) return NULL;

    strcpy(nodo->stazione.stazione_partenza, nome_stazione);
    nodo->stazione.numero_treni = 0;
    nodo->stazione.primo = nodo->stazione.ultimo = NULL;

    nodo->next = *lista_stazioni;

    *lista_stazioni = nodo;

    return nodo;
}

/*
 * Aggiunge un treno alla coda di treni di una stazione.
 *
 * Parametri in ingresso:
 * - stazione: puntatore alla stazione di partenza
 * - treno: treno da aggiungere
 *
 * Valore di ritorno:
 * - 1 se l'aggiunta è andata a buon fine, 0 altrimenti
 */
int aggiungi_treno(T_stazione *stazione, T_treno treno) {
    NodoCodaTreni *nodo = (NodoCodaTreni *) malloc(sizeof(NodoCodaTreni));
    if (nodo == NULL) return 0;

    nodo->treno = treno;
    nodo->next = NULL;

    if (stazione->primo == NULL) {
        stazione->primo = stazione->ultimo = nodo;
    } else {
        stazione->ultimo->next = nodo;
        stazione->ultimo = nodo;
    }

    stazione->numero_treni++;

    return 1;
}

/* Quesito 2a
 *
 *   Carica i dati dal file e li salva in una lista di
 *   code di treni.
 *
 *   Ogni nodo della lista rappresenta una stazione di partenza,
 *   mentre la coda rappresenta i treni in partenza da quella stazione.
 *
 *
 *     Il file ha il seguente formato:
 *
 *      - 1 riga contenente il nome della stazione di partenza e
 *          il numero N di treni in partenza da quella stazione:
 *
 *          NomeStazionePartenza NumeroTreni
 *
 *          Esempio:
 *          Milano 3
 *
 *      - N righe contenenti i dati dei treni in partenza da quella stazione:
 *          CodiceTreno NomeStazioneArrivo PostiTotali PostiOccupati OrarioPartenza OrarioArrivo
 *
 *          Esempio:
 *          Treno1 Roma 100 50 08:00 10:00
 *          Treno2 Napoli 150 100 09:00 11:00
 *
 *      Il formato si ripete per ogni stazione di partenza fino alla fine del file.
 *
 *	 Parametri in ingresso:
 *	   - nome_file: nome del file da cui caricare i dati
 *
 *	 Parametri in uscita:
 *	   - lista_stazioni: puntatore alla lista di stazioni
 *
 *	 Valore di ritorno:
 *	   - numero di stazioni caricate
 * */
int carica_stazioni(char *nome_file, ListaStazioni *lista_stazioni) {
    T_stazione stazione;
    T_treno treno;

    int n_stazioni = 0;

    FILE *fp = fopen(nome_file, "r");
    if (fp == NULL) return 0;

    while (!feof(fp)) {
        // TODO MODULO 2: da implementare
        if (fscanf(fp, "%s %u", stazione.stazione_partenza, &stazione.numero_treni) != 2) continue;

        NodoListaStazioni *nodo = aggiungi_stazione(lista_stazioni, stazione.stazione_partenza);
        if (nodo == NULL) {
            fclose(fp);
            return 0;
        }

        for (unsigned int i = 0; i < stazione.numero_treni; i++) {
            if (fscanf(fp, "%s%s%u%u%s%s", treno.codice_treno, treno.stazione_arrivo, &treno.posti_totali, &treno.posti_occupati, treno.orario_partenza, treno.orario_arrivo) != 6) {
                continue;
            }
            if (!aggiungi_treno(&nodo->stazione, treno)) {
                return 0;
            }
        }
        n_stazioni++;
    }

    fclose(fp);
    return n_stazioni;
}

/* Stampa i dati di un treno
 *
 * Parametri in ingresso:
 * - treno: treno da stampare
 * */
void stampa_treno(T_treno treno) {
    printf("[%s] %s (%s - %s). Posti occupati: %u/%u\n", treno.codice_treno, treno.stazione_arrivo,
           treno.orario_partenza, treno.orario_arrivo, treno.posti_occupati, treno.posti_totali);
}

void stampa_stazione(T_stazione stazione) {
    printf("Previsti %d treni dalla stazione: %s. Lista:\n", stazione.numero_treni, stazione.stazione_partenza);

    NodoCodaTreni *nodo = stazione.primo;
    while (nodo != NULL) {
        printf("\t- ");
        stampa_treno(nodo->treno);
        nodo = nodo->next;
    }
}

/* Stampa stazioni */
void stampa_stazioni(ListaStazioni lista_stazioni) {
    NodoListaStazioni *nodo = lista_stazioni;
    while (nodo != NULL) {
        stampa_stazione(nodo->stazione);
        nodo = nodo->next;
    }
}

/*
 * 2b. Calcolo del numero di posti disponibili per una data stazione di partenza
 * */
NodoListaStazioni *trova_stazione(ListaStazioni lista_stazioni, const char *nome_stazione) {
    NodoListaStazioni *nodo = lista_stazioni;
    while (nodo != NULL) {
        if (strcmp(nodo->stazione.stazione_partenza, nome_stazione) == 0) {
            return nodo;
        }
        nodo = nodo->next;
    }

    return NULL;
}

unsigned posti_disponibili(ListaStazioni lista_stazioni, const char *nome_stazione) {
    // TODO MODULO 2: da implementare
    NodoListaStazioni *stazione = trova_stazione(lista_stazioni, nome_stazione);
    if  (stazione == NULL) {
        return 0;
    }
    NodoCodaTreni *nodo = stazione->stazione.primo;

    unsigned posti_disponibili = 0;
    while (nodo != NULL) {
        posti_disponibili += nodo->treno.posti_totali - nodo->treno.posti_occupati;
        nodo = nodo->next;
    }
    return posti_disponibili;
}


/*
 * 2c. Restituzione del tempo di percorrenza per tutti i treni che partono da
 *     una data stazione di partenza
 *
 *     La funzione restituisce un vettore di tempi di percorrenza, uno per ogni treno.
 *     Il vettore è allocato dinamicamente e la sua dimensione è restituita tramite il parametro dim.
 *     La funzione restituisce NULL in caso di errore.
 *
 *     Parametri in ingresso:
 *     - lista_stazioni: lista di stazioni
 *     - nome_stazione: nome della stazione di partenza
 *
 *     Parametri in uscita:
 *     - dim: dimensione del vettore restituito
 *
 *     Valore di ritorno:
 *     - vettore di tempi di percorrenza, NULL in caso di errore
 */

/* Funzione ausiliaria che permette di calcolare
 * la differenza (in minuti) tra due orari
 *
 * Parametri in ingresso:
 * - t1: orario di partenza
 * - t2: orario di arrivo
 * Return:
 * - differenza in minuti tra i due orari
 * */
int time_delta(const char *t1, const char *t2) {
    unsigned h1, m1, h2, m2;
    if (sscanf(t1, "%u:%u", &h1, &m1) != 2) return 0;
    if (sscanf(t2, "%u:%u", &h2, &m2) != 2) return 0;

    int delta = (h2 - h1) * 60 + (m2 - m1);
    // In caso di orari che vanno oltre la mezzanotte
    if (delta < 0) delta += 24 * 60;
    return delta;
}

unsigned *tempo_percorrenza(ListaStazioni lista_stazioni, const char *nome_stazione, unsigned *dim) {
    // TODO MODULO 2: da implementare
    NodoListaStazioni *stazione = trova_stazione(lista_stazioni, nome_stazione);
    if (stazione == NULL) {
        *dim = 0;
        return NULL;
    }

    unsigned *tempi = calloc(stazione->stazione.numero_treni, sizeof(unsigned));
    NodoCodaTreni *nodo = stazione->stazione.primo;
    if (tempi == NULL) return NULL;
    *dim = 0;
    while (nodo != NULL) {
        tempi[(*dim)++] = time_delta(nodo->treno.orario_partenza, nodo->treno.orario_arrivo);
        nodo = nodo->next;
    }
    return tempi;
}

int Menu() {
    int scelta;

    printf("*** M E N U ***\n"
           "1 - Quesito a: carica da file\n"
           "2 - Quesito b: calcola posti disponibili\n"
           "3 - Quesito c: calcola tempo di percorrenza\n"
           "0 - Uscita\n\n"
           "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

int main() {
    ListaStazioni lista_stazioni = NULL;

    char stazione[STR_LEN];
    unsigned dim = 0;
    unsigned *tempi = NULL;

    int scelta;
    do {
        scelta = Menu();

        switch (scelta) {
            case 1:
                if (carica_stazioni(NOME_FILE, &lista_stazioni) == 0) {
                    printf("Errore nel caricamento delle stazioni\n");
                }

                printf("Stazioni caricate:\n");
                stampa_stazioni(lista_stazioni);
                break;
            case 2:
                printf("Inserisci il nome della stazione: ");
                if (scanf("%s", stazione) != 1) {
                    printf("Errore nell'inserimento della stazione\n");
                    break;
                }
                unsigned totali_disponibili = posti_disponibili(lista_stazioni, stazione);
                printf("Posti disponibili totali in partenza da %s: %u\n", stazione, totali_disponibili);
                break;
            case 3:
                printf("Inserisci il nome della stazione: ");
                if (scanf("%s", stazione) != 1) {
                    printf("Errore nell'inserimento della stazione\n");
                    break;
                }
                tempi = tempo_percorrenza(lista_stazioni, stazione, &dim);

                for (unsigned i = 0; i < dim; i++) {
                    printf("Treno %d: %u minuti\n", i, tempi[i]);
                }

                free(tempi);
                dim = 0;

                break;

            case 0:
                return 0;

            default:
                printf("Scelta non valida\n");
        }

    } while (scelta);
}