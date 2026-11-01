/*
  Sviluppo di applicazione in ANSI C per gestire
  un servizio di prestito libri di una libreria.

  In un file di testo ("libri.txt") e' memorizzato
  l'elenco dei libri della biblioteca.
  Cosi' come visibile nel file, per ciascun libro
  sono memorizzate le seguenti informazioni:
  - codice libro
  - titolo libro
  - genere libro (es: biografia, romanzo, giallo, thriller, avventura, fantascienza, etc)
  - costo settimanale

  Si assuma che il titolo del libro non contenga spazi.

Implementare le seguenti funzioni:
  1. CaricaLibri: carica i libri presenti nel file in due
  liste rispettivamente una contenente quelli disponibili e l'altra contenente quelli prestati.

  2. Prestito: dato il codice libro, rimuove tale libro (se
  esiste) dalla lista dei libri disponibili e lo aggiunge a
  quella deli libri prestati.

  3. EstraiLibriDiInteresse: dato un genere e un costo massimo,
  seleziona dalla lista dei libri disponibili quelli che
  soddisfano tale criteri e li inserisce in un apposito vettore di libri.

  4 Costruire un albero binario di ricerca ordinato per codice del libro che contiene tutti i libri presenti nelle due liste

  5 Stampare l'elenco di libri ordinati per codice 

  La descrizione dettagliata di ogni funzione e' riportata come commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Libro {
    char codice[8];
    char titolo[64];
    char genere[16];
    float costo;
} TLibro;

typedef struct NodoLibro {
    TLibro info;
    struct NodoLibro* next;
} TNodoLibro;

typedef TNodoLibro* TListaLibri;

typedef struct NodoAlbero {
    TLibro info;
    struct NodoAlbero* destro;
    struct NodoAlbero* sinistro;
} TNodoAlbero;

typedef TNodoAlbero* TAlberoLibri;

/* AggiungiLibro inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiLibro(TListaLibri* plis, TLibro elem) {
    TListaLibri paux;

    paux = (TListaLibri)malloc(sizeof(TNodoLibro));

    if (paux == NULL)
        return 0;

    paux->info = elem;
    paux->next = *plis;

    *plis = paux;

    return 1;
}

/*
  1. CaricaLibri: carica i libri presenti nel file in due
  liste rispettivamente una contenente quelli disponibili e l'altra
  contenente quelli prestati.


  Parametri di ingresso: nome del file
  Parametri di uscita:  lista deli libri disponibili (disponibili),
                        lista dei libri prestati (prestati)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/
int CaricaLibri(char* nome_file,
    TListaLibri* disponibili,
    TListaLibri* prestati) {
    // Implementare il corpo della funzione

    TLibro elem;
    FILE *fp;
    fp = fopen(nome_file, "r");
    char stato[15];
    if (fp == NULL) {
        printf("\nErrore apertura file");
        return 0;
    }

    while (fscanf(fp, "%7s %15s %63s %f %14s\n", elem.codice,
            elem.genere,
            elem.titolo,
            &elem.costo,
            stato) == 5) {
        if (strcmp(stato, "disponibile") == 0) {
            AggiungiLibro(disponibili, elem);
        } else if (strcmp(stato, "prestato") == 0) {
            AggiungiLibro(prestati, elem);
        } else {
            printf("\nErrore stato libro");
            break;
        }
    }
    fclose(fp);
    return 1;
}

/*
  CancellaLibro: ricerca nella lista lis il libro con numero
  di codice fornito in ingresso (codice) e lo rimuove dalla lista.
*/
void CancellaLibro(TListaLibri* lis, char* codice) {

    if (*lis == NULL) return;

    TListaLibri nodo_generatore = (TListaLibri)malloc(sizeof(TNodoLibro));
    if (nodo_generatore == NULL){
        printf("\nErrore allocazione memoria");
        return;
    }
    nodo_generatore->next = *lis;

    TListaLibri precedente = nodo_generatore;
    TListaLibri corrente = precedente->next;

    while (corrente != NULL) {
        if (strcmp(corrente->info.codice, codice) == 0) {
            precedente->next = corrente->next;
            free(corrente);
            break;
        }
        precedente = corrente;
        corrente = corrente->next;
    }
    //cancella nodo generatore
    *lis = nodo_generatore->next;
    free(nodo_generatore);
}


/*
  2. Prestito: dato il codice libro, rimuove tale libro (se
  esiste) dalla lista dei libri disponibili e la aggiunge a quella
  dei libri prestati.

  Parametri di ingresso:
  numero codice libro,

  Parametri di ingresso/uscita:
  lista dei libri disponibili (disponibili),
  lista dei libri prestati (prestati)

  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Prestito(char* codice, TListaLibri* disponibili,
    TListaLibri* prestati) {
    // Implementare il corpo della funzione

    TListaLibri aux = *disponibili;
    int esito = 0;
    while (aux != NULL) {
        if (strcmp(aux->info.codice, codice) == 0) {
            esito = 1;
            AggiungiLibro(prestati, aux->info);
            break;
        }
        aux = aux->next;
    }
    if (esito == 1) {
        CancellaLibro(disponibili, codice);
    }
    return esito;
}

/*
  3. EstraiLibriDiInteresse: dato un genere e un costo massimo,
  seleziona dalla lista dei libri disponibili quelli che
  soddisfano tale criterio e li inserisce in un apposito vettore di
  libri.

  Parametri di ingresso:
  lis - lista deli libri disponibili
  genere - genere libro
  max_costo - costo massimo

  Parametri di uscita:
  dim - numero di libri che soddisfano i criteri

  Valore restituito:
  TLibro* - vettore deli libri selezionate
*/
TLibro* EstraiLibriDiInteresse(TListaLibri lis, float max_costo, char* genere, int* dim) {
    // Implementare il corpo della funzione
    int i = 0;
    TListaLibri aux = lis;
    *dim = 0;
    while (aux != NULL) {
        if ((strcmp(aux->info.genere, genere) == 0) && (aux->info.costo <= max_costo)) {
            (*dim)++;
        } aux = aux->next;
    }

    TLibro *vettore = malloc(sizeof(TLibro)*(*dim));
    aux = lis;
    while (aux != NULL) {
        if ((strcmp(aux->info.genere, genere) == 0) && (aux->info.costo <= max_costo)) {
            vettore[i++]=aux->info;
        } aux = aux->next;
    }
    return vettore;
}


/*
  VisualizzaLibri visualizza le informazioni dei libri
  nella lista passata come parametro
*/
void VisualizzaLibri(TListaLibri lis) {
    while (lis != NULL) {
        printf("%s %s %s %.2f\n",
            lis->info.codice,
            lis->info.genere,
            lis->info.titolo,
            lis->info.costo);
        lis = lis->next;
    }
}

/*
  VisualizzaVettoreLibri visualizza le informazioni dei libri
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreLibri(TLibro v[], int dim) {
    for (int i = 0; i < dim; i++) {
        printf("\n%s %s %s %.2f", v[i].codice, v[i].genere, v[i].titolo, v[i].costo);
    }
}

/*
  ComparaCodiceLibri: compara il codice di due libri passati come parametro

  Valore restituito:
   < 1 se a è 'minore' di b
   0 se a e b sono equivalenti
   > 1 se a è 'maggiore' di b
*/
int ComparaCodiceLibri(TLibro a, TLibro b) {
    return strcmp(a.codice, b.codice);
}

/*
  CostruisciAlbero: costruisce un nuovo albero, avente come radice l'elemento 
  fornito come primo parametro, e come figli i due sottoalberi forniti come secondo
  e terzo parametro

  Parametri di ingresso:
  etichetta del nuovo nodo,
  sottoalbero sinistro,
  sottoalbero destro

  Valore restituito: puntatore al nodo radice del nuovo albero
*/

TAlberoLibri CostruisciAlbero(TLibro elem, TAlberoLibri sx, TAlberoLibri dx){
    //Implementare il corpo della funzione
    TAlberoLibri aux = malloc(sizeof(TNodoAlbero));
    if (aux == NULL) {
        printf("\nErrore allocazione");
        exit(1);
    }
    aux->info = elem;
    aux->destro = dx;
    aux->sinistro = sx;
    return aux;
}


/*
    Genitore: dato un libro, la funzione restituisce il potenziale nodo genitore 
    all'interno dell'albero binario di ricerca ordinato per codice libro. 
    La funzione restituisce il puntatore al nodo genitore
*/
TAlberoLibri Genitore(TAlberoLibri albero, TLibro libro) {

    TAlberoLibri pred = NULL;
    while (albero != NULL) {
        pred = albero;
        if (ComparaCodiceLibri(libro, pred->info ) <= 0)
            albero = albero->sinistro;
        else albero = albero->destro;
    }
    return pred;
}


/*
    CercaNodoAlbero: dato un albero e un libro, la funzione cerca se il libro
    e' gia' presente nell'albero.
    La funzione restituisce il puntatore al nodo desiderato, NULL altrimenti.
*/
TAlberoLibri CercaNodoLibroPerCodice(TAlberoLibri albero, TLibro libro) {
    TAlberoLibri sottoalbero;

    if (albero == NULL)
        sottoalbero = NULL;
    else if (ComparaCodiceLibri(albero->info, libro) == 0) //elemento trovato
        sottoalbero = albero;
    else if (ComparaCodiceLibri(albero->info, libro) > 0) //cerca nel sottoalbero sx
        sottoalbero = CercaNodoLibroPerCodice(albero->sinistro, libro);
    else sottoalbero = CercaNodoLibroPerCodice(albero->destro, libro); //cerca nel sottoalbero dx

    return sottoalbero;
}

/* 
    InserisciNodoAlbero: inserisce un nuovo nodo in un albero binario di ricerca
    ordinato per codice libro. Il nuovo nodo ha per etichetta il libro passato come
    secondo parametro. ATTENZIONE: in un albero binario di ricerca ordinato per codice
    libro, non possono esistere due nodi con lo stesso codice libro. 
*/
void InserisciNodoAlbero(TAlberoLibri* palbero, TLibro elem) {
    //implementare il corpo della funzione
    //utilizzando le funzioni CostruisciAlbero, Genitore 
    TAlberoLibri aux, prec;
    if (CercaNodoLibroPerCodice(*palbero, elem) == NULL) {
        aux = CostruisciAlbero(elem, NULL, NULL);
        if (*palbero == NULL) {
            *palbero = aux;
        } else {
            prec = Genitore(*palbero, elem);
            if (ComparaCodiceLibri(elem, prec->info) < 0) {
                prec->sinistro = aux;
            } else {
                prec->destro = aux;
            }
        }
    }

}


/*
    4.CreaAlberoABR: crea un albero binario di ricerca ordinato per codice libro
    a partire dalle liste dei libri disponibili e prestati. 
*/
void CreaAlberoBR(TAlberoLibri *palbero, TListaLibri disp, TListaLibri prest) {
    //implementare il corpo utilizzando le funzioni esistenti
    while (disp != NULL) {
        InserisciNodoAlbero(palbero, disp->info);
        disp = disp->next;
    }
    while (prest != NULL) {
        InserisciNodoAlbero(palbero, prest->info);
        prest = prest->next;
    }
}


/*
  5.StampaElenco Libri: la funzione prende in input l'albero binario di ricerca 
  contenente tutti i libri (disponibili e prestati) e li stampa ordinati per codice libro
*/
void StampaElencoLibri(TAlberoLibri albero) {
    //da implementare
    if (albero != NULL) {
        StampaElencoLibri(albero->sinistro);

        printf("\n%s %s %s %.2f", albero->info.codice, albero->info.genere, albero->info.titolo, albero->info.costo);

        StampaElencoLibri(albero->destro);
    }


}

int Menu() {
    int scelta;

    printf("\n*** M E N U ***\n"
        "1 - Carica libri\n"
        "2 - Prestito libro\n"
        "3 - Cerca libri di interesse \n"
        "4 - Crea Albero binario di ricerca \n"
        "5 - Stampa Elenco ordinato \n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DeallocaLista(TListaLibri *lista) {
    // Implementare il corpo della funzione
    TListaLibri aux;
    while (*lista != NULL) {
        aux = *lista;
        *lista = (*lista)->next;
        free(aux);
    }

}

void DeallocaAlbero(TAlberoLibri* albero) {
    // Implementare il corpo della funzione
    if (*albero != NULL) {
        if ((*albero)->sinistro !=NULL) {
            DeallocaAlbero(&(*albero)->sinistro);
        }
        if ((*albero)->destro !=NULL) {
            DeallocaAlbero(&(*albero)->destro);
        }
        free(*albero);
    }
}


int main(void) {
    TListaLibri disponibili = NULL;
    TListaLibri prestati = NULL;
    TAlberoLibri albero = NULL;

    TListaLibri aux_disp;
    TListaLibri aux_prest;

    int scelta;
    char nomefile[32];
    char codice[8];
    char genere[16];
    int dim;
    float costo_max;
    TLibro* vett;
    int esito;

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            // acquisire il nome del file
            // invocare la funzione CaricaLibri
            // visualizzare le liste ottenute
            printf("\nInserisci nome file: ");
            scanf("%s", nomefile);
            CaricaLibri(nomefile, &disponibili, &prestati);
            printf("\nLista libri disponibili:\n");
            VisualizzaLibri(disponibili);
            printf("\nLista libri prestati:\n");
            VisualizzaLibri(prestati);
            break;

        case 2:
            // acquisire il codice libro da prestare
            // invocare la funzione Prestito
            // visualizzare le liste modificate
            printf("\nInserisci codice libro: ");
            scanf("%s", codice);
            esito = Prestito(codice, &disponibili, &prestati);
            if (esito)
                printf("\nLibro %s pretato correttamente\n", codice);
            else
                printf("\nLibro %s non trovato\n", codice);

            printf("\nLista libri disponibili:\n");
            VisualizzaLibri(disponibili);
            printf("\nLista libri prestati\n");
            VisualizzaLibri(prestati);
            break;

        case 3:
            // acquisire il costo massimo
            // acquisire una categoria
            // invocare la funzione EstraiLibriDiInteresse
            // visualizzare il vettore restituito
            printf("\nInserisci categoria: ");
            scanf("%s", genere);
            while (getchar() != '\n');
            printf("\nInserisci costo massimo: ");
            scanf("%f", &costo_max);
            vett = EstraiLibriDiInteresse(disponibili, costo_max, genere, &dim);
            VisualizzaVettoreLibri(vett, dim);
            free(vett);
            break;
        case 4:
            // scorrere le liste dei libri e creare l'albero binario di ricerca ordinato per codice libro
            // invocare la funzione CreaAlberoBR
            CreaAlberoBR(&albero, disponibili, prestati);

            break;
        case 5:
            //invocare la funzione StampaElencoLibri
            StampaElencoLibri(albero);

        }

    } while (scelta != 0);

    // Deallocare le liste e l'albero
    DeallocaLista(&disponibili);
    DeallocaLista(&prestati);
    DeallocaAlbero(&albero);
    return 0;
}

