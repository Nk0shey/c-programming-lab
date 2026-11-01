#include "../../common/console.h"
/******************************************************************************
 * === MODULO 2 ===
 * SIMULAZIONE ESAME - Fondamenti di Programmazione - A.A. 2025/26
 * Tempo consigliato: 120 minuti
 *
 * Implementare in C un programma per la gestione dei ticket di un centro
 * assistenza.
 *
 * I ticket sono memorizzati in una struttura composta da un vettore di code.
 * La posizione del vettore in cui inserire un ticket e' calcolata tramite una
 * funzione indice applicata al nome del reparto.
 *
 * Nota: il reparto NON identifica univocamente un ticket. Piu' ticket possono
 * appartenere allo stesso reparto e quindi trovarsi nella stessa coda del
 * vettore.
 *
 * Ogni posizione del vettore contiene una coda FIFO di ticket:
 * - i nuovi ticket vengono inseriti in fondo alla coda;
 * - i ticket nella stessa coda sono quindi memorizzati in ordine di arrivo
 *   nel file di input.
 *
 * Ogni ticket e' caratterizzato da:
 * - codice     stringa senza spazi
 * - cliente    stringa senza spazi
 * - reparto    stringa senza spazi, es. Hardware, Software, Reti, Sistemi
 * - categoria  stringa senza spazi, es. PC, Server, Router, App
 * - priorita   intero compreso tra 1 e 5, dove 1 = massima urgenza
 * - tempo      valore reale che indica il tempo stimato in ore
 *
 * Il file ticket.txt contiene un ticket per riga, nel formato:
 *
 *      codice cliente reparto categoria priorita tempo
 *
 * Esempio:
 *
 *      TK001 Rossi Hardware PC 2 1.50
 *      TK014 Verdi Software App 1 3.00
 *
 * Il programma deve implementare le seguenti funzionalita':
 *
 * 1. Inserire un ticket in fondo alla coda FIFO corrispondente.
 *
 * 2. Caricare i dati dal file ticket.txt nel vettore di code.
 *
 * 3. Cercare il primo ticket associato a un dato reparto.
 *
 * 4. Estrarre tutti i ticket con priorita minore o uguale a una soglia in una
 *    nuova struttura dati scelta dallo studente. Sono ammesse tre possibilita':
 *    - array dinamico di ticket_t;
 *    - lista collegata di ticket;
 *    - pila LIFO di ticket.
 *
 *    La funzione di estrazione deve:
 *    - scorrere tutte le code del vettore;
 *    - selezionare solo i ticket con priorita <= soglia;
 *    - produrre una nuova struttura contenente i ticket selezionati;
 *    - rendere disponibile al chiamante il numero di elementi estratti;
 *    - se non ci sono ticket che soddisfano il filtro, il numero di elementi
 *      estratti deve essere zero.
 *
 * 5. Deallocare le strutture allocate dinamicamente.
 *
 ******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_INPUT   "ticket.txt"

#define STR_LEN      50
#define VETT_DIM     7

#define OK                0
#define ERRORE_FILE       1
#define ERRORE_MEMORIA    2
#define ERRORE_PARAMETRI  3
#define ERRORE_DATI       4

/*
 * Tipo fittizio usato per la funzione il cui tipo di ritorno deve essere
 * completato dallo studente.
 */


/*
 * Tipo fittizio usato nel main per memorizzare il risultato dell'estrazione.
 * Lo studente deve sostituirlo con il tipo coerente con la propria scelta:
 * - ticket_t *      se usa array dinamico;
 * - lista_t         se usa lista collegata;
 * - pila_t          se usa pila LIFO.
 */



/* ============================================================================
 * STRUTTURE DATI
 * ========================================================================== */

typedef struct {
    char codice[STR_LEN];
    char cliente[STR_LEN];
    char reparto[STR_LEN];
    char categoria[STR_LEN];
    int priorita;
    float tempo;
} ticket_t;

typedef struct nodo_ticket {
    ticket_t info;
    struct nodo_ticket *next;
} nodo_ticket_t;

typedef nodo_ticket_t *lista_t;

/*
 * Coda FIFO di ticket.
 */
typedef struct {
    nodo_ticket_t *primo;
    nodo_ticket_t *ultimo;
} coda_t;

/*
 * Pila LIFO di ticket.
 * Puoi usarla per il Quesito 4 se scegli la rappresentazione con pila.
 */
typedef struct {
    nodo_ticket_t *cima;
} pila_t;

typedef coda_t centro_t[VETT_DIM];


/* ============================================================================
 * FUNZIONI GIA' FORNITE
 * ========================================================================== */

/*
 * Calcola la posizione del vettore associata a una stringa.
 */
int funzione_indice(const char s[]) {
    unsigned int h = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        h = (h * 31u + (unsigned char)s[i]) % VETT_DIM;
    }

    return (int)h;
}

void coda_init(coda_t *coda) {
    if (coda == NULL)
        return;

    coda->primo = NULL;
    coda->ultimo = NULL;
}

void pila_init(pila_t *pila) {
    if (pila == NULL)
        return;

    pila->cima = NULL;
}

void centro_init(centro_t centro) {
    for (int i = 0; i < VETT_DIM; i++) {
        coda_init(&centro[i]);
    }
}

void stampa_ticket(const ticket_t *t) {
    if (t == NULL)
        return;

    printf("%s %s %s %s %d %.2f\n",
           t->codice,
           t->cliente,
           t->reparto,
           t->categoria,
           t->priorita,
           t->tempo);
}

void stampa_lista_ticket(lista_t lista) {
    nodo_ticket_t *p = lista;

    while (p != NULL) {
        stampa_ticket(&p->info);
        p = p->next;
    }
}

void stampa_coda_ticket(const coda_t *coda) {
    if (coda == NULL || coda->primo == NULL) {
        printf("Coda vuota.\n");
        return;
    }

    stampa_lista_ticket(coda->primo);
}

void stampa_pila_ticket(pila_t pila) {
    if (pila.cima == NULL) {
        printf("Pila vuota.\n");
        return;
    }

    stampa_lista_ticket(pila.cima);
}

void stampa_array_ticket(const ticket_t ticket[], int dim) {
    if (ticket == NULL || dim <= 0) {
        printf("Array vuoto.\n");
        return;
    }

    for (int i = 0; i < dim; i++) {
        stampa_ticket(&ticket[i]);
    }
}

void stampa_centro(const centro_t centro) {
    for (int i = 0; i < VETT_DIM; i++) {
        printf("Coda %d:\n", i);
        stampa_coda_ticket(&centro[i]);
    }
}

void dealloca_lista(lista_t *lista) {
    if (lista == NULL)
        return;

    while (*lista != NULL) {
        nodo_ticket_t *tmp = *lista;
        *lista = (*lista)->next;
        free(tmp);
    }
}

void dealloca_coda(coda_t *coda) {
    if (coda == NULL)
        return;

    dealloca_lista(&coda->primo);
    coda->ultimo = NULL;
}

void dealloca_centro(centro_t centro) {
    for (int i = 0; i < VETT_DIM; i++) {
        dealloca_coda(&centro[i]);
    }
}


/* ============================================================================
 * QUESITO 1 - INSERIMENTO IN CODA
 * ========================================================================== */

/*
 * Inserisce un ticket in fondo a una coda FIFO.
 *
 * La funzione deve allocare un nuovo nodo, copiare al suo interno il ticket
 * ricevuto come parametro e collegarlo in fondo alla coda.
 *
 * Parametri in ingresso/uscita:
 * - coda: puntatore alla coda da modificare
 *
 * Parametri in ingresso:
 * - ticket: ticket da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int accoda_ticket(coda_t *coda, ticket_t ticket) {
    // TODO implementazione a cura dello studente
    if (!coda) return ERRORE_DATI;
    nodo_ticket_t *paux = malloc(sizeof(nodo_ticket_t));
    if (!paux) return ERRORE_DATI;

    paux->info = ticket;
    paux->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = paux;
        coda->ultimo = paux;
    } else {
        coda->ultimo->next = paux;
        coda->ultimo = paux;
    }

    return OK;
}

/*
 * Inserisce un ticket nel centro assistenza.
 *
 * La funzione calcola la posizione del vettore a partire dal reparto e
 * inserisce il ticket in fondo alla coda corrispondente.
 */
int centro_put(centro_t centro, ticket_t ticket) {
    int k = funzione_indice(ticket.reparto);
    return accoda_ticket(&centro[k], ticket);
}


/* ============================================================================
 * QUESITO 2 - CARICAMENTO DA FILE
 * ========================================================================== */

/*
 * Carica i ticket dal file indicato e li inserisce nel vettore di code.
 *
 * Il file contiene un ticket per riga nel formato:
 *
 *      codice cliente reparto categoria priorita tempo
 *
 * Parametri in ingresso/uscita:
 * - centro: vettore di code in cui inserire i ticket
 *
 * Parametri in ingresso:
 * - nome_file: nome del file da leggere
 *
 * Parametri in uscita:
 * - num_caricati: numero di ticket caricati correttamente
 *
 * Valore di ritorno:
 * - OK se il caricamento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int carica_ticket(centro_t centro, const char nome_file[], int *num_caricati) {
    // TODO implementazione a cura dello studente
    if (!centro || !nome_file || !num_caricati) return ERRORE_DATI;
    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
        return ERRORE_FILE;
    }
    *num_caricati = 0;

    ticket_t ticket;
    while (fscanf(fp, "%s %s %s %s %d %f", ticket.codice, ticket.cliente, ticket.reparto, ticket.categoria, &ticket.priorita, &ticket.tempo) == 6) {
        if (centro_put(centro, ticket) == OK) {
            (*num_caricati)++;
        } else {
            fclose(fp);
            return ERRORE_MEMORIA;
        }
    }

    fclose(fp);
    return OK;
}


/* ============================================================================
 * QUESITO 3 - RICERCA PER REPARTO
 * ========================================================================== */

/*
 * Cerca il primo ticket appartenente al reparto specificato.
 *
 * La funzione deve calcolare la posizione del vettore a partire dal reparto e
 * scorrere la coda corrispondente. Poiche' il reparto non e' un identificatore
 * univoco, e' sufficiente restituire la prima occorrenza trovata.
 *
 * Parametri in ingresso:
 * - centro:  vettore di code
 * - reparto: reparto da cercare
 *
 * Valore di ritorno:
 * - puntatore al nodo contenente il primo ticket trovato
 * - NULL se non esiste alcun ticket per il reparto indicato
 */
nodo_ticket_t *cerca_reparto(centro_t centro, const char reparto[]) {
    // TODO implementazione a cura dello studente
    if (!centro || !reparto) return NULL;
    int indice = funzione_indice(reparto);
    nodo_ticket_t *paux = centro[indice].primo;
    while (paux) {
        if (strcmp(paux->info.reparto, reparto) == 0) {
            return paux;
        }
        paux = paux->next;
    }
    return NULL;
}


/* ============================================================================
 * QUESITO 4 - ESTRAZIONE PER PRIORITA'
 * ========================================================================== */

/*
 * Estrarre dal centro tutti i ticket con priorita minore o uguale alla soglia.
 *
 * La funzione deve produrre una nuova struttura dati scelta dallo studente.
 * Sono ammesse le seguenti rappresentazioni:
 * - array dinamico di ticket_t;
 * - lista collegata di ticket;
 * - pila LIFO di ticket.
 *
 * Requisiti:
 * - completare il tipo di ritorno sostituendo DA_SOSTITUIRE;
 * - completare la lista dei parametri;
 * - scorrere tutte le code del vettore;
 * - selezionare i ticket con priorita <= soglia;
 * - produrre una nuova struttura contenente i ticket selezionati;
 * - rendere disponibile al chiamante il numero di elementi estratti.
 */
lista_t estrai_urgenti(centro_t centro, float soglia, int *num_estratte) {
    // TODO implementazione a cura dello studente
    // if (!centro || !num_estratte) return NULL;
    // *num_estratte = 0;
    // for (int i = 0; i < VETT_DIM; i++) {
    //     nodo_ticket_t *paux = centro[i].primo;
    //     while (paux) {
    //         if (paux->info.priorita <= soglia) {
    //             (*num_estratte)++;
    //         }
    //         paux = paux->next;
    //     }
    // }
    //
    // if (*num_estratte == 0) return NULL;
    // ticket_t *estratti = malloc(sizeof(ticket_t) * (*num_estratte));
    // if (!estratti) return estratti;
    // for (int i = 0, j = 0; i < VETT_DIM; i++) {
    //     nodo_ticket_t *paux = centro[i].primo;
    //     while (paux) {
    //         if (paux->info.priorita <= soglia) {
    //             estratti[j++] = paux->info;
    //         }
    //         paux = paux->next;
    //     }
    // }
    // return estratti;

    if (!centro || !num_estratte) return NULL;
    *num_estratte = 0;
    lista_t lista = NULL;
    nodo_ticket_t *ultimo = NULL;

    for (int i = 0; i < VETT_DIM; i++) {
        nodo_ticket_t *paux = centro[i].primo;
        while (paux) {
            if (paux->info.priorita <= soglia) {
                nodo_ticket_t *nuovo = malloc(sizeof(nodo_ticket_t));
                if (!nuovo) return lista;

                nuovo->info = paux->info;
                nuovo->next = NULL;
                if (lista == NULL) {
                    lista = nuovo;
                    ultimo = nuovo;
                } else {
                    ultimo->next = nuovo;
                    ultimo = nuovo;
                }
                (*num_estratte)++;
            }
            paux = paux->next;
        }
    }
    return lista;


}


/* ============================================================================
 * QUESITO 5 - DEALLOCAZIONE STRUTTURA ESTRATTA
 * ========================================================================== */

/*
 * Deallocare la struttura creata dal Quesito 4.
 *
 * Nota:
 * - se scegli array dinamico, basta free(array);
 * - se scegli lista collegata, devi scorrere e liberare tutti i nodi;
 * - se scegli pila LIFO, devi liberare tutti i nodi partendo da cima.
 *
 * Il prototipo puo' essere modificato coerentemente con la struttura scelta.
 */
void dealloca_estratti(lista_t *estratti) {
while (*estratti) { lista_t n=*estratti; *estratti=n->next; free(n); }
}


/* ============================================================================
 * MAIN
 * ========================================================================== */

int menu(void) {
    int scelta;

    printf("\n*** MENU ***\n");
    printf("1. Cerca primo ticket di un reparto\n");
    printf("2. Stampa ticket di un reparto\n");
    printf("3. Estrai ticket urgenti\n");
    printf("4. Stampa ultimi ticket estratti\n");
    printf("0. Esci\n");
    printf("Scelta: ");

    if (lab_scanf("%d", &scelta) != 1) {
        return 0;
    }

    return scelta;
}

int main(void) {
    centro_t centro;
    lista_t estratti = NULL;
    nodo_ticket_t *trovato = NULL;
    int num_caricati = 0;
    int num_estratti = 0;
    int scelta;
    int soglia;
    char reparto[STR_LEN];

    centro_init(centro);

    if (carica_ticket(centro, FILE_INPUT, &num_caricati) != OK) {
        printf("Errore nel caricamento dei ticket.\n");
        dealloca_centro(centro);
        return 1;
    }

    printf("Ticket caricati: %d\n", num_caricati);
    stampa_centro(centro);

    do {
        scelta = menu();

        switch (scelta) {
            case 1:
                printf("Inserire reparto: ");
                lab_scanf("%49s", reparto);

                trovato = cerca_reparto(centro, reparto);
                if (trovato != NULL) {
                    stampa_ticket(&trovato->info);
                } else {
                    printf("Nessun ticket trovato per il reparto indicato.\n");
                }
                break;

            case 2:
                printf("Inserire reparto: ");
                lab_scanf("%49s", reparto);

                trovato = cerca_reparto(centro, reparto);
                if (trovato != NULL) {
                    stampa_coda_ticket(&centro[funzione_indice(reparto)]);
                } else {
                    printf("Nessun ticket trovato per il reparto indicato.\n");
                }
                break;

            case 3:
                printf("Inserire soglia priorita (1-5): ");
                lab_scanf("%d", &soglia);

                num_estratti = 0;

                /*
                 * Dopo avere completato il prototipo di estrai_urgenti,
                 * completare la chiamata alla funzione.
                 */
                // TODO implementazione a cura dello studente
                dealloca_estratti(&estratti);
                estratti = estrai_urgenti(centro, soglia, &num_estratti);
                stampa_lista_ticket(estratti);

                printf("Ticket estratti: %d\n", num_estratti);

                /*
                 * Stampare subito i ticket estratti usando la funzione coerente
                 * con la struttura scelta:
                 * - stampa_array_ticket(estratti, num_estratti);
                 * - stampa_lista_ticket(estratti);
                 * - stampa_pila_ticket(estratti);
                 */
                // TODO implementazione a cura dello studente
                break;

            case 4:
                /*
                 * Chiamare la funzione di stampa coerente con la struttura
                 * scelta per l'estrazione.
                 */
                // TODO implementazione a cura dello studente
                stampa_lista_ticket(estratti);
                break;

            case 0:
                printf("Uscita dal programma.\n");
                break;

            default:
                printf("Scelta non valida.\n");
                break;
        }

    } while (scelta != 0);

    dealloca_estratti(&estratti);
    dealloca_centro(centro);

    return 0;
}
