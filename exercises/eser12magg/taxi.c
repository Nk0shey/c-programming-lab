#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "taxi.txt"
#define MAX_STR_LEN 31

typedef enum {
    OCCUPATO=0,
    DISPONIBILE
}stato_taxi;

char* stato_taxi_to_string(stato_taxi stato) {
    switch (stato) {
        case OCCUPATO:
            return "OCCUPATO";
        case DISPONIBILE:
            return "DISPONIBILE";
        default:
            return "ERRORE STATO";
    }
}


/* Struttura dati Taxi */
typedef struct {
    char targa[MAX_STR_LEN];
    char codice[MAX_STR_LEN];
    int km_totali;
    int passeggeri;
    stato_taxi stato;
}T_Taxi;

/* Definizione Nodo Taxi */
typedef struct nodoTaxi{
    T_Taxi info;
    struct nodoTaxi *next;
}NodoTaxi;

/* Definizione Lista Taxi */
typedef NodoTaxi *ListaTaxi;

/* Definizione Coda Taxi */
typedef struct {
    NodoTaxi *primo;
    NodoTaxi *ultimo;
}CodaTaxi;

/* Definizione Struttura Corsa */
typedef struct {
    char codice_taxi[MAX_STR_LEN];
    int passeggeri;
    int km_tratta;
}T_Corsa;

/* Definizione Nodo Corse */
typedef struct nodoCorsa {
    T_Corsa info;
    struct nodoCorsa *next;
}NodoCorsa;

/* Definizione Lista Corse */
typedef NodoCorsa* ListaCorse;

/* Definizione Struttura InfoTaxi (per il Quesito 7) */
typedef struct {
    char targa[MAX_STR_LEN];
    char codice[MAX_STR_LEN];
    int counter_corse;
}T_InfoTaxi;




/* Funzioni per la gestione della coda */

/* restituisce 1 se la coda è vuota, 0 altrimenti */
int CodaVuota(CodaTaxi c) {
    return c.primo == NULL;
}

/* inizializza la cosa */
void InitCoda(CodaTaxi *c) {
    c->primo = NULL;
    c->ultimo = NULL;
}





/* Quesito 1 */

/* Inserisci un nuovo taxi in testa alla lista dei taxi */
int InserisciInTestaListaTaxi(ListaTaxi *l, T_Taxi elem) {
   ListaTaxi nodo = malloc(sizeof(NodoTaxi));
    if (nodo == NULL) {
        printf("Errore");
        return -1;
    }
    nodo->info = elem;
    nodo->next = *l;
    *l = nodo;
    return 1;
    //TODO: da completare
}


/* Inserisce in coda un nuovo taxi */
int InCoda(CodaTaxi *c, T_Taxi elem) {
    //TODO: da completare
    NodoTaxi* nodo = malloc(sizeof(NodoTaxi));
    if (nodo == NULL) {
        printf("Errore");
        return -1;
    }
    nodo->info = elem;
    nodo->next = NULL;
    if (CodaVuota(*c)) {
        c->primo = nodo;
        c->ultimo = nodo;
    } else {
        c->ultimo->next = nodo;
        c->ultimo = nodo;
    }
    return 1;
}


/* Carica i dati dei taxi presenti nel file e li memorizza nell'opportuna struttura dati.
 * Il file ha il seguente formato:
 *
 * targa_taxi codice_taxi km_percorsi stato(1/0)
 *
 * Esempio:
 * AB777CD alpha1 35000 150 1
 *
 * Parametri in ingresso:
 * - nome_file: nome del file da cui caricare i dati
 *
 * Parametri in uscita:
 * - p_lista_taxi: puntatore alla lista dei taxi
 * - p_coda_taxi: puntatore alla coda dei taxi
 *
 * Valore di ritorno:
 * - numero di taxi caricati
 */

int leggi_da_file(ListaTaxi *p_lista_taxi, CodaTaxi *p_coda_taxi, char* nome_file) {
FILE *f = fopen(nome_file,"r"); if (!f) return -1;
    T_Taxi t; int stato,n,count = 0;
    while ((n=fscanf(f,"%30s %30s %d %d %d",t.targa,t.codice,&t.km_totali,&t.passeggeri,&stato)) == 5) {
        if (stato < 0 || stato > 1 || t.km_totali < 0 || t.passeggeri < 0) { fclose(f); return -1; }
        t.stato = (stato_taxi)stato;
        int ok = stato == DISPONIBILE ? InCoda(p_coda_taxi,t) : InserisciInTestaListaTaxi(p_lista_taxi,t);
        if (ok != 1) { fclose(f); return -1; } ++count;
    }
    int ok = n == EOF && !ferror(f); fclose(f); return ok ? count : -1;
}

/* Quesito 2 */
void stampa_taxi(T_Taxi taxi) {
    printf("\n%s\t%s\t%d\t%d\t%s", taxi.targa, taxi.codice, taxi.km_totali, taxi.passeggeri, stato_taxi_to_string(taxi.stato));
}


/* stampa la lista dei taxi (richiamando la funzione stampa_taxi) */
void stampa_taxi_occupati(ListaTaxi l) {
    //TODO: da completare
    printf("\n\n Lista taxi occupati");
    printf("\ntarga\tcodice\tkm\tpass\tstato");
    while (l != NULL) {
        stampa_taxi(l->info);
        l = l->next;
    }
}

/* Quesito 3 */

/* stampa la coda dei taxi (richiamando la funzione stampa */
void stampa_taxi_disponibili(CodaTaxi c) {
    //TODO: da completare
    printf("\n\n Lista taxi disponibili");
    printf("\ntarga\tcodice\tkm\tpass\tstato");
    NodoTaxi* nodo = c.primo;
    while (nodo != NULL) {
        stampa_taxi(nodo->info);
        nodo = nodo->next;
    }
}


/* Quesito 4 */
/* inserisci un nuovo taxi nella coda dei taxi */
void inserisci_nuovo_taxi(CodaTaxi *c) {
T_Taxi t = {0};
    printf("Targa codice km passeggeri: ");
    if (scanf("%30s %30s %d %d",t.targa,t.codice,&t.km_totali,&t.passeggeri) != 4) return;
    if (t.km_totali < 0 || t.passeggeri < 0) return;
    t.stato = DISPONIBILE; InCoda(c,t);
}

/* Quesito 5: Inserisci nuova corsa */

/* elimina il primo nodo della coda c, restituendo il valore in *elem */
int OutCoda(CodaTaxi *c, T_Taxi *elem) {
    //TODO: da completare
    if (CodaVuota(*c)) {
        printf("Coda Vuota");
        return -1;
    }

    NodoTaxi *nodo = c->primo;
    *elem = nodo->info;
    c->primo = c->primo->next;
    free(nodo);

    if (c->primo == NULL)
        c->ultimo = NULL;
    return 1;
}

/* Inserisci una nuova corsa in testa alla lista delle corse; */
int InserisciInTestaListaCorse(ListaCorse *plc, T_Corsa elem) {
    //TODO: da completare
    NodoCorsa *nodo = malloc(sizeof(NodoCorsa));
    if (nodo == NULL) {
        printf("Errore allocazione");
        return -1;
    }
    nodo->info = elem;
    nodo->next = *plc;
    *plc = nodo;
    return 1;
}

int inserisci_nuova_corsa(ListaTaxi *plt, CodaTaxi *c, ListaCorse *plc, T_Corsa nuova_corsa) {
if (!c->primo || nuova_corsa.passeggeri <= 0 || nuova_corsa.km_tratta < 0) return 0;
    NodoCorsa *r = malloc(sizeof *r); if (!r) return 0;
    NodoTaxi *t = c->primo; c->primo = t->next; if (!c->primo) c->ultimo = NULL;
    strcpy(nuova_corsa.codice_taxi,t->info.codice); r->info = nuova_corsa; r->next = *plc; *plc = r;
    t->info.stato = OCCUPATO; t->next = *plt; *plt = t; return 1;
}

/* Quesito 6: Termina Corsa */

/* Estrae dalla lista dei taxi occupati il taxi con il codice specificato. 
 * Parametri in ingresso:
 * - plt: puntatore lista taxi
 * - codice_taxi: codice del taxi da ricercare
 * 
 * Parametri in uscita:
 * - elem: puntatore al taxi ricercato
 *
 * Valore di ritorno:
 * 1 se il taxi è stato trovato, 0 altrimenti
*/
int estrai_taxi_by_codice(ListaTaxi *plt, char *codice_taxi, T_Taxi *elem) {
while (*plt && strcmp((*plt)->info.codice,codice_taxi)) plt = &(*plt)->next;
    if (!*plt) return 0;
    NodoTaxi *n = *plt; *elem = n->info; *plt = n->next; free(n); return 1;
}

/*
 * Cerca nella lista delle corse la corsa del taxi ricercato.
 * Parametri in ingresso:
 * - lc: lista delle corse
 * - codice_taxi: codice del taxi da ricercare
 *
 * Parametri in uscita:
 * - corsa: puntatore alla corsa ricercato
 *
 * Valore di ritorno:
 * 1 se la corsa è stata trovata, 0 altrimenti
 */
int ricerca_in_lista_corse(ListaCorse lc, char *codice_taxi, T_Corsa *corsa) {
    //TODO: da completare
    while (lc != NULL) {
        if (strcmp(lc->info.codice_taxi, codice_taxi) == 0) {
            *corsa = lc->info;
            return 1;
        }
        lc = lc->next;
    }
    printf("\n codice taxi %s non trovato nella lista corse", codice_taxi);
    return 0;
}

int termina_corsa(ListaTaxi *plt, CodaTaxi *pct, ListaCorse lc, char *codice_taxi) {
T_Corsa corsa;
    if (!ricerca_in_lista_corse(lc,codice_taxi,&corsa)) return 0;
    while (*plt && strcmp((*plt)->info.codice,codice_taxi)) plt = &(*plt)->next;
    if (!*plt) return 0;
    NodoTaxi *t = *plt; *plt = t->next; t->next = NULL;
    t->info.passeggeri += corsa.passeggeri; t->info.km_totali += 2*corsa.km_tratta; t->info.stato = DISPONIBILE;
    if (pct->ultimo) pct->ultimo->next = t; else pct->primo = t;
    pct->ultimo = t; return 1;
}

/* Quesito 7: Stampare numero di corse effettuato da ogni taxi */

/* restituisce il numero di elementi della lista */
int conta_elementi_lista(NodoTaxi *plt) {
    //TODO: da completare
    int count = 0;
    NodoTaxi *aux = plt;
    while (aux != NULL) {
        aux = aux->next;
        count++;
    }
    return count;
}

/* Calcola il numero di corse effettuate da ogni taxi, tramite un vettore allocato dinamicamente in cui memorizzare
 * per ogni taxi il numero di corse.
 *
 * Suggerimento:
 * 1) Calcolare la dimensione del vettore da allocare (lunghezza lista + lunghezza coda)
 * 2) Allocare il vettore delle statistiche
 * 3) Inizializzare le statistiche di ogni elemento del vettore
 * 4) Scorrere la lista delle corse e aggiornare le statistiche dei taxi
 *
 *
 * Parametri in ingresso:
 * - lt: lista dei taxi occupati
 * - ct: coda dei taxi disponibili
 * - lc: lista delle corse
 *
 * Parametri in uscita:
 * - dim: puntatore dimensione vettore allocato
 *
 * Valore di ritorno:
 * vettore contenente le informazioni dei taxi;
 */
T_InfoTaxi * calcola_corse_per_taxi(ListaTaxi lt, CodaTaxi ct, ListaCorse lc, int *dim) {
*dim = conta_elementi_lista(lt) + conta_elementi_lista(ct.primo);
    if (!*dim) return NULL;
    T_InfoTaxi *v = calloc((size_t)*dim,sizeof *v); if (!v) { *dim = 0; return NULL; }
    int i = 0;
    for (NodoTaxi *t = lt; t; t = t->next,++i) { strcpy(v[i].codice,t->info.codice); strcpy(v[i].targa,t->info.targa); }
    for (NodoTaxi *t = ct.primo; t; t = t->next,++i) { strcpy(v[i].codice,t->info.codice); strcpy(v[i].targa,t->info.targa); }
    for (; lc; lc = lc->next) for (int j = 0; j < *dim; ++j) if (!strcmp(v[j].codice,lc->info.codice_taxi)) ++v[j].counter_corse;
    return v;
}

/* Quesito 8: Scrivere su un file binario i dati di tutti i taxi (disponibili o occupati) */
void scrivi_file_binario(ListaTaxi *plt, CodaTaxi *pct, char* nome_file) {
    FILE* fp;

    //TODO: da completare

    NodoTaxi *aux;
    if (((*plt != NULL) || !CodaVuota(*pct))) {
        fp = fopen(nome_file, "wb");
        if (fp == NULL) {
            printf("Errore apertura file");
            return;
        }

        aux = *plt;
        while (aux != NULL) {
            fwrite(&aux->info, sizeof(T_Taxi), 1, fp);
            aux = aux->next;
        }

        aux = pct->primo;
        while (aux != NULL) {
            fwrite(&aux->info, sizeof(T_Taxi), 1, fp);
            aux = aux->next;
        }
        fclose(fp);
        printf("\n creato con successo");
        return;
    }
    printf("\nLista e coda vuote");

}

/* Quesito 9: Leggere da un file binario i dati di tutti i taxi e li memorizzi nell'elenco opportuno a
 * seconda dello stato.
 */
void leggi_file_binario(ListaTaxi *plt, CodaTaxi *pct, char* nome_file) {
FILE *fp = fopen(nome_file,"rb"); if (!fp) return;
    T_Taxi t;
    while (fread(&t,sizeof t,1,fp) == 1) {
        t.targa[MAX_STR_LEN-1] = '\0'; t.codice[MAX_STR_LEN-1] = '\0';
        if (t.stato == DISPONIBILE) InCoda(pct,t);
        else if (t.stato == OCCUPATO) InserisciInTestaListaTaxi(plt,t);
    } fclose(fp);
}

/* Quesito 10: Cancellare la lista dei taxi disponibili e dei taxi occupati */

int CancellaTuttiLista(ListaTaxi *plt) {
    NodoTaxi *aux;
    while ((*plt != NULL)) {
        aux = (*plt);
        *plt = (*plt)->next;
        free(aux);
    }
    return 1;
    //TODO: da completare
}

int CancellaTuttiCoda(CodaTaxi *pct) {
    T_Taxi aux;
    while (OutCoda(pct, &aux) != -1);
    return 1;
    //TODO: da completare
}

int main(void) {

    ListaTaxi taxi_occupati = NULL;
    CodaTaxi taxi_disponibili;
    ListaCorse storico_corse = NULL;
    T_InfoTaxi* vettore = NULL;
    int dim_vettore = 0;
    T_Taxi elem_taxi;
    T_Corsa nuova_corsa;
    char nome_file_binario[21];
    char codice_corsa[MAX_STR_LEN];
    int numero_taxi_letti = 0;
    int scelta;

    InitCoda(&taxi_disponibili);

    do {
        printf("\n\n\n *** COMPAGNIA TAXI ***");
        printf("\n1. Carica da file");
        printf("\n2. Stampa taxi occupati");
        printf("\n3. Stampa taxi disponibili");
        printf("\n4. Inserisci nuovo taxi");
        printf("\n5. Inserisci nuova corsa");
        printf("\n6. Termina corsa");
        printf("\n7. Stampa numero di corse per taxi");
        printf("\n8. Salva su file binario i dati dei taxi");
        printf("\n9. Leggi da file binario");
        printf("\n10. Cancella taxi liberi e occupati");
        printf("\n0. ESCI");

        printf("\n\nScelta: ");
        scanf("%d", &scelta);
        while (getchar() != '\n');

        switch(scelta) {
            case 1:
                numero_taxi_letti = leggi_da_file(&taxi_occupati, &taxi_disponibili, NOME_FILE);
                printf("\nCaricamento completato. Sono stati letti %d taxi", numero_taxi_letti);
                break;
            case 2:
                stampa_taxi_occupati(taxi_occupati);
                break;
            case 3:
                stampa_taxi_disponibili(taxi_disponibili);
                break;
            case 4:
                inserisci_nuovo_taxi(&taxi_disponibili);
                break;
            case 5:
                //TODO: Da completare
                printf("Inserisci numero passeggeri: ");
                scanf("%d", &nuova_corsa.passeggeri);
                printf("Inserisci km tratta: ");
                scanf("%d", &nuova_corsa.km_tratta);
                inserisci_nuova_corsa(&taxi_occupati, &taxi_disponibili, &storico_corse, nuova_corsa);
                break;
            case 6:
                printf("\nInserisci codice taxi: ");
                scanf("%s", codice_corsa);
                termina_corsa(&taxi_occupati, &taxi_disponibili, storico_corse, codice_corsa);
                break;
            case 7:
                vettore = calcola_corse_per_taxi(taxi_occupati, taxi_disponibili, storico_corse, &dim_vettore);
                printf("\ncodice\ttarga\tnum corse");
                for (int i = 0; i < dim_vettore; i++) {
                    printf("\n%s\t%s\t%d", vettore[i].codice, vettore[i].targa, vettore[i].counter_corse);
                }
                free(vettore);
                break;
            case 8:
                printf("\nInserisci nome file: ");
                scanf("%s", nome_file_binario);
                scrivi_file_binario(&taxi_occupati, &taxi_disponibili, nome_file_binario);
                break;
            case 9:
                printf("\nInserisci nome file: ");
                scanf("%s", nome_file_binario);
                leggi_file_binario(&taxi_occupati, &taxi_disponibili, nome_file_binario);
                break;
            case 10:
                CancellaTuttiLista(&taxi_occupati);
                CancellaTuttiCoda(&taxi_disponibili);
                printf("\nLista Taxi occupati vuota? %d", taxi_occupati==NULL);
                printf("\nCoda Taxi disponibili vuota? %d", CodaVuota(taxi_disponibili));
                break;
            case 0:
                //dealloca variabili allocate dinamicamente
                CancellaTuttiLista(&taxi_occupati);
                CancellaTuttiCoda(&taxi_disponibili);

                NodoCorsa *aux;
                while (storico_corse != NULL) {
                    aux = storico_corse;
                    storico_corse = storico_corse->next;
                    free(aux);
                }
                // Cleanup complete.
                break;
            default:
                printf("\nscelta errata");
        }
    }while (scelta != 0);
    return 0;
}