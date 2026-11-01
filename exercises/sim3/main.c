#include "../../common/console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 30

typedef struct {
    char id[MAX_STR];
    char cliente[MAX_STR];
    int priorita;
    int tempo;
} Richiesta;


/* =========================
 * CODA DI RICHIESTE
 * ========================= */

typedef struct nodo_richiesta {
    Richiesta info;
    struct nodo_richiesta *next;
} NodoRichiesta;

typedef struct {
    NodoRichiesta *primo;
    NodoRichiesta *ultimo;
} CodaRichieste;


/* =========================
 * LISTA DEI REPARTI
 * ========================= */

typedef struct nodo_reparto {
    char nome[MAX_STR];
    CodaRichieste richieste;
    struct nodo_reparto *next;
} NodoReparto;

typedef NodoReparto *ListaReparti;


/* =========================
 * PILA DELLE RICHIESTE
 * PROCESSATE
 * ========================= */

typedef struct nodo_cronologia {
    Richiesta info;
    struct nodo_cronologia *next;
} NodoCronologia;

typedef NodoCronologia *PilaCronologia;


/* =========================
 * PROTOTIPI
 * ========================= */

void inizializza_coda(CodaRichieste *coda);
int coda_vuota(CodaRichieste coda);

NodoReparto *cerca_reparto(
    ListaReparti lista,
    const char nome[]
);


NodoReparto *aggiungi_reparto(
    ListaReparti *lista,
    const char nome[]
);

/*
 * Inserisce una richiesta in fondo alla coda.
 *
 * Parametri:
 * - coda: coda da modificare;
 * - richiesta: dato da inserire.
 *
 * Operazioni richieste:
 * 1. allocare un NodoRichiesta;
 * 2. copiare richiesta in info;
 * 3. porre next a NULL;
 * 4. gestire il caso di coda vuota;
 * 5. altrimenti collegare il vecchio ultimo al nuovo nodo;
 * 6. aggiornare ultimo.
 *
 * Restituisce 1 in caso di successo, 0 in caso di errore.
 */
int inserisci_richiesta(
    CodaRichieste *coda,
    Richiesta richiesta
);

/*
 * Carica le richieste dal file.
 *
 * Formato di ogni riga:
 * ID CLIENTE REPARTO PRIORITA TEMPO
 * Esempio:
 * R101 Rossi hardware 4 35
 *
 * Il campo REPARTO deve essere letto in una stringa temporanea,
 * perche' non appartiene alla struct Richiesta.
 *
 * Per ogni riga:
 * 1. leggere i 5 campi con fscanf;
 * 2. cercare il reparto con cerca_reparto;
 * 3. se non esiste, crearlo con aggiungi_reparto;
 * 4. inserire la richiesta nella coda del reparto;
 * 5. incrementare il contatore solo se l'inserimento riesce.
 *
 * Chiudere sempre il file.
 *
 * Restituisce:
 * - numero di richieste caricate;
 * - -1 se il file non puo' essere aperto.
 */
int carica_richieste(
    ListaReparti *lista,
    const char nome_file[]
);

/*
 * Cerca la prima richiesta con priorita >= priorita_minima.
 *
 * Ordine di visita:
 * 1. dal primo reparto all'ultimo;
 * 2. dal primo nodo della coda all'ultimo.
 *
 * La visita non deve modificare le strutture originali.
 *
 * Restituisce l'indirizzo della richiesta trovata,
 * oppure NULL se non esiste.
 */
Richiesta *prima_richiesta_urgente(
    ListaReparti lista,
    int priorita_minima
);

/*
 * Crea un vettore dinamico con tutte le richieste
 * aventi tempo >= tempo_minimo.
 *
 * Operazioni richieste:
 * 1. prima visita: contare gli elementi validi;
 * 2. se il conteggio e' 0, porre *num_richieste = 0 e restituire NULL;
 * 3. allocare un vettore della dimensione esatta;
 * 4. seconda visita: copiare gli elementi validi;
 * 5. salvare la dimensione in *num_richieste.
 *
 * La lista e le code non devono essere modificate.
 */
Richiesta *crea_vettore_richieste_lunghe(
    ListaReparti lista,
    int tempo_minimo,
    int *num_richieste
);

/*
 * Ordina il vettore con Insertion Sort.
 *
 * Criterio:
 * - tempo in ordine decrescente;
 * - a parita' di tempo, priorita in ordine decrescente.
 *
 * L'ordinamento deve essere in-place.
 * Non usare qsort().
 */
void ordina_per_tempo(
    Richiesta vettore[],
    int dimensione
);


int estrai_richiesta(
    CodaRichieste *coda,
    Richiesta *richiesta_estratta
);


int push_cronologia(
    PilaCronologia *pila,
    Richiesta richiesta
);

/*
 * Processa tutte le richieste con priorita >= priorita_minima.
 *
 * Ogni richiesta processata deve essere rimossa dalla propria coda
 * e inserita nella pila cronologia.
 *
 * Le richieste non processate devono rimanere nella coda
 * mantenendo lo stesso ordine relativo.
 *
 * Esempio:
 * R1(p=5) -> R2(p=2) -> R3(p=4), soglia 4
 * coda finale: R2
 * processate: R1 e R3
 *
 * Restituisce il numero totale di richieste processate.
 */
int processa_richieste(
    ListaReparti lista,
    int priorita_minima,
    PilaCronologia *cronologia
);

/*
 * Stampa la pila dalla richiesta piu' recente alla meno recente.
 *
 * Formato:
 * ID CLIENTE priorita=P tempo=T
 *
 * La pila originale non deve essere modificata.
 */
void stampa_cronologia(
    PilaCronologia pila
);


void dealloca_strutture(
    ListaReparti *lista,
    PilaCronologia *cronologia
);


/* =========================
 * FUNZIONI GIA' DISPONIBILI
 * ========================= */

void inizializza_coda(CodaRichieste *coda) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}


int coda_vuota(CodaRichieste coda) {
    return coda.primo == NULL;
}


NodoReparto *cerca_reparto(
    ListaReparti lista,
    const char nome[]
) {
    NodoReparto *corrente = lista;

    while (corrente != NULL) {
        if (strcmp(corrente->nome, nome) == 0)
            return corrente;

        corrente = corrente->next;
    }

    return NULL;
}


/* =========================
 * QUESITO 1
 * Inserimento di un reparto
 * ========================= */

/*
 * Aggiunge un nuovo reparto in testa alla lista.
 *
 * Parametri:
 * - lista: indirizzo del puntatore al primo nodo;
 * - nome: nome del reparto.
 *
 * Operazioni richieste:
 * 1. allocare un nuovo NodoReparto;
 * 2. controllare l'allocazione;
 * 3. copiare il nome;
 * 4. inizializzare la coda del reparto;
 * 5. inserire il nodo in testa;
 * 6. aggiornare *lista.
 *
 * Restituisce:
 * - il puntatore al nuovo reparto;
 * - NULL in caso di errore.
 */

NodoReparto *aggiungi_reparto(
    ListaReparti *lista,
    const char nome[]
) {
    /* TODO: implementare */
    NodoReparto *nuovo = malloc(sizeof(NodoReparto));
    if (nuovo == NULL) return NULL;
    strcpy(nuovo->nome, nome);
    inizializza_coda(&nuovo->richieste);
    nuovo->next = *lista;
    *lista = nuovo;

    return nuovo;
}


/* =========================
 * QUESITO 2
 * Inserimento in coda
 * ========================= */

/*
 * Inserisce una richiesta in fondo alla coda.
 *
 * Parametri:
 * - coda: coda da modificare;
 * - richiesta: dato da inserire.
 *
 * Operazioni richieste:
 * 1. allocare un NodoRichiesta;
 * 2. copiare richiesta in info;
 * 3. porre next a NULL;
 * 4. gestire il caso di coda vuota;
 * 5. altrimenti collegare il vecchio ultimo al nuovo nodo;
 * 6. aggiornare ultimo.
 *
 * Restituisce 1 in caso di successo, 0 in caso di errore.
 */

int inserisci_richiesta(
    CodaRichieste *coda,
    Richiesta richiesta
) {
    /* TODO: implementare */

    NodoRichiesta *nodo = malloc(sizeof(NodoRichiesta));
    if (nodo == NULL) return 0;
    nodo->info = richiesta;
    nodo->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = nodo;
        coda->ultimo = nodo;
    } else {
        coda->ultimo->next = nodo;
        coda->ultimo = nodo;
    }

    return 1;
}


/* =========================
 * QUESITO 3
 * Caricamento da file
 * ========================= */

/*
 * Carica le richieste dal file.
 *
 * Formato di ogni riga:
 * ID CLIENTE REPARTO PRIORITA TEMPO
 * Esempio:
 * R101 Rossi hardware 4 35
 *
 * Il campo REPARTO deve essere letto in una stringa temporanea,
 * perche' non appartiene alla struct Richiesta.
 *
 * Per ogni riga:
 * 1. leggere i 5 campi con fscanf;
 * 2. cercare il reparto con cerca_reparto;
 * 3. se non esiste, crearlo con aggiungi_reparto;
 * 4. inserire la richiesta nella coda del reparto;
 * 5. incrementare il contatore solo se l'inserimento riesce.
 *
 * Chiudere sempre il file.
 *
 * Restituisce:
 * - numero di richieste caricate;
 * - -1 se il file non puo' essere aperto.
 */

int carica_richieste(
    ListaReparti *lista,
    const char nome_file[]
) {
    /* TODO: implementare */
    if (!lista || !nome_file) return -1;
    int count = 0;
    NodoReparto *nodo_reparto;

    FILE *fp = fopen(nome_file, "r");
    if (!fp) return -1;

    Richiesta r;
    char reparto[15];

    while (fscanf(fp, "%s %s %s %d %d", r.id, r.cliente, reparto, &r.priorita, &r.tempo) == 5) {
        nodo_reparto = cerca_reparto(*lista, reparto);
        if (nodo_reparto == NULL) {
            nodo_reparto = aggiungi_reparto(lista, reparto);
            if (nodo_reparto == NULL) {
                fclose(fp);
                return -1;
            }
        }

        if (inserisci_richiesta(&nodo_reparto->richieste, r) == 1) {
            count++;
        }
    }

    fclose(fp);
    return 1;
}


/* =========================
 * QUESITO 4
 * Ricerca prima richiesta urgente
 * ========================= */

/*
 * Cerca la prima richiesta con priorita >= priorita_minima.
 *
 * Ordine di visita:
 * 1. dal primo reparto all'ultimo;
 * 2. dal primo nodo della coda all'ultimo.
 *
 * La visita non deve modificare le strutture originali.
 *
 * Restituisce l'indirizzo della richiesta trovata,
 * oppure NULL se non esiste.
 */

Richiesta *prima_richiesta_urgente(
    ListaReparti lista,
    int priorita_minima
) {
    /* TODO: implementare */

    NodoReparto *nodo_reparto = lista;
    NodoRichiesta *nodo_richiesta;
     while (nodo_reparto != NULL) {
         nodo_richiesta = nodo_reparto->richieste.primo;
         while (nodo_richiesta != NULL) {
             if (nodo_richiesta->info.priorita >= priorita_minima) {
                 return &nodo_richiesta->info;
             }
             nodo_richiesta = nodo_richiesta -> next;
         }
         nodo_reparto = nodo_reparto->next;
     }
    return NULL;
}


/* =========================
 * QUESITO 5
 * Vettore dinamico richieste lunghe
 * ========================= */

/*
 * Crea un vettore dinamico con tutte le richieste
 * aventi tempo >= tempo_minimo.
 *
 * Operazioni richieste:
 * 1. prima visita: contare gli elementi validi;
 * 2. se il conteggio e' 0, porre *num_richieste = 0 e restituire NULL;
 * 3. allocare un vettore della dimensione esatta;
 * 4. seconda visita: copiare gli elementi validi;
 * 5. salvare la dimensione in *num_richieste.
 *
 * La lista e le code non devono essere modificate.
 */

Richiesta *crea_vettore_richieste_lunghe(
    ListaReparti lista,
    int tempo_minimo,
    int *num_richieste
) {
    /* TODO: implementare */
    NodoReparto *nodo_reparto = lista;
    NodoRichiesta *nodo_richiesta;
    *num_richieste = 0;

    while (nodo_reparto != NULL) {
        nodo_richiesta = nodo_reparto->richieste.primo;
        while (nodo_richiesta != NULL) {
            if (nodo_richiesta->info.tempo >= tempo_minimo) {
                (*num_richieste)++;
            }
            nodo_richiesta = nodo_richiesta->next;
        }
        nodo_reparto = nodo_reparto->next;
    }

    if (*num_richieste == 0) return NULL;

    Richiesta *nuovo = malloc(sizeof(Richiesta)*(*num_richieste));
    if (nuovo == NULL) { *num_richieste = 0; return NULL; }

    nodo_reparto = lista;
    int i = 0;
    while (nodo_reparto != NULL) {
        nodo_richiesta = nodo_reparto->richieste.primo;
        while (nodo_richiesta != NULL) {
            if (nodo_richiesta->info.tempo >= tempo_minimo) {
                nuovo[i++] = nodo_richiesta->info;
            }
            nodo_richiesta = nodo_richiesta->next;
        }
        nodo_reparto = nodo_reparto->next;
    }

    return nuovo;
}


/* =========================
 * QUESITO 6
 * Ordinamento con Insertion Sort
 * ========================= */

/*
 * Ordina il vettore con Insertion Sort.
 *
 * Criterio:
 * - tempo in ordine decrescente;
 * - a parita' di tempo, priorita in ordine decrescente.
 *
 * L'ordinamento deve essere in-place.
 * Non usare qsort().
 */

void ordina_per_tempo(
    Richiesta vettore[],
    int dimensione
) {
    if (!vettore || dimensione <= 1) return;
    /* TODO: implementare */
    int i, j;
    Richiesta chiave;
    for (i = 1; i < dimensione; i++) {
        chiave = vettore[i];
        j = i - 1;
        while (j >= 0 && (vettore[j].tempo < chiave.tempo || (vettore[j].tempo == chiave.tempo && vettore[j].priorita < chiave.priorita))) {
            vettore[j + 1] = vettore[j];
            j--;
        }
        vettore[j + 1] = chiave;
    }
}


/* =========================
 * QUESITO 7
 * Estrazione dalla coda
 * ========================= */

/*
 * Estrae il primo elemento della coda.
 *
 * Operazioni richieste:
 * 1. controllare se la coda e' vuota;
 * 2. salvare il primo nodo in un puntatore ausiliario;
 * 3. copiare info in *richiesta_estratta;
 * 4. avanzare primo;
 * 5. se la coda diventa vuota, porre anche ultimo = NULL;
 * 6. liberare il nodo estratto.
 *
 * Restituisce 1 se estrae, 0 se la coda e' vuota.
 */

int estrai_richiesta(
    CodaRichieste *coda,
    Richiesta *richiesta_estratta
) {
    /* TODO: implementare */
    if (!coda || !coda->primo) return 0;
    NodoRichiesta *nodo_richiesta = coda->primo;
    if (nodo_richiesta == NULL) return 0;
    *richiesta_estratta = nodo_richiesta->info;
    coda->primo = coda->primo->next;

    if (coda->primo == NULL) coda->ultimo = NULL;
    free(nodo_richiesta);

    return 1;
}


/* =========================
 * QUESITO 8
 * Processamento delle richieste
 * ========================= */

/*
 * Processa tutte le richieste con priorita >= priorita_minima.
 *
 * Ogni richiesta processata deve essere rimossa dalla propria coda
 * e inserita nella pila cronologia.
 *
 * Le richieste non processate devono rimanere nella coda
 * mantenendo lo stesso ordine relativo.
 *
 * Esempio:
 * R1(p=5) -> R2(p=2) -> R3(p=4), soglia 4
 * coda finale: R2
 * processate: R1 e R3
 *
 * Restituisce il numero totale di richieste processate.
 */

int processa_richieste(
    ListaReparti lista,
    int priorita_minima,
    PilaCronologia *cronologia
) {
    /* TODO: implementare */
    NodoReparto *nodo_reparto = lista;
    Richiesta richiesta;
    int processate = 0;
    while (nodo_reparto != NULL) {
        int numero_elementi = 0;
        NodoRichiesta *nodo_richiesta = nodo_reparto->richieste.primo;
        while (nodo_richiesta != NULL) {
            numero_elementi++;
            nodo_richiesta = nodo_richiesta->next;
        }

        for (int i = 0; i < numero_elementi; i++) {
            estrai_richiesta(&nodo_reparto->richieste, &richiesta);

            if (richiesta.priorita >= priorita_minima) {
                push_cronologia(cronologia, richiesta);
                processate++;
            } else {
                inserisci_richiesta(&nodo_reparto->richieste, richiesta);
            }
        }
        nodo_reparto = nodo_reparto->next;
    }

    return processate;
}

/* =========================
 * QUESITO 9
 * Inserimento nella pila
 * ========================= */
/*
 * Inserisce una richiesta in cima alla pila cronologia.
 *
 * Operazioni richieste:
 * 1. allocare un NodoCronologia;
 * 2. copiare la richiesta;
 * 3. collegare il nuovo nodo alla vecchia cima;
 * 4. aggiornare *pila.
 *
 * Restituisce 1 in caso di successo, 0 in caso di errore.
 */
int push_cronologia(
    PilaCronologia *pila,
    Richiesta richiesta
) {
    /* TODO: implementare */
    NodoCronologia *nuovo = malloc(sizeof(NodoCronologia));
    if (nuovo == NULL) return 0;
    nuovo->info = richiesta;
    nuovo->next = *pila;
    *pila = nuovo;
    return 1;
}

/* =========================
 * QUESITO 10
 * Stampa cronologia
 * ========================= */

void stampa_cronologia(
    PilaCronologia pila
) {
    /* TODO: implementare */
    NodoCronologia *nodo = pila;
    while (nodo != NULL) {
        printf("Id: %s, Cliente: %s, Priorita: %d, Tempo: %d\n", nodo->info.id, nodo->info.cliente, nodo->info.priorita, nodo->info.tempo);
        nodo = nodo->next;
    }
}


/* =========================
 * QUESITO 11
 * Deallocazione completa
 * ========================= */

/*
 * Libera tutta la memoria allocata dinamicamente.
 *
 * Operazioni richieste:
 * 1. per ogni reparto, liberare tutti i nodi della sua coda;
 * 2. liberare tutti i nodi reparto;
 * 3. liberare tutti i nodi della pila;
 * 4. porre *lista = NULL;
 * 5. porre *cronologia = NULL.
 *
 * Al termine non devono rimanere memory leak.
 */

void dealloca_strutture(
    ListaReparti *lista,
    PilaCronologia *cronologia
) {
    /* TODO: implementare */
    NodoReparto *nodo_reparto = *lista;
    NodoReparto *successivo_reparto;
    NodoCronologia *nodo_cronologia = *cronologia;
    NodoCronologia *successivo_cronologia;
    NodoRichiesta *nodo_richiesta;
    NodoRichiesta *successivo_richiesta;

    while (nodo_reparto != NULL) {
        nodo_richiesta = nodo_reparto->richieste.primo;
        while (nodo_richiesta != NULL) {
            successivo_richiesta = nodo_richiesta->next;
            free(nodo_richiesta);
            nodo_richiesta = successivo_richiesta;

        }
        successivo_reparto = nodo_reparto->next;
        free(nodo_reparto);
        nodo_reparto = successivo_reparto;
    }

    while (nodo_cronologia != NULL) {
        successivo_cronologia = nodo_cronologia->next;
        free(nodo_cronologia);
        nodo_cronologia = successivo_cronologia;
    }

    *lista = NULL;
    *cronologia = NULL;

}


/* =========================
 * MAIN
 * ========================= */

int main(void) {

    ListaReparti reparti = NULL;
    PilaCronologia cronologia = NULL;

    Richiesta *vettore = NULL;
    Richiesta *trovata;

    int dimensione = 0;
    int scelta;
    int soglia;
    int caricate;

    do {

        printf(
            "\n\n"
            "===== CENTRO ASSISTENZA =====\n"
            "1. Carica richieste da file\n"
            "2. Cerca prima richiesta urgente\n"
            "3. Crea vettore richieste lunghe\n"
            "4. Processa richieste\n"
            "5. Stampa cronologia\n"
            "0. Esci\n"
            "\nScelta: "
        );

        lab_scanf("%d", &scelta);

        switch (scelta) {

        case 1:

            caricate = carica_richieste(
                &reparti,
                "richieste.txt"
            );

            if (caricate == -1)
                printf("Errore apertura file\n");
            else
                printf("Richieste caricate: %d\n", caricate);

            break;


        case 2:

            printf("Inserire priorita minima: ");
            lab_scanf("%d", &soglia);

            trovata = prima_richiesta_urgente(
                reparti,
                soglia
            );

            if (trovata == NULL) {
                printf("Nessuna richiesta trovata\n");
            } else {
                printf(
                    "%s %s priorita=%d tempo=%d\n",
                    trovata->id,
                    trovata->cliente,
                    trovata->priorita,
                    trovata->tempo
                );
            }

            break;


        case 3:

            printf("Inserire tempo minimo: ");
            lab_scanf("%d", &soglia);

            free(vettore);

            vettore = crea_vettore_richieste_lunghe(
                reparti,
                soglia,
                &dimensione
            );

            ordina_per_tempo(
                vettore,
                dimensione
            );

            for (int i = 0; i < dimensione; i++) {

                printf(
                    "%s %s %d %d\n",
                    vettore[i].id,
                    vettore[i].cliente,
                    vettore[i].priorita,
                    vettore[i].tempo
                );
            }

            break;


        case 4: {

            int processate;

            printf("Inserire priorita minima: ");
            lab_scanf("%d", &soglia);

            processate = processa_richieste(
                reparti,
                soglia,
                &cronologia
            );

            printf(
                "Richieste processate: %d\n",
                processate
            );

            break;
        }


        case 5:

            stampa_cronologia(
                cronologia
            );

            break;


        case 0:

            printf("Chiusura programma\n");

            break;


        default:

            printf("Scelta non valida\n");
        }

    } while (scelta != 0);


    free(vettore);

    dealloca_strutture(
        &reparti,
        &cronologia
    );

    return 0;
}
