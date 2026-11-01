/*
===============================================================================
SIMULAZIONE FINALE PRE-ESAME - FONDAMENTI DI PROGRAMMAZIONE, MODULO 2
LINGUAGGIO C - ALLENAMENTO COMPLETO ADT COLLEGATI

OBIETTIVO
---------
Allenare le funzioni fondamentali delle strutture collegate e TUTTE le
combinazioni realistiche tra:

    LISTA
    CODA FIFO
    PILA LIFO

VARIANTI PRESENTI
-----------------
1. LISTA -> CODA
2. LISTA -> PILA
3. CODA  -> LISTA
4. CODA  -> PILA
5. PILA  -> LISTA
6. PILA  -> CODA

Ogni freccia significa:
    ogni elemento dell'ADT esterno contiene un ADT interno.

Esempio:
    LISTA -> CODA
    lista di reparti, ogni reparto contiene una coda di ticket.

MODALITA' CONSIGLIATA
---------------------
- Per una simulazione da 120 minuti: scegli 3 varianti su 6.
- Per il ripasso finale completo: svolgi tutte le varianti.
- NON modificare le typedef.
- NON cambiare i prototipi.
- Usa malloc/free correttamente.
- Dopo la deallocazione, azzera sempre i puntatori esterni.
- Nelle code, quando diventano vuote:
      primo == NULL
      ultimo == NULL

IMPORTANTE
----------
Le funzioni marcate TODO sono volutamente NON implementate.
Le funzioni di stampa e ricerca fornite servono come supporto.

===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERRORE 0

#define MAX_COD 16
#define MAX_NOME 40
#define MAX_DESC 80
#define MAX_DEST 40


/* ============================================================================
 * VARIANTE 1
 * LISTA -> CODA
 *
 * Scenario:
 * Un centro assistenza possiede una LISTA ORDINATA di reparti.
 * Ogni reparto contiene una CODA FIFO di ticket.
 * ========================================================================== */

typedef struct {
    char id[MAX_COD];
    int priorita;
    char descrizione[MAX_DESC];
} V1_Ticket;

typedef struct v1_nodo_ticket {
    V1_Ticket info;
    struct v1_nodo_ticket *next;
} V1_NodoTicket;

typedef struct {
    V1_NodoTicket *primo;
    V1_NodoTicket *ultimo;
} V1_CodaTicket;

typedef struct {
    char codice[MAX_COD];
    char nome[MAX_NOME];
    V1_CodaTicket ticket;
} V1_Reparto;

typedef struct v1_nodo_reparto {
    V1_Reparto info;
    struct v1_nodo_reparto *next;
} V1_NodoReparto;

typedef V1_NodoReparto *V1_ListaReparti;


void v1_init_coda(V1_CodaTicket *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}

V1_NodoReparto *v1_cerca_reparto(V1_ListaReparti lista,
                                  const char codice[]) {
    while (lista != NULL) {
        if (strcmp(lista->info.codice, codice) == 0)
            return lista;
        lista = lista->next;
    }
    return NULL;
}

void v1_stampa(V1_ListaReparti lista) {
    printf("\n===== V1: LISTA -> CODA =====\n");

    while (lista != NULL) {
        printf("[%s] %s\n", lista->info.codice, lista->info.nome);

        V1_NodoTicket *t = lista->info.ticket.primo;
        while (t != NULL) {
            printf("   %s priorita=%d %s\n",
                   t->info.id,
                   t->info.priorita,
                   t->info.descrizione);
            t = t->next;
        }

        lista = lista->next;
    }
}


/* QUESITO 1A
 *
 * Inserire un reparto nella lista mantenendo l'ordine alfabetico crescente
 * per codice.
 *
 * Vincoli:
 * - rifiutare codici duplicati;
 * - inizializzare la coda interna;
 * - gestire inserimento in testa, mezzo e fondo.
 */
int v1_inserisci_reparto_ordinato(V1_ListaReparti *lista,
                                  const char codice[],
                                  const char nome[]) {
    /* TODO QUESITO 1A */
    V1_NodoReparto *corrente = *lista;
    V1_NodoReparto *precedente = NULL;

    while (corrente != NULL && strcmp(corrente->info.codice, codice) < 0) {
        precedente = corrente;
        corrente = corrente->next;
    }

    if (corrente != NULL && strcmp(corrente->info.codice, codice) == 0) {
        return ERRORE;
    }

    V1_NodoReparto *nodo = malloc(sizeof(V1_NodoReparto));
    if (nodo == NULL) {
        return ERRORE;
    }

    strcpy(nodo->info.codice, codice);
    strcpy(nodo->info.nome, nome);
    v1_init_coda(&nodo->info.ticket);

    nodo->next = corrente;
    if (precedente == NULL) {
        *lista = nodo;
    }
    else {
        precedente->next = nodo;
    }

    return OK;
}


/* QUESITO 1B
 *
 * Inserire un ticket in CODA FIFO.
 *
 * Gestire correttamente:
 * - coda inizialmente vuota;
 * - coda non vuota;
 * - aggiornamento di ultimo.
 */
int v1_enqueue_ticket(V1_CodaTicket *coda, V1_Ticket ticket) {
    /* TODO QUESITO 1B */

    V1_NodoTicket *nodo = malloc(sizeof(V1_NodoTicket));
    if (nodo == NULL) {
        return ERRORE;
    }

    nodo->info = ticket;
    nodo->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = nodo;
        coda->ultimo = nodo;
    } else {
        coda->ultimo->next = nodo;
        coda->ultimo = nodo;
    }

    return OK;
}


/* QUESITO 1C
 *
 * Estrarre il primo ticket della coda.
 *
 * Restituire:
 * - OK se l'estrazione avviene;
 * - ERRORE se la coda e' vuota.
 *
 * Se viene estratto l'ultimo nodo:
 *     primo = NULL
 *     ultimo = NULL
 */
int v1_dequeue_ticket(V1_CodaTicket *coda, V1_Ticket *ticket) {
    /* TODO QUESITO 1C */
    if (coda->primo == NULL) {
        return ERRORE;
    }

    V1_NodoTicket *temp = coda->primo;
    *ticket = temp->info;
    coda->primo = coda->primo->next;

    if (coda->primo == NULL) {
        coda->ultimo = NULL;
    }

    free(temp);
    return OK;
}


/* QUESITO 1D
 *
 * Rimuovere dalla lista il reparto avente il codice indicato.
 *
 * PRIMA di liberare il nodo reparto:
 * - deallocare completamente la sua coda interna.
 *
 * Gestire rimozione:
 * - testa;
 * - mezzo;
 * - fondo.
 */
int v1_rimuovi_reparto(V1_ListaReparti *lista,
                       const char codice[]) {
    /* TODO QUESITO 1D */

    V1_NodoReparto *corrente = *lista;
    V1_NodoReparto *precedente = NULL;

    while (corrente != NULL && strcmp(corrente->info.codice, codice) != 0) {
        precedente = corrente;
        corrente = corrente->next;
    }
    if (corrente == NULL) {
        return ERRORE;
    }

    V1_NodoTicket *nodo_corrente = corrente->info.ticket.primo;
    while (nodo_corrente!= NULL) {
        V1_NodoTicket *temp = nodo_corrente;
        nodo_corrente = nodo_corrente->next;
        free(temp);
    }

    corrente->info.ticket.primo = NULL;
    corrente->info.ticket.ultimo = NULL;

    if (precedente == NULL) {
        *lista = corrente -> next;
    } else {
        precedente->next = corrente->next;
    }

    free(corrente);
    return OK;
}


/* QUESITO 1E
 *
 * Deallocazione profonda:
 * - tutte le code interne;
 * - tutti i nodi della lista.
 *
 * Al termine:
 *     *lista == NULL
 */
void v1_dealloca_tutto(V1_ListaReparti *lista) {
    /* TODO QUESITO 1E */
    V1_NodoReparto *nodo_reparto = *lista;
    while (nodo_reparto != NULL) {
        V1_NodoTicket *nodo = nodo_reparto->info.ticket.primo;
        while (nodo != NULL) {
            V1_NodoTicket *temp = nodo;
            nodo = nodo->next;
            free(temp);
        }
        V1_NodoReparto * temp = nodo_reparto;
        nodo_reparto = nodo_reparto->next;
        free(temp);
    }
    *lista = NULL;
}


/* ============================================================================
 * VARIANTE 2
 * LISTA -> PILA
 *
 * Scenario:
 * Un deposito possiede una LISTA di scaffali.
 * Ogni scaffale contiene una PILA LIFO di pacchi.
 * ========================================================================== */

typedef struct {
    char id[MAX_COD];
    float peso;
    char destinazione[MAX_DEST];
} V2_Pacco;

typedef struct v2_nodo_pacco {
    V2_Pacco info;
    struct v2_nodo_pacco *next;
} V2_NodoPacco;

typedef V2_NodoPacco *V2_PilaPacchi;

typedef struct {
    char codice[MAX_COD];
    char zona[MAX_NOME];
    V2_PilaPacchi pacchi;
} V2_Scaffale;

typedef struct v2_nodo_scaffale {
    V2_Scaffale info;
    struct v2_nodo_scaffale *next;
} V2_NodoScaffale;

typedef V2_NodoScaffale *V2_ListaScaffali;


V2_NodoScaffale *v2_cerca_scaffale(V2_ListaScaffali lista,
                                    const char codice[]) {
    while (lista != NULL) {
        if (strcmp(lista->info.codice, codice) == 0)
            return lista;
        lista = lista->next;
    }
    return NULL;
}

void v2_stampa(V2_ListaScaffali lista) {
    printf("\n===== V2: LISTA -> PILA =====\n");

    while (lista != NULL) {
        printf("[%s] zona=%s\n",
               lista->info.codice,
               lista->info.zona);

        V2_NodoPacco *p = lista->info.pacchi;
        while (p != NULL) {
            printf("   %s peso=%.2f dest=%s\n",
                   p->info.id,
                   p->info.peso,
                   p->info.destinazione);
            p = p->next;
        }

        lista = lista->next;
    }
}


/* QUESITO 2A
 *
 * Inserire un nuovo scaffale IN TESTA alla lista.
 * Rifiutare codici duplicati.
 * La pila interna deve essere inizializzata a NULL.
 */
int v2_inserisci_scaffale(V2_ListaScaffali *lista,
                          const char codice[],
                          const char zona[]) {
    /* TODO QUESITO 2A */
    if (v2_cerca_scaffale(*lista, codice) != NULL) return ERRORE;

    V2_NodoScaffale *nodo = malloc(sizeof(V2_NodoScaffale));
    if (nodo == NULL) return ERRORE;
    strcpy(nodo->info.codice, codice);
    strcpy(nodo->info.zona, zona);
    nodo->info.pacchi = NULL;

    V2_NodoScaffale *p = *lista;
    nodo->next = p;
    *lista = nodo;

    return OK;
}


/* QUESITO 2B
 *
 * Push LIFO di un pacco.
 */
int v2_push_pacco(V2_PilaPacchi *pila, V2_Pacco pacco) {
    /* TODO QUESITO 2B */
    if (!*pila) return ERRORE;

    V2_NodoPacco *nodo = malloc(sizeof(V2_NodoScaffale));
    if (nodo == NULL) return ERRORE;

    nodo->info = pacco;
    nodo->next = *pila;
    *pila = nodo;

    return OK;
}


/* QUESITO 2C
 *
 * Pop LIFO di un pacco.
 * Il nodo estratto deve essere liberato.
 */
int v2_pop_pacco(V2_PilaPacchi *pila, V2_Pacco *pacco) {
    /* TODO QUESITO 2C */
    if (!*pila) return ERRORE;

    V2_NodoPacco *nodo = *pila;
    *pacco = nodo->info;
    *pila = nodo->next;

    return OK;
}


/* QUESITO 2D
 *
 * Spostare UN SOLO pacco:
 * - dalla cima della pila dello scaffale sorgente;
 * - alla cima della pila dello scaffale destinazione.
 *
 * Usare logicamente pop + push.
 *
 * Se una delle operazioni non puo' essere eseguita,
 * lasciare le strutture in uno stato coerente.
 */
int v2_sposta_pacco(V2_ListaScaffali lista,
                    const char sorgente[],
                    const char destinazione[]) {
    /* TODO QUESITO 2D */

    V2_NodoScaffale *nodo_sorgente = v2_cerca_scaffale(lista, sorgente);
    if (nodo_sorgente == NULL) return ERRORE;

    V2_NodoScaffale *nodo_destinazione = v2_cerca_scaffale(lista, destinazione);
    if (nodo_destinazione == NULL) return ERRORE;

    V2_Pacco pacco;

    if (v2_pop_pacco(&nodo_sorgente->info.pacchi, &pacco) != OK) {
        return ERRORE;
    }

    if (v2_push_pacco(&nodo_destinazione->info.pacchi, pacco) != OK) {
        v2_push_pacco(&nodo_sorgente->info.pacchi, pacco);
        return ERRORE;
    }
    return OK;
}


/* QUESITO 2E
 *
 * Deallocare:
 * - tutte le pile interne;
 * - tutta la lista degli scaffali.
 *
 * Al termine:
 *     *lista == NULL
 */
void v2_dealloca_tutto(V2_ListaScaffali *lista) {
    /* TODO QUESITO 2E */
    V2_NodoScaffale *nodo = *lista;
    while (nodo != NULL) {
        V2_NodoPacco *nodo_pacco = nodo->info.pacchi;
        while (nodo_pacco != NULL) {
            V2_NodoPacco *temp = nodo_pacco;
            nodo_pacco = nodo_pacco->next;
            free(temp);
        }
        V2_NodoScaffale *temp = nodo;
        nodo = nodo->next;
        free(temp);
    }
    *lista = NULL;
}


/* ============================================================================
 * VARIANTE 3
 * CODA -> LISTA
 *
 * Scenario:
 * Uno sportello amministrativo gestisce una CODA FIFO di pratiche.
 * Ogni pratica contiene una LISTA ORDINATA di documenti.
 * ========================================================================== */

typedef struct {
    char codice[MAX_COD];
    char descrizione[MAX_DESC];
} V3_Documento;

typedef struct v3_nodo_documento {
    V3_Documento info;
    struct v3_nodo_documento *next;
} V3_NodoDocumento;

typedef V3_NodoDocumento *V3_ListaDocumenti;

typedef struct {
    char id[MAX_COD];
    char richiedente[MAX_NOME];
    V3_ListaDocumenti documenti;
} V3_Pratica;

typedef struct v3_nodo_pratica {
    V3_Pratica info;
    struct v3_nodo_pratica *next;
} V3_NodoPratica;

typedef struct {
    V3_NodoPratica *primo;
    V3_NodoPratica *ultimo;
} V3_CodaPratiche;


void v3_init_coda(V3_CodaPratiche *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}

V3_NodoPratica *v3_cerca_pratica(V3_CodaPratiche coda,
                                  const char id[]) {
    V3_NodoPratica *p = coda.primo;

    while (p != NULL) {
        if (strcmp(p->info.id, id) == 0)
            return p;
        p = p->next;
    }

    return NULL;
}

void v3_stampa(V3_CodaPratiche coda) {
    printf("\n===== V3: CODA -> LISTA =====\n");

    V3_NodoPratica *p = coda.primo;

    while (p != NULL) {
        printf("Pratica %s - %s\n",
               p->info.id,
               p->info.richiedente);

        V3_NodoDocumento *d = p->info.documenti;
        while (d != NULL) {
            printf("   %s %s\n",
                   d->info.codice,
                   d->info.descrizione);
            d = d->next;
        }

        p = p->next;
    }
}


/* QUESITO 3A
 *
 * Inserire una nuova pratica in fondo alla CODA FIFO.
 * La lista interna dei documenti deve essere inizializzata a NULL.
 */
int v3_enqueue_pratica(V3_CodaPratiche *coda,
                       const char id[],
                       const char richiedente[]) {
    /* TODO QUESITO 3A */

    V3_NodoPratica *nodo = malloc(sizeof(V3_NodoPratica));
    if (nodo == NULL) {
        return ERRORE;
    }

    strcpy(nodo->info.id, id);
    strcpy(nodo->info.richiedente, richiedente);
    nodo->info.documenti = NULL;
    nodo->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = nodo;
        coda->ultimo = nodo;
    } else {
        coda->ultimo->next = nodo;
        coda->ultimo = nodo;
    }

    return OK;
}


/* QUESITO 3B
 *
 * Cercare la pratica indicata e inserire un documento nella sua LISTA
 * mantenendo l'ordine crescente per codice documento.
 *
 * Rifiutare documenti duplicati nella stessa pratica.
 */
int v3_inserisci_documento_ordinato(V3_CodaPratiche coda,
                                    const char id_pratica[],
                                    V3_Documento documento) {
    /* TODO QUESITO 3B */
    V3_NodoPratica *trovato = v3_cerca_pratica(coda, id_pratica);
    if (trovato == NULL) {
        return ERRORE;
    }

    V3_NodoDocumento *corrente = trovato->info.documenti;
    V3_NodoDocumento *precedente = NULL;
    while (corrente != NULL && strcmp(corrente->info.codice, documento.codice) < 0) {
        precedente = corrente;
        corrente = corrente->next;
    }

    if (corrente != NULL && strcmp(corrente->info.codice,  documento.codice) == 0) {
        return ERRORE;
    }

    V3_NodoDocumento *nodo = malloc(sizeof(V3_NodoDocumento));
    if (nodo == NULL) {
        return ERRORE;
    }

    nodo->info = documento;
    nodo->next = corrente;

    if (precedente == NULL) {
        trovato->info.documenti = nodo;
    } else {
        precedente->next = nodo;
    }

    return OK;

}


/* QUESITO 3C
 *
 * Rimuovere dalla lista interna di una pratica il documento con codice dato.
 *
 * Gestire testa, mezzo e fondo.
 */
int v3_rimuovi_documento(V3_CodaPratiche coda,
                         const char id_pratica[],
                         const char codice_documento[]) {
    /* TODO QUESITO 3C */
    V3_NodoPratica *trovato = v3_cerca_pratica(coda, id_pratica);
    if (trovato == NULL) {
        return ERRORE;
    }

    V3_NodoDocumento *corrente = trovato->info.documenti;
    V3_NodoDocumento *precedente = NULL;
    while (corrente != NULL && strcmp(corrente->info.codice, codice_documento) != 0) {
        precedente = corrente;
        corrente = corrente->next;
    }

    if (corrente == NULL) return ERRORE;

    if (precedente == NULL) {
        trovato->info.documenti = corrente->next;
    } else {
        precedente->next = corrente->next;
    }
    free(corrente);
    return OK;
}


/* QUESITO 3D
 *
 * Chiudere la PRIMA pratica della coda.
 *
 * Prima di liberare il nodo esterno:
 * - deallocare TUTTA la lista documenti della pratica.
 *
 * Aggiornare correttamente primo e ultimo.
 */
int v3_dequeue_pratica(V3_CodaPratiche *coda) {
    /* TODO QUESITO 3D */

    if (coda->primo == NULL) {
        return ERRORE;
    }

    V3_NodoPratica *nodo = coda->primo;

    V3_NodoDocumento *nodo_documento = nodo->info.documenti;
    while (nodo_documento != NULL) {
        V3_NodoDocumento *temp = nodo_documento;
        nodo_documento = nodo_documento->next;
        free(temp);
    }

    coda->primo = nodo->next;
    if (coda->primo == NULL) {
        coda->ultimo = NULL;
    }

    free(nodo);

    return OK;
}


/* QUESITO 3E
 *
 * Deallocazione profonda dell'intera CODA DI LISTE.
 *
 * Al termine:
 *     coda->primo == NULL
 *     coda->ultimo == NULL
 */
void v3_dealloca_tutto(V3_CodaPratiche *coda) {
    /* TODO QUESITO 3E */

    V3_NodoPratica *nodo = coda->primo;
    while (nodo != NULL) {
        V3_NodoDocumento *nodo_documento = nodo->info.documenti;
        while (nodo_documento != NULL) {
            V3_NodoDocumento *temp = nodo_documento;
            nodo_documento = nodo_documento->next;
            free(temp);
        }
        V3_NodoPratica *temp = nodo;
        nodo = nodo->next;
        free(temp);
    }

    coda->primo = NULL;
    coda->ultimo = NULL;
}


/* ============================================================================
 * VARIANTE 4
 * CODA -> PILA
 *
 * Scenario:
 * Un magazzino gestisce una CODA FIFO di ordini.
 * Ogni ordine contiene una PILA LIFO di colli.
 * L'ultimo collo caricato e' il primo da scaricare.
 * ========================================================================== */

typedef struct {
    char id[MAX_COD];
    float peso;
} V4_Collo;

typedef struct v4_nodo_collo {
    V4_Collo info;
    struct v4_nodo_collo *next;
} V4_NodoCollo;

typedef V4_NodoCollo *V4_PilaColli;

typedef struct {
    char id[MAX_COD];
    char destinazione[MAX_DEST];
    V4_PilaColli colli;
} V4_Ordine;

typedef struct v4_nodo_ordine {
    V4_Ordine info;
    struct v4_nodo_ordine *next;
} V4_NodoOrdine;

typedef struct {
    V4_NodoOrdine *primo;
    V4_NodoOrdine *ultimo;
} V4_CodaOrdini;


void v4_init_coda(V4_CodaOrdini *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}

V4_NodoOrdine *v4_cerca_ordine(V4_CodaOrdini coda,
                                const char id[]) {
    V4_NodoOrdine *o = coda.primo;

    while (o != NULL) {
        if (strcmp(o->info.id, id) == 0)
            return o;
        o = o->next;
    }

    return NULL;
}

void v4_stampa(V4_CodaOrdini coda) {
    printf("\n===== V4: CODA -> PILA =====\n");

    V4_NodoOrdine *o = coda.primo;

    while (o != NULL) {
        printf("Ordine %s -> %s\n",
               o->info.id,
               o->info.destinazione);

        V4_NodoCollo *c = o->info.colli;
        while (c != NULL) {
            printf("   collo=%s peso=%.2f\n",
                   c->info.id,
                   c->info.peso);
            c = c->next;
        }

        o = o->next;
    }
}


/* QUESITO 4A
 *
 * Inserire un nuovo ordine in fondo alla coda.
 * La pila interna deve iniziare da NULL.
 */
int v4_enqueue_ordine(V4_CodaOrdini *coda,
                      const char id[],
                      const char destinazione[]) {
if (!coda || strlen(id) >= MAX_COD || strlen(destinazione) >= sizeof ((V4_Ordine*)0)->destinazione || v4_cerca_ordine(*coda,id)) return ERRORE;
    V4_NodoOrdine *n = calloc(1,sizeof *n); if (!n) return ERRORE;
    strcpy(n->info.id,id); strcpy(n->info.destinazione,destinazione);
    if (coda->ultimo) coda->ultimo->next = n; else coda->primo = n;
    coda->ultimo = n; return OK;
}


/* QUESITO 4B
 *
 * Cercare l'ordine e fare PUSH di un collo nella sua pila.
 */
int v4_push_collo(V4_CodaOrdini coda,
                  const char id_ordine[],
                  V4_Collo collo) {
V4_NodoOrdine *o = v4_cerca_ordine(coda,id_ordine); if (!o) return ERRORE;
    V4_NodoCollo *n = malloc(sizeof *n); if (!n) return ERRORE;
    n->info = collo; n->next = o->info.colli; o->info.colli = n; return OK;
}


/* QUESITO 4C
 *
 * Fare POP di un collo dalla pila del PRIMO ordine in coda.
 *
 * NON rimuovere l'ordine dalla coda.
 */
int v4_pop_collo_primo_ordine(V4_CodaOrdini *coda,
                              V4_Collo *collo) {
if (!coda || !collo || !coda->primo || !coda->primo->info.colli) return ERRORE;
    V4_NodoCollo *n = coda->primo->info.colli; *collo = n->info;
    coda->primo->info.colli = n->next; free(n); return OK;
}


/* QUESITO 4D
 *
 * Rimuovere il PRIMO ordine dalla coda SOLO se la sua pila colli e' vuota.
 *
 * Se ci sono ancora colli:
 *     restituire ERRORE senza modificare la coda.
 */
int v4_completa_primo_ordine(V4_CodaOrdini *coda) {
if (!coda || !coda->primo || coda->primo->info.colli) return ERRORE;
    V4_NodoOrdine *n = coda->primo; coda->primo = n->next;
    if (!coda->primo) { coda->ultimo = NULL; }
    free(n); return OK;
}


/* QUESITO 4E
 *
 * Deallocare:
 * - tutte le pile di colli;
 * - tutti i nodi della coda ordini.
 */
void v4_dealloca_tutto(V4_CodaOrdini *coda) {
V4_Collo c;
    while (coda->primo) { while (v4_pop_collo_primo_ordine(coda,&c)) { } v4_completa_primo_ordine(coda); }
}


/* ============================================================================
 * VARIANTE 5
 * PILA -> LISTA
 *
 * Scenario:
 * Un editor mantiene una PILA LIFO di snapshot per l'UNDO.
 * Ogni snapshot contiene una LISTA di modifiche effettuate.
 * ========================================================================== */

typedef struct {
    int id;
    char descrizione[MAX_DESC];
} V5_Modifica;

typedef struct v5_nodo_modifica {
    V5_Modifica info;
    struct v5_nodo_modifica *next;
} V5_NodoModifica;

typedef V5_NodoModifica *V5_ListaModifiche;

typedef struct {
    int id_snapshot;
    V5_ListaModifiche modifiche;
} V5_Snapshot;

typedef struct v5_nodo_snapshot {
    V5_Snapshot info;
    struct v5_nodo_snapshot *next;
} V5_NodoSnapshot;

typedef V5_NodoSnapshot *V5_PilaSnapshot;


void v5_stampa(V5_PilaSnapshot pila) {
    printf("\n===== V5: PILA -> LISTA =====\n");

    while (pila != NULL) {
        printf("Snapshot %d\n", pila->info.id_snapshot);

        V5_NodoModifica *m = pila->info.modifiche;
        while (m != NULL) {
            printf("   modifica %d: %s\n",
                   m->info.id,
                   m->info.descrizione);
            m = m->next;
        }

        pila = pila->next;
    }
}


/* QUESITO 5A
 *
 * Push di un nuovo snapshot.
 * La sua lista modifiche deve iniziare vuota.
 */
int v5_push_snapshot(V5_PilaSnapshot *pila,
                     int id_snapshot) {
    /* TODO QUESITO 5A */
    if (!pila) {
        return ERRORE;
    }

    V5_NodoSnapshot *o = malloc(sizeof(V5_NodoSnapshot));
    if (o == NULL) {
        return ERRORE;
    }

    o->info.id_snapshot = id_snapshot;
    o->info.modifiche = NULL ;

    o->next = *pila;
    *pila = o;
    return OK;
}


/* QUESITO 5B
 *
 * Inserire una modifica IN FONDO alla lista delle modifiche
 * dello snapshot in cima alla pila.
 *
 * Se la pila e' vuota:
 *     restituire ERRORE.
 */
int v5_aggiungi_modifica_in_fondo(V5_PilaSnapshot pila,
                                  V5_Modifica modifica) {
if (!pila) return ERRORE;
    V5_NodoModifica **p = &pila->info.modifiche;
    while (*p) p = &(*p)->next;
    *p = malloc(sizeof **p); if (!*p) return ERRORE;
    (*p)->info = modifica; (*p)->next = NULL; return OK;
}


/* QUESITO 5C
 *
 * Rimuovere dalla lista dello snapshot in cima la prima modifica
 * avente l'id indicato.
 */
int v5_rimuovi_modifica(V5_PilaSnapshot pila,
                        int id_modifica) {
if (!pila) return ERRORE;
    V5_NodoModifica **p = &pila->info.modifiche;
    while (*p && (*p)->info.id != id_modifica) p = &(*p)->next;
    if (!*p) return ERRORE;
    V5_NodoModifica *n = *p; *p = n->next; free(n); return OK;
}


/* QUESITO 5D
 *
 * Pop dello snapshot in cima.
 *
 * PRIMA di liberare il nodo snapshot:
 * - deallocare tutta la lista modifiche interna.
 */
int v5_pop_snapshot(V5_PilaSnapshot *pila) {
if (!pila || !*pila) return ERRORE;
    V5_NodoSnapshot *n = *pila;
    while (n->info.modifiche) { V5_NodoModifica *m = n->info.modifiche; n->info.modifiche = m->next; free(m); }
    *pila = n->next; free(n); return OK;
}


/* QUESITO 5E
 *
 * Deallocazione profonda della PILA DI LISTE.
 *
 * Al termine:
 *     *pila == NULL
 */
void v5_dealloca_tutto(V5_PilaSnapshot *pila) {
while (v5_pop_snapshot(pila)) { }
}


/* ============================================================================
 * VARIANTE 6
 * PILA -> CODA
 *
 * Scenario:
 * Una centrale operativa mantiene una PILA di turni recenti.
 * Ogni turno contiene una CODA FIFO di interventi ancora da completare.
 * ========================================================================== */

typedef struct {
    char id[MAX_COD];
    int priorita;
    char descrizione[MAX_DESC];
} V6_Intervento;

typedef struct v6_nodo_intervento {
    V6_Intervento info;
    struct v6_nodo_intervento *next;
} V6_NodoIntervento;

typedef struct {
    V6_NodoIntervento *primo;
    V6_NodoIntervento *ultimo;
} V6_CodaInterventi;

typedef struct {
    int numero_turno;
    char operatore[MAX_NOME];
    V6_CodaInterventi interventi;
} V6_Turno;

typedef struct v6_nodo_turno {
    V6_Turno info;
    struct v6_nodo_turno *next;
} V6_NodoTurno;

typedef V6_NodoTurno *V6_PilaTurni;


void v6_init_coda(V6_CodaInterventi *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}

void v6_stampa(V6_PilaTurni pila) {
    printf("\n===== V6: PILA -> CODA =====\n");

    while (pila != NULL) {
        printf("Turno %d - %s\n",
               pila->info.numero_turno,
               pila->info.operatore);

        V6_NodoIntervento *i = pila->info.interventi.primo;
        while (i != NULL) {
            printf("   %s priorita=%d %s\n",
                   i->info.id,
                   i->info.priorita,
                   i->info.descrizione);
            i = i->next;
        }

        pila = pila->next;
    }
}


/* QUESITO 6A
 *
 * Push di un nuovo turno.
 * La coda interna deve essere inizializzata correttamente.
 */
int v6_push_turno(V6_PilaTurni *pila,
                  int numero_turno,
                  const char operatore[]) {
if (!pila || strlen(operatore) >= MAX_NOME) return ERRORE;
    V6_NodoTurno *n = calloc(1,sizeof *n); if (!n) return ERRORE;
    n->info.numero_turno = numero_turno; strcpy(n->info.operatore,operatore);
    n->next = *pila; *pila = n; return OK;
}


/* QUESITO 6B
 *
 * Inserire un intervento in CODA FIFO nel turno in cima alla pila.
 */
int v6_enqueue_intervento(V6_PilaTurni pila,
                          V6_Intervento intervento) {
if (!pila) return ERRORE;
    V6_NodoIntervento *n = malloc(sizeof *n); if (!n) return ERRORE;
    n->info = intervento; n->next = NULL;
    V6_CodaInterventi *c = &pila->info.interventi;
    if (c->ultimo) c->ultimo->next = n; else c->primo = n;
    c->ultimo = n; return OK;
}


/* QUESITO 6C
 *
 * Estrarre il primo intervento dalla coda del turno in cima.
 */
int v6_dequeue_intervento(V6_PilaTurni pila,
                          V6_Intervento *intervento) {
if (!pila || !intervento || !pila->info.interventi.primo) return ERRORE;
    V6_CodaInterventi *c = &pila->info.interventi;
    V6_NodoIntervento *n = c->primo; *intervento = n->info;
    c->primo = n->next; if (!c->primo) c->ultimo = NULL; free(n); return OK;
}


/* QUESITO 6D
 *
 * Chiudere, cioe' fare POP, del turno in cima SOLO se
 * la sua coda interventi e' vuota.
 *
 * Se la coda non e' vuota:
 *     restituire ERRORE.
 */
int v6_chiudi_turno(V6_PilaTurni *pila) {
if (!pila || !*pila || (*pila)->info.interventi.primo) return ERRORE;
    V6_NodoTurno *n = *pila; *pila = n->next; free(n); return OK;
}


/* QUESITO 6E
 *
 * Deallocazione profonda della PILA DI CODE.
 */
void v6_dealloca_tutto(V6_PilaTurni *pila) {
V6_Intervento i;
    while (*pila) { while (v6_dequeue_intervento(*pila,&i)) { } v6_chiudi_turno(pila); }
}


/* ============================================================================
 * BONUS FINALE - SIMBIOSI CODA <-> PILA
 * ========================================================================== */

/* Tipi semplici per il bonus. */

typedef struct {
    int valore;
} B_Elemento;

typedef struct b_nodo {
    B_Elemento info;
    struct b_nodo *next;
} B_Nodo;

typedef struct {
    B_Nodo *primo;
    B_Nodo *ultimo;
} B_Coda;

typedef B_Nodo *B_Pila;


/* QUESITO BONUS A
 *
 * Spostare TUTTI gli elementi da una coda a una pila:
 * - estrarre dalla testa della coda;
 * - inserire in cima alla pila.
 *
 * Alla fine la coda deve essere vuota.
 *
 * Osservare l'effetto sull'ordine.
 */
int bonus_coda_a_pila(B_Coda *coda, B_Pila *pila) {
if (!coda || !pila) return ERRORE;
    while (coda->primo) { B_Nodo *n = coda->primo; coda->primo = n->next; n->next = *pila; *pila = n; }
    coda->ultimo = NULL; return OK;
}


/* QUESITO BONUS B
 *
 * Spostare TUTTI gli elementi dalla pila alla coda:
 * - pop dalla pila;
 * - enqueue nella coda.
 *
 * Alla fine la pila deve essere NULL.
 */
int bonus_pila_a_coda(B_Pila *pila, B_Coda *coda) {
if (!coda || !pila) return ERRORE;
    while (*pila) { B_Nodo *n = *pila; *pila = n->next; n->next = NULL;
        if (coda->ultimo) coda->ultimo->next = n; else coda->primo = n; coda->ultimo = n;
    } return OK;
}


/* QUESITO BONUS C
 *
 * Usando una PILA di appoggio, invertire l'ordine degli elementi
 * presenti in una CODA collegata.
 *
 * Esempio:
 *     coda iniziale: 10 20 30 40
 *     coda finale:   40 30 20 10
 *
 * Non usare vettori.
 */
int bonus_inverti_coda_con_pila(B_Coda *coda) {
if (!coda) return ERRORE;
    B_Pila p = NULL; bonus_coda_a_pila(coda,&p); return bonus_pila_a_coda(&p,coda);
}


/* ============================================================================
 * MAIN DI TEST
 *
 * Il main NON contiene soluzioni.
 * Serve per controllare velocemente le funzioni dopo averle implementate.
 * Puoi commentare le sezioni che non stai ancora svolgendo.
 * ========================================================================== */

int main(void) {

    printf("============================================================\n");
    printf(" SIMULAZIONE FINALE ADT - LISTE / CODE / PILE\n");
    printf("============================================================\n");
    printf("Il file contiene 6 varianti + 3 bonus.\n");
    printf("Completa le funzioni TODO e aggiungi qui i tuoi test.\n\n");

    /*
     * SUGGERIMENTO DI TEST
     *
     * VARIANTE 1:
     *
     * V1_ListaReparti reparti = NULL;
     *
     * v1_inserisci_reparto_ordinato(&reparti, "R02", "SOFTWARE");
     * v1_inserisci_reparto_ordinato(&reparti, "R01", "RETI");
     *
     * V1_Ticket t1 = {"T001", 4, "Router_non_raggiungibile"};
     * V1_Ticket t2 = {"T002", 2, "Password_scaduta"};
     *
     * V1_NodoReparto *r = v1_cerca_reparto(reparti, "R01");
     * if (r != NULL) {
     *     v1_enqueue_ticket(&r->info.ticket, t1);
     *     v1_enqueue_ticket(&r->info.ticket, t2);
     * }
     *
     * v1_stampa(reparti);
     * v1_dealloca_tutto(&reparti);
     *
     *
     * Ripeti lo stesso principio per le altre varianti.
     */

    return 0;
}


/*
===============================================================================
CHECKLIST PRE-ESAME
===============================================================================

LISTA
-----
[ ] so inserire in testa
[ ] so inserire in fondo
[ ] so inserire ordinatamente
[ ] so cercare un nodo
[ ] so rimuovere testa / mezzo / fondo
[ ] so deallocare tutta la lista
[ ] so deallocare prima l'ADT interno e poi il nodo esterno

CODA
----
[ ] so inizializzare primo e ultimo
[ ] so fare enqueue
[ ] so fare dequeue
[ ] so gestire il caso con un solo elemento
[ ] so mantenere ultimo coerente
[ ] so deallocare tutta la coda

PILA
----
[ ] so fare push
[ ] so fare pop
[ ] so leggere la cima senza modificarla
[ ] so deallocare tutta la pila

STRUTTURE ANNIDATE
------------------
[ ] Lista -> Coda
[ ] Lista -> Pila
[ ] Coda  -> Lista
[ ] Coda  -> Pila
[ ] Pila  -> Lista
[ ] Pila  -> Coda

MEMORIA
-------
[ ] ogni malloc ha un free
[ ] nessun accesso al nodo dopo free
[ ] salvo next PRIMA di free
[ ] dopo deallocazione azzero il puntatore esterno
[ ] in una coda vuota azzero sia primo sia ultimo

===============================================================================
FINE SIMULAZIONE
===============================================================================
*/
