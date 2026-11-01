/*
  Sviluppo di applicazione in ANSI C per gestire le code di un ufficio
  postale.

  In un file di testo ("prenotato.txt"), è memorizzato l'elenco dei prenotati. 
  Per ciascuno dei prenotati è memorizzato il nome, il cognome e il tipo di
  operazione.

  Le operazioni previste sono tre:
  - raccomandata
  - spedizione_pacco
  _ conto_corrente

  Si assuma che il nome e cognome non contengano spazi.

  Implementare le seguenti funzioni:

  1. CaricaOperazioni: carica le operazioni presenti nel file in un
  vettore di tre code che contengono, rispettivamente, i clienti prenotati per
  le raccomandate, quelli per la spedizione di un pacco e quelli per il pagamento
  di un conto corrente.

  2. Operazione: dato il tipo di operazione, rimuove il primo cliente
  dalla coda corrispondente e lo introduce nella lista delle operazioni
  effettuate. La lista delle operazioni effettuate contiene come informazione
  sia il cliente che il tipo di operazione.

  3. EstraiNumeroDiOperazioni: data la lista delle operazioni calcola il numero
  di operazione di ciascun tipo e le restituisce inserendole in un apposito
  vettore di interi.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// la funzione codifica restituisce un intero in basa al valore della stringa
int codifica(char* st) {
if (!strcmp(st, "raccomandata")) return 0;
    if (!strcmp(st, "pacco") || !strcmp(st, "spedizione_pacco")) return 1;
    if (!strcmp(st, "contocorrente") || !strcmp(st, "conto_corrente")) return 2;
    return -1;
}

// Implementazione coda di clienti
typedef struct Cliente
{
    char  nome[20];
    char  cognome[64];
} TCliente;

typedef struct NodoCliente {
    TCliente           info;
    struct NodoCliente* next;
} TNodoCliente;

typedef struct C {
    TNodoCliente* primo, * ultimo;
} Coda;


/* AggiungiCliente inserisce un elemento in una coda passata
   come primo parametro.
   Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti
 */
int AggiungiCliente(Coda* pC, TCliente cliente)
{
    TNodoCliente* paux;

    paux = (TNodoCliente*)malloc(sizeof(TNodoCliente));

    if (paux == NULL)
        return 0;
    paux->info = cliente;
    paux->next = NULL;
    if (pC->primo == NULL)
        pC->primo = pC->ultimo = paux;
    else {
        pC->ultimo->next = paux;
        pC->ultimo = paux;
    }
    return 1;
}

/*crea una coda vuota*/
void CodaVuota(Coda* pC) {
    pC->primo = pC->ultimo = NULL;
}

/*elimina un elemento dalla coda e restituisce, come parametro, il cliente
estratto dalla coda, la funzione restituisce 1 se a buon esito 0 se non
viene estratto nessun elemento dalla coda*/
int eliminaCoda(Coda* pC, TCliente* pCliente) {
if (!pC || !pCliente || !pC->primo) return 0;
    TNodoCliente *n = pC->primo;
    *pCliente = n->info; pC->primo = n->next;
    if (!pC->primo) pC->ultimo = NULL;
    free(n); return 1;
}
//lista di operazioni
typedef struct Operazione
{
    char  nome[20];
    char  cognome[64];
    char operazione[20];
} TOperazione;

typedef struct NodoOperazione {
    TOperazione           info;
    struct NodoOperazione* next;
} TNodoOperazione, * TListaOperazione;

/*inserimento in testa nella lista delle operazioni, restituisce 1 se l'operazione
ha successo 0 altrimenti*/
int InserisciTestaLista(TListaOperazione* plis, TOperazione operazione) {
    TListaOperazione paux;
    paux = (TListaOperazione)malloc(sizeof(TNodoOperazione));
    if (paux == NULL) return 0;
    paux->next = *plis;
    paux->info = operazione;
    *plis = paux;
    return 1;
}
//---------------------------
/*
  1. CaricaOperazioni: carica i dati del cliente in base al valore
  della operazione richiesta nella coda corrispondente.


  Parametri di ingresso: nome del file
  Parametri di uscita: il vettore contenente le tre code (coda dei clienti prenotati per una raccomandata (raccomandata),
  coda dei clienti prenotati per spedire un pacco (pacco)
  coda dei clienti prenotati per un contocorrente (contocorrente))
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/
int CaricaOperazioni(char* nome_file, Coda* vettoreCode)
{
FILE *f = fopen(nome_file, "r");
    if (!f) return 0;
    TCliente cliente; char operazione[20]; int n, ok = 1;
    while ((n = fscanf(f, "%19s %63s %19s", cliente.nome, cliente.cognome, operazione)) == 3) {
        int i = codifica(operazione);
        if (i < 0 || !AggiungiCliente(&vettoreCode[i], cliente)) { ok = 0; break; }
    }
    if (n != EOF || ferror(f)) ok = 0;
    fclose(f); return ok;
}
/*
  2. Operazione: dato il tipo di operazione, rimuove il primo cliente
  dalla coda corrispondente e lo introduce nella lista delle operazioni
  effettuate. La lista delle operazioni effettuate contiene come informazione
  sia il cliente che il tipo di operazione.

  La funzione prende in ingresso la coda da cui estrarre, la stringa che identifica
  il tipo di operazione e la lista in cui inserire l'operazione.
*/
int Operazione(Coda* pC, char* tipo, TListaOperazione* pLista) {
if (!pC || !pC->primo || codifica(tipo) < 0) return 0;
    TOperazione o;
    strcpy(o.nome, pC->primo->info.nome);
    strcpy(o.cognome, pC->primo->info.cognome);
    snprintf(o.operazione, sizeof o.operazione, "%s", tipo);
    if (!InserisciTestaLista(pLista, o)) return 0;
    TCliente c; return eliminaCoda(pC, &c);
}

/*
  3. ContaNumeroDiOperazioni: data la lista delle operazioni calcola il numero
  di operazione di ciascun tipo e le restituisce inserendole in un apposito
  vettore di interi

  Parametri di ingresso:
  lis - lista delle operazioni

  Valore restituito:
  int - vettore contenente il numero di operazioni per tipo
*/


int* ContaNumeroDiOperazioni(TListaOperazione lis) {
int *v = calloc(3, sizeof *v);
    if (!v) return NULL;
    for (; lis; lis = lis->next) { int i = codifica(lis->info.operazione); if (i >= 0) ++v[i]; }
    return v;
}


/*
  VisualizzaCoda visualizza le informazioni dei clienti
  contenute in una coda passata come parametro
*/
void VisualizzaCoda(Coda C)
{
    TNodoCliente* paux = C.primo;
    while (paux != NULL)
    {
        printf("\t%s %s \n", paux->info.nome, paux->info.cognome);
        paux = paux->next;
    }
}

/*
  VisualizzaLista visualizza le informazioni delle operazioni
  contenute in una lista passata come parametro
*/
void Visualizzalista(TListaOperazione l)
{
    while (l != NULL)
    {
        printf("\n%s %s  %s\n", l->info.nome, l->info.cognome, l->info.operazione);
        l = l->next;
    }
}
/*
  VisualizzaVettoreInteri v
*/
void VisualizzaVettore(int v[], int dim)
{
    int i;
    for (i = 0; i < dim; i++) printf("%d\n", v[i]);
}



int Menu()
{
int scelta = 0;
    printf("1 Carica | 2 Operazione | 3 Statistiche | 0 Esci: ");
    if (scanf("%d", &scelta) != 1) return 0;
    return scelta;
}

void DisallocaLista(TListaOperazione* lista)
{
while (*lista) { TListaOperazione n = *lista; *lista = n->next; free(n); }
}

void DisallocaCoda(Coda* c)
{
    TNodoCliente* paux, * lis = c->primo;

    while (lis != NULL)
    {
        paux = lis;
        lis = lis->next;
        free(paux);
    }
    c->primo = c->ultimo = NULL;
}

int main(void)
{
Coda code[3] = {{0}}; TListaOperazione lista = NULL;
    int scelta;
    while ((scelta = Menu()) != 0) {
        if (scelta == 1) {
            char nome[256]; if (scanf("%255s", nome) != 1) break;
            printf("Caricamento: %d\n", CaricaOperazioni(nome, code));
            for (int i = 0; i < 3; ++i) VisualizzaCoda(code[i]);
        } else if (scelta == 2) {
            char tipo[20]; if (scanf("%19s", tipo) != 1) break;
            int i = codifica(tipo);
            printf("Operazione: %d\n", i >= 0 ? Operazione(&code[i], tipo, &lista) : 0);
            Visualizzalista(lista);
        } else if (scelta == 3) {
            int *v = ContaNumeroDiOperazioni(lista);
            if (v) { VisualizzaVettore(v, 3); free(v); }
        }
    }
    DisallocaLista(&lista);
    for (int i = 0; i < 3; ++i) DisallocaCoda(&code[i]);
    return 0;
}