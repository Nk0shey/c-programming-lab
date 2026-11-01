/*
 * Simulazione M2 - Fondamenti di Programmazione
 * Prova al calcolatore - Strutture dati lineari
 *
 * Argomenti allenati:
 * - file testuali
 * - liste collegate
 * - vettori dinamici
 * - pile
 * - code
 * - ordinamento di vettori
 *
 * NOTA:
 * Il codice base e' gia' scritto.
 * Le funzioni contrassegnate con TODO sono da completare.
 *
 * Standard: ANSI C / C90 friendly
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODICE 16
#define MAX_NOME 32
#define MAX_STATO 20
#define OK 1
#define KO 0

/* ============================================================
 * TIPO BASE
 * ============================================================ */

typedef struct {
    char codice[MAX_CODICE];
    char mittente[MAX_NOME];
    char destinatario[MAX_NOME];
    float peso;
    char stato[MAX_STATO]; /* "attesa" oppure "consegnata" */
} Spedizione;

/* ============================================================
 * LISTA COLLEGATA DI SPEDIZIONI
 * ============================================================ */

typedef struct nodo_spedizione {
    Spedizione info;
    struct nodo_spedizione* next;
} NodoSpedizione;

typedef NodoSpedizione* ListaSpedizioni;

void init_lista(ListaSpedizioni* pl) {
    *pl = NULL;
}

int lista_vuota(ListaSpedizioni l) {
    return l == NULL;
}

void stampa_spedizione(Spedizione s) {
    printf("%s %s %s %.2f %s\n",
           s.codice,
           s.mittente,
           s.destinatario,
           s.peso,
           s.stato);
}

void stampa_lista(ListaSpedizioni l) {
    while (l != NULL) {
        stampa_spedizione(l->info);
        l = l->next;
    }
}

int inserisci_testa(ListaSpedizioni* pl, Spedizione s) {
    NodoSpedizione* nuovo;

    nuovo = (NodoSpedizione*) malloc(sizeof(NodoSpedizione));
    if (nuovo == NULL) {
        return KO;
    }

    nuovo->info = s;
    nuovo->next = *pl;
    *pl = nuovo;

    return OK;
}

int inserisci_coda_lista(ListaSpedizioni* pl, Spedizione s) {
    NodoSpedizione* nuovo;
    NodoSpedizione* aux;

    nuovo = (NodoSpedizione*) malloc(sizeof(NodoSpedizione));
    if (nuovo == NULL) {
        return KO;
    }

    nuovo->info = s;
    nuovo->next = NULL;

    if (*pl == NULL) {
        *pl = nuovo;
        return OK;
    }

    aux = *pl;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = nuovo;

    return OK;
}

int conta_lista(ListaSpedizioni l) {
    int count;
    count = 0;

    while (l != NULL) {
        count++;
        l = l->next;
    }

    return count;
}

void cancella_lista(ListaSpedizioni* pl) {
    NodoSpedizione* aux;

    while (*pl != NULL) {
        aux = *pl;
        *pl = (*pl)->next;
        free(aux);
    }
}

/* Cerca una spedizione per codice. Restituisce 1 se trovata, 0 altrimenti. */
int cerca_spedizione(ListaSpedizioni l, char* codice, Spedizione* out) {
    while (l != NULL) {
        if (strcmp(l->info.codice, codice) == 0) {
            *out = l->info;
            return OK;
        }
        l = l->next;
    }
    return KO;
}

/* ============================================================
 * PILA COLLEGATA DI OPERAZIONI
 * ============================================================ */

typedef struct {
    char operazione[20];
    Spedizione spedizione;
} Operazione;

typedef struct nodo_pila {
    Operazione info;
    struct nodo_pila* next;
} NodoPila;

typedef NodoPila* PilaOperazioni;

void init_pila(PilaOperazioni* pp) {
    *pp = NULL;
}

int pila_vuota(PilaOperazioni p) {
    return p == NULL;
}

int push(PilaOperazioni* pp, Operazione op) {
    NodoPila* nuovo;

    nuovo = (NodoPila*) malloc(sizeof(NodoPila));
    if (nuovo == NULL) {
        return KO;
    }

    nuovo->info = op;
    nuovo->next = *pp;
    *pp = nuovo;

    return OK;
}

int pop(PilaOperazioni* pp, Operazione* op) {
    NodoPila* aux;

    if (*pp == NULL) {
        return KO;
    }

    aux = *pp;
    *op = aux->info;
    *pp = (*pp)->next;
    free(aux);

    return OK;
}

void cancella_pila(PilaOperazioni* pp) {
    Operazione op;
    while (pop(pp, &op) == OK) {
        /* svuota la pila */
    }
}

void stampa_pila_svuotando(PilaOperazioni* pp) {
    Operazione op;

    while (pop(pp, &op) == OK) {
        printf("%s -> ", op.operazione);
        stampa_spedizione(op.spedizione);
    }
}

/* ============================================================
 * CODA COLLEGATA DI SPEDIZIONI
 * ============================================================ */

typedef struct nodo_coda {
    Spedizione info;
    struct nodo_coda* next;
} NodoCoda;

typedef struct {
    NodoCoda* primo;
    NodoCoda* ultimo;
} CodaSpedizioni;

void init_coda(CodaSpedizioni* pc) {
    pc->primo = NULL;
    pc->ultimo = NULL;
}

int coda_vuota(CodaSpedizioni c) {
    return c.primo == NULL;
}

int in_coda(CodaSpedizioni* pc, Spedizione s) {
    NodoCoda* nuovo;

    nuovo = (NodoCoda*) malloc(sizeof(NodoCoda));
    if (nuovo == NULL) {
        return KO;
    }

    nuovo->info = s;
    nuovo->next = NULL;

    if (pc->primo == NULL) {
        pc->primo = nuovo;
        pc->ultimo = nuovo;
    } else {
        pc->ultimo->next = nuovo;
        pc->ultimo = nuovo;
    }

    return OK;
}

int out_coda(CodaSpedizioni* pc, Spedizione* s) {
    NodoCoda* aux;

    if (pc->primo == NULL) {
        return KO;
    }

    aux = pc->primo;
    *s = aux->info;
    pc->primo = pc->primo->next;

    if (pc->primo == NULL) {
        pc->ultimo = NULL;
    }

    free(aux);
    return OK;
}

void cancella_coda(CodaSpedizioni* pc) {
    Spedizione s;
    while (out_coda(pc, &s) == OK) {
        /* svuota la coda */
    }
}

void stampa_coda_senza_modificare(CodaSpedizioni c) {
    NodoCoda* aux;
    aux = c.primo;

    while (aux != NULL) {
        stampa_spedizione(aux->info);
        aux = aux->next;
    }
}

/* ============================================================
 * FUNZIONI DI SUPPORTO GIA' IMPLEMENTATE
 * ============================================================ */

void scambia_spedizioni(Spedizione* a, Spedizione* b) {
    Spedizione tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void stampa_vettore(Spedizione* v, int dim) {
    int i;

    if (v == NULL || dim <= 0) {
        printf("Vettore vuoto.\n");
        return;
    }

    for (i = 0; i < dim; i++) {
        stampa_spedizione(v[i]);
    }
}

/* ============================================================
 * QUESITI DA COMPLETARE
 * ============================================================ */

/*
 * Quesito 1
 * Carica i dati dal file e separa le spedizioni in due liste:
 * - attesa
 * - consegnate
 *
 * Formato file:
 * codice mittente destinatario peso stato
 *
 * Esempio:
 * S01 Marco Anna 3.5 attesa
 * S02 Luca Sara 2.0 consegnata
 *
 * Valore di ritorno:
 * - numero di spedizioni caricate correttamente
 * - 0 se il file non puo' essere aperto
 */
int carica_spedizioni(char* nome_file,
                      ListaSpedizioni* attesa,
                      ListaSpedizioni* consegnate) {
    /* TODO 1:
     * 1. aprire il file in lettura
     * 2. leggere una Spedizione alla volta con fscanf
     * 3. se stato == "attesa", inserirla nella lista attesa
     * 4. se stato == "consegnata", inserirla nella lista consegnate
     * 5. contare quante spedizioni sono state caricate
     * 6. chiudere il file
     */

    int num_spedizioni = 0;
    Spedizione s;

    FILE *fp = fopen(nome_file, "r");
    if (fp == NULL) {
        printf("Errore\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s %f %s", s.codice, s.mittente, s.destinatario, &s.peso, s.stato) == 5) {
        if (strcmp(s.stato, "attesa")) {
            if (inserisci_coda_lista(attesa, s) == OK) {
                num_spedizioni++;
            }
        }
        else if (strcmp(s.stato, "consegnate")) {
            if (inserisci_coda_lista(consegnate, s) == OK) {
                num_spedizioni++;
            }
        }
    }
    fclose(fp);
    return num_spedizioni;
}

/*
 * Quesito 2
 * Conta le spedizioni nella lista attesa con peso maggiore della soglia.
 */
int conta_pesanti(ListaSpedizioni attesa, float soglia) {
    /* TODO 2:
     * Scorrere la lista e contare gli elementi con peso > soglia.
     */

    int count = 0;

    while (attesa != NULL) {
        if (attesa->info.peso > soglia) {
            count++;
        }
        attesa = attesa->next;
    }
    return count;
}

/*
 * Quesito 3
 * Crea un vettore dinamico contenente solo le spedizioni in attesa
 * con peso maggiore della soglia.
 *
 * Parametri:
 * - attesa: lista da cui estrarre i dati
 * - soglia: peso minimo escluso
 * - dim: parametro di output per restituire la dimensione del vettore
 *
 * Valore di ritorno:
 * - puntatore al vettore allocato dinamicamente
 * - NULL se non ci sono elementi o se malloc fallisce
 */
Spedizione* crea_vettore_pesanti(ListaSpedizioni attesa,
                                 float soglia,
                                 int* dim) {
    /* TODO 3:
     * 1. usare conta_pesanti
     * 2. se count == 0: *dim = 0; return NULL;
     * 3. allocare un vettore dinamico di count Spedizione
     * 4. secondo passaggio sulla lista per copiare gli elementi validi
     * 5. assegnare *dim = count
     * 6. restituire il vettore
     */

    Spedizione* vettore;
    int count;
    int i = 0;

    count = conta_pesanti(attesa, soglia);
    if (count == 0) {
        *dim = 0;
        return NULL;
    }

    vettore = (Spedizione*) malloc(sizeof(Spedizione));
    if (vettore == NULL) {
        printf("Errore\n");
        *dim = 0;
        return NULL;
    }

    while (attesa != NULL) {
        if (attesa->info.peso > soglia) {
            vettore[i] = attesa->info;
            i++;
        }
        attesa = attesa->next;
    }
    *dim = count;
    return vettore;
}

/*
 * Quesito 4
 * Ordina il vettore per peso decrescente.
 * Se due spedizioni hanno lo stesso peso, ordina per codice crescente.
 *
 * Suggerimento: usare insertion sort.
 */
void ordina_per_peso_decrescente(Spedizione* v, int dim) {
    /* TODO 4:
     * Implementare un insertion sort oppure bubble sort.
     * Criterio:
     * - peso maggiore prima
     * - a parita' di peso, codice alfabeticamente crescente
     */

    int i, j;
    Spedizione key;

    if (v == NULL || dim <= 1) {
        return;
    }

    for (i = 0; i < dim; i++) {
        key = v[i];
        j = i - 1;
        while (j>=0 && (v[j].peso < key.peso || (v[j].peso == key.peso && strcmp(v[j].codice, key.codice) > 0))) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}

/*
 * Quesito 5
 * Crea una coda contenente tutte le spedizioni della lista attesa.
 * L'ordine nella coda deve rispettare l'ordine della lista.
 *
 * Valore di ritorno:
 * - numero di spedizioni inserite in coda
 */
int crea_coda_consegne(ListaSpedizioni attesa, CodaSpedizioni* coda) {
    /* TODO 5:
     * 1. inizializzare la coda
     * 2. scorrere la lista attesa
     * 3. inserire ogni spedizione nella coda
     * 4. restituire il numero di elementi inseriti
     */

    init_coda(coda);
    int count = 0;

    while (attesa != NULL) {
        if (in_coda(coda, attesa->info) == OK) {
            count++;
        }
        attesa = attesa->next;
    }

    return count;
}

/*
 * Quesito 6
 * Evade al massimo n spedizioni dalla coda.
 * Ogni spedizione estratta dalla coda viene marcata come "consegnata"
 * e inserita nella lista consegnate.
 * Ogni operazione viene salvata nella pila storico.
 *
 * Valore di ritorno:
 * - numero di spedizioni effettivamente evase
 */
int evadi_consegne(CodaSpedizioni* coda,
                   ListaSpedizioni* consegnate,
                   PilaOperazioni* storico,
                   int n) {
    /* TODO 6:
     * 1. ripetere finche' i < n e la coda non e' vuota
     * 2. estrarre una spedizione dalla coda con out_coda
     * 3. cambiare stato in "consegnata"
     * 4. inserirla nella lista consegnate
     * 5. creare una Operazione con operazione = "EVASA"
     * 6. fare push nello storico
     * 7. restituire quante spedizioni sono state evase
     */

    Spedizione s;
    Operazione op;
    int count = 0;

    while (count < n && out_coda(coda, &s) == OK) {

        strcpy(s.stato, "consegnata");

        if (inserisci_coda_lista(consegnate, s) == OK) {
            strcpy(s.stato, "EVASA");
            op.spedizione = s;
            push(storico, op);
            count++;
        }
    }

    return count;
}

/*
 * Quesito 7
 * Estrae da una lista la spedizione con un certo codice.
 * La funzione deve rimuovere fisicamente il nodo dalla lista e restituire
 * la spedizione estratta tramite parametro di output.
 *
 * Valore di ritorno:
 * - 1 se trovata ed estratta
 * - 0 altrimenti
 */
int estrai_spedizione_by_codice(ListaSpedizioni* pl,
                                char* codice,
                                Spedizione* out) {
    /* TODO 7:
     * Gestire tre casi:
     * 1. lista vuota
     * 2. elemento da estrarre in testa
     * 3. elemento da estrarre in mezzo o in fondo
     *
     * Suggerimento:
     * NodoSpedizione* precedente;
     * NodoSpedizione* corrente;
     */

    NodoSpedizione* precedente;
    NodoSpedizione* corrente;

    if (*pl == NULL) {
        return 0;
    }

    if (strcmp((*pl)->info.codice, codice) == 0) {
        corrente = (*pl);
        *out = corrente->info;
        *pl = corrente->next;
        free(corrente);
        return OK;
    }

    precedente = (*pl);
    corrente = (*pl)->next;
    while (corrente != NULL) {
        if (strcmp(corrente->info.codice, codice) == 0) {
            *out = corrente->info;
            precedente->next = corrente->next;
            free(corrente);
            return OK;
        }

        precedente = corrente;
        corrente = corrente->next;
    }

    return OK;
}

/*
 * Quesito 8
 * Salva una lista di spedizioni su file.
 *
 * Formato output:
 * codice mittente destinatario peso stato
 *
 * Valore di ritorno:
 * - numero di righe scritte
 * - 0 se il file non puo' essere aperto
 */
int salva_lista_su_file(char* nome_file, ListaSpedizioni lista) {
    /* TODO 8:
     * 1. aprire file in scrittura
     * 2. scorrere la lista
     * 3. scrivere ogni spedizione con fprintf
     * 4. chiudere il file
     */
    int count = 0;

    FILE *fp = fopen(nome_file, "w");
    if (fp == NULL) {
        printf("Errore\n");
        return 0;
    }

    while (lista != NULL) {
        fprintf(fp, "%s %s %s %.2f %s", lista->info.codice, lista->info.mittente, lista->info.destinatario, lista->info.peso, lista->info.stato);
        count++;
        lista = lista->next;
    }
    fclose(fp);
    return count;
}

/*
 * Quesito 9
 * Costruisce un vettore di liste in base alla prima lettera del destinatario.
 * Il vettore ha dimensione 26:
 * - indice 0: destinatari che iniziano con A/a
 * - indice 1: destinatari che iniziano con B/b
 * - ...
 * - indice 25: destinatari che iniziano con Z/z
 *
 * Nota: considerare solo lettere alfabetiche A-Z / a-z.
 * Le altre iniziali possono essere ignorate.
 */
void distribuisci_per_destinatario(ListaSpedizioni lista,
                                   ListaSpedizioni vett[26]) {
    /* TODO 9:
     * 1. inizializzare tutte le liste del vettore a NULL
     * 2. scorrere la lista di input
     * 3. calcolare indice dalla prima lettera del destinatario
     * 4. inserire la spedizione nella lista vett[indice]
     */

    int i, indice;
    char iniziale;

    for (i = 0; i < 26; i++) {
        init_lista(&vett[i]);
    }

    while (lista != NULL) {
        iniziale = lista->info.destinatario[0];

        if (iniziale >= 'A' && iniziale <= 'Z') {
            indice = iniziale - 'A';
            inserisci_coda_lista(&vett[indice], lista->info);
        } else if (iniziale >= 'a' && iniziale <= 'z') {
            indice = iniziale - 'a';
            inserisci_coda_lista(&vett[indice], lista->info);
        }
        lista = lista->next;
    }
}

/*
 * Quesito 10
 * Libera tutte le liste contenute nel vettore di liste.
 */
void cancella_vettore_liste(ListaSpedizioni vett[26]) {
    /* TODO 10:
     * Ciclo da 0 a 25 e chiamata a cancella_lista su ogni cella.
     */

    for (int i = 0; i < 26; i++) {
        cancella_lista(&vett[i]);
    }
}

/* ============================================================
 * MAIN DI TEST
 * ============================================================ */

int main(void) {
    ListaSpedizioni attesa;
    ListaSpedizioni consegnate;
    ListaSpedizioni vett_liste[26];
    CodaSpedizioni coda;
    PilaOperazioni storico;
    Spedizione* pesanti;
    int dim_pesanti;
    int caricati;
    int inseriti_coda;
    int evase;
    float soglia;

    init_lista(&attesa);
    init_lista(&consegnate);
    init_coda(&coda);
    init_pila(&storico);

    printf("=== SIMULAZIONE M2 STRUTTURE LINEARI ===\n\n");

    caricati = carica_spedizioni("spedizioni.txt", &attesa, &consegnate);
    printf("Spedizioni caricate: %d\n\n", caricati);

    printf("--- Lista attesa ---\n");
    stampa_lista(attesa);

    printf("\n--- Lista consegnate ---\n");
    stampa_lista(consegnate);

    soglia = 3.0f;
    pesanti = crea_vettore_pesanti(attesa, soglia, &dim_pesanti);

    printf("\n--- Vettore spedizioni in attesa con peso > %.2f ---\n", soglia);
    stampa_vettore(pesanti, dim_pesanti);

    ordina_per_peso_decrescente(pesanti, dim_pesanti);
    printf("\n--- Vettore ordinato per peso decrescente ---\n");
    stampa_vettore(pesanti, dim_pesanti);

    inseriti_coda = crea_coda_consegne(attesa, &coda);
    printf("\nSpedizioni inserite nella coda consegne: %d\n", inseriti_coda);
    printf("--- Coda consegne ---\n");
    stampa_coda_senza_modificare(coda);

    evase = evadi_consegne(&coda, &consegnate, &storico, 2);
    printf("\nSpedizioni evase: %d\n", evase);

    printf("\n--- Lista consegnate aggiornata ---\n");
    stampa_lista(consegnate);

    printf("\n--- Storico operazioni, dalla piu' recente alla meno recente ---\n");
    stampa_pila_svuotando(&storico);

    distribuisci_per_destinatario(consegnate, vett_liste);
    salva_lista_su_file("consegnate_out.txt", consegnate);
    cancella_vettore_liste(vett_liste);

    free(pesanti);
    cancella_lista(&attesa);
    cancella_lista(&consegnate);
    cancella_coda(&coda);
    cancella_pila(&storico);

    return 0;
}
