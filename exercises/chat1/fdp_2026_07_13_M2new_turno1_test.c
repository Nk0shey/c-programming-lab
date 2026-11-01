/******************************************************************************
=== MODULO 2 ===
Appello di Fondamenti di Programmazione - A.A. 2025/26
Tempo: 120 minuti

Implementare in C un programma per analizzare i log di accensione e
spegnimento di un insieme di dispositivi.

I dispositivi devono essere memorizzati in una lista collegata. Ogni nodo
della lista contiene i dati del dispositivo e una coda FIFO degli eventi
associati a quel dispositivo.

Il programma deve implementare le seguenti funzionalita':

1. Caricare i dispositivi dal file dispositivi.txt e gli eventi dal file
  eventi.txt, costruendo una lista di dispositivi, ognuno con la propria
  coda di eventi.

2. Cercare il primo evento di spegnimento successivo a un evento di accensione all'interno della coda di eventi di un dispositivo.

3. Produrre un vettore dinamico contenente le statistiche relative ai periodi
  di accensione-spegnimento.

4. Salvare le statistiche relative ai periodi di accensione-spegnimento su file,
  se corrispondono ad un certo filtro.


*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DISPOSITIVI "dispositivi.txt"
#define FILE_EVENTI      "eventi.txt"
#define FILE_OUTPUT      "statistiche_periodi.txt"

#define STR_LEN     50
#define COD_LEN     16
#define ORARIO_LEN  6

#define OK                0
#define ERRORE_FILE       (-1)
#define ERRORE_MEMORIA    (-2)
#define ERRORE_PARAMETRI  (-3)
#define ERRORE_DATI       (-4)


typedef enum {
    STATO_SCONOSCIUTO = -1,
    ACCESO,
    SPENTO
} stato_t;

typedef struct {
    char id_evento[COD_LEN];
    char orario[ORARIO_LEN];
    stato_t stato;
} evento_t;

typedef struct nodo_evento {
    evento_t info;
    struct nodo_evento *next;
} nodo_evento_t;


typedef struct {
    nodo_evento_t *primo;
    nodo_evento_t *ultimo;
} coda_eventi_t;


typedef struct {
    char id_dispositivo[COD_LEN];
    char nome[STR_LEN];
    float potenza_kw;
    coda_eventi_t eventi;
} dispositivo_t;

typedef struct nodo_dispositivo {
    dispositivo_t info;
    struct nodo_dispositivo *next;
} nodo_dispositivo_t;

typedef nodo_dispositivo_t *lista_dispositivi_t;

/* Record prodotto dal filtro sui consumi.
   Ogni elemento statistica_t deve contenere:
   - identificativo del dispositivo;
   - nome del dispositivo;
   - orario di accensione;
   - orario di spegnimento;
   - durata del periodo in minuti;
   - consumo del periodo in kWh.
 */
typedef struct {
    char id_dispositivo[COD_LEN], nome[STR_LEN];
    char accensione[ORARIO_LEN], spegnimento[ORARIO_LEN];
    int minuti;
    double consumo;
} statistica_t;


/* ============================================================================
   FUNZIONI GIA' FORNITE
   ========================================================================== */

/* Data una stringa di stato, restituisce il valore dell'enum corrispondente */
stato_t string_to_stato(const char s[]) {
    if (s == NULL) return STATO_SCONOSCIUTO;
    if (strcmp(s, "ACCESO") == 0) return ACCESO;
    if (strcmp(s, "SPENTO") == 0) return SPENTO;
    return STATO_SCONOSCIUTO;
}

/* Dato uno stato_t, restituisce la stringa corrispondente */
const char *stato_to_string(stato_t stato) {
    switch (stato) {
        case ACCESO: return "ACCESO";
        case SPENTO: return "SPENTO";
        default: return "SCONOSCIUTO";
    }
}

/* Funzione ausiliaria che permette di calcolare
 * la differenza (in minuti) tra due orari
 *
 * Parametri in ingresso:
 * - inizio: orario di partenza
 * - fine: orario di arrivo
 * Return:
 * - differenza in minuti tra i due orari
 * */
int differenza_minuti(const char inizio[], const char fine[]) {
int h1,m1,h2,m2;
    if (sscanf(inizio,"%d:%d",&h1,&m1)!=2 || sscanf(fine,"%d:%d",&h2,&m2)!=2 || h1<0 || h1>23 || h2<0 || h2>23 || m1<0 || m1>59 || m2<0 || m2>59) return -1;
    int d=(h2-h1)*60+m2-m1; return d<0 ? d+1440 : d;
}

/* Data una coda per indirizzo, la inizializza */
void coda_init(coda_eventi_t *coda) {
    if (coda == NULL) return;
    coda->primo = NULL;
    coda->ultimo = NULL;
}

/* Dato un evento, lo inserisce nella una coda
   passata per indirizzo.

   Restituisce OK se l'inserimento e' avvenuto correttamente,
    altrimenti un codice di errore.
   */
int accoda_evento(coda_eventi_t *coda, evento_t evento) {
    nodo_evento_t *nuovo;

    if (coda == NULL) return ERRORE_PARAMETRI;

    nuovo = malloc(sizeof(nodo_evento_t));
    if (nuovo == NULL) return ERRORE_MEMORIA;

    nuovo->info = evento;
    nuovo->next = NULL;

    if (coda->ultimo != NULL) {
        coda->ultimo->next = nuovo;
    } else {
        coda->primo = nuovo;
    }

    coda->ultimo = nuovo;
    return OK;
}

/* Aggiunge un dispositivo in testa alla lista passata per indirizzo

    Restituisce OK se l'inserimento e' avvenuto correttamente,
    altrimenti un codice di errore.
*/
int aggiungi_dispositivo_testa(lista_dispositivi_t *lista, dispositivo_t dispositivo) {
    nodo_dispositivo_t *nuovo;

    if (lista == NULL) return ERRORE_PARAMETRI;

    nuovo = malloc(sizeof(nodo_dispositivo_t));
    if (nuovo == NULL) return ERRORE_MEMORIA;

    nuovo->info = dispositivo;
    nuovo->next = *lista;
    *lista = nuovo;

    return OK;
}


/*
   Cerca un dispositivo per id e lo restituisce per indirizzo.
   Se non trovato, restituisce NULL.
*/
dispositivo_t *cerca_dispositivo(lista_dispositivi_t lista, const char id_dispositivo[]) {
    nodo_dispositivo_t *p = lista;

    while (p != NULL) {
        if (strcmp(p->info.id_dispositivo, id_dispositivo) == 0) {
            return &p->info;
        }
        p = p->next;
    }

    return NULL;
}

void stampa_evento(evento_t e) {
    printf("%s %s %s\n", e.id_evento, e.orario, stato_to_string(e.stato));
}
void stampa_coda(coda_eventi_t coda) {
    nodo_evento_t *p = coda.primo;
    while (p != NULL) {
        printf("\t- ");
        stampa_evento(p->info);
        p = p->next;
    }
}
void stampa_lista(lista_dispositivi_t lista) {
    nodo_dispositivo_t *p = lista;
    while (p != NULL) {
        printf("%s %s %.2fkW\n", p->info.id_dispositivo, p->info.nome, p->info.potenza_kw);
        stampa_coda(p->info.eventi);
        p = p->next;
    }
}
/* Dato un array di statistiche, le stampa */
void stampa_statistiche(statistica_t v[], int dim) {
for (int i=0;i<dim;++i) printf("%s %s-%s %s minuti=%d consumo=%.3f kWh\n",v[i].id_dispositivo,v[i].accensione,v[i].spegnimento,v[i].nome,v[i].minuti,v[i].consumo);
}

/* Dealloca una coda di eventi (fornita per indirizzo) */
void dealloca_coda(coda_eventi_t *coda) {
    if (coda == NULL) return;

    while (coda->primo != NULL) {
        nodo_evento_t *tmp = coda->primo;
        coda->primo = coda->primo->next;
        free(tmp);
    }

    coda->ultimo = NULL;
}

/* Dealloca una lista di dispositivi (fornita per indirizzo) */
void dealloca_dispositivi(lista_dispositivi_t *lista) {
    if (lista == NULL) return;

    while (*lista != NULL) {
        nodo_dispositivo_t *tmp = *lista;
        *lista = (*lista)->next;
        dealloca_coda(&tmp->info.eventi);
        free(tmp);
    }
}


/* ============================================================================
   QUESITO 1 - CARICAMENTO DA DUE FILE
   ========================================================================== */

/*
   Carica i dispositivi dal primo file e gli eventi dal secondo file.
   I dati sono distribuiti su due file:

   1) dispositivi.txt
      Contiene l'elenco dei dispositivi da monitorare, uno per riga:

          id_dispositivo nome potenza_kw

      Esempio:

          D01 ServerA 1.20
          D02 RouterLab 0.35
          D03 Stampante3D 2.10

   2) eventi.txt
      Contiene gli eventi di accensione/spegnimento, uno per riga:

          id_dispositivo id_evento orario stato

      dove stato puo' assumere i valori ACCESO oppure SPENTO.

      Esempio:

          D01 E001 08:00 ACCESO
          D02 E002 08:10 ACCESO
          D01 E003 09:30 SPENTO
          D03 E004 10:00 ACCESO
      Gli eventi nel file eventi.txt sono da considerarsi gia' ordinati
      temporalmente per ciascun dispositivo. L'inserimento nella coda deve quindi
      preservare l'ordine di arrivo dal file.


   Parametri in ingresso:
   - file_dispositivi: nome del file dei dispositivi
   - file_eventi:      nome del file degli eventi

   Parametri in uscita:
   - lista: puntatore alla lista di dispositivi da costruire

   Valore di ritorno:
   - OK se il caricamento e' avvenuto correttamente
   - un codice di errore diverso da OK altrimenti
*/
int carica_dati(const char file_dispositivi[], const char file_eventi[], lista_dispositivi_t *lista) {
if (!lista) return ERRORE_PARAMETRI;
    FILE *fd=fopen(file_dispositivi,"r"); if (!fd) return ERRORE_FILE;
    FILE *fe=fopen(file_eventi,"r"); if (!fe) { fclose(fd); return ERRORE_FILE; }
    lista_dispositivi_t temp=NULL; dispositivo_t d; int n,rc=OK;
    while ((n=fscanf(fd,"%15s %49s %f",d.id_dispositivo,d.nome,&d.potenza_kw))==3) {
        if (d.potenza_kw<0 || cerca_dispositivo(temp,d.id_dispositivo)) { rc=ERRORE_DATI; break; }
        coda_init(&d.eventi); rc=aggiungi_dispositivo_testa(&temp,d); if (rc!=OK) break;
    }
    if (rc==OK && (n!=EOF || ferror(fd))) rc=ERRORE_DATI;
    evento_t e; char id[COD_LEN],stato[STR_LEN];
    while (rc==OK && (n=fscanf(fe,"%15s %15s %5s %49s",id,e.id_evento,e.orario,stato))==4) {
        dispositivo_t *p=cerca_dispositivo(temp,id); e.stato=string_to_stato(stato);
        if (!p || e.stato==STATO_SCONOSCIUTO || differenza_minuti(e.orario,e.orario)<0) { rc=ERRORE_DATI; break; }
        rc=accoda_evento(&p->eventi,e);
    }
    if (rc==OK && (n!=EOF || ferror(fe))) rc=ERRORE_DATI;
    fclose(fd); fclose(fe);
    if (rc!=OK) { dealloca_dispositivi(&temp); return rc; }
    dealloca_dispositivi(lista); *lista=temp; return OK;
}


/* ============================================================================
   QUESITO 2 - RICERCA EVENTO DI SPEGNIMENTO
   ========================================================================== */
/*
    Cercare il primo evento di spegnimento successivo a un evento di accensione.
    Da usare per trovare il corrispettivo di una accensione.

    Parametri in ingresso:
    - lista: puntatore al primo nodo della (sotto)lista di eventi del
        dispositivo di interesse

    Valore di ritorno:
    - Puntatore all'evento corrispondente (o NULL se non trovato)
*/
evento_t *cerca_evento_spegnimento(nodo_evento_t *lista) {
for (;lista;lista=lista->next) if (lista->info.stato==SPENTO) return &lista->info;
    return NULL;
}

/* ============================================================================
   QUESITO 3 - CALCOLO CONSUMI PER PERIODO
   ========================================================================== */
/*
   Produce un vettore dinamico di statistiche per ogni periodo di accensione-spegnimento.

   Per ogni dispositivo, gli eventi della coda devono essere analizzati in
   ordine. Ogni coppia ACCESO-SPENTO determina un periodo di funzionamento.
   Suggerimento: dato un evento di ACCENSIONE di un dispositivo, cercare
        (dalla sottolista con inizio il successivo del nodo) l'evento
        di spegnimento corrispondente. Gli eventi sono infatti ordinati.

   Il consumo e' calcolabile come:
        potenza_kw * (minuti_attivi / 60.0)

   Parametri in ingresso:
   - lista: lista dei dispositivi

   Parametri in uscita:
   - dim_out: numero di elementi del vettore restituito (uno per accensione-spegnimento)

   Valore di ritorno:
   - vettore dinamico di statistica_t
   - NULL se lista vuota o in caso di errore
*/
statistica_t *calcola_consumo_periodi(lista_dispositivi_t lista, int *dim_out) {
if (!dim_out) return NULL;
    *dim_out=0; statistica_t *v=NULL;
    for (;lista;lista=lista->next) {
        nodo_evento_t *p=lista->info.eventi.primo;
        while (p) {
            if (p->info.stato!=ACCESO) { p=p->next; continue; }
            nodo_evento_t *fine=p->next; while (fine && fine->info.stato!=SPENTO) fine=fine->next;
            if (!fine) break;
            int minuti=differenza_minuti(p->info.orario,fine->info.orario);
            if (minuti<0) { free(v); *dim_out=0; return NULL; }
            statistica_t *nuovo=realloc(v,((size_t)*dim_out+1)*sizeof *v);
            if (!nuovo) { free(v); *dim_out=0; return NULL; } v=nuovo;
            statistica_t *r=&v[(*dim_out)++];
            strcpy(r->id_dispositivo,lista->info.id_dispositivo); strcpy(r->nome,lista->info.nome);
            strcpy(r->accensione,p->info.orario); strcpy(r->spegnimento,fine->info.orario);
            r->minuti=minuti; r->consumo=lista->info.potenza_kw*(minuti/60.0); p=fine->next;
        }
    } return v;
}


/* ============================================================================
   QUESITO 4 - SALVATAGGIO FILTRATO SU FILE
   ========================================================================== */
/*
   Salva le statistiche relative ai singoli periodi se soddisfano i criteri desiderati.

    Parametri in ingresso:
    - Percorso del file dove salvare
    - Vettore delle statistiche dei singoli
    - Dimensione del vettore
    - Consumo minimo: double
    - Tempo minimo: int
    Valore di ritorno:
    - Numero di eventi salvati (>=0) OPPURE il codice di errore (<0)
*/
int salva_statistiche_filtrate(const char percorso[], statistica_t array[], int dim, double consumo_min,
                               int minuti_min) {
if (!percorso || dim<0 || (dim && !array)) return ERRORE_PARAMETRI;
    FILE *f=fopen(percorso,"w"); if (!f) return ERRORE_FILE;
    int count=0,ok=1;
    for (int i=0;i<dim;++i) if (array[i].consumo>=consumo_min && array[i].minuti>=minuti_min) {
        if (fprintf(f,"%s %s %s %s %d %.3f\n",array[i].id_dispositivo,array[i].nome,array[i].accensione,array[i].spegnimento,array[i].minuti,array[i].consumo)<0) { ok=0; break; } ++count;
    }
    if (fclose(f)) { ok=0; }
    return ok ? count : ERRORE_FILE;
}


/* ============================================================================
   MAIN
   ========================================================================== */

int main(void) {
    lista_dispositivi_t dispositivi = NULL;
    statistica_t *statistiche = NULL;
    int dim_statistiche = 0;

    if (carica_dati(FILE_DISPOSITIVI, FILE_EVENTI, &dispositivi) != OK) {
        printf("Errore nel caricamento dei dati.\n");
        dealloca_dispositivi(&dispositivi);
        return 1;
    }
    printf("Dispositivi caricati:\n");
    stampa_lista(dispositivi);

    printf("Statistiche dei periodi di accensione-spegnimento:\n");
    statistiche = calcola_consumo_periodi(dispositivi, &dim_statistiche);
    if (statistiche != NULL) {
        stampa_statistiche(statistiche, dim_statistiche);
    } else {
        printf("Nessuna statistica disponibile.\n");
    }

    int salvati = salva_statistiche_filtrate(FILE_OUTPUT, statistiche, dim_statistiche, 0.5, 30);
    if (salvati < 0) {
        printf("Errore nel salvataggio delle statistiche filtrate.\n");
    } else {
        printf("Statistiche filtrate salvate: %d\n", salvati);
    }

    free(statistiche);
    dealloca_dispositivi(&dispositivi);

    return 0;
}
