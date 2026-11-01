#include "../../common/console.h"
/******************************************************************************
 * === SIMULAZIONE ESAME MODULO 2 ===
 * Fondamenti di Programmazione - A.A. 2025/26
 * Tempo consigliato: 120 minuti
 *
 * STRUTTURE DATI: VETTORE DINAMICO DI CODE + PILA + VETTORE DINAMICO
 * Alberi e ABR NON sono richiesti.
 *
 * Implementare in ANSI C un programma per la gestione delle richieste di
 * assistenza tecnica di una rete di laboratori universitari.
 *
 * Ogni laboratorio e' identificato da un codice univoco e gestisce una coda
 * FIFO di richieste. Le richieste vengono inserite nella coda del laboratorio
 * corrispondente rispettando l'ordine di arrivo nel file.
 *
 * Ogni richiesta e' caratterizzata da:
 * - codice_richiesta : stringa senza spazi
 * - matricola        : stringa senza spazi
 * - categoria        : HARDWARE / SOFTWARE / RETE
 * - priorita         : intero compreso tra 1 e 5
 * - durata_stimata   : intero, espresso in minuti
 *
 * La struttura principale e' un VETTORE DINAMICO DI CODE. La dimensione del
 * vettore viene letta dal file. Ogni elemento del vettore rappresenta un
 * laboratorio e contiene il codice del laboratorio e la relativa coda FIFO.
 *
 * Le richieste elaborate vengono memorizzate in una PILA collegata: l'ultima
 * richiesta elaborata deve essere la prima a poter essere annullata/ripristinata.
 *
 * Il file "richieste.txt" ha il seguente formato:
 *
 *      <numero_laboratori>
 *      <codice_lab_1>
 *      ...
 *      <codice_lab_N>
 *      <numero_richieste>
 *      <codice_lab> <codice_richiesta> <matricola> <categoria> <priorita> <durata>
 *      ...
 *
 * Esempio:
 *      3
 *      LAB_A
 *      LAB_B
 *      LAB_C
 *      8
 *      LAB_A R001 100001 HARDWARE 4 35
 *      LAB_B R002 100114 SOFTWARE 2 20
 *      LAB_A R003 100221 RETE 5 50
 *
 * Il programma deve implementare le seguenti funzionalita':
 *
 * QUESITO 1 - Caricamento dati
 * Caricare i laboratori e le richieste dal file in un vettore dinamico di code.
 * Le richieste dello stesso laboratorio devono mantenere l'ordine di arrivo.
 *
 * QUESITO 2 - Statistiche per laboratorio
 * Data una categoria, restituire un vettore dinamico di float di dimensione N.
 * L'elemento i-esimo contiene la durata media delle richieste della categoria
 * indicata presenti nel laboratorio i-esimo. Se nessuna richiesta appartiene
 * alla categoria, memorizzare -1.0f.
 *
 * QUESITO 3 - Elaborazione della prossima richiesta
 * Dato il codice di un laboratorio:
 * - estrarre la prima richiesta dalla sua coda;
 * - inserirla in cima alla pila delle richieste elaborate;
 * - restituire 1 in caso di successo, 0 se il laboratorio non esiste o la coda
 *   e' vuota, -1 in caso di errore di allocazione.
 *
 * QUESITO 4 - Estrazione selettiva
 * Estrarre, SENZA rimuoverle dalle code originali, tutte le richieste con
 * priorita maggiore o uguale a una soglia e durata stimata maggiore o uguale
 * a una seconda soglia. Restituire un vettore dinamico di Richiesta e rendere
 * disponibile al chiamante il numero di elementi estratti.
 *
 * QUESITO 5 - Ripristino dell'ultima richiesta
 * Estrarre la richiesta in cima alla pila e reinserirla IN FONDO alla coda del
 * laboratorio da cui proveniva. Restituire 1 in caso di successo, 0 se la pila
 * e' vuota, -1 in caso di errore.
 *
 * QUESITO 6 - Deallocazione
 * Deallocare tutte le code, il vettore dei laboratori, la pila e gli eventuali
 * vettori dinamici creati.
 *
 * NOTA: il main e alcune funzioni di supporto sono gia' fornite. Completare
 * esclusivamente le parti contrassegnate con TODO.
 ******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_INPUT "richieste(1).txt"
#define STR_LEN 32

#define OK 1
#define ERRORE_LOGICO 0
#define ERRORE_MEMORIA -1

typedef enum {
    CAT_NON_VALIDA = -1,
    HARDWARE,
    SOFTWARE,
    RETE
} Categoria;

typedef struct {
    char codice_richiesta[STR_LEN];
    char matricola[STR_LEN];
    Categoria categoria;
    int priorita;
    int durata_stimata;
} Richiesta;

typedef struct nodo_richiesta {
    Richiesta info;
    struct nodo_richiesta *next;
} NodoRichiesta;

typedef struct {
    NodoRichiesta *primo;
    NodoRichiesta *ultimo;
    unsigned num_richieste;
} CodaRichieste;

typedef struct {
    char codice_lab[STR_LEN];
    CodaRichieste coda;
} Laboratorio;

/* Elemento della pila: oltre alla richiesta si memorizza il laboratorio
 * di provenienza, necessario per un eventuale ripristino. */
typedef struct nodo_elaborata {
    Richiesta richiesta;
    char codice_lab[STR_LEN];
    struct nodo_elaborata *next;
} NodoElaborata;

typedef NodoElaborata *PilaElaborate;

/* ========================================================================== */
/* FUNZIONI DI SUPPORTO GIA' FORNITE                                          */
/* ========================================================================== */

Categoria string_to_categoria(const char *s) {
    if (s == NULL) return CAT_NON_VALIDA;
    if (strcmp(s, "HARDWARE") == 0) return HARDWARE;
    if (strcmp(s, "SOFTWARE") == 0) return SOFTWARE;
    if (strcmp(s, "RETE") == 0) return RETE;
    return CAT_NON_VALIDA;
}

const char *categoria_to_string(Categoria c) {
    switch (c) {
        case HARDWARE: return "HARDWARE";
        case SOFTWARE: return "SOFTWARE";
        case RETE: return "RETE";
        default: return "NON_VALIDA";
    }
}

void inizializza_coda(CodaRichieste *coda) {
    if (coda == NULL) return;
    coda->primo = NULL;
    coda->ultimo = NULL;
    coda->num_richieste = 0;
}

int accoda_richiesta(CodaRichieste *coda, Richiesta r) {
    NodoRichiesta *nuovo;

    if (coda == NULL) return 0;

    nuovo = (NodoRichiesta *) malloc(sizeof(NodoRichiesta));
    if (nuovo == NULL) return 0;

    nuovo->info = r;
    nuovo->next = NULL;

    if (coda->ultimo == NULL) {
        coda->primo = nuovo;
        coda->ultimo = nuovo;
    } else {
        coda->ultimo->next = nuovo;
        coda->ultimo = nuovo;
    }

    coda->num_richieste++;
    return 1;
}

int cerca_indice_laboratorio(const Laboratorio *laboratori,
                             unsigned num_laboratori,
                             const char *codice_lab) {
    unsigned i;

    if (laboratori == NULL || codice_lab == NULL) return -1;

    for (i = 0; i < num_laboratori; i++) {
        if (strcmp(laboratori[i].codice_lab, codice_lab) == 0)
            return (int) i;
    }

    return -1;
}

void stampa_richiesta(const Richiesta *r) {
    if (r == NULL) return;

    printf("%s %s %s priorita=%d durata=%d\n",
           r->codice_richiesta,
           r->matricola,
           categoria_to_string(r->categoria),
           r->priorita,
           r->durata_stimata);
}

void stampa_laboratori(const Laboratorio *laboratori,
                       unsigned num_laboratori) {
    unsigned i;
    NodoRichiesta *corrente;

    if (laboratori == NULL) return;

    for (i = 0; i < num_laboratori; i++) {
        printf("\nLaboratorio %s (%u richieste):\n",
               laboratori[i].codice_lab,
               laboratori[i].coda.num_richieste);

        corrente = laboratori[i].coda.primo;
        while (corrente != NULL) {
            printf("  ");
            stampa_richiesta(&corrente->info);
            corrente = corrente->next;
        }
    }
}

/* ========================================================================== */
/* QUESITO 1                                                                  */
/* ========================================================================== */

/*
 * Carica dal file un vettore dinamico di laboratori, ciascuno contenente una
 * coda FIFO di richieste.
 *
 * Parametri:
 * - nome_file: nome del file di input;
 * - num_laboratori: parametro di uscita, numero di laboratori caricati.
 *
 * Restituisce:
 * - puntatore al vettore dinamico in caso di successo;
 * - NULL in caso di errore di file, dati non validi o memoria.
 */
Laboratorio *carica_laboratori(const char *nome_file,
                               unsigned *num_laboratori) {
if (!nome_file || !num_laboratori) return NULL;
    *num_laboratori = 0;
    FILE *fp = fopen(nome_file, "r"); if (!fp) return NULL;
    unsigned count = 0, requests;
    Laboratorio *labs = NULL;
    if (fscanf(fp, "%u", &count) != 1 || !count || count > 10000) goto fail;
    labs = calloc(count, sizeof *labs); if (!labs) goto fail;
    for (unsigned i = 0; i < count; ++i) {
        if (fscanf(fp, "%31s", labs[i].codice_lab) != 1) goto fail;
        for (unsigned j = 0; j < i; ++j) if (!strcmp(labs[i].codice_lab, labs[j].codice_lab)) goto fail;
    }
    if (fscanf(fp, "%u", &requests) != 1) goto fail;
    for (unsigned i = 0; i < requests; ++i) {
        Richiesta r; char lab[STR_LEN], category[STR_LEN];
        if (fscanf(fp, "%31s %31s %31s %31s %d %d", lab, r.codice_richiesta, r.matricola, category, &r.priorita, &r.durata_stimata) != 6) goto fail;
        r.categoria = string_to_categoria(category);
        int index = cerca_indice_laboratorio(labs, count, lab);
        if (index < 0 || r.categoria == CAT_NON_VALIDA || r.durata_stimata < 0 || !accoda_richiesta(&labs[index].coda, r)) goto fail;
    }
    fclose(fp); *num_laboratori = count; return labs;
fail:
    if (labs) { for (unsigned i = 0; i < count; ++i) {
        NodoRichiesta *n = labs[i].coda.primo;
        while (n) { NodoRichiesta *next = n->next; free(n); n = next; }
    } free(labs); }
    fclose(fp); return NULL;
}

/* ========================================================================== */
/* QUESITO 2                                                                  */
/* ========================================================================== */

/*
 * Calcola, per ogni laboratorio, la durata media delle richieste appartenenti
 * alla categoria indicata.
 *
 * Restituisce un vettore dinamico di num_laboratori float.
 * Se per un laboratorio non esistono richieste della categoria scelta,
 * il valore corrispondente deve essere -1.0f.
 * Restituisce NULL in caso di parametri non validi o errore di allocazione.
 */
float *medie_durata_per_categoria(const Laboratorio *laboratori,
                                  unsigned num_laboratori,
                                  Categoria categoria) {
    /* TODO QUESITO 2 */
    if (!laboratori || !num_laboratori) return NULL;
    float *vettore = malloc(num_laboratori * sizeof(float));
    if (vettore == NULL) {
        return NULL;
    }
    NodoRichiesta *paux;
    for (unsigned i = 0; i < num_laboratori; i++) {
        int count = 0;
        int durata = 0;
        paux = laboratori[i].coda.primo;
        while (paux != NULL) {
            if (paux->info.categoria == categoria) {
                durata += paux->info.durata_stimata;
                count++;
            }
            paux = paux->next;
        }
        if (count == 0) {
            vettore[i] = -1.0f;
        } else {
            vettore[i] = (float) durata / (float) count;
        }

    }

    return vettore;
}

/* ========================================================================== */
/* QUESITO 3                                                                  */
/* ========================================================================== */

/*
 * Elabora la prima richiesta della coda del laboratorio specificato:
 * 1. rimuove il nodo in testa alla coda;
 * 2. aggiorna correttamente primo, ultimo e num_richieste;
 * 3. inserisce la richiesta in cima alla pila, memorizzando anche il codice
 *    del laboratorio di provenienza.
 *
 * Restituisce:
 *  1 = successo;
 *  0 = laboratorio inesistente oppure coda vuota;
 * -1 = errore di allocazione per il nodo della pila.
 *
 * ATTENZIONE: in caso di errore di allocazione della pila, la coda originale
 * non deve essere modificata.
 */
int elabora_prossima_richiesta(Laboratorio *laboratori,
                               unsigned num_laboratori,
                               const char *codice_lab,
                               PilaElaborate *pila) {
    /* TODO QUESITO 3 */
    if (!laboratori || !num_laboratori || !codice_lab || !pila) return 0;
    int indice = cerca_indice_laboratorio(laboratori, num_laboratori, codice_lab);
    if (indice == -1) return 0;
    NodoRichiesta *nodo = laboratori[indice].coda.primo;

    if (nodo == NULL) return 0;

    NodoRichiesta *temp;
    Richiesta r = nodo->info;
    NodoElaborata *el = malloc(sizeof(NodoElaborata));
    if (el == NULL) {
        return -1;
    }

    strcpy(el->codice_lab, codice_lab);
    el->richiesta = r;
    el->next = *pila;
    *pila = el;


    laboratori[indice].coda.primo = nodo -> next;
    if (laboratori[indice].coda.primo == NULL) {
       laboratori[indice].coda.ultimo = NULL;
    }

    laboratori[indice].coda.num_richieste--;
    free(nodo);
    return 1;
}

/* ========================================================================== */
/* QUESITO 4                                                                  */
/* ========================================================================== */

/*
 * Crea un vettore dinamico contenente una COPIA di tutte le richieste che
 * rispettano entrambe le condizioni:
 * - priorita >= priorita_minima;
 * - durata_stimata >= durata_minima.
 *
 * Le code originali non devono essere modificate.
 * L'ordine nel vettore deve essere:
 * - ordine crescente di indice del laboratorio;
 * - ordine FIFO interno a ciascuna coda.
 *
 * Parametro di uscita:
 * - num_estratte: numero di richieste copiate.
 *
 * Restituisce NULL se non esistono richieste compatibili oppure in caso di
 * errore. In ogni caso *num_estratte deve essere posto inizialmente a 0.
 */
Richiesta *estrai_richieste(const Laboratorio *laboratori,
                            unsigned num_laboratori,
                            int priorita_minima,
                            int durata_minima,
                            unsigned *num_estratte) {
    /* TODO QUESITO 4 */
    if (!num_estratte) return NULL;
    *num_estratte = 0;
    if (!laboratori || num_laboratori == 0) return NULL;
    for (unsigned i = 0; i < num_laboratori; i++) {
        NodoRichiesta *nodo = laboratori[i].coda.primo;
        while (nodo != NULL) {
            if (nodo->info.priorita >= priorita_minima && nodo->info.durata_stimata >= durata_minima) {
                (*num_estratte)++;
            }
            nodo = nodo->next;
        }
    }

    if (*num_estratte == 0) return NULL;
    Richiesta *vettore = malloc(sizeof (Richiesta) * (*num_estratte));
    if (vettore == NULL) {
        *num_estratte = 0;
        return NULL;
    }

    for (unsigned i = 0, j = 0; i < num_laboratori; i++) {
        NodoRichiesta *nodo = laboratori[i].coda.primo;
        while (nodo != NULL) {
            if (nodo->info.priorita >= priorita_minima && nodo->info.durata_stimata >= durata_minima) {
                vettore[j++] = nodo->info;
            }
            nodo = nodo->next;
        }
    }

    return vettore;
}

/* ========================================================================== */
/* QUESITO 5                                                                  */
/* ========================================================================== */

/*
 * Ripristina l'ultima richiesta elaborata:
 * - legge l'elemento in cima alla pila;
 * - cerca il laboratorio di provenienza;
 * - reinserisce la richiesta in fondo alla relativa coda;
 * - rimuove e dealloca il nodo della pila solo dopo che l'accodamento e'
 *   avvenuto con successo.
 *
 * Restituisce:
 *  1 = successo;
 *  0 = pila vuota oppure laboratorio non trovato;
 * -1 = errore di allocazione durante il reinserimento in coda.
 */
int ripristina_ultima_richiesta(Laboratorio *laboratori,
                                unsigned num_laboratori,
                                PilaElaborate *pila) {
    /* TODO QUESITO 5 */
    if (!laboratori || !num_laboratori || !pila) return 0;
    NodoElaborata *nodo = *pila;
    NodoElaborata *temp;
    while (nodo == NULL) return 0;

    int indice = cerca_indice_laboratorio(laboratori, num_laboratori, nodo->codice_lab);
    if (indice == -1) return 0;

    if (accoda_richiesta(&laboratori[indice].coda, nodo->richiesta) == 1) {
        *pila = nodo->next;
        free(nodo);
    } else return -1;

    return 1;
}

/* ========================================================================== */
/* QUESITO 6                                                                  */
/* ========================================================================== */

/* Dealloca tutti i nodi di tutte le code e il vettore dei laboratori.
 * Al termine *laboratori deve valere NULL e *num_laboratori deve valere 0. */
void dealloca_laboratori(Laboratorio **laboratori,
                         unsigned *num_laboratori) {
    /* TODO QUESITO 6A */
    if (!laboratori || !num_laboratori) return;

    if (*laboratori == NULL) {
        *num_laboratori = 0;
        return;
    }

    for (unsigned i = 0; i < (*num_laboratori); i++) {
        NodoRichiesta *nodo = (*laboratori)[i].coda.primo;
        NodoRichiesta *nodo_successivo;
        while (nodo != NULL) {
            nodo_successivo = nodo -> next;
            free(nodo);
            nodo = nodo_successivo;
        }
        (*laboratori)[i].coda.primo = NULL;
        (*laboratori)[i].coda.ultimo = NULL;
        (*laboratori)[i].coda.num_richieste = 0;

    }
    free(*laboratori);
    *laboratori = 0;
    *num_laboratori = 0;
}

/* Dealloca tutti i nodi della pila e pone *pila a NULL. */
void dealloca_pila(PilaElaborate *pila) {
    /* TODO QUESITO 6B */
    if (!pila) return;
    NodoElaborata *nodo = *pila;
    while (nodo != NULL) {
        NodoElaborata *temp = nodo->next;
        free(nodo);
        nodo = temp;
    }
    *pila = NULL;
}

/* ========================================================================== */
/* MAIN GIA' FORNITO                                                          */
/* ========================================================================== */

int main(void) {
    Laboratorio *laboratori = NULL;
    unsigned num_laboratori = 0;
    PilaElaborate pila = NULL;

    float *medie = NULL;
    Richiesta *estratte = NULL;
    unsigned num_estratte = 0;

    int scelta;

    do {
        printf("\n\n===== MENU =====\n");
        printf("1. Carica dati da file\n");
        printf("2. Stampa laboratori e code\n");
        printf("3. Calcola medie per categoria\n");
        printf("4. Elabora prossima richiesta\n");
        printf("5. Estrai richieste per soglie\n");
        printf("6. Ripristina ultima richiesta\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        lab_scanf("%d", &scelta);

        switch (scelta) {
            case 1: {
                Laboratorio *nuovi;
                unsigned num_nuovi = 0;

                nuovi = carica_laboratori(FILE_INPUT, &num_nuovi);
                if (nuovi == NULL) {
                    printf("Errore durante il caricamento.\n");
                } else {
                    dealloca_laboratori(&laboratori, &num_laboratori);
                    laboratori = nuovi;
                    num_laboratori = num_nuovi;
                    printf("Caricamento completato.\n");
                }
                break;
            }

            case 2:
                stampa_laboratori(laboratori, num_laboratori);
                break;

            case 3: {
                char categoria_str[STR_LEN];
                Categoria categoria;
                unsigned i;

                printf("Categoria (HARDWARE/SOFTWARE/RETE): ");
                lab_scanf("%31s", categoria_str);
                categoria = string_to_categoria(categoria_str);

                free(medie);
                medie = medie_durata_per_categoria(laboratori,
                                                   num_laboratori,
                                                   categoria);

                if (medie == NULL) {
                    printf("Impossibile calcolare le medie.\n");
                } else {
                    for (i = 0; i < num_laboratori; i++)
                        printf("%s: %.2f\n",
                               laboratori[i].codice_lab,
                               medie[i]);
                }
                break;
            }

            case 4: {
                char codice_lab[STR_LEN];
                int esito;

                printf("Codice laboratorio: ");
                lab_scanf("%31s", codice_lab);

                esito = elabora_prossima_richiesta(laboratori,
                                                    num_laboratori,
                                                    codice_lab,
                                                    &pila);
                printf("Esito elaborazione: %d\n", esito);
                break;
            }

            case 5: {
                int priorita_minima;
                int durata_minima;
                unsigned i;

                printf("Priorita minima: ");
                lab_scanf("%d", &priorita_minima);
                printf("Durata minima: ");
                lab_scanf("%d", &durata_minima);

                free(estratte);
                estratte = estrai_richieste(laboratori,
                                             num_laboratori,
                                             priorita_minima,
                                             durata_minima,
                                             &num_estratte);

                printf("Richieste estratte: %u\n", num_estratte);
                for (i = 0; i < num_estratte; i++)
                    stampa_richiesta(&estratte[i]);
                break;
            }

            case 6: {
                int esito = ripristina_ultima_richiesta(laboratori,
                                                        num_laboratori,
                                                        &pila);
                printf("Esito ripristino: %d\n", esito);
                break;
            }

            case 0:
                break;

            default:
                printf("Scelta non valida.\n");
        }

    } while (scelta != 0);

    free(medie);
    free(estratte);
    dealloca_pila(&pila);
    dealloca_laboratori(&laboratori, &num_laboratori);

    return 0;
}
