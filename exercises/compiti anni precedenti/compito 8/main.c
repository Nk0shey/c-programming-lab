#include "../../../common/console.h"
/***************************************************************************************************************
* ==== MODULO 2 =====
*
* Implementare un programma ANSI C per la gestione di un pronto soccorso.
*
* In un file di testo ("pronto_soccorso.txt") è memorizzato l'elenco dei pazienti che arrivano al pronto soccorso, con i loro
* rispettivi dati.
*
* Ogni paziente è caratterizzato da:* - nome
* - cognome,
* - età,
* - codice priorità (0:rosso, 1:giallo, 2:verde, 3:bianco),
* - uno stato (0:attesa, 1:dimesso, 2:riceverato),
* - un reparto (se lo stato è diverso da ricoverato, il valore di reparto è uguale allo stato).
*
* Scrivere un programma che esegue le seguenti operazioni:
*
* 2a. Aggiungere un paziente alla coda dei pazienti in base alla priorità.
*
* 2b. Caricare i dati dei pazienti presenti nel file e memorizzarli in una lista di code.
*     Ogni nodo della lista rappresenta un codice priorità e contiene una coda di pazienti.
*     La lista è ordinata per priorità decrescente (rosso: priorità più alta; bianco: priorità più bassa).
*
* 2c. Gestire il trattamento del prossimo paziente in attesa in base alla priorità. Il suo stato deve essere aggiornato a 'dimesso' o 'ricoverato'.
*     Se il paziente è ricoverato, deve essere assegnato ad un reparto specifico.
*
* 2d. Dato un codice priorità, restituire le informazioni di tutti i pazienti dimessi tramite un vettore.
*
* I pazienti ricoverati vengono assegnati ad una stanza. Il numero di stanza è determinato in base al cognome e al reparto,
* tramite una funzione fornita. Ogni stanza può contenere un solo paziente.
*
* 2e. Inserire tutti i pazienti ricoverati in un albero binario ordinato per numero di stanza. Se la stanza calcolata è già occupata,
*     provare con la successiva fino a trovarne una libera (Si suppone che i numeri di stanza vadano da 0 a N).
*
* 2f. Dato il nome di un reparto, restituire la lista dei pazienti ricoverati in quel reparto.
*
* TEMPO: 120 minuti.
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "pronto_soccorso.txt"
#define MAX_STR_LEN 30
#define NUM_CODE_PRIORITA 4 // una coda per ogni codice priorità

typedef enum {
    ATTESA,
    DIMESSO,
    RICOVERATO,
}StatoPaziente;

const char* statoToString(StatoPaziente s) {
    switch(s) {
    case ATTESA: return "ATTESA";
    case DIMESSO: return "DIMESSO";
    case RICOVERATO: return "RICOVERATO";
    default:
        return "ERRORE";
    }
}

typedef enum {
    ROSSO,
    GIALLO,
    VERDE,
    BIANCO,
}CodicePriorita;

const char* prioritaToString(CodicePriorita p) {
    switch (p){
    case ROSSO: return "ROSSO";
    case GIALLO: return "GIALLO";
    case VERDE: return "VERDE";
    case BIANCO: return "BIANCO";
    default:
        return "ERRORE";
    }
}

/* Struttura dati paziente */
typedef struct {
    char nome[MAX_STR_LEN];
    char cognome[MAX_STR_LEN];
    unsigned eta;
    StatoPaziente stato;
    char reparto[MAX_STR_LEN];
}TPaziente;

/* Struttura dati nodo coda pazienti */
typedef struct nodo_coda_paziente{
    TPaziente info;
    struct nodo_coda_paziente* next;
}NodoCodaPazienti;

typedef struct {
    NodoCodaPazienti* primo;
    NodoCodaPazienti* ultimo;
}CodaPazienti;

typedef NodoCodaPazienti* ListaPazientiReparto;

/* Struttura dati nodo e lista code */
typedef struct nodo_lista_code {
    CodicePriorita priorita;
    CodaPazienti pazienti;
    struct nodo_lista_code* next;
}NodoListaCode;

typedef NodoListaCode* ListaCodePazienti;

typedef struct nodo_albero_stanze {
    int stanza;
    TPaziente paziente;
    struct nodo_albero_stanze* dx;
    struct nodo_albero_stanze* sx;
}NodoAlbero;

typedef NodoAlbero* Albero;



/* Inserisce una nuova coda nella lista di code ordinate per priorità.
*
*  Parametri in ingresso:
*  - lista: puntatore alla lista di code
*  - priorita: priorità della coda da aggiungere
*
*  Valore di ritorno:
*  - 1 se la lista è stata creata, 0 altrimenti
*/
int aggiungi_nodo_lista_code(ListaCodePazienti* lista, CodicePriorita priorita) {
    if ((*lista == NULL) || (*lista)->priorita > priorita ) {
        NodoListaCode* nodo = (NodoListaCode*)malloc(sizeof(NodoListaCode));
        if (nodo == NULL) return 0;

        nodo->priorita = priorita;
        nodo->pazienti.primo = NULL;
        nodo->pazienti.ultimo = NULL;
        nodo->next = *lista;
        *lista = nodo;
        return 1;
    }
    return aggiungi_nodo_lista_code(&(*lista)->next, priorita);
}

/*
* Cerca un nodo della lista delle code in base alla priorità
*
* Parametri in ingresso:
* - lista: lista di code dei pazienti
* - priorita: priorità della coda da cercare
*
* Valore di ritorno:
* - Puntatore al nodo della coda corrispondente, NULL altrimenti
*/
NodoListaCode* cerca_coda_priorita(ListaCodePazienti lista_code, CodicePriorita priorita) {
    if (lista_code == NULL) return NULL;
    if (lista_code->priorita == priorita) return lista_code;
    return cerca_coda_priorita(lista_code->next, priorita);
}


/*
* Quesito 2a.
* Aggiunge un paziente alla coda dei pazienti in base alla priorità.
*
* Parametri in ingresso:
* - lista_pazienti: lista di code dei pazienti
* - paziente: paziente da aggiungere
* - priorita: codice priorita del paziente
*
* Valore di ritorno:
* - 1 se l'aggiunta è andata a buon fine, 0 altrimenti
*/
int aggiungi_paziente(ListaCodePazienti *lista_code, TPaziente paziente, CodicePriorita priorita){
    //TODO da implementare a cura dello studente
    NodoListaCode *nodo_priorita;
    NodoCodaPazienti *nuovo;

    nodo_priorita = cerca_coda_priorita(*lista_code, priorita);

    if (nodo_priorita == NULL) {
        if (!aggiungi_nodo_lista_code(lista_code, priorita)) return 0;

        nodo_priorita = cerca_coda_priorita(*lista_code, priorita);
        if (nodo_priorita == NULL) {
            return 0;
        }
    };

    nuovo = (NodoCodaPazienti*)malloc(sizeof(NodoCodaPazienti));
    if (nuovo == NULL) return 0;

    nuovo->info = paziente;
    nuovo->next = NULL;

    if (nodo_priorita->pazienti.primo == NULL) {
        nodo_priorita->pazienti.primo = nuovo;
        nodo_priorita->pazienti.ultimo = nuovo;
    } else {
        nodo_priorita->pazienti.ultimo->next = nuovo;
        nodo_priorita->pazienti.ultimo = nuovo;
    }
    return 1;
}


/*
* Quesito 2b.
* Carica i dati dal file e li inserisce nella lista di code di pazienti.
*
* Il File ha il seguente formato:
* Cognome nome eta priorita stato reparto
*
* Parametri in ingresso:
* - nome_file: nome del file contenente i dati dei pazienti
*
* Parametri in uscita:
* - lista_code: puntatore alla lista delle code
*
* Valore di ritorno:
* - numero di pazienti caricati
*/
int carica_pazienti(const char* nome_file, ListaCodePazienti* lista_code) {
    TPaziente paziente;
    int priorita;
    int stato;
    int n_pazienti = 0;

    FILE* fp = fopen(nome_file, "r");
    if (fp == NULL) return 0;
    // TODO: da implementare a cura dello studente

    while (fscanf(fp,"%s %s %u %d %d %s", paziente.cognome, paziente.nome, &paziente.eta, &priorita, &stato, paziente.reparto) == 6) {
        if (priorita < ROSSO || priorita > BIANCO) {
            continue;
        }

        if (stato < ATTESA || stato > RICOVERATO) {
            continue;
        }

        paziente.stato = (StatoPaziente)stato;
        if (aggiungi_paziente(lista_code, paziente, priorita)) {
            n_pazienti++;
        }
    }
    fclose(fp);
    return n_pazienti;
}


/*
* Quesito 2c.
 * Restituisce il prossimo paziente da visitare in base alla priorità e all'ordine della coda.
 *
 * Parametri in ingresso:
 * - lista_code: lista delle code dei pazienti
 *
 * Valore di ritorno:
 * - Puntatore al paziente da visitare, se presente; NULL se non ci sono pazienti in attesa
 */
TPaziente* prossimo_paziente(ListaCodePazienti lista_code) {
    NodoListaCode* nodo_coda = lista_code;
    NodoCodaPazienti* nodo_paziente = NULL;

    //TODO da implementare a cura dello studente

   while (nodo_coda != NULL) {
       nodo_paziente = nodo_coda->pazienti.primo;
       while (nodo_paziente != NULL) {
           if (nodo_paziente->info.stato == ATTESA) {
               return &(nodo_paziente->info);
           }
           nodo_paziente = nodo_paziente->next;
       }
        nodo_coda = nodo_coda->next;
   }
    return NULL;
}


/*
* Quesito 2d.
*
* Restituisce un vettore contenente i pazienti dimessi per una data priorità.
*
* Parametri in ingresso:
* - lista_coda: lista di code dei pazienti.
* - priorita: codice priorita
*
* Parametri in uscita:
* - dim: dimensione del vettore
*
* Valore di ritorno:
* - vettore dei pazienti dimessi
*/
TPaziente* pazienti_dimessi(ListaCodePazienti lista_code, int priorita, int* dim) {
    //TODO da implementare a cura dello studente

    NodoListaCode* nodo_priorita;
    NodoCodaPazienti* corrente;
    TPaziente *vettore;
    int i = 0;
    int count = 0;
    *dim = 0;

    nodo_priorita = cerca_coda_priorita(lista_code, priorita);
    if (nodo_priorita == NULL) {
        return NULL;
    }

    corrente = nodo_priorita->pazienti.primo;
    while (corrente != NULL) {
        if (corrente->info.stato == DIMESSO) {
            count++;
        }
        corrente = corrente->next;
    }

    if (count == 0) {
        return NULL;
    }

    vettore = (TPaziente*)malloc(sizeof(TPaziente) * count);
    if (vettore == NULL) {
        return NULL;
    }

    corrente = nodo_priorita->pazienti.primo;
    while (corrente != NULL) {
        if (corrente->info.stato == DIMESSO) {
            vettore[i] = corrente->info;
            i++;
        }
        corrente = corrente->next;
    }
    *dim = count;
    return vettore;
}



/*
* Funzione calcolo numero stanza
*
* Parametri in ingresso:
* - cognome: cognome paziente
* - reparto: reparto
*
* Valore di ritorno:
* - numero della stanza
*/
int calcola_stanza_paziente(const char* cognome, const char* reparto) {
    int somma = 0;
    for (int i = 0; cognome[i] != '\0'; i++)
        somma += cognome[i];
    for (int i = 0; reparto[i] != '\0'; i++)
        somma += reparto[i];
    return somma % 17;
}

/*
* Funzione ricerca nodo albero dato un numero di stanza
*
* Parametri in ingrsso:
* - n_albero: puntatore nodo dell'albero
* - stanza: stanza da ricercare
*
* Valore di ritorno:
* - puntatore al nodo dell'albero se presente, NULL altrimenti
*/
NodoAlbero* cerca_nodo_albero(NodoAlbero* n_albero, int stanza) {

    if ((n_albero == NULL) || n_albero->stanza == stanza)
        return n_albero;

    if (n_albero->stanza < stanza)
        return cerca_nodo_albero(n_albero->dx, stanza);
    else
        return cerca_nodo_albero(n_albero->sx, stanza);
}


/*
* Quesito 2e.
* Inserisce un paziente nell'albero binario ordinato per numero di stanza.
*
* Parametri in ingresso:
* - p_albero: puntatore all'albero
* - paziente: paziente da associare al nodo.
* - stanza: numero della stanza associato al paziente.
*
* Valore di ritorno:
* - void
*
*/
void inserisci_nodo_albero(Albero* p_albero, TPaziente paziente, int stanza) {
/* The supplied hash maps to 0..16. Probe all 17 rooms once. */
    Albero root = *p_albero;
    int room = ((stanza % 17) + 17) % 17;
    int attempts = 0;
    while (attempts < 17 && cerca_nodo_albero(root, room)) { room = (room + 1) % 17; ++attempts; }
    if (attempts == 17) { fputs("Nessuna stanza disponibile\n", stderr); return; }
    while (*p_albero) p_albero = room < (*p_albero)->stanza ? &(*p_albero)->sx : &(*p_albero)->dx;
    *p_albero = malloc(sizeof **p_albero); if (!*p_albero) return;
    (*p_albero)->stanza = room; (*p_albero)->paziente = paziente;
    (*p_albero)->sx = (*p_albero)->dx = NULL;
}

/*
* Crea un albero binario ordinato per numero di stanza a partire dai pazienti ricoverati.
*
* Parametri in ingresso:
* - lista_code: lista delle code dei pazienti
* - p_albero: puntatore alla radice dell'albero.
*
* Valore di ritorno:
* - void
*/
void crea_albero(ListaCodePazienti lista_code, Albero* p_albero) {
for (; lista_code; lista_code=lista_code->next) for (NodoCodaPazienti *p=lista_code->pazienti.primo; p; p=p->next)
        if (p->info.stato==RICOVERATO) inserisci_nodo_albero(p_albero,p->info,calcola_stanza_paziente(p->info.cognome,p->info.reparto));
}


/*
 * Inserisce un paziente in testa alla lista di pazienti di un reparto.
 *
 * Parametri in ingresso:
 * - p_lista: puntatore alla lista dei pazienti del reparto.
 * - paziente: paziente da aggiungere.
 *
 * Valore di ritorno:
 * - 1 se l'inserimento è andato a buon fine, 0 altrimenti.
 */
int inserisci_nodo_testa(ListaPazientiReparto* p_lista, TPaziente paziente) {
    NodoCodaPazienti* nodo = (NodoCodaPazienti*)malloc(sizeof(NodoCodaPazienti));
    if (nodo == NULL) return 0;
    nodo->info = paziente;
    nodo->next = *p_lista;
    *p_lista = nodo;
    return 1;
}


/*
* Crea una lista con i pazienti ricoverati in un determinato reparto.
*
* Parametri in ingresso:
* - albero: albero binario delle stanze.
* - l_pazienti_reparto: puntatore alla lista dei pazienti del reparto.
* - reparto: nome del reparto da cercare.
*
* Valore di ritorno:
* - void.
*
*/
void pazienti_reparto(Albero albero, ListaPazientiReparto* l_pazienti_reparto, const char* reparto) {
if (!albero) return;
    pazienti_reparto(albero->sx,l_pazienti_reparto,reparto);
    if (!strcmp(albero->paziente.reparto,reparto)) inserisci_nodo_testa(l_pazienti_reparto,albero->paziente);
    pazienti_reparto(albero->dx,l_pazienti_reparto,reparto);
}

/*
* Stampa a video i dati di un paziente
*
* Parametri in ingresso:
* - p: informazioni del paziente da stampare
*
* Valore di ritorno:
* - void.
*
*/
void stampa_paziente(TPaziente p) {
    printf("\n%s %s, stato: %s, reparto: %s", p.cognome, p.nome, statoToString(p.stato), p.reparto);
}

void stampa_liste_code(ListaCodePazienti lista_pazienti) {
    NodoListaCode* ncd = lista_pazienti;
    while (ncd != NULL) {
        NodoCodaPazienti* ncp = ncd->pazienti.primo;
        printf("\n >> codice: %s", prioritaToString(ncd->priorita));
        while (ncp != NULL) {
            stampa_paziente(ncp->info);
            ncp = ncp->next;
        }
        ncd = ncd->next;
    }
}
void libera_pazienti(ListaPazientiReparto *p) {
    while (*p) { NodoCodaPazienti *n = *p; *p = n->next; free(n); }
}
void libera_code_pazienti(ListaCodePazienti *p) {
    while (*p) { NodoListaCode *n = *p; *p = n->next; libera_pazienti(&n->pazienti.primo); free(n); }
}
void libera_stanze(Albero *a) {
    if (!*a) return;
    libera_stanze(&(*a)->sx); libera_stanze(&(*a)->dx); free(*a); *a = NULL;
}
int main() {

    int num_pazienti = 0;
    int nuovo_stato = 0;
    int priorita = 0;
    int dim = 0;
    int scelta;
    char reparto[MAX_STR_LEN];

    TPaziente* paziente = NULL;
    TPaziente* vett_pazienti = NULL;

    ListaCodePazienti lista_pazienti = NULL;
    Albero albero_ricoveri = NULL;
    for (int i = 0; i < NUM_CODE_PRIORITA; i++)
        aggiungi_nodo_lista_code(&lista_pazienti, i);

    do {
        printf("\n\n *** MENU ***"
            "\n 1. Carica da file"
            "\n 2. Processa prossimo paziente"
            "\n 3. Stampa pazienti dimessi data priorita"
            "\n 4. Crea Albero Binario"
            "\n 5. Cerca pazienti dato reparto"
            "\n 0. Esci"
            "\n\nScelta: ");
        lab_scanf("%d", &scelta);

        switch (scelta) {
        case 1:
            num_pazienti = carica_pazienti(NOME_FILE, &lista_pazienti);
            printf("\nTotale pazienti caricati: %d\n", num_pazienti);

            stampa_liste_code(lista_pazienti);
            break;
        case 2:
            paziente = prossimo_paziente(lista_pazienti);
            // TODO da completare a cura dello studente
            /*
            * Gestire il trattamento del prossimo paziente in attesa in base alla priorità. Il suo stato deve essere aggiornato a 'dimesso' o 'ricoverato'.
            * Se il paziente è ricoverato, deve essere assegnato ad un reparto specifico.
            */
            if (paziente == NULL) {
                printf("\nErrore\n");
            } else {
                printf("Prox paziente da processare: ");
                stampa_paziente(*paziente);

                do {
                    printf("Inserire il nuovo stato 1 o 2: ");
                    lab_scanf("%d", &nuovo_stato);
                } while (nuovo_stato != DIMESSO && nuovo_stato != RICOVERATO);

                paziente->stato = (StatoPaziente)nuovo_stato;

                if (paziente->stato == DIMESSO) {
                    strcpy(paziente->reparto, "dimesso");
                } else {
                    printf("\nInserisci reparto: ");
                    lab_scanf("%29s", paziente->reparto);
                }
            }
            stampa_liste_code(lista_pazienti);
            break;
        case 3:
            do {
                printf("\nInserisci codice priorita: ");
                lab_scanf("%d", &priorita);
            } while (priorita < ROSSO || priorita > BIANCO);

            vett_pazienti = pazienti_dimessi(lista_pazienti, priorita, &dim);
            for (int i = 0; i < dim; i++)
                stampa_paziente(vett_pazienti[i]);

            free(vett_pazienti);
            dim = 0;
            break;

        case 4:
            libera_stanze(&albero_ricoveri);
            crea_albero(lista_pazienti, &albero_ricoveri);
            break;

        case 5:
            printf("\nInserisci nome reparto: ");
            lab_scanf("%29s", reparto);

            ListaPazientiReparto l_reparto = NULL;
            pazienti_reparto(albero_ricoveri, &l_reparto, reparto);

            NodoCodaPazienti* nodo = l_reparto;
            while (nodo != NULL) {
                stampa_paziente(nodo->info);
                nodo = nodo->next;
            }
            libera_pazienti(&l_reparto);
            break;

        case 0:
            libera_stanze(&albero_ricoveri);
            libera_code_pazienti(&lista_pazienti);
            return 0;

        default:
            printf("\nScelta non valida");
        }

    } while (scelta);
}