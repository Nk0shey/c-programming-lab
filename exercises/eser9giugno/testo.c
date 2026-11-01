/**********************************************************************************
 * === MODULO 2 ===
 *
 * Implementare in ANSI C un programma per la gestione di consegne a domicilio.
 *
 * Gli ordini dei clienti arrivano a un server centrale che li assegna ai rider in base alla zona coperta
 * (centro, periferia o hinterland). Ogni rider gestisce gli ordini assegnati secondo l'ordine di arrivo (gestione FIFO).
 * I dati sono memorizzati in una lista di rider, ognuno con la coda dei propri ordini.
 *
 * Per ogni ordine vengono memorizzate le seguenti informazioni:
 * - id_ordine (alfanumerico senza spazi)
 * - codice_cliente (alfanumerico senza spazi)
 * - importo (float)
 * - stato ordine (enum: PREPARAZIONE / IN_CONSEGNA / CONSEGNATO)
 *
 * Ogni rider è caratterizzato da:
 * - codice_rider (alfanumerico senza spazi)
 * - nome (stringa senza spazi)
 * - zona coperta (enum: CENTRO / PERIFERIA / HINTERLAND)
 * - coda degli ordini assegnati
 *
 * Il programma deve implementare le seguenti operazioni:
 *
 * 2a. Caricare i dati dai file "rider.txt" e "ordini.txt" e memorizzarli in una lista di code.
 * 2b. Data una zona, stampare a video gli ordini non ancora consegnati.
 * 2c. Calcolare il guadagno totale per rider (somma di tutti gli ordini assegnati), e restituirlo tramite
 *     un vettore allocato dinamicamente (un elemento per ogni rider).
 * 2d. Creare un albero binario di ricerca ordinato per codice_cliente, contenente il numero di ordini effettuati e il
 *     totale degli importi per cliente.
 * 2e. Salvare in un file "output.txt" i dati dei clienti che hanno effettuato più di un ordine, ordinati per codice cliente.
 * 2f. Completare il main e deallocare tutte le strutture dati allocate dinamicamente.
**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ORDINI "ordini.txt"
#define FILE_RIDER "rider.txt"
#define FILE_OUT "output.txt"

#define STR_LEN 11
#define COD_LEN 6


typedef enum {
    STATO_SCONOSCIUTO = -1,
    PREPARAZIONE,
    IN_CONSEGNA,
    CONSEGNATO
}stato_t;

const char* stato_to_string(stato_t s) {
    switch (s) {
        case PREPARAZIONE: return "PREPARAZIONE";
        case IN_CONSEGNA: return "IN_CONSEGNA";
        case CONSEGNATO: return "CONSEGNATO";
        default: return "SCONOSCIUTO";
    }
}

stato_t string_to_stato(const char* str) {
    if (!str) return STATO_SCONOSCIUTO;
    if (strcmp(str, "PREPARAZIONE") == 0) return PREPARAZIONE;
    if (strcmp(str, "IN_CONSEGNA") == 0) return IN_CONSEGNA;
    if (strcmp(str, "CONSEGNATO") == 0) return CONSEGNATO;
    return STATO_SCONOSCIUTO;
}

typedef enum {
    ZONA_SCONOSCIUTA = -1,
    CENTRO,
    PERIFERIA,
    HINTERLAND
}zona_t;

zona_t string_to_zona(const char* str) {
    if (!str) return ZONA_SCONOSCIUTA;
    if (strcmp(str, "CENTRO") == 0) return CENTRO;
    if (strcmp(str, "PERIFERIA") == 0) return PERIFERIA;
    if (strcmp(str, "HINTERLAND") == 0) return HINTERLAND;
    return ZONA_SCONOSCIUTA;
}

/* struttura dati coda di ordini */
typedef struct{
    char id_ordine[COD_LEN];
    char codice_cliente[COD_LEN];
    float importo;
    stato_t stato;
}ordine_t;

typedef struct nodo_ordine{
    ordine_t info;
    struct nodo_ordine* next;
}NodoOrdine;

typedef struct {
    NodoOrdine* primo;
    NodoOrdine* ultimo;
}CodaOrdini;

/* struttura dati lista di rider */
typedef struct{
    char codice_rider[COD_LEN];
    char nome[STR_LEN];
    zona_t zona;
    CodaOrdini ordini;
}rider_t;

typedef struct nodo_rider {
    rider_t info;
    struct nodo_rider* next;
}NodoRider;
typedef NodoRider* ListaRider;




/*
 * Aggiunge un nuovo rider alla lista dei rider
 *
 * Parametri in ingresso:
 * - lista: puntatore alla lista dei rider
 * - r: rider da aggiungere
 *
 * Valore di ritorno:
 * 1 se l'aggiunta è avvenuta con successo, 0 altrimenti.
 */
int aggiungi_rider(ListaRider* lista, rider_t r) {
    NodoRider* nuovo_nodo = (NodoRider*)malloc(sizeof(NodoRider));
    if (nuovo_nodo == NULL) {
        printf("Errore allocazione memoria");
        return 0;
    }
    nuovo_nodo->info = r;
    nuovo_nodo->next = *lista;
    *lista = nuovo_nodo;
    return 1;
}

/*
 * Cerca un nodo della lista dei rider per codice_rider
 *
 * Parametri in ingresso:
 * - lista: lista dei rider
 * - codice_rider: codice del rider da ricercare
 *
 * Valore di ritorno:
 * puntatore al nodo cercato se esiste, NULL altrimenti.
 */
rider_t* cerca_rider_codice(ListaRider lista, const char* codice_rider) {
    if (lista == NULL) return NULL;
    if (strcmp(lista->info.codice_rider, codice_rider) == 0) return &lista->info;
    return cerca_rider_codice(lista->next, codice_rider);
}


/*
 * Inserisce un nuovo ordine alla coda degli ordini.
 *
 * Parametri in ingresso:
 * - coda: puntatore alla coda degli ordini
 * - o: nuovo ordine da aggiungere
 *
 * Valore di ritorno:
 * 1 se l'inserimento è avvenuto con successo, 0 altrimenti
*/
int aggiungi_ordine_a_rider(CodaOrdini* coda, ordine_t o) {
    NodoOrdine* nodo = (NodoOrdine*)malloc(sizeof(NodoOrdine));
    if (nodo == NULL) {
        printf("Errore allocazione memoria");
        return 0;
    }
    nodo->info = o;
    nodo->next = NULL;
    if (coda->primo == NULL)
        coda->primo = nodo;
    else
        coda->ultimo->next = nodo;

    coda->ultimo = nodo;
    return 1;
}


/*
 * Quesito 2a
 * Carica i dati dai file e li memorizza ina una lista di code.
 *
 * Il file ordini.txt ha il seguente formato:
 * codice_rider(stringa) id_ordine(stringa) codice_cliente(stringa) importo(float) stato(stringa "PREPARAZIONE"/"IN_CONSEGNA"/"CONSEGNATO")
 *
 * Esempio:
 * 016CD AAB12 ABCDE 48.50 CONSEGNATO
 *
 * Il file rider.txt ha il seguente formato:
 * codice_rider(stringa) nome(stringa) zona(stringa "CENTRO"/"PERIFERIA"/"HINTERLAND")
 *
 * Esempio:
 * 0A4BF Salvo CENTRO
 * 016CD Manuel PERIFERIA
 * ...
 *
 *
 * Valore di ritorno
 *  - numero di ordini caricati se l'operazione è andata a buon fine, -1 altrimenti
 */
int carica_dati(const char* nome_file_rider, const char* nome_file_ordini, ListaRider* lista) {
    FILE *fp = NULL;
    rider_t rider;
    char zona_str[STR_LEN];
    int totale_ordini = 0;
    //TODO: da implementare
    fp = fopen(nome_file_rider, "r");
    if (fp == NULL) {
        printf("Errore allocazione memoria");
        return -1;
    }

    while (fscanf(fp, "%s %s %s", rider.codice_rider, rider.nome, zona_str) == 3) {
        rider.zona = string_to_zona(zona_str);
        rider.ordini.primo = NULL;
        rider.ordini.ultimo = NULL;

        if (rider.zona == ZONA_SCONOSCIUTA) {
            fclose(fp);
            return -1;
        }

        if (!aggiungi_rider(lista, rider)) {
            fclose(fp);
            return -1;
        }
    }
    fclose(fp);

    fp = fopen(nome_file_ordini, "r");
    if (fp == NULL) {
        printf("Errore allocazione memoria");
        return -1;
    }

    char codice_rider[COD_LEN];
    char stato[STR_LEN];
    ordine_t ordine;
    rider_t* rider_trovato;

    while (fscanf(fp, "%s %s %s %f %s", codice_rider, ordine.id_ordine, ordine.codice_cliente, &ordine.importo, stato)) {
        ordine.stato = string_to_stato(stato);

        if (ordine.stato == STATO_SCONOSCIUTO) {
            fclose(fp);
            return -1;
        }

        rider_trovato = cerca_rider_codice(*lista, codice_rider);

        if (rider_trovato == NULL) {
            fclose(fp);
            return -1;
        }

        if (!aggiungi_ordine_a_rider(&rider_trovato->ordini, ordine)) {
            fclose(fp);
            return -1;
        }

        totale_ordini++;
    }
    fclose(fp);
    return totale_ordini;
}


/*
 * Quesito 2b
 * Data una zona della città, stampare a video tutti gli ordini non ancora consegnati.
 *
 * Parametri in ingresso:
 * - lista: puntatore alla lista dei rider
 * - zona: zona della cità per cui cercare
 *
 * Valore di ritorno:
 * void
 *
*/
void stampa_ordini_da_consegnare(ListaRider* lista, zona_t zona) {

    //TODO: da completare
    NodoRider* aux_rider = *lista;
    NodoOrdine *aux_ordine;

    while (aux_rider != NULL) {
        if (aux_rider->info.zona == zona) {
            aux_ordine = aux_rider->info.ordini.primo;

            while (aux_ordine != NULL) {
                if (aux_ordine->info.stato != CONSEGNATO) {
                    printf("\nRider: %s - %s | Ordine: %s | Cliente: %s | Importo: %.2f | Stato: %s",
                           aux_rider->info.codice_rider,
                           aux_rider->info.nome,
                           aux_ordine->info.id_ordine,
                           aux_ordine->info.codice_cliente,
                           aux_ordine->info.importo,
                           stato_to_string(aux_ordine->info.stato));
                }
                aux_ordine = aux_ordine->next;
            }
        }
        aux_rider = aux_rider->next;
    }
}

/*
 * Quesito 2c
 * Restituisce il guadagno totale per rider (somma di tutti gli ordini assegnati), tramite
 * un vettore allocato dinamicamente (un elemento del vettore per ogni rider della lista).
 *
 * Parametri in ingresso:
 * - lista: lista di rider
 *
 * Parametri in uscita:
 * - dim: dimensione del vettore allocato
 *
 * Valore di ritorno:
 * puntare al vettore allocato
*/

float* totale_per_rider(ListaRider lista, int* dim) {

    //TODO: da completare
    *dim = 0;
    int i = 0;
    NodoRider* aux_rider = lista;
    NodoOrdine *aux_ordine;
    float *vettore;

    while (aux_rider != NULL) {
        (*dim)++;
        aux_rider = aux_rider->next;
    }

    if (*dim == 0) {
        return NULL;
    }

    vettore = (float*) malloc((*dim) * sizeof(float));
    if (vettore == NULL) {
        printf("Errore allocazione memoria");
        *dim = 0;
        return NULL;
    }

    aux_rider = lista;
    while (aux_rider != NULL) {
        vettore[i] = 0;
        aux_ordine = aux_rider->info.ordini.primo;
        while (aux_ordine != NULL) {
            vettore[i] += aux_ordine->info.importo;
            aux_ordine = aux_ordine->next;
        }
        i++;
        aux_rider = aux_rider->next;
    }

    return vettore;
}


/* struttura dati albero */
typedef struct {
    char codice_cliente[STR_LEN];
    unsigned int numero_ordini;
    float importo_totale;
}cliente_t;

typedef struct nodo_cliente {
    cliente_t cliente;
    struct nodo_cliente* left;
    struct nodo_cliente* right;
}NodoAlbero;
typedef NodoAlbero* Albero;


/* inizializza ABR */
void init_albero(Albero * a) {
    *a = NULL;
}

/* Inserisce un nuovo nodo nell ABR */
Albero inserisci_nodo(Albero radice, cliente_t c) {
    if (radice == NULL) {
        NodoAlbero * nuovo = (NodoAlbero*)malloc(sizeof(NodoAlbero));
        if (nuovo == NULL) {
            printf("Errore allocazione memoria.");
            return NULL;
        }
        nuovo->cliente = c;
        nuovo->left = nuovo->right = NULL;
        return nuovo;
    }
    if (strcmp(radice->cliente.codice_cliente, c.codice_cliente) > 0)
        radice->left = inserisci_nodo(radice->left, c);
    else if (strcmp(radice->cliente.codice_cliente, c.codice_cliente) < 0)
        radice->right = inserisci_nodo(radice->right, c);
    return radice;
}

/* Cerca un nodo nell'ABR per codice_cliente
 *
 * Parametri in ingresso:
 * - a: Albero
 * - codice_cliente: stringa codice cliente da ricercare
 *
 * Valore di ritorno:
 * puntatore al cliente se trovato, NULL altrimenti
 */
cliente_t* cerca_cliente_ABR(Albero a, char* codice_cliente) {
while (a) { int cmp=strcmp(codice_cliente,a->cliente.codice_cliente);
        if (!cmp) return &a->cliente;
        a=cmp<0 ? a->left : a->right;
    } return NULL;
}


/* Quesito 2d
 * Creare un albero binario di ricerca ordinato per codice_cliente, in cui per ogni cliente viene memorizzato il numero
 * di ordini effettuati e il totale degli importi.
 *
 * Parametri in ingresso:
 * -lista: puntatore alla lista dei rider
 *
 * valore di ritorno:
 * puntatore all'albero di ricerca creato
 */
Albero crea_albero_clienti(ListaRider* lista) {
Albero a=NULL;
    for (NodoRider *r=*lista; r; r=r->next) for (NodoOrdine *o=r->info.ordini.primo; o; o=o->next) {
        cliente_t *c=cerca_cliente_ABR(a,o->info.codice_cliente);
        if (c) { ++c->numero_ordini; c->importo_totale+=o->info.importo; }
        else { cliente_t nuovo={0}; strcpy(nuovo.codice_cliente,o->info.codice_cliente); nuovo.numero_ordini=1; nuovo.importo_totale=o->info.importo; a=inserisci_nodo(a,nuovo); }
    } return a;
}


/* Quesito 2e
 * Salva in un file di testo tutti i clienti che hanno effettuato più di un ordine, ordinati per codice cliente.
 *
 * Parametri in ingresso:
 * - a: albero di ricerca
 * - f_out: puntatore al file di output
 */
void salva_albero_file(Albero a, FILE* f_out) {
    //TODO: da completare
    if (a == NULL) {
        return;
    }

    salva_albero_file(a->left, f_out);

    if (a->cliente.numero_ordini > 1) {
        fprintf(f_out, "%s %u %.2f", a->cliente.codice_cliente, a->cliente.numero_ordini, a->cliente.importo_totale);

    }

    salva_albero_file(a->right, f_out);
}




/* Quesito 2f
 * Deallocare tutte le strutture dati allocate dinamicamente
 */

/* Dealloca la memoria allocata per la lista di code
 *
 * Parametri in ingresso:
 * - lista: puntatore alla lista dei rider
 */
void dealloca_lista(ListaRider* lista) {
    //TODO: da completare
    NodoRider *aux_rider;
    NodoOrdine *aux_ordine;

    while (*lista != NULL) {
        aux_rider = *lista;
        *lista = (*lista)->next;
        while (aux_rider->info.ordini.primo != NULL) {
            aux_ordine = aux_rider->info.ordini.primo;
            aux_rider->info.ordini.primo = aux_rider->info.ordini.primo->next;
            free(aux_ordine);
        }
        free(aux_rider);
    }
}

/* Dealloca la memoria allocata per l'ABR
 *
 * Parametri in ingresso:
 * - a: ABR da deallocare
 *
 */
void dealloca_ABR(Albero* a) {
    //TODO: da completare
    if (*a == NULL) {
        return;
    }

    dealloca_ABR(&(*a)->left);
    dealloca_ABR(&(*a)->right);
    free(*a);
    *a = NULL;
}



unsigned menu() {
    unsigned scelta;
    printf("\n **** MENU **** \n"
           "1. Carica da file\n"
           "2. Stampa ordini non consegnati\n"
           "3. Totale ordini per rider\n"
           "4. Crea ABR\n"
           "5. Salva clienti su file\n"
           "0. Esci\n"
           "\tSCELTA: ");
    fflush(stdout);
    scanf("%u", &scelta);
    return scelta;
}





int main() {
    ListaRider lista = NULL;
    int numero_rider = 0;
    int numero_ordini;
    unsigned scelta;
    float * vettore_guadagni = NULL;
    Albero albero = NULL;
    FILE* f_out;


    do {
        scelta = menu();

        switch (scelta) {
            case 1:
                if (lista != NULL)
                    dealloca_lista(&lista);
                numero_ordini = carica_dati(FILE_RIDER, FILE_ORDINI, &lista);
                printf("Caricate %d ordini.", numero_ordini);
                break;
            case 2:;
                int zona;
                do {
                    printf("\nInserisci zona [%d: CENTRO/%d: PERIFERIA/%d: HINTERLAND]: ", CENTRO, PERIFERIA, HINTERLAND);
                    scanf("%d",&zona);
                }while (zona < CENTRO || zona > HINTERLAND);
                stampa_ordini_da_consegnare(&lista, (zona_t) zona);
                break;
            case 3: {
                int dim=0;
                float *guadagni=totale_per_rider(lista,&dim);
                if (guadagni) { for (int i=0;i<dim;++i) printf("Rider %d: %.2f\n",i,guadagni[i]); free(guadagni); }
                break;
            }
            case 4:
                dealloca_ABR(&albero);
                albero = crea_albero_clienti(&lista);
                printf("Albero creato");
                break;
            case 5:
                f_out = fopen(FILE_OUT, "w");
                if (f_out == NULL) {
                    printf("errore apertura file");
                    break;
                }
                salva_albero_file(albero, f_out);
                fclose(f_out);
                printf("File salvato");
                break;
            case 0:
                printf("EXIT");
                break;
            default:
                printf("Scelta non valida");
        }
    } while (scelta != 0);

    //Deallocazione memoria
    //TODO: da completare


    dealloca_lista(&lista);
    dealloca_ABR(&albero);
    return 0;
}

