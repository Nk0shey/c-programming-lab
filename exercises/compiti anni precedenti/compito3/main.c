/******************************************************************************
*  Implementare in ANSI C un programma che permetta la gestione di un centro di
*   smistamento di merci.
*
*  Il centro riceve merci da diverse fonti e le smista verso destinazioni,
*   ognuna delle quali è caratterizzata da un codice univoco e ha un rullo
*   trasportatore (una coda) dedicato dove le merci dirette a quella destinazione
*   vengono depositate in ordine di arrivo.
*   Il centro è quindi gestito tramite un array di code (una per ogni destinazione
*   in quanto ogni coda rappresenta un rullo e integra i dati sulla destinazione).
*
*  Le merci sono caratterizzate da un codice univoco, da una data di partenza,
*   da un peso e dalla destinazione.
*
*  Il programma esegue le seguenti operazioni:
*
*  1. Caricare i dati sui rulli e sulle merci da un file di testo "merci.txt".
*     Inizialmente, il file contiene il numero di rulli e la destinazione di ciascun rullo.
*     Successivamente, il file contiene le merci in arrivo.
*
*  2. Dato un codice di destinazione, quantificare il numero di elementi e
*       il peso totale delle merci.
*
*  4. Generare un albero binario di ricerca delle merci smistate dove la chiave
*       è il codice della merce e il contenuto del nodo è la merce stessa.
*
*  5. Dato un codice di merce, ricercare le informazioni relative a quella merce
*       nell'albero e stamparle.
*
*  6. Creare una coda di merci nell'albero che hanno un peso superiore a un certo
*       valore di soglia. La coda deve essere ordinata per codice di merce.
*
*  3. [BONUS] Dato un codice di destinazione, estrarre (e restituire in un array dinamico) le
*       prime N merci sul rullo corrispondente, dove N è il numero di merci da estrarre.
*       Nel caso siano presenti meno di N merci, restituire tutte le merci disponibili.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOME_FILE "merci.txt"
#define OK (0)
#define ERRORE_FILE (-1)
#define ERRORE_MEMORIA (-2)
#define ERRORE_INPUT (-4)
#define DESTINAZIONE_NON_PRESENTE (-8)
#define CODA_VUOTA (-10)


typedef struct {
    char codice[10];        // Codice della merce
    char data_partenza[11]; // Data di partenza (formato GG-MM-AAAA)
    float peso;             // Peso della merce
    char destinazione[10];  // Codice di destinazione
} Merce;

typedef struct nodo_merce {
    Merce info;
    struct nodo_merce *next;
} NodoMerce;

typedef struct {
    char destinazione[10]; // Codice della destinazione del rullo
    NodoMerce *primo; // Puntatore al primo nodo della coda
    NodoMerce *ultimo; // Puntatore all'ultimo nodo della coda
    unsigned int num_elementi; // Numero di elementi nella coda
} CodaMerce;

/* Inizializza la coda di merci
 *
 * Parametri in ingresso
 * - coda: puntatore alla coda da inizializzare
 * - destinazione: codice della destinazione del rullo
 * Nessun parametro di uscita o valore di ritorno
 */
void inizializzaCoda(CodaMerce *coda, const char destinazione[]) {
    coda->primo = NULL;
    coda->ultimo = NULL;
    strcpy(coda->destinazione, destinazione);
    coda->num_elementi = 0;
}

/* CercaRullo:
 * Dato un array di rulli e un codice di destinazione,
 * restituisce il puntatore al rullo corrispondente
 */
CodaMerce* cercaRullo(CodaMerce rulli[], unsigned num_rulli, const char codice_destinazione[]) {
    if (num_rulli == 0 || rulli == NULL) return NULL; // Nessun rullo disponibile
    for (unsigned i = 0; i < num_rulli; i++) {
        if (strcmp(rulli[i].destinazione, codice_destinazione) == 0) {
            return &rulli[i];
        }
    }
    return NULL; // Rullo non trovato
}

/* Aggiungi una merce alla coda di merci
 *
 * Parametri in ingresso:
 * - coda: puntatore alla coda di merci
 * - m: merce da aggiungere
 * Restituisce:
 * - OK in caso di successo
 * - ERRORE_MEMORIA in caso di errore di allocazione
 */
int aggiungiMerceInCoda(CodaMerce *coda, Merce m) {
    NodoMerce *nuovo_nodo = malloc(sizeof(NodoMerce));
    if (nuovo_nodo == NULL)
        return ERRORE_MEMORIA; // Errore di allocazione

    nuovo_nodo->info = m;
    nuovo_nodo->next = NULL;

    if (coda->ultimo == NULL) {
        // Coda vuota
        coda->primo = nuovo_nodo;
    } else {
        // Aggiungi in coda
        coda->ultimo->next = nuovo_nodo;
    }

    coda->ultimo = nuovo_nodo;

    coda->num_elementi++;
    return OK; // Successo
}

void disallocaCoda(CodaMerce *coda) {
    if (coda == NULL) return;

    NodoMerce *corrente = coda->primo;
    while (corrente != NULL) {
        NodoMerce *da_eliminare = corrente;
        corrente = corrente->next;
        free(da_eliminare);
    }

    coda->primo = NULL;
    coda->ultimo = NULL;
    coda->num_elementi = 0;

}

/* Quesito 1.
 *
 * Caricare i dati sui rulli e sulle merci da un file di testo "merci.txt".
 * Il file ha la seguente struttura:
 *  - La prima riga contiene il numero M di rulli
 *  - Le M righe successive contengono il codice di destinazione per ciascun rullo
 *     con il seguito formato:
 *      CodiceDestinazione
 *  - Le righe successive contengono le merci in arrivo, con il formato:
 *      CodiceMerce DataPartenza Peso Destinazione
 *
 *    Nel caso in cui nel file sia presente un rullo con una destinazione non valida,
 *      questo rullo non viene considerato.
 *    Nota bene: l'inizializzazione del rullo deve essere fatta prima di aggiungere
 *      le merci, e include l'inizializzazione della destinazione oltre che della coda corrispondente
 *
 *    Esempio:
       2
       MI
       CT
       XXA004 01-06-2025 10.5 CT
       AB1234 02-06-2025 5.0 MI
 *
 * Parametro di ingresso:
 * - nome_file: nome del file da cui caricare i dati
 * Parametri di uscita:
 * - num_rulli: puntatore al numero di rulli caricati
 * Restituisce:
 * - rulli: array di strutture CodaMerce che rappresentano i rulli
*/
CodaMerce* caricaRulli(const char nome_file[], unsigned *num_rulli) {
    char destinazione[10];
    CodaMerce* rulli = NULL;
    Merce m;
    FILE *fp;
    unsigned i, j;

    if (num_rulli == NULL) {
        return NULL;
    }

    *num_rulli = 0;

    fp = fopen(nome_file, "r");
    if (fp == NULL) {
        return NULL;
    }

    if (fscanf(fp, "%u", num_rulli) != 1) {
        printf("Errore nella lettura del numero di rulli\n");
        fclose(fp);
        return NULL;
    }

    if (*num_rulli == 0) {
        fclose(fp);
        return NULL;
    }

    rulli = (CodaMerce*)malloc((*num_rulli) * sizeof(CodaMerce));
    if (rulli == NULL) {
        fclose(fp);
        return NULL;
    }

    for (i = 0; i < *num_rulli; i++) {
        if (fscanf(fp, "%9s", destinazione) != 1) {
            printf("Errore nella lettura della destinazione del rullo %u\n", i + 1);

            for (j = 0; j < i; j++) {
                disallocaCoda(&rulli[j]);
            }

            free(rulli);
            fclose(fp);
            return NULL;
        }

        inizializzaCoda(&rulli[i], destinazione);
    }

    while (fscanf(fp, "%9s %10s %f %9s",
                  m.codice,
                  m.data_partenza,
                  &m.peso,
                  m.destinazione) == 4) {

        CodaMerce* rullo = cercaRullo(rulli, *num_rulli, m.destinazione);

        if (rullo == NULL) {
            printf("Rullo con destinazione %s non trovato. Merce %s non aggiunta.\n",
                   m.destinazione,
                   m.codice);
        } else {
            if (aggiungiMerceInCoda(rullo, m) != OK) {
                printf("Errore nell'aggiunta della merce %s al rullo %s\n",
                       m.codice,
                       m.destinazione);
            }
        }
                  }

    fclose(fp);
    return rulli;
}

/* Quesito 2.
*   Dato un codice di destinazione, quantificare il numero di elementi e
*       il peso totale delle merci.
*
*   Parametri in ingresso:
*     - rulli: array di strutture CodaMerce che rappresentano i rulli
*     - codice_destinazione: codice della destinazione da cercare
*     - num_rulli: numero di rulli nell'array
*   Parametri di uscita:
*     - num_elementi: puntatore al numero di merci trovate
*     - peso_totale: puntatore al peso totale delle merci trovate
*   Restituisce:
*     - OK in caso di successo
*     - ERRORE_INPUT in caso di parametri non validi
*     - DESTINAZIONE_NON_PRESENTE se il rullo con la destinazione specificata non esiste
*/
int quantificaMerce(const CodaMerce rulli[],
    const char codice_destinazione[],
    unsigned num_rulli,
    unsigned *num_elementi, float *peso_totale) {
if (!rulli || !codice_destinazione || !num_elementi || !peso_totale) return ERRORE_INPUT;
    *num_elementi=0; *peso_totale=0;
    const CodaMerce *rullo=NULL;
    for (unsigned i=0;i<num_rulli;++i) if (!strcmp(rulli[i].destinazione,codice_destinazione)) { rullo=&rulli[i]; break; }
    if (!rullo) return DESTINAZIONE_NON_PRESENTE;
    for (NodoMerce *n=rullo->primo;n;n=n->next) { ++*num_elementi; *peso_totale+=n->info.peso; }
    return OK;
}

typedef struct nodo_albero {
    Merce info;
    struct nodo_albero *sx;
    struct nodo_albero *dx;
} NodoAlbero, *Albero;

void disallocaAlbero(Albero *a);

/* Inizializza un albero vuoto
 * Parametro di uscita:
 * - a: puntatore all'albero da inizializzare
 * Nessun valore di ritorno
 */
void inizializzaAlbero(Albero *a) {
    *a = NULL; // Inizializza l'albero come vuoto
}
/* Costruisce un nodo dell'albero binario di ricerca.
 * Copia la merce nel nodo
 *
 * Parametri di ingresso:
 * - a: puntatore all'albero binario di ricerca
 * - m: merce da inserire
 * Restituisce:
 * - OK in caso di successo
 * - ERRORE_MEMORIA in caso di errore di allocazione
 */
int inserisciAlbero(Albero *a, Merce m) {
    if (*a == NULL) {
        // Crea un nuovo nodo
        *a = malloc(sizeof(NodoAlbero));
        if (*a == NULL) {
            return ERRORE_MEMORIA; // Errore di allocazione
        }
        (*a)->info = m; // Copia la merce nel nodo
        (*a)->sx = NULL; // Inizializza il sottoalbero sinistro
        (*a)->dx = NULL; // Inizializza il sottoalbero destro
        return OK; // Successo
    }

    int risultato_cmp = strcmp(m.codice, (*a)->info.codice);
    if (risultato_cmp < 0) {
        // Inserisci nel sottoalbero sinistro
        return inserisciAlbero(&(*a)->sx, m);
    } else if (risultato_cmp > 0) {
        // Inserisci nel sottoalbero destro
        return inserisciAlbero(&(*a)->dx, m);
    } else {
        return ERRORE_INPUT; // Codice già presente nell'albero
    }
}

/*  Quesito 4.
 *  Generare un albero binario di ricerca delle merci smistate dove la chiave
 *       è il codice della merce e il contenuto del nodo è la merce stessa.
 *
 *   Parametri:
 *    - a: puntatore all'albero binario di ricerca da creare
 *   - rulli: array di strutture CodaMerce che rappresentano i rulli
 *   - num_rulli: numero di rulli nell'array
 *
 *   Restituisce:
 *   - OK in caso di successo
 *   - ERRORE_MEMORIA in caso di errore di allocazione
*/
int creaAlbero(Albero* a, const CodaMerce rulli[], unsigned num_rulli) {
    if (a == NULL || rulli == NULL || num_rulli == 0) {
        return ERRORE_INPUT; // Parametri non validi
    }

    inizializzaAlbero(a); // Inizializza l'albero

    // TODO: Implementare da qui in poi

    for (unsigned i = 0; i < num_rulli; i++) {
        NodoMerce *corrente = rulli[i].primo;
        while (corrente != NULL) {
            int res = inserisciAlbero(a, corrente->info);
            if (res == ERRORE_MEMORIA) {
                disallocaAlbero(a);
                return ERRORE_MEMORIA;
            }
            if (res == ERRORE_INPUT) {
                printf("Codice duplicato '%s', ignorato\n", corrente->info.codice);
            }
            corrente = corrente->next;
        }
    }

    return OK; // Successo
}

/* Quesito 5.
 * Dato un codice di merce, ricercare le informazioni relative a quella merce
*       nell'albero e restituirle (la stampa avviene nel main!)
*
*  Parametri di ingresso:
*  - a: puntatore all'albero binario di ricerca
*  - codice: codice della merce da cercare
*  Restituisce:
*  - Puntatore alla merce trovata, NULL se non trovata
*/
Merce* cercaMerceInAlbero(const Albero a, const char codice[]) {
    if (a == NULL || codice == NULL) {
        return NULL; // Albero vuoto o codice non valido
    }

    // TODO: Implementare da qui in poi

    int risultato_cmp = strcmp(codice, a->info.codice);
    if (risultato_cmp == 0) {
        return &a->info;
    } else if (risultato_cmp < 0) {
        return cercaMerceInAlbero(a->sx, codice);
    } else {
        return cercaMerceInAlbero(a->dx, codice);
    }
}

/* Quesito 6.
 *   Creare una coda di merci nell'albero che hanno un peso superiore a un certo
 *       valore di soglia.
 *   La coda deve essere ordinata per codice di merce.
 */
void creaCodaMerciPesanti(const Albero a, CodaMerce* coda, float soglia) {
    if (a == NULL) return;

    creaCodaMerciPesanti(a->sx, coda, soglia);

    if (a->info.peso > soglia) {
        aggiungiMerceInCoda(coda, a->info);
    }

    creaCodaMerciPesanti(a->dx, coda, soglia);
}


/* EstraiCoda:
 * Dato un rullo, estrae la prima merce dalla coda e la restituisce.
 * Parametri in ingresso:
 * - rullo: puntatore alla coda di merci
 * Parametri di uscita:
 * - merce: puntatore alla merce estratta
 * Valori di ritorno:
 * - OK in caso di successo
 * - CODA_VUOTA se la coda è vuota
 */
int estraiCoda(CodaMerce* rullo, Merce* merce) {
    if (rullo == NULL || rullo->primo == NULL) {
        return CODA_VUOTA;
    }

    NodoMerce *nodo_estratto = rullo->primo;
    Merce merce_estratta = nodo_estratto->info;

    rullo->primo = nodo_estratto->next;
    if (rullo->primo == NULL) {
        rullo->ultimo = NULL; // Se la coda diventa vuota, aggiorna l'ultimo nodo
    }

    free(nodo_estratto);
    rullo->num_elementi--;
    *merce = merce_estratta; // Copia la merce estratta nel parametro di uscita
    return OK; // Restituisce la merce estratta
}
/* Quesito 3.
 * Dato un codice di destinazione, estrarre (e restituire in un array dinamico) le
 *  prime N merci sul rullo corrispondente, dove N è il numero di merci da estrarre.
 *  Nel caso siano presenti meno di N merci, restituire tutte le merci disponibili.
 *
 * Parametri in ingresso:
 * - rulli: array di strutture CodaMerce che rappresentano i rulli
 * - codice_destinazione: codice della destinazione da cercare
 * - num_rulli: numero di rulli nell'array
 * - N: numero di merci da estrarre
 * Parametri di uscita:
 * - num_merci: puntatore al numero di merci estratte
 * Restituisce:
 * - Un array dinamico di merci estratte in caso di successo
*/
Merce* estraiPrimeNMerci(CodaMerce rulli[],
    const char codice_destinazione[], unsigned num_rulli,
    unsigned N, unsigned *num_merci) {
if (!num_merci) return NULL;
    *num_merci=0;
    if (!rulli || !codice_destinazione || !N) return NULL;
    CodaMerce *q=cercaRullo(rulli,num_rulli,codice_destinazione); if (!q) return NULL;
    unsigned count=0; for (NodoMerce *n=q->primo;n && count<N;n=n->next) ++count;
    if (!count) return NULL;
    Merce *v=malloc((size_t)count*sizeof *v); if (!v) return NULL;
    for (unsigned i=0;i<count;++i) { NodoMerce *n=q->primo; v[i]=n->info; q->primo=n->next; free(n); }
    if (!q->primo) q->ultimo=NULL;
    q->num_elementi -= count;
    *num_merci=count; return v;
}

void stampaMerce(const Merce *m) {
    if (m != NULL) {
        printf("Codice: %s, Data Partenza: %s, Peso: %.2f, Destinazione: %s\n",
               m->codice, m->data_partenza, m->peso, m->destinazione);
    } else {
        printf("Merce non trovata.\n");
    }
}
void stampaCoda(const CodaMerce *coda) {
    if (coda == NULL || coda->primo == NULL) {
        printf("Coda vuota.\n");
        return;
    }

    printf("Coda per destinazione %s:\n", coda->destinazione);
    NodoMerce *corrente = coda->primo;
    while (corrente != NULL) {
        stampaMerce(&corrente->info);
        corrente = corrente->next;
    }
}

void stampaArrayRulli(const CodaMerce rulli[], unsigned num_rulli) {
    if (rulli == NULL || num_rulli == 0) {
        printf("Nessun rullo disponibile.\n");
        return;
    }

    for (unsigned i = 0; i < num_rulli; i++) {
        printf("Rullo %u - Destinazione: %s\n", i + 1, rulli[i].destinazione);
        stampaCoda(&rulli[i]);
    }
}


void stampaAlbero(const Albero a) {
    if (a == NULL) return;
    stampaMerce(&a->info);

    stampaAlbero(a->sx);
    stampaAlbero(a->dx);
}



void disallocaAlbero(Albero *a) {
    if (*a == NULL) return;
    disallocaAlbero(&(*a)->sx);
    disallocaAlbero(&(*a)->dx);
    free(*a);
    *a = NULL;
}

int Menu() {
    int scelta;

    printf("*** M E N U ***\n"
           "1 - Carica rulli e merci da file\n"
           "2 - Quantifica merci per destinazione\n"
           "3 - Estrai prime N merci da rullo\n"
           "4 - Crea albero binario di ricerca delle merci\n"
           "5 - Cerca merce in albero\n"
           "6 - Crea coda merci pesanti\n"
           "0 - Esci\n"
           "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

int main() {
    CodaMerce* rulli = NULL;
    Albero A;
    unsigned num_rulli = 0;
    char codice_destinazione[10];
    char codice_merce[10];
    CodaMerce coda_pesanti;
    Merce* merce_trovata;

    inizializzaAlbero(&A);
    int scelta;
    do {
        scelta = Menu();
        switch (scelta) {
            case 1:

                // Carica i rulli e le merci da file
                rulli = caricaRulli(NOME_FILE, &num_rulli);
                if (rulli == NULL) {
                    printf("Errore nel caricamento dei rulli e delle merci.\n");
                }
                else {
                    stampaArrayRulli(rulli, num_rulli);
                }

                break;

            case 2:
                // Quantifica merci per destinazione
                if (rulli == NULL) {
                    printf("Nessun rullo disponibile.\n");
                    break;
                }
                printf("Inserisci il codice di destinazione: ");
                scanf("%s", codice_destinazione);
                unsigned num_elementi;
                float peso_totale;
                int risultato = quantificaMerce(rulli, codice_destinazione,
                    num_rulli, &num_elementi, &peso_totale);
                if (risultato == OK) {
                    printf("Numero di merci: %u, Peso totale: %.2f\n", num_elementi, peso_totale);
                } else if (risultato == DESTINAZIONE_NON_PRESENTE) {
                    printf("Rullo con destinazione %s non trovato.\n", codice_destinazione);
                } else {
                    printf("Errore nella quantificazione delle merci.\n");
                }

                break;

            case 3:
                // Estrai prime N merci da rullo
                if (rulli == NULL) {
                    printf("Nessun rullo disponibile.\n");
                    break;
                }
                printf("Inserisci il codice di destinazione: ");
                scanf("%s", codice_destinazione);
                unsigned N;
                printf("Inserisci il numero di merci da estrarre: ");
                scanf("%u", &N);
                unsigned num_merci;
                Merce* merci_estratte = estraiPrimeNMerci(rulli, codice_destinazione, num_rulli, N, &num_merci);
                if (merci_estratte == NULL) {
                    printf("Nessun merci estratte o errore.\n");
                } else {
                    printf("Merci estratte:\n");
                    for (unsigned i = 0; i < num_merci; i++) {
                        stampaMerce(&merci_estratte[i]);
                    }
                    free(merci_estratte); // Libera la memoria allocata
                }

                break;
            case 4:
                // Crea albero binario di ricerca delle merci
                if (rulli == NULL) {
                    printf("Nessun rullo disponibile.\n");
                    break;
                }
                disallocaAlbero(&A);
                if (creaAlbero(&A, rulli, num_rulli) == OK) {
                    printf("Albero binario di ricerca creato con successo.\n");
                    stampaAlbero(A);
                } else {
                    printf("Errore nella creazione dell'albero binario di ricerca.\n");
                }
                break;
            case 5:
                // Cerca merce in albero
                if (A == NULL) {
                    printf("Albero vuoto. Creare l'albero con l'opzione 4.\n");
                    break;
                }
                printf("Inserisci il codice della merce da cercare: ");

                scanf("%s", codice_merce);
                merce_trovata = cercaMerceInAlbero(A, codice_merce);
                if (merce_trovata != NULL) {
                    printf("Merce trovata:\n");
                    stampaMerce(merce_trovata);
                } else {
                    printf("Merce con codice %s non trovata nell'albero.\n", codice_merce);
                }
                break;
            case 6:
                // Crea coda merci pesanti
                if (A == NULL) {
                    printf("Albero vuoto. Creare l'albero con l'opzione 4.\n");
                    break;
                }

                float soglia;
                do {
                    printf("Inserisci il valore di soglia per il peso: ");

                    if (scanf("%f", &soglia) != 1) {
                        printf("Input non valido. Inserisci un numero.\n");
                        while (getchar() != '\n'); // Pulisce il buffer di input
                    } else
                        break; // Input valido
                } while (true);
                if (soglia <= 0) {
                    printf("Soglia non valida. Deve essere un numero positivo.\n");
                    break;
                }

                inizializzaCoda(&coda_pesanti, "Pesanti");
                creaCodaMerciPesanti(A, &coda_pesanti, soglia);
                printf("Coda di merci con peso superiore a %.2f:\n", soglia);
                stampaCoda(&coda_pesanti);

                disallocaCoda(&coda_pesanti); // Libera la memoria della coda
                break;
            case 0:
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
                break;

        }
    } while (scelta != 0);

    //TODO: Disalloca Albero
    //TODO: Disalloca i rulli
    disallocaAlbero(&A);
    if (rulli != NULL) {
        for (unsigned i = 0; i < num_rulli; i++) {
            disallocaCoda(&rulli[i]);
        }
        free(rulli);
        rulli = NULL;
    }
    return 0;
}