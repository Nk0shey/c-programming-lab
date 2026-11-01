/******************************************************************************
 * === MODULO 2 ===
 * Appello di Fondamenti di Programmazione - A.A. 2025/26
 * Tempo: 120 minuti
 *
 * Implementare in C un programma per la gestione delle spedizioni di un
 * magazzino.
 *
 * Le spedizioni sono memorizzate in una struttura composta da un vettore di
 * code. La posizione del vettore in cui inserire una spedizione e' calcolata
 * tramite una funzione indice applicata al nome del corriere.
 *
 * Nota: il corriere NON identifica univocamente una spedizione. Piu' spedizioni
 * possono essere affidate allo stesso corriere e quindi trovarsi nella stessa
 * coda del vettore.
 *
 * Ogni posizione del vettore contiene una coda FIFO di spedizioni:
 * - le nuove spedizioni vengono inserite in fondo alla coda;
 * - le spedizioni nella stessa coda sono quindi memorizzate in ordine di arrivo
 *   nel file di input.
 *
 * Ogni spedizione e' caratterizzata da:
 * - codice        stringa senza spazi
 * - destinatario  stringa senza spazi
 * - zona          stringa senza spazi, es. Centro, Nord, Sud, Isole
 * - corriere      stringa senza spazi
 * - peso          valore reale
 *
 * Il file spedizioni.txt contiene una spedizione per riga, nel formato:
 *
 *      codice destinatario zona corriere peso
 *
 * Esempio:
 *
 *      SP001 Rossi Centro DHL 2.50
 *      SP014 Verdi Nord GLS 1.20
 *      SP003 Bianchi Centro SDA 4.00
 *      SP021 Neri Sud DHL 0.80
 *
 * Il programma deve implementare le seguenti funzionalita':
 *
 * 1. Caricare i dati dal file spedizioni.txt nel vettore di code.
 *
 * 2. Inserire ogni spedizione in fondo alla coda corrispondente, preservando
 *    l'ordine di arrivo delle spedizioni associate alla stessa posizione del
 *    vettore.
 *
 * 3. Cercare la prima spedizione associata a un dato corriere.
 *
 * 4. Estrarre tutte le spedizioni con peso maggiore o uguale a una soglia in
 *    una nuova struttura dati scelta dallo studente. Sono ammesse tre
 *    possibilita':
 *    - array dinamico di spedizione_t;
 *    - lista collegata di spedizioni;
 *    - coda FIFO di spedizioni.
 *
 *    La funzione di estrazione deve:
 *    - scorrere tutte le code del vettore;
 *    - selezionare solo le spedizioni con peso maggiore o uguale alla soglia;
 *    - produrre una nuova struttura contenente le spedizioni selezionate;
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

#define FILE_INPUT   "spedizioni.txt"

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
 * ad esempio un puntatore (array), una lista collegata oppure una coda.
 */
typedef void *STRUTTURA_ESTRATTA;


/* ============================================================================
 * STRUTTURE DATI
 * ========================================================================== */

typedef struct {
    char codice[STR_LEN];
    char destinatario[STR_LEN];
    char zona[STR_LEN];
    char corriere[STR_LEN];
    float peso;
} spedizione_t;

typedef struct nodo_spedizione {
    spedizione_t info;
    struct nodo_spedizione *next;
} nodo_spedizione_t;

typedef nodo_spedizione_t *lista_t;

/*
 * Coda FIFO di spedizioni.
 */
typedef struct {
    nodo_spedizione_t *primo;
    nodo_spedizione_t *ultimo;
} coda_t;

typedef coda_t magazzino_t[VETT_DIM];


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
 * Inizializza una coda ponendo entrambi i puntatori a NULL.
 *
 * Parametri in ingresso/uscita:
 * - coda: puntatore alla coda da inizializzare
 *
 * Valore di ritorno:
 * - nessuno
 */
void coda_init(coda_t *coda) {
    if (coda == NULL)
        return;

    coda->primo = NULL;
    coda->ultimo = NULL;
}


/*
 * Inizializza il magazzino inizializzando tutte le code del vettore.
 *
 * Parametri in ingresso/uscita:
 * - magazzino: vettore di code da inizializzare
 *
 * Valore di ritorno:
 * - nessuno
 */
void magazzino_init(magazzino_t magazzino) {
    for (int i = 0; i < VETT_DIM; i++) {
        coda_init(&magazzino[i]);
    }
}


/*
 * Stampa una singola spedizione.
 *
 * Parametri in ingresso:
 * - spedizione: puntatore alla spedizione da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_spedizione(const spedizione_t *s) {
    if (s == NULL)
        return;

    printf("%s %s %s %s %.2f\n", s->codice, s->destinatario, s->zona, s->corriere, s->peso);
}


/*
 * Stampa una lista collegata di spedizioni.
 *
 * Parametri in ingresso:
 * - lista: lista da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_lista_spedizioni(lista_t lista) {
    nodo_spedizione_t *p = lista;

    while (p != NULL) {
        stampa_spedizione(&p->info);
        p = p->next;
    }
}


/*
 * Stampa una coda di spedizioni senza modificarla.
 *
 * Parametri in ingresso:
 * - coda: puntatore alla coda da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_coda_spedizioni(const coda_t *coda) {
    if (coda == NULL) {
        printf("Coda vuota.\n");
        return;
    }

    stampa_lista_spedizioni(coda->primo);
}


/*
 * Stampa un array di spedizioni.
 *
 * Parametri in ingresso:
 * - spedizioni: array di spedizioni
 * - dim:        numero di elementi dell'array
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_array_spedizioni(const spedizione_t spedizioni[], int dim) {
    if (spedizioni == NULL || dim <= 0) {
        printf("Array vuoto.\n");
        return;
    }

    for (int i = 0; i < dim; i++) {
        stampa_spedizione(&spedizioni[i]);
    }
}

/* Stampa tutte le code del magazzino senza modificarle.
 *
 * Parametri in ingresso:
 * - magazzino: vettore di code da stampare
 *
 * Valore di ritorno:
 * - nessuno
 */
void stampa_magazzino(const magazzino_t magazzino) {
    for (int i = 0; i < VETT_DIM; i++) {
        printf("Coda %d:\n", i);
        stampa_coda_spedizioni(&magazzino[i]);
    }
}

/*
 * Dealloca tutti i nodi di una coda.
 * Al termine, la coda risulta vuota.
 *
 * Parametri in ingresso/uscita:
 * - coda: puntatore alla coda da deallocare
 *
 * Valore di ritorno:
 * - nessuno
 */
void dealloca_coda(coda_t *coda) {
    if (coda == NULL) {
        return;
    }

    while (coda->primo != NULL) {
        nodo_spedizione_t *tmp = coda->primo;
        coda->primo = coda->primo->next;
        free(tmp);
    }

    coda->ultimo = NULL;
}


/*
 * Dealloca tutte le code del magazzino.
 *
 * Parametri in ingresso/uscita:
 * - magazzino: vettore di code da deallocare
 *
 * Valore di ritorno:
 * - nessuno
 */
void dealloca_magazzino(magazzino_t magazzino) {
    for (int i = 0; i < VETT_DIM; i++) {
        dealloca_coda(&magazzino[i]);
    }
}


/* ============================================================================
 * QUESITO 1 - INSERIMENTO IN CODA
 * ========================================================================== */

/*
 * Inserisce una spedizione in fondo a una coda FIFO.
 *
 * La funzione deve allocare un nuovo nodo, copiare al suo interno la spedizione
 * ricevuta come parametro e collegarlo in fondo alla coda.
 *
 * Parametri in ingresso/uscita:
 * - coda: puntatore alla coda da modificare
 *
 * Parametri in ingresso:
 * - spedizione: spedizione da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int accoda_spedizione(coda_t *coda, spedizione_t spedizione) {
    // TODO implementazione a cura dello studente
    if (!coda) {
        return ERRORE_PARAMETRI;
    }

    nodo_spedizione_t *nuovo = malloc(sizeof(nodo_spedizione_t));
    nuovo->info = spedizione;
    nuovo->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = nuovo;
    }
    if (coda->ultimo) {
        coda->ultimo->next = nuovo;
    }
    coda->ultimo = nuovo;

    return OK;
}


/*
 * Inserisce una spedizione nel magazzino.
 *
 * La funzione calcola la posizione del vettore a partire dal corriere e
 * inserisce la spedizione in fondo alla coda corrispondente.
 *
 * Parametri in ingresso/uscita:
 * - magazzino: vettore di code
 *
 * Parametri in ingresso:
 * - spedizione: spedizione da inserire
 *
 * Valore di ritorno:
 * - OK se l'inserimento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int magazzino_put(magazzino_t magazzino, spedizione_t spedizione) {
    int k = funzione_indice(spedizione.corriere);
    return accoda_spedizione(&magazzino[k], spedizione);
}


/* ============================================================================
 * QUESITO 2 - CARICAMENTO DA FILE
 * ========================================================================== */

/*
 * Carica le spedizioni dal file indicato e le inserisce nel vettore di code.
 *
 * Il file contiene una spedizione per riga nel formato:
 *
 *      codice destinatario zona corriere peso
 *
 * Esempio:
 *
 *      SP001 Rossi Centro DHL 2.50
 *
 * Parametri in ingresso/uscita:
 * - magazzino: vettore di code in cui inserire le spedizioni
 *
 * Parametri in ingresso:
 * - nome_file: nome del file da leggere
 *
 * Parametri in uscita:
 * - num_caricate: numero di spedizioni caricate correttamente
 *
 * Valore di ritorno:
 * - OK se il caricamento e' avvenuto correttamente
 * - un codice di errore diverso da OK altrimenti
 */
int carica_spedizioni(magazzino_t magazzino, const char nome_file[], int *num_caricate) {
    // TODO implementazione a cura dello studente
    if (!magazzino || !nome_file || !num_caricate) return ERRORE_PARAMETRI;
    *num_caricate = 0;
    FILE *fp = fopen(nome_file, "r");
    if (!fp) return ERRORE_FILE;

    spedizione_t spedizione;
    while (fscanf(fp, "%s %s %s %s %f", spedizione.codice, spedizione.destinatario, spedizione.zona, spedizione.corriere, &spedizione.peso) == 5) {
        if (magazzino_put(magazzino, spedizione) == OK) {
            (*num_caricate)++;
        }
    }

    fclose(fp);
    return OK;
}


/* ============================================================================
 * QUESITO 3 - RICERCA PER CORRIERE
 * ========================================================================== */

/*
 * Cerca la prima spedizione affidata al corriere specificato.
 *
 * La funzione deve calcolare la posizione del vettore a partire dal corriere e
 * scorrere la coda corrispondente. Poiche' il corriere non e' un identificatore
 * univoco, e' sufficiente restituire la prima occorrenza trovata.
 *
 * Parametri in ingresso:
 * - magazzino: vettore di code
 * - corriere:  corriere da cercare
 *
 * Valore di ritorno:
 * - puntatore al nodo contenente la prima spedizione trovata
 * - NULL se non esiste alcuna spedizione per il corriere indicato
 */
nodo_spedizione_t *cerca_corriere(magazzino_t magazzino, const char corriere[]) {
    // TODO implementazione a cura dello studente
    if (magazzino == NULL || corriere == NULL) {
        return NULL;
    }

    for (int i = 0; i < VETT_DIM; i++) {
        nodo_spedizione_t *p = magazzino[i].primo;
        while (p != NULL) {
            if (strcmp(p->info.corriere, corriere) == 0)
                return p;
            p = p->next;
        }
    }

    return NULL;
}


/* ============================================================================
 * QUESITO 4 - ESTRAZIONE PER PESO
 * ========================================================================== */

/*
 * Estrarre dal magazzino tutte le spedizioni con peso maggiore o uguale alla
 * soglia indicata.
 *
 * La funzione deve produrre una nuova struttura dati scelta dallo studente.
 * Sono ammesse le seguenti rappresentazioni:
 * - array dinamico di spedizione_t;
 * - lista collegata di spedizioni;
 * - coda FIFO di spedizioni.
 *
 * Requisiti:
 * - completare il tipo di ritorno sostituendo DA_SOSTITUIRE;
 * - completare la lista dei parametri;
 * - scorrere tutte le code del vettore;
 * - selezionare le spedizioni con peso maggiore o uguale alla soglia;
 * - produrre una nuova struttura contenente le spedizioni selezionate;
 * - rendere disponibile al chiamante il numero di elementi estratti;
 * - se non ci sono spedizioni che soddisfano il filtro, il numero di elementi
 *   estratti deve essere zero.
 */
spedizione_t *estrai_pesanti(magazzino_t magazzino, float soglia, int *num_estratte) {
    // TODO implementazione a cura dello studente
    if (!magazzino || !num_estratte) return NULL;
    *num_estratte = 0;
    for (int i = 0; i < VETT_DIM; i++) {
        nodo_spedizione_t *p = magazzino[i].primo;
        while (p != NULL) {
            if (p->info.peso >= soglia) {
                (*num_estratte)++;
            }
            p = p->next;
        }
    }

    if (*num_estratte == 0) return NULL;
    spedizione_t *estratti = malloc(sizeof(spedizione_t) * (*num_estratte));
    if (!estratti) return NULL;

    for (int i = 0, j = 0; i < VETT_DIM; i++) {
        nodo_spedizione_t *p = magazzino[i].primo;
        while (p != NULL) {
            if (p->info.peso >= soglia) {
                estratti[j++] = p->info;
            }
            p = p->next;
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
    printf("1. Cerca prima spedizione di un corriere\n");
    printf("2. Stampa spedizioni di un corriere\n");
    printf("3. Estrai spedizioni con peso almeno pari a una soglia\n");
    printf("4. Stampa ultime spedizioni estratte\n");
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
 * Dopo avere completato il prototipo di estrai_pesanti e scelto la struttura
 * dati da usare per l'estrazione, lo studente deve completare la chiamata alla
 * funzione e usare la funzione di stampa coerente con la propria scelta.
 */
int main(void) {
    magazzino_t magazzino;
    spedizione_t* estratti = NULL;
    nodo_spedizione_t *trovata = NULL;
    int num_caricate = 0;
    int num_estratte = 0;
    int scelta;
    char corriere[STR_LEN];
    float soglia;

    magazzino_init(magazzino);

    if (carica_spedizioni(magazzino, FILE_INPUT, &num_caricate) != OK) {
        printf("Errore nel caricamento delle spedizioni.\n");
        dealloca_magazzino(magazzino);
        return 1;
    }

    printf("Spedizioni caricate: %d\n", num_caricate);
    stampa_magazzino(magazzino);

    do {
        scelta = menu();

        switch (scelta) {
            case 1:
                printf("Inserire corriere: ");
                scanf("%49s", corriere);

                trovata = cerca_corriere(magazzino, corriere);
                if (trovata != NULL) {
                    stampa_spedizione(&trovata->info);
                } else {
                    printf("Nessuna spedizione trovata per il corriere indicato.\n");
                }
                break;

            case 2:
                printf("Inserire corriere: ");
                scanf("%49s", corriere);

                trovata = cerca_corriere(magazzino, corriere);
                if (trovata != NULL) {
                    stampa_lista_spedizioni(trovata);
                } else {
                    printf("Nessuna spedizione trovata per il corriere indicato.\n");
                }
                break;

            case 3:
                printf("Inserire soglia di peso: ");
                scanf("%f", &soglia);

                if (estratti != NULL) {
                    free(estratti);
                    estratti = NULL;
                    printf("Deallocare la struttura usata per l'estrazione precedente.\n");
                }

                num_estratte = 0;

                estratti = estrai_pesanti(magazzino, soglia, &num_estratte);
                if (estratti == NULL) {
                    printf("Nessuna spedizione estratta.\n");
                } else {
                    printf("Spedizioni estratte: ");
                    stampa_array_spedizioni(estratti, num_estratte);
                }

                printf("Spedizioni estratte: %d\n", num_estratte);
                break;

            case 4:
                if (estratti == NULL || num_estratte == 0) {
                    printf("Nessuna estrazione precedente disponibile.\n");
                } else {
                    printf("Ultime spedizioni estratte:\n");
                    stampa_array_spedizioni(estratti, num_estratte);
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

    dealloca_magazzino(magazzino);

    return 0;
}
