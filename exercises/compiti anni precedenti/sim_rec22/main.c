/******************************************************************************
 * === MODULO 2 ===
 * Appello di Fondamenti di Programmazione - A.A. 2025/26
 * Tempo: 120 minuti
 *
 * Implementare in C un programma per la gestione di un catalogo di libri.
 *
 * Il catalogo e' memorizzato in una struttura composta da un vettore di liste.
 * La posizione del vettore in cui inserire un libro e' calcolata tramite una
 * funzione indice applicata al nome della casa editrice.
 *
 * Nota: la casa editrice NON identifica univocamente un libro. Piu' libri
 * possono avere la stessa casa editrice e quindi trovarsi nella stessa lista
 * del vettore.
 *
 * Ogni lista deve essere mantenuta ordinata alfabeticamente per autore.
 *
 * Ogni libro e' caratterizzato da:
 * - autore       stringa senza spazi
 * - titolo       stringa senza spazi
 * - tipo         stringa senza spazi, es. Romanzo, Saggio, Manuale, Fantasy
 * - casa         stringa senza spazi, casa editrice
 *
 * Il file catalogo.txt contiene un libro per riga, nel formato:
 *
 *      autore titolo tipo casa
 *
 * Esempio:
 *
 *      Calvino Le_Citta_Invisibili Romanzo Einaudi
 *      Asimov Fondazione Fantascienza Mondadori
 *      Eco Il_Nome_Della_Rosa Romanzo Bompiani
 *      Knuth The_Art_of_Computer_Programming Manuale Addison
 *
 * Il programma deve implementare le seguenti funzionalita':
 *
 * 1. Caricare i dati dal file catalogo.txt nel vettore di liste.
 *
 * 2. Inserire ogni libro nella lista corrispondente mantenendo l'ordinamento
 *    crescente per autore.
 *
 * 3. Cercare il primo libro appartenente a una data casa editrice.
 *
 * 4. Estrarre tutti i libri di un certo tipo in una nuova struttura dati scelta
 *    dallo studente. Sono ammesse due possibilita':
 *    - array dinamico di libro_t;
 *    - lista collegata di libri.
 *
 *    La funzione di estrazione deve:
 *    - scorrere tutte le liste del vettore;
 *    - selezionare solo i libri del tipo richiesto;
 *    - produrre una nuova struttura (a scelta tra vettore e lista) contenente i libri selezionati;
 *    - rendere disponibile al chiamante il numero di elementi estratti.
 *
 *    Il tipo di ritorno e la lista dei parametri della funzione di estrazione
 *    devono essere completati dallo studente. Lo studente deve anche adattare
 *    il typedef fittizio STRUTTURA_ESTRATTA alla rappresentazione scelta.
 *
 * 5. Deallocare le strutture allocate dinamicamente.
 *
 ******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_INPUT   "catalogo.txt"

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
typedef void DA_SOSTITUIRE;

/*
 * Tipo fittizio usato nel main per memorizzare il risultato dell'estrazione.
 * Lo studente deve sostituirlo con il tipo coerente con la propria scelta,
 * ad esempio un puntatore (array) oppure una lista collegata.
 */
typedef void *STRUTTURA_ESTRATTA;


/* ============================================================================
 * STRUTTURE DATI
 * ========================================================================== */

typedef struct {
    char autore[STR_LEN];
    char titolo[STR_LEN];
    char tipo[STR_LEN];
    char casa[STR_LEN];
} libro_t;

typedef struct nodo_libro {
    libro_t info;
    struct nodo_libro *next;
} nodo_libro_t;

typedef nodo_libro_t *lista_t;

typedef lista_t catalogo_t[VETT_DIM];


/* ============================================================================
 * FUNZIONI GIA' FORNITE
 * ========================================================================== */

/*
 * Calcola la posizione del vettore associata a una stringa.
 *
 * Parametri in ingresso:
 * - s: stringa da usare per il calcolo della posizione
 *
 * Valore di ritorno:
 * - indice compreso tra 0 e VETT_DIM - 1
 */
int funzione_indice(const char s[]) {
    unsigned int h = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        h = (h * 31u + (unsigned char)s[i]) % VETT_DIM;
    }

    return (int)h;
}


/*
 * Inizializza il catalogo ponendo tutte le liste a NULL.
 *
 * Parametri in ingresso/uscita:
 * - catalogo: vettore di liste da inizializzare
 *
 * Valore di ritorno:
 * - nessuno
 */
void catalogo_init(catalogo_t catalogo) {
    for (int i = 0; i < VETT_DIM; i++) {
        catalogo[i] = NULL;
    }
}


/*
 * Stampa un singolo libro.
 *
 * Parametri in ingresso:
 * - libro: puntatore al libro da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_libro(const libro_t *libro) {
    if (libro == NULL)
        return;

    printf("%s %s %s %s\n", libro->autore, libro->titolo, libro->tipo, libro->casa);
}

/*
 * Stampa una lista collegata di libri.
 *
 * Parametri in ingresso:
 * - lista: lista da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_lista_libri(lista_t lista) {
    nodo_libro_t *p = lista;

    while (p != NULL) {
        stampa_libro(&p->info);
        p = p->next;
    }
}


/*
 * Stampa un array di libri.
 *
 * Parametri in ingresso:
 * - libri: array di libri
 * - dim:   numero di elementi dell'array
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_array_libri(const libro_t libri[], int dim) {
    if (libri == NULL || dim <= 0) {
        printf("Array vuoto.\n");
        return;
    }

    for (int i = 0; i < dim; i++) {
        stampa_libro(&libri[i]);
    }
}


/* Stampa tutte le liste del catalogo senza modificarle.
 *
 * Parametri in ingresso:
 * - catalogo: vettore di liste da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_catalogo(const catalogo_t catalogo) {
    for (int i = 0; i < VETT_DIM; i++) {
        printf("Lista %d:\n", i);
        stampa_lista_libri(catalogo[i]);
    }
}

/*
 * Dealloca tutti i nodi di una lista e pone la testa a NULL.
 *
 * Parametri in ingresso/uscita:
 * - lista: puntatore alla testa della lista da deallocare
 *
 * Valore di ritorno:
 * - nessuno
 */
void dealloca_lista(lista_t *lista) {
    if (lista == NULL) {
        return;
    }

    while (*lista != NULL) {
        nodo_libro_t *tmp = *lista;
        *lista = (*lista)->next;
        free(tmp);
    }
}


/*
 * Dealloca tutte le liste del catalogo.
 *
 * Parametri in ingresso/uscita:
 * - catalogo: vettore di liste da deallocare
 *
 * Valore di ritorno:
 * - nessuno
 */
void dealloca_catalogo(catalogo_t catalogo) {
    for (int i = 0; i < VETT_DIM; i++) {
        dealloca_lista(&catalogo[i]);
    }
}


/* ============================================================================
 * QUESITO 1 - INSERIMENTO ORDINATO
 * ========================================================================== */

/*
 * Inserisce un libro in testa a una lista.
 *
 * Parametri in ingresso/uscita:
 * - lista: puntatore alla testa della lista da modificare
 *
 * Parametri in ingresso:
 * - libro: libro da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int inserisci_testa(lista_t *lista, libro_t libro) {
    if (lista == NULL) {
        return ERRORE_PARAMETRI;
    }

    nodo_libro_t *nuovo = malloc(sizeof(nodo_libro_t));
    if (nuovo == NULL) {
        return ERRORE_MEMORIA;
    }

    nuovo->info = libro;
    nuovo->next = *lista;
    *lista = nuovo;

    return OK;
}

/*
 * Inserisce un libro in una lista mantenendo l'ordine alfabetico crescente
 * sul campo autore.
 *
 * Parametri in ingresso/uscita:
 * - lista: puntatore alla testa della lista da modificare
 *
 * Parametri in ingresso:
 * - libro: libro da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int inserisci_ordinato(lista_t *lista, libro_t libro) {
    // TODO implementazione a cura dello studente
    if (!lista) return ERRORE_DATI;
    nodo_libro_t **cursore = lista;

    while (*cursore && strcmp((*cursore)->info.autore, libro.autore) < 0) {
        cursore = &(*cursore)->next;
    }
    return inserisci_testa(cursore, libro);
}


/*
 * Inserisce un libro nel catalogo.
 *
 * La funzione calcola la posizione del vettore a partire dalla casa editrice e
 * inserisce il libro nella lista corrispondente.
 *
 * Parametri in ingresso/uscita:
 * - catalogo: vettore di liste
 *
 * Parametri in ingresso:
 * - libro: libro da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int catalogo_put(catalogo_t catalogo, libro_t libro) {
    int k = funzione_indice(libro.casa);
    return inserisci_ordinato(&catalogo[k], libro);
}


/* ============================================================================
 * QUESITO 2 - CARICAMENTO DA FILE
 * ========================================================================== */

/*
 * Carica il catalogo dal file indicato e inserisce tutti i libri nel vettore
 * di liste.
 *
 * Il file contiene un libro per riga nel formato:
 *
 *      autore titolo tipo casa
 *
 * Esempio:
 *
 *      Calvino Le_Citta_Invisibili Romanzo Einaudi
 *
 * Parametri in ingresso/uscita:
 * - catalogo: vettore di liste in cui inserire i libri
 *
 * Parametri in ingresso:
 * - nome_file: nome del file da leggere
 *
 * Parametri in uscita:
 * - num_caricati: numero di libri caricati correttamente
 *
 * Valore di ritorno:
 * - OK se il caricamento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int carica_catalogo(catalogo_t catalogo, const char nome_file[], int *num_caricati) {
    // TODO implementazione a cura dello studente

    if (!catalogo || !nome_file || !num_caricati) {
        return ERRORE_PARAMETRI;
    }

    *num_caricati = 0;

    FILE *fp = fopen(nome_file, "r");
    if (!fp) return ERRORE_FILE;

    libro_t libro;

    while (fscanf(fp, "%s %s %s %s", libro.autore, libro.titolo, libro.tipo, libro.casa) == 4) {
        if (catalogo_put(catalogo, libro) == OK) {
            (*num_caricati)++;
        }
    }

    return OK;
}


/* ============================================================================
 * QUESITO 3 - RICERCA PER CASA EDITRICE
 * ========================================================================== */

/*
 * Cerca il primo libro appartenente alla casa editrice specificata.
 *
 * La funzione deve calcolare la posizione del vettore a partire dalla casa
 * editrice e scorrere la lista corrispondente. Poiche' la casa editrice non e'
 * un identificatore univoco, e' sufficiente restituire la prima occorrenza
 * trovata.
 *
 * Parametri in ingresso:
 * - catalogo: vettore di liste
 * - casa:     casa editrice da cercare
 *
 * Valore di ritorno:
 * - puntatore al nodo contenente il primo libro trovato
 * - NULL se non esiste alcun libro della casa editrice indicata
 */
nodo_libro_t *cerca_casa(catalogo_t catalogo, const char casa[]) {
    // TODO implementazione a cura dello studente

    if (!catalogo || !casa) return NULL;

    for (int i = 0; i < VETT_DIM; i++) {
        nodo_libro_t *p = catalogo[i];
        while (p != NULL) {
            if (strcmp(p->info.casa, casa) == 0)
                return p;
            p = p->next;
        }
    }
    return NULL;
}


/* ============================================================================
 * QUESITO 4 - ESTRAZIONE PER TIPO
 * ========================================================================== */

/*
 * Estrarre dal catalogo tutti i libri aventi un certo tipo.
 *
 * La funzione deve produrre una nuova struttura dati scelta dallo studente.
 * Sono ammesse le seguenti rappresentazioni:
 * - array dinamico di libro_t;
 * - lista collegata di libri.
 *
 * Requisiti:
 * - completare il tipo di ritorno sostituendo DA_SOSTITUIRE;
 * - completare la lista dei parametri;
 * - scorrere tutte le liste del vettore;
 * - selezionare i libri con tipo uguale a quello richiesto;
 * - produrre una nuova struttura contenente i libri selezionati;
 * - rendere disponibile al chiamante il numero di elementi estratti;
 * - se non ci sono libri del tipo richiesto, il numero di elementi estratti
 *   deve essere zero.
 */
libro_t *estrai_tipo(catalogo_t catalogo, const char tipo[], int* num_estratti) {
    // TODO implementazione a cura dello studente
    if (!catalogo || !tipo || !num_estratti) {
        return NULL;
    }

    *num_estratti = 0;

    for (int i = 0; i < VETT_DIM; i++) {
        nodo_libro_t *p = catalogo[i];
        while (p != NULL) {
            if (strcmp(p->info.tipo, tipo) == 0) {
                (*num_estratti)++;
            }
            p = p -> next;
        }
    }

    if (*num_estratti == 0) return NULL;
    libro_t* estratti = malloc(sizeof(nodo_libro_t) * (*num_estratti));
    if (!estratti) {
        *num_estratti = 0;
        return NULL;
    }

    for (int i = 0, j = 0; i < VETT_DIM; i++) {
        nodo_libro_t *p = catalogo[i];
        while (p != NULL) {
            if (strcmp(p->info.tipo, tipo) == 0) {
                estratti[j++] = p->info;
            }
            p = p -> next;
        }
    }
    return estratti;
}


/* ============================================================================
 * MAIN
 * ========================================================================== */

/*
 * Stampa il menu e acquisisce la scelta dell'utente.
 *
 * Valore di ritorno:
 * - scelta dell'utente
 */
int menu(void) {
    int scelta;

    printf("\n*** MENU ***\n");
    printf("1. Cerca primo libro di una casa editrice\n");
    printf("2. Stampa i libri di una casa editrice\n");
    printf("3. Estrai libri di un tipo\n");
    printf("4. Stampa ultimi libri estratti\n");

    printf("0. Esci\n");
    printf("Scelta: ");

    if (scanf("%d", &scelta) != 1) {
        return 0;
    }

    return scelta;
}


/*
 * Main del programma.
 *
 * Dopo avere completato il prototipo di estrai_tipo e scelto la struttura dati
 * da usare per l'estrazione, lo studente deve completare la chiamata alla
 * funzione e usare la funzione di stampa coerente con la propria scelta.
 */
int main(void) {
    catalogo_t catalogo;
    STRUTTURA_ESTRATTA estratti = NULL;
    nodo_libro_t *trovato = NULL;
    int num_caricati = 0;
    int num_estratti = 0;
    int scelta;
    char casa[STR_LEN];
    char tipo[STR_LEN];

    catalogo_init(catalogo);

    if (carica_catalogo(catalogo, FILE_INPUT, &num_caricati) != OK) {
        printf("Errore nel caricamento del catalogo.\n");
        dealloca_catalogo(catalogo);
        return 1;
    }

    printf("Libri caricati: %d\n", num_caricati);
    stampa_catalogo(catalogo);

    do {
        scelta = menu();

        switch (scelta) {
            case 1:
                printf("Inserire casa editrice: ");
                scanf("%49s", casa);

                trovato = cerca_casa(catalogo, casa);
                if (trovato != NULL) {
                    stampa_libro(&trovato->info);
                } else {
                    printf("Nessun libro trovato per la casa editrice indicata.\n");
                }
                break;

            case 2:
                printf("Inserire casa editrice: ");
                scanf("%49s", casa);

                trovato = cerca_casa(catalogo, casa);
                if (trovato != NULL) {
                    stampa_lista_libri(catalogo[funzione_indice(casa)]);
                } else {
                    printf("Nessun libro trovato per la casa editrice indicata.\n");
                }
                break;

            case 3:
                printf("Inserire tipo da estrarre: ");
                scanf("%49s", tipo);

                num_estratti = 0;

                /*
                 * Dopo avere completato il prototipo di estrai_tipo,
                 * completare la chiamata alla funzione.
                 */

                // Verificare se l'estrazione è andata a buon fine e stampare,
                //  oppure mostrare un messaggio di errore o di nessun libro trovato.

                // TODO implementazione a cura dello studente
                estratti = estrai_tipo(catalogo, tipo, &num_estratti);
                if (estratti) {
                    printf("Libri estratti: ");
                    stampa_array_libri(estratti, num_estratti);
                } else {
                    printf("Nessuna spedizione estratta.\n");
                }
                printf("Libri estratti: %d\n", num_estratti);

                break;

            case 4:
                /*
                 * Chiamare la funzione di stampa coerente con la struttura
                 * scelta per l'estrazione.
                 *
                 * Esempi possibili:
                 * - stampa_array_libri(estratti, num_estratti);
                 * - stampa_lista_libri(estratti);
                 */
                // TODO implementazione a cura dello studente
                if (estratti == NULL || num_estratti == 0) {
                    printf("Nessuna estrazione precedente disponibile.\n");
                } else {
                    printf("Ultime spedizioni estratte:\n");
                    stampa_array_libri(estratti, num_estratti);
                }
                break;

            case 0:
                printf("Uscita dal programma.\n");
                break;

            default:
                printf("Scelta non valida.\n");
                break;
        }

    } while (scelta != 0);

    /*
     * Se necessario, deallocare la struttura usata per l'estrazione.
     */
    // TODO implementazione a cura dello studente

    if (estratti != NULL) {
        free(estratti);
        estratti = NULL;
    }
    dealloca_catalogo(catalogo);

    return 0;
}