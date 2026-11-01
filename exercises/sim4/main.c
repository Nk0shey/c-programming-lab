#include "../../common/console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 30

typedef struct {
    int matricola;
    char cognome[MAX_STR];
} Studente;

typedef struct nodo_studente {
    Studente info;
    struct nodo_studente *next;
} NodoStudente;

typedef struct {
    NodoStudente *primo;
    NodoStudente *ultimo;
} CodaStudenti;

typedef struct {
    char codice[MAX_STR];
    char nome[MAX_STR];
    int cfu;
} Corso;

typedef struct nodo_corso {
    Corso info;
    CodaStudenti iscritti;
    struct nodo_corso *next;
} NodoCorso;

typedef NodoCorso *ListaCorsi;


/* PROTOTIPI */

void inizializza_coda(CodaStudenti *coda);

int inserisci_corso_ordinato(
    ListaCorsi *lista,
    Corso corso
);

int carica_corsi(
    ListaCorsi *lista,
    const char nome_file[]
);

NodoCorso *cerca_corso(
    ListaCorsi lista,
    const char codice[]
);

int inserisci_studente(
    CodaStudenti *coda,
    Studente studente
);

int carica_iscrizioni(
    ListaCorsi lista,
    const char nome_file[]
);

Corso *crea_vettore_corsi(
    ListaCorsi lista,
    int minimo_studenti,
    int *dimensione
);

void ordina_corsi(
    Corso vettore[],
    int dimensione
);

void stampa_corsi(
    ListaCorsi lista
);

void dealloca_corsi(
    ListaCorsi *lista
);


/* QUESITO 1
 *
 * Inizializza la coda:
 * - primo = NULL
 * - ultimo = NULL
 */
void inizializza_coda(
    CodaStudenti *coda
) {
    coda->primo = NULL;
    coda->ultimo = NULL;
}


/* QUESITO 2
 *
 * Inserisce un corso nella lista mantenendo
 * l'ordine alfabetico crescente per nome.
 *
 * Operazioni:
 * 1. allocare NodoCorso;
 * 2. copiare corso in info;
 * 3. inizializzare la coda iscritti;
 * 4. cercare la posizione con strcmp;
 * 5. inserire in testa, in mezzo o in fondo.
 *
 * Restituisce 1 in caso di successo, 0 altrimenti.
 */
int inserisci_corso_ordinato(
    ListaCorsi *lista,
    Corso corso
) {
    /* TODO */
    NodoCorso *nuovo = malloc(sizeof(NodoCorso));
    if (nuovo == NULL) return 0;

    nuovo->info = corso;

    inizializza_coda(&nuovo->iscritti);

    NodoCorso *corrente = *lista;
    NodoCorso *precedente = NULL;

    while (corrente != NULL && strcmp(corrente->info.nome, corso.nome) < 0) {
        precedente = corrente;
        corrente = corrente -> next;
    }

    if (precedente == NULL) {
        nuovo->next = *lista;
        *lista = nuovo;
    } else {
        nuovo->next = corrente;
        precedente->next = nuovo;
    }

    return 1;
}


/* QUESITO 3
 *
 * Carica i corsi dal file.
 *
 * Formato:
 * CODICE NOME_CORSO CFU
 *
 * Esempio:
 * C01 Analisi 9
 *
 * Ogni corso deve essere inserito tramite
 * inserisci_corso_ordinato().
 *
 * Restituisce:
 * - numero di corsi caricati;
 * - -1 se il file non si apre.
 */
int carica_corsi(
    ListaCorsi *lista,
    const char nome_file[]
) {
    /* TODO */
    if (!lista || !nome_file) return -1;

    Corso c;
    int count = 0;

    FILE *fp = fopen(nome_file, "r");
    if (!fp) return -1;

    while (fscanf(fp, "%s %s %d", c.codice, c.nome, &c.cfu) == 3) {
        if (inserisci_corso_ordinato(lista, c) == 1) count++;
    }
    fclose(fp);
    return count;
}


/* QUESITO 4
 *
 * Cerca un corso tramite il codice.
 *
 * Restituisce:
 * - puntatore al NodoCorso trovato;
 * - NULL se non esiste.
 *
 * La lista non deve essere modificata.
 */
NodoCorso *cerca_corso(
    ListaCorsi lista,
    const char codice[]
) {
    /* TODO */
    NodoCorso *nodo_corso = lista;
    while (nodo_corso != NULL) {
        if (strcmp(nodo_corso->info.codice, codice) == 0) {
            return nodo_corso;
        }
        nodo_corso = nodo_corso->next;
    }
    return NULL;
}


/* QUESITO 5
 *
 * Inserisce uno studente in fondo alla coda.
 *
 * Gestire:
 * - coda vuota;
 * - coda non vuota.
 *
 * Restituisce 1 in caso di successo, 0 altrimenti.
 */
int inserisci_studente(
    CodaStudenti *coda,
    Studente studente
) {
    /* TODO */
    NodoStudente *nuovo = malloc(sizeof(NodoStudente));
    if (!nuovo) return 0;
    nuovo->info = studente;
    nuovo->next = NULL;

    if (coda->primo == NULL) {
        coda->primo = nuovo;
        coda->ultimo = nuovo;
    } else {
        coda->ultimo->next = nuovo;
        coda->ultimo = nuovo;
    }

    return 1;
}


/* QUESITO 6
 *
 * Carica le iscrizioni dal file.
 *
 * Formato:
 * MATRICOLA COGNOME CODICE_CORSO
 *
 *
 * Esempio:
 * 1001 Rossi C03
 *
 * Per ogni riga:
 * 1. leggere i dati;
 * 2. cercare il corso;
 * 3. inserire lo studente nella coda del corso;
 * 4. incrementare il contatore solo se l'inserimento riesce.
 *
 * Restituisce:
 * - numero di iscrizioni caricate;
 * - -1 se il file non si apre.
 */
int carica_iscrizioni(
    ListaCorsi lista,
    const char nome_file[]
) {
    /* TODO */
    if (!lista || !nome_file) return -1;
    FILE *fp = fopen(nome_file, "r");
    if (!fp) return -1;

    Studente studente;
    NodoCorso *trovato;
    char corso[MAX_STR];
    int count = 0;

    while (fscanf(fp, "%d %s %s", &studente.matricola, studente.cognome, corso) == 3) {
        trovato = cerca_corso(lista, corso);
        if (trovato) {
            if (inserisci_studente(&trovato->iscritti, studente) == 1) count++;
        }
    }

    fclose(fp);
    return count;
}


/* QUESITO 7
 *
 * Crea un vettore dinamico contenente i corsi
 * con almeno minimo_studenti iscritti.
 *
 * Operazioni:
 * 1. contare gli studenti di ogni corso;
 * 2. contare i corsi validi;
 * 3. allocare un vettore della dimensione esatta;
 * 4. copiare i corsi validi;
 * 5. aggiornare *dimensione.
 *
 * Se nessun corso e' valido:
 * - *dimensione = 0;
 * - return NULL.
 */
Corso *crea_vettore_corsi(
    ListaCorsi lista,
    int minimo_studenti,
    int *dimensione
) {
    /* TODO */

    *dimensione = 0;
    NodoCorso *nodo_corso = lista;
    NodoStudente *nodo_studente;

    int numero_studenti;

    while (nodo_corso != NULL) {
        numero_studenti = 0;
        nodo_studente = nodo_corso->iscritti.primo;
        while (nodo_studente != NULL) {
            numero_studenti++;
            nodo_studente = nodo_studente->next;
        }

        if (numero_studenti >= minimo_studenti) {
            (*dimensione)++;
        }

        nodo_corso = nodo_corso->next;
    }

    if (*dimensione == 0) return NULL;

    Corso *vettore = malloc(sizeof(Corso) * (*dimensione));
    if (!vettore) { *dimensione = 0; return NULL; }

    nodo_corso = lista;

    int i = 0;


    while (nodo_corso != NULL) {

        numero_studenti = 0;

        nodo_studente =
            nodo_corso->iscritti.primo;


        while (nodo_studente != NULL) {

            numero_studenti++;

            nodo_studente =
                nodo_studente->next;
        }


        if (
            numero_studenti
            >= minimo_studenti
        ) {

            vettore[i] =
                nodo_corso->info;

            i++;
        }


        nodo_corso =
            nodo_corso->next;
    }


    return vettore;
}


/* QUESITO 8
 *
 * Ordina il vettore con Bubble Sort.
 *
 * Criteri:
 * - CFU decrescente;
 * - a parita' di CFU, nome alfabetico crescente.
 *
 * Non usare qsort().
 */
void ordina_corsi(
    Corso vettore[],
    int dimensione
) {
    if (!vettore || dimensione <= 1) return;
    /* TODO */
    Corso temp;
    for (int i = 0; i < dimensione - 1; i++) {
        for (int j = 0; j < dimensione - 1 - i; j++) {
            if (vettore[j].cfu < vettore[j + 1].cfu ||(vettore[j].cfu == vettore[j + 1].cfu && strcmp(vettore[j].nome, vettore[j + 1].nome) > 0)) {
                temp = vettore[j];
                vettore[j] = vettore[j + 1];
                vettore[j + 1] = temp;
            }
        }
    }
}


/* QUESITO 9
 *
 * Stampa tutti i corsi e gli studenti iscritti.
 *
 * Formato indicativo:
 *
 * C04 Algebra CFU=6
 * 1006 Greco
 *
 * La visita deve essere non distruttiva.
 */
void stampa_corsi(
    ListaCorsi lista
) {
    NodoCorso *nodo_corso = lista;

    NodoStudente *nodo_studente;


    while (nodo_corso != NULL) {

        printf(
            "%s %s CFU=%d\n",
            nodo_corso->info.codice,
            nodo_corso->info.nome,
            nodo_corso->info.cfu
        );


        nodo_studente =
            nodo_corso->iscritti.primo;


        while (nodo_studente != NULL) {

            printf(
                "%d %s\n",
                nodo_studente->info.matricola,
                nodo_studente->info.cognome
            );

            nodo_studente =
                nodo_studente->next;
        }


        printf("\n");


        nodo_corso =
            nodo_corso->next;
    }
}


/* QUESITO 10
 *
 * Dealloca tutta la struttura.
 *
 * Operazioni:
 * 1. per ogni corso liberare tutta la coda iscritti;
 * 2. liberare il nodo corso;
 * 3. impostare *lista = NULL.
 *
 * Prima di ogni free salvare il puntatore al nodo successivo.
 */
void dealloca_corsi(
    ListaCorsi *lista
) {

    NodoCorso *nodo_corso = *lista;
    NodoCorso *succ_corso;
    NodoStudente *nodo_studente;
    NodoStudente *succ_studente;
    while (nodo_corso != NULL) {
        nodo_studente = nodo_corso->iscritti.primo;
        while (nodo_studente != NULL) {
            succ_studente = nodo_studente->next;
            free(nodo_studente);
            nodo_studente = succ_studente;
        }
        succ_corso = nodo_corso->next;
        free(nodo_corso);
        nodo_corso = succ_corso;
    }

}


int main(void) {

    ListaCorsi lista = NULL;

    Corso *vettore = NULL;

    int dimensione = 0;

    int scelta;

    int caricati;

    int soglia;


    do {

        printf(
            "\n\n"
            "===== GESTIONE CORSI =====\n"
            "1. Carica corsi\n"
            "2. Carica iscrizioni\n"
            "3. Stampa corsi e iscritti\n"
            "4. Crea vettore corsi frequentati\n"
            "0. Esci\n"
            "\nScelta: "
        );

        lab_scanf("%d", &scelta);


        switch (scelta) {

        case 1:

            caricati = carica_corsi(
                &lista,
                "corsi.txt"
            );

            if (caricati == -1)
                printf("Errore apertura file corsi.txt\n");
            else
                printf("Corsi caricati: %d\n", caricati);

            break;


        case 2:

            caricati = carica_iscrizioni(
                lista,
                "iscrizioni.txt"
            );

            if (caricati == -1)
                printf("Errore apertura file iscrizioni.txt\n");
            else
                printf("Iscrizioni caricate: %d\n", caricati);

            break;


        case 3:

            stampa_corsi(lista);

            break;


        case 4:

            printf("Inserire il numero minimo di studenti: ");

            lab_scanf("%d", &soglia);

            free(vettore);

            vettore = crea_vettore_corsi(
                lista,
                soglia,
                &dimensione
            );

            ordina_corsi(
                vettore,
                dimensione
            );

            for (int i = 0; i < dimensione; i++) {

                printf(
                    "%s %s CFU=%d\n",
                    vettore[i].codice,
                    vettore[i].nome,
                    vettore[i].cfu
                );
            }

            break;


        case 0:

            printf("Chiusura programma\n");

            break;


        default:

            printf("Scelta non valida\n");
        }


    } while (scelta != 0);


    free(vettore);

    dealloca_corsi(&lista);

    return 0;
}
