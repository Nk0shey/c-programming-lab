/******************************************************************************
=== MODULO 2 ===
Appello di Fondamenti di Programmazione - A.A. 2025/26
Tempo: 120 minuti

Implementare in C un programma per analizzare i ticket di un servizio di
help desk tecnico.

Le categorie di ticket devono essere memorizzate in una lista collegata. Ogni nodo
della lista contiene i dati della categoria e una coda FIFO degli eventi
associati ai ticket di quella categoria.

Il programma deve implementare le seguenti funzionalita':
1. Caricare le categorie dal file categorie.txt e gli eventi dal file ticket.txt,
    costruendo una lista di categorie, ognuna con la propria coda di eventi.
2. Cercare il primo evento di chiusura corrispondente a un certo ticket.
3. Produrre un vettore dinamico contenente le statistiche relative ai ticket
    aperti e chiusi.
4. Salvare le statistiche relative ai ticket su file, se corrispondono ad un
    certo filtro.

******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_CATEGORIE "categorie.txt"
#define FILE_TICKET    "ticket.txt"
#define FILE_OUTPUT    "statistiche_ticket.txt"

#define STR_LEN     80
#define COD_LEN     16
#define ORARIO_LEN  6

#define OK                0
#define ERRORE_FILE       (-1)
#define ERRORE_MEMORIA    (-2)
#define ERRORE_PARAMETRI  (-3)
#define ERRORE_DATI       (-4)


typedef enum {
    STATO_TICKET_SCONOSCIUTO = -1,
    APERTO,
    CHIUSO
} stato_ticket_t;


typedef enum {
    PRIORITA_SCONOSCIUTA = -1,
    BASSA,
    MEDIA,
    ALTA,
    CRITICA
} priorita_t;


typedef struct {
    char id_ticket[COD_LEN];
    char orario[ORARIO_LEN];
    stato_ticket_t stato;
    priorita_t priorita;
    char descrizione[STR_LEN];
} evento_ticket_t;


typedef struct nodo_evento_ticket {
    evento_ticket_t info;
    struct nodo_evento_ticket *next;
} nodo_evento_ticket_t;


typedef struct {
    nodo_evento_ticket_t *primo;
    nodo_evento_ticket_t *ultimo;
} coda_ticket_t;


typedef struct {
    char codice_categoria[COD_LEN];
    char descrizione[STR_LEN];
    coda_ticket_t eventi;
} categoria_t;


typedef struct nodo_categoria {
    categoria_t info;
    struct nodo_categoria *next;
} nodo_categoria_t;


typedef nodo_categoria_t *lista_categorie_t;


/* Record prodotto dal filtro sui tempi di risoluzione.
 * Ogni elemento statistica_ticket_t deve contenere:
   - codice della categoria;
   - id del ticket;
   - ora di apertura del ticket;
   - ora di chiusura del ticket;
   - descrizione del ticket (dell'evento APERTO);
   - priorità del ticket (dell'evento APERTO);
   - minuti impiegati per risolvere (chiudere) il ticket
 */
typedef struct {
    char codice_categoria[COD_LEN];
    char id_ticket[COD_LEN];
    char ora_apertura[ORARIO_LEN];
    char ora_chiusura[ORARIO_LEN];
    char descrizione[STR_LEN];
    priorita_t priorita;
    int minuti_risoluzione;
    // TODO: da completare a cura dello studente
} statistica_ticket_t;


/* ============================================================================
FUNZIONI GIA' FORNITE
========================================================================== */

/* Data una stringa di stato, restituisce il valore dell'enum corrispondente */
stato_ticket_t string_to_stato_ticket(const char s[]) {
    if (s == NULL) return STATO_TICKET_SCONOSCIUTO;
    if (strcmp(s, "APERTO") == 0) return APERTO;
    if (strcmp(s, "CHIUSO") == 0) return CHIUSO;
    return STATO_TICKET_SCONOSCIUTO;
}


/* Dato uno stato_ticket_t, restituisce la stringa corrispondente */
const char *stato_ticket_to_string(stato_ticket_t stato) {
    switch (stato) {
        case APERTO: return "APERTO";
        case CHIUSO: return "CHIUSO";
        default: return "SCONOSCIUTO";
    }
}


/* Data una stringa di priorita, restituisce il valore dell'enum corrispondente */
priorita_t string_to_priorita(const char s[]) {
    if (s == NULL) return PRIORITA_SCONOSCIUTA;
    if (strcmp(s, "BASSA") == 0) return BASSA;
    if (strcmp(s, "MEDIA") == 0) return MEDIA;
    if (strcmp(s, "ALTA") == 0) return ALTA;
    if (strcmp(s, "CRITICA") == 0) return CRITICA;
    return PRIORITA_SCONOSCIUTA;
}


/* Dato un valore priorita_t, restituisce la stringa corrispondente */
const char *priorita_to_string(priorita_t priorita) {
    switch (priorita) {
        case BASSA: return "BASSA";
        case MEDIA: return "MEDIA";
        case ALTA: return "ALTA";
        case CRITICA: return "CRITICA";
        default: return "SCONOSCIUTA";
    }
}


/* Funzione ausiliaria che permette di calcolare
 * la differenza (in minuti) tra due orari
 *
 * Parametri in ingresso:
 * - inizio: orario di partenza
 * - fine: orario di arrivo
 * Return:
 * - differenza in minuti tra i due orari
 * */
int differenza_minuti(const char inizio[], const char fine[]) {
    unsigned h1, m1, h2, m2;
    if (sscanf(inizio, "%u:%u", &h1, &m1) != 2) return 0;
    if (sscanf(fine, "%u:%u", &h2, &m2) != 2) return 0;

    int delta = (h2 - h1) * 60 + (m2 - m1);
    // In caso di orari che vanno oltre la mezzanotte
    if (delta < 0) delta += 24 * 60;
    return delta;
}


/* Data una coda per indirizzo, la inizializza */
void coda_init(coda_ticket_t *coda) {
    if (coda == NULL) return;
    coda->primo = NULL;
    coda->ultimo = NULL;
}


/* Dato un evento, lo inserisce nella una coda
   passata per indirizzo.

   Restituisce OK se l'inserimento e' avvenuto correttamente,
   altrimenti un codice di errore.
   */
int accoda_evento(coda_ticket_t *coda, evento_ticket_t evento) {
    nodo_evento_ticket_t *nuovo;

    if (coda == NULL) return ERRORE_PARAMETRI;

    nuovo = malloc(sizeof(nodo_evento_ticket_t));
    if (nuovo == NULL) return ERRORE_MEMORIA;

    nuovo->info = evento;
    nuovo->next = NULL;

    if (coda->ultimo != NULL) {
        coda->ultimo->next = nuovo;
    } else {
        coda->primo = nuovo;
    }

    coda->ultimo = nuovo;
    return OK;
}


/* Aggiunge una categoria in testa alla lista passata per indirizzo

   Restituisce OK se l'inserimento e' avvenuto correttamente,
   altrimenti un codice di errore.
*/
int aggiungi_categoria_testa(lista_categorie_t *lista, categoria_t categoria) {
    nodo_categoria_t *nuovo;

    if (lista == NULL) return ERRORE_PARAMETRI;

    nuovo = malloc(sizeof(nodo_categoria_t));
    if (nuovo == NULL) return ERRORE_MEMORIA;

    nuovo->info = categoria;
    nuovo->next = *lista;
    *lista = nuovo;

    return OK;
}


/*
   Cerca una categoria per codice e la restituisce per indirizzo.
   Se non trovata, restituisce NULL.
*/
categoria_t *cerca_categoria(lista_categorie_t lista, const char codice_categoria[]) {
    nodo_categoria_t *p = lista;

    while (p != NULL) {
        if (strcmp(p->info.codice_categoria, codice_categoria) == 0) {
            return &p->info;
        }
        p = p->next;
    }

    return NULL;
}

void stampa_ticket(evento_ticket_t e) {
    printf("%s %s %s %s %s\n", e.id_ticket, e.orario, stato_ticket_to_string(e.stato), priorita_to_string(e.priorita), e.descrizione);
}
void stampa_coda_ticket(coda_ticket_t coda) {
    nodo_evento_ticket_t *p = coda.primo;
    while (p != NULL) {
        printf("\t- ");
        stampa_ticket(p->info);
        p = p->next;
    }
}
void stampa_lista(lista_categorie_t lista) {
    nodo_categoria_t *p = lista;
    while (p != NULL) {
        printf("%s %s\n", p->info.codice_categoria, p->info.descrizione);
        stampa_coda_ticket(p->info.eventi);
        p = p->next;
    }
}
/* Dato un array di statistiche, le stampa */
void stampa_statistiche(statistica_ticket_t v[], int dim) {
    for (int i = 0; i < dim; i++) {
        // TODO: da completare a cura dello studente
        printf("%s %s %s-%s %s priorita=%s minuti=%d\n", v[i].codice_categoria, v[i].id_ticket, v[i].ora_apertura, v[i].ora_chiusura, v[i].descrizione, priorita_to_string(v[i].priorita), v[i].minuti_risoluzione /* COMPLETARE */);
    }
}


/* Dealloca una coda di eventi (fornita per indirizzo) */
void dealloca_coda(coda_ticket_t *coda) {
    if (coda == NULL) return;

    while (coda->primo != NULL) {
        nodo_evento_ticket_t *tmp = coda->primo;
        coda->primo = coda->primo->next;
        free(tmp);
    }

    coda->ultimo = NULL;
}


/* Dealloca una lista di categorie (fornita per indirizzo) */
void dealloca_categorie(lista_categorie_t *lista) {
    if (lista == NULL) return;

    while (*lista != NULL) {
        nodo_categoria_t *tmp = *lista;
        *lista = (*lista)->next;
        dealloca_coda(&tmp->info.eventi);
        free(tmp);
    }
}


/* ============================================================================
QUESITO 1 - CARICAMENTO DA DUE FILE
========================================================================== */

/*  Carica le categorie dal primo file e gli eventi ticket dal secondo file.
    I dati sono distribuiti su due file:

    - categorie.txt
        Contiene l'elenco delle categorie gestite dal servizio, una per riga:

            codice_categoria descrizione

        Esempio:
            RETE Problemi_di_rete_e_connettivita
            ACCOUNT Credenziali_accessi_e_permessi
            HARDWARE Dispositivi_fisici_e_postazioni

    - ticket.txt
        Contiene gli eventi relativi ai ticket, uno per riga:

            codice_categoria id_ticket orario stato priorita descrizione_evento

        Dove stato puo' assumere i valori APERTO oppure CHIUSO.
        Dove priorita puo' assumere i valori BASSA, MEDIA, ALTA oppure CRITICA.

        Esempio:
            RETE T001 08:05 APERTO ALTA Router_lab_non_raggiungibile
            ACCOUNT T002 08:12 APERTO MEDIA Password_scaduta
            RETE T001 09:30 CHIUSO ALTA Router_riavviato

    Gli eventi nel file ticket.txt sono da considerarsi gia' ordinati
    temporalmente per ciascuna categoria. L'inserimento nella coda deve quindi
    preservare l'ordine di arrivo dal file.

    Parametri in ingresso:
    - file_categorie: nome del file delle categorie
    - file_ticket:    nome del file degli eventi ticket

    Parametri in uscita:
    - lista: puntatore alla lista di categorie da costruire

    Valore di ritorno:
    - OK se il caricamento e' avvenuto correttamente
    - un codice di errore diverso da OK altrimenti
*/
int carica_dati(const char file_categorie[], const char file_ticket[], lista_categorie_t *lista) {
    // TODO: da implementare a cura dello studente

    if (file_categorie == NULL || file_ticket == NULL || lista == NULL) return ERRORE_PARAMETRI;
    categoria_t categoria;
    FILE *fp = fopen(file_categorie, "r");
    if (fp == NULL) return ERRORE_FILE;
    while (fscanf(fp, "%s %s", categoria.codice_categoria, categoria.descrizione) == 2) {
        coda_init(&categoria.eventi);
        if (aggiungi_categoria_testa(lista, categoria) != OK) {
            fclose(fp);
            return ERRORE_MEMORIA;
        }
    }
    fclose(fp);

    evento_ticket_t evento;
    char stato[STR_LEN];
    char priorita[STR_LEN];
    FILE *fp2 = fopen(file_ticket, "r");
    if (fp2 == NULL) return ERRORE_FILE;
    while (fscanf(fp2, "%s %s %s %s %s %s", categoria.codice_categoria, evento.id_ticket, evento.orario, stato, priorita, evento.descrizione) == 6) {
        categoria_t *cat = cerca_categoria(*lista, categoria.codice_categoria);
        if (cat == NULL) return ERRORE_MEMORIA;
        evento.stato = string_to_stato_ticket(stato);
        evento.priorita = string_to_priorita(priorita);
        if (accoda_evento(&cat->eventi, evento) != OK) {
            fclose(fp2);
            return ERRORE_MEMORIA;
        }
    }
    fclose(fp2);
    return OK;
}


/* ============================================================================
QUESITO 2 - RICERCA EVENTO DI CHIUSURA
========================================================================== */
/*
    Cerca il primo evento di chiusura relativo a un ticket con un certo ID
    nella lista fornita.
    Da usare per trovare il corrispettivo di una apertura.

    Parametri in ingresso:
    - lista: puntatore al primo nodo della (sotto)lista di eventi della
        categoria di interesse
    - id_ticket: identificativo del ticket di cui si cerca la chiusura

    Valore di ritorno:
    - Puntatore all'evento corrispondente (o NULL se non trovato)
*/
evento_ticket_t *cerca_evento_chiusura(nodo_evento_ticket_t *lista, const char id_ticket[]) {
    // TODO implementazione a cura dello studente

    for (nodo_evento_ticket_t *tmp = lista; tmp != NULL; tmp = tmp->next) {
        if (tmp->info.stato == CHIUSO && strcmp(tmp->info.id_ticket, id_ticket) == 0) {
            return &tmp->info;
        }
    }
    return NULL;
}


/* ============================================================================
QUESITO 3 - CALCOLO TEMPI DI RISOLUZIONE
========================================================================== */
/*  Produce un vettore dinamico di statistiche per ogni ticket aperto-chiuso.

    Per ogni categoria, gli eventi della coda devono essere analizzati in
    ordine. Ogni coppia APERTO-CHIUSO con lo stesso id_ticket determina un ticket
    risolto.
    Suggerimento: dato un evento di APERTURA di un ticket, cercare
    (dalla sottolista con inizio il successivo del nodo) l'evento di chiusura
    corrispondente, cioe' con lo stesso id_ticket. Gli eventi sono infatti ordinati.

    Il tempo di risoluzione e' calcolabile come differenza in minuti tra orario
    di apertura e orario di chiusura.

    Un evento APERTO per cui non esiste un successivo evento CHIUSO con lo stesso
    id_ticket non deve produrre alcuna statistica.

    Parametri in ingresso:
    - lista: lista delle categorie

    Parametri in uscita:
    - dim_out: numero di elementi del vettore restituito (uno per ticket risolto)

    Valore di ritorno:
    - vettore dinamico di statistica_ticket_t
    - NULL se lista vuota o in caso di errore
*/
statistica_ticket_t *calcola_tempi_risoluzione(lista_categorie_t lista, int *dim_out) {
    // TODO: Da implementare a cura dello studente
    if (dim_out == NULL) return NULL;
    *dim_out = 0;
    if (lista == NULL) return NULL;
    int i = 0;
    for (nodo_categoria_t *c = lista; c != NULL; c = c->next) {
        for (nodo_evento_ticket_t *e = c->info.eventi.primo; e != NULL; e = e->next) {
            if (e->info.stato == APERTO && cerca_evento_chiusura(e->next, e->info.id_ticket)) {
                i++;
            }
        }
    }

    if (i == 0) return NULL;
    statistica_ticket_t *v = malloc(sizeof(statistica_ticket_t) * i);
    if (v == NULL) return NULL;
    *dim_out = i;
    i = 0;

    statistica_ticket_t stat;
    for (nodo_categoria_t *c = lista; c != NULL; c = c->next) {
        for (nodo_evento_ticket_t *e = c->info.eventi.primo; e != NULL; e = e->next) {
            if (e->info.stato == APERTO) {
                evento_ticket_t *chiusura = cerca_evento_chiusura(e->next, e->info.id_ticket);
                if (chiusura != NULL) {
                    int min_ris = differenza_minuti(e->info.orario, chiusura->orario);
                    strcpy(stat.codice_categoria, c->info.codice_categoria);
                    strcpy(stat.id_ticket, e->info.id_ticket);
                    strcpy(stat.ora_apertura, e->info.orario);
                    strcpy(stat.ora_chiusura, chiusura->orario);
                    strcpy(stat.descrizione, e->info.descrizione);
                    stat.priorita = e->info.priorita;
                    stat.minuti_risoluzione = min_ris;
                    v[i++] = stat;
                }
            }
        }
    }
    return v;
}


/* ============================================================================
QUESITO 4 - SALVATAGGIO FILTRATO
========================================================================== */
/* Salvare le statistiche per cui risultano vere entrambe le condizioni:
    - priorita >= priorita_min;
    - minuti_risoluzione >= minuti_min.

    Parametri in ingresso:
        - Percorso del file dove salvare
        - Vettore delle statistiche dei singoli ticket
        - Dimensione del vettore
        - Priorita minima
        - Tempo minimo

    Valore di ritorno:
        - OK se il salvataggio e' avvenuto correttamente
        - un codice di errore diverso da OK altrimenti
*/
int salva_statistiche_filtrate(const char percorso[], statistica_ticket_t array[], int dim,
                               priorita_t priorita_min, int minuti_min) {
    // TODO implementazione a cura dello studente

    FILE *file = fopen(percorso, "w");
    if (file == NULL) {
        return ERRORE_FILE;
    }

    for (int i = 0; i < dim; i++) {
        if (array[i].priorita >= priorita_min && array[i].minuti_risoluzione >= minuti_min) {
            fprintf(file, "Categoria: %s\n", array[i].codice_categoria);
            fprintf(file, "Ticket: %s\n", array[i].id_ticket);
            fprintf(file, "Apertura: %s\n", array[i].ora_apertura);
            fprintf(file, "Chiusura: %s\n", array[i].ora_chiusura);
            fprintf(file, "Descrizione: %s\n", array[i].descrizione);
            fprintf(file, "Priorità: %d\n", array[i].priorita);
            fprintf(file, "Minuti di risoluzione: %d\n", array[i].minuti_risoluzione);
            fprintf(file, "---\n");
        }
    }
    fclose(file);
    return OK;
}


/* ============================================================================
MAIN
========================================================================== */

int main(void) {
    lista_categorie_t categorie = NULL;
    statistica_ticket_t *statistiche = NULL;
    int dim_statistiche = 0;
    char priorita_str[COD_LEN];
    priorita_t priorita_min;
    int minuti_min;

    if (carica_dati(FILE_CATEGORIE, FILE_TICKET, &categorie) != OK) {
        printf("Errore nel caricamento dei dati.\n");
        dealloca_categorie(&categorie);
        return 1;
    }
    printf("Ticket caricati:\n");
    stampa_lista(categorie);

    printf("Statistiche dei tempi di risoluzione:\n");
    statistiche = calcola_tempi_risoluzione(categorie, &dim_statistiche);
    if (statistiche != NULL) {
        stampa_statistiche(statistiche, dim_statistiche);
    } else {
        printf("Nessun ticket risolto trovato.\n");
    }

    printf("Inserire priorita minima da salvare (BASSA/MEDIA/ALTA/CRITICA): ");
    scanf("%15s", priorita_str);
    priorita_min = string_to_priorita(priorita_str);

    printf("Inserire tempo minimo di risoluzione in minuti: ");
    scanf("%d", &minuti_min);

    if (statistiche != NULL) {
        if (salva_statistiche_filtrate(FILE_OUTPUT, statistiche, dim_statistiche,
                                       priorita_min, minuti_min) == OK) {
            printf("Statistiche salvate su %s\n", FILE_OUTPUT);
        } else {
            printf("Errore nel salvataggio delle statistiche.\n");
        }
    }

    free(statistiche);
    dealloca_categorie(&categorie);

    return 0;
}
