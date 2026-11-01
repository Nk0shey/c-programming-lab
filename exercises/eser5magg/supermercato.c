#include "../../common/console.h"
#include <stdio.h>

/*
 * Esercitazione - Liste Ordinate
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> //per usare la costante FLT_MAX

#define NOME_FILE_INPUT "prodotti.txt"
#define COD_ARTICOLO 16
#define L_STRINGA 31


typedef struct {
	char cod[COD_ARTICOLO];
	char nome[L_STRINGA];
	char marca[L_STRINGA];
	int reparto;
	float prezzo;
	int quantita;
}T_Prodotto;

typedef struct nodoLista {
	T_Prodotto info;
	struct nodoLista* next;
}TipoNodoLista;

typedef TipoNodoLista* List;


/* Funzioni Punto 1: Leggi da file e inserisci in Lista ordinata*/

/**
 * funzione di confronto tra due elementi.
 * Restituisce:
 * <0 se *a viene prima di *b
 * 0 se *a é equivalente a *b
 * >0 se *a viene dopo di *b
*/
int comparaCodice(const void* a, const void* b) {
	//TODO: da completare
	T_Prodotto* x = (T_Prodotto*)a;
	T_Prodotto* y = (T_Prodotto*)b;
	return strcmp(x->cod, y->cod);
}


/**
 * Inserisce in una lista ordinata
 * Parametri:
 * - l: puntatore alla lista dei prodotti
 * - elem : elemento da inserire nella lista
 *
 * Restituisce:
 *  1 se l'inserimento è andato a buon fine, 0 altrimenti
 */
int InserisciInListaOrdinata(List* l, T_Prodotto elem) {
	//TODO: da completare
	List paux;
	if ((*l) == NULL || comparaCodice(&elem, &(*l)->info) < 0) {
		paux = malloc(sizeof(TipoNodoLista));
		if (paux == NULL) {
			return -1;
		}

		paux -> info = elem;
		paux -> next = (*l);
		(*l) = paux;

		return 1;
	}
	return InserisciInListaOrdinata(&(*l)->next, elem);
}


/**
 * Carica i dati dal file e li inserisce in una lista di prodotti ordinata per codice
 * Parametri:
 * - nome_file: nome del file contenente i prodotti
 * - l : puntatore alla lista dei prodotti
 *
 * Restituisce:
 * numero di prodotti caricati
 */
int CaricaProdotti(const char* nome_file, List * l) {
if (!l) return -1;
    FILE *fp=fopen(nome_file,"r"); if (!fp) return -1;
    T_Prodotto p; int n,count=0;
    while ((n=fscanf(fp,"%15s %30s %30s %d %f %d",p.cod,p.nome,p.marca,&p.reparto,&p.prezzo,&p.quantita))==6) {
        if (!InserisciInListaOrdinata(l,p)) { fclose(fp); return -1; } ++count;
    }
    int ok=n==EOF && !ferror(fp); fclose(fp); return ok ? count : -1;
}

/* Funzioni Punto 2: visualizza elementi in lista*/
/*
 * Stampa a video un prodotto
 * Parametri:
 * - articolo: articolo da stampare a video
 *
 * Restituisce:
 * void
 */
void stampaArticolo(T_Prodotto articolo) {
	//TODO: da completare
	printf("%-10s %-20s %-20s %-8d %-8.2f %-8d", articolo.cod, articolo.nome, articolo.marca, articolo.reparto,
	       articolo.prezzo, articolo.quantita);
}

/*
 * Stampa la lista dei prodotti (richiamando la funzione stampaArticolo)
 * Parametri:
 * - l: lista di prodotti da stampare a video
 * Restituisce:
 * void
 */
void VisualizzaLista(List l) {
	//TODO: da completare
	printf("\nLista Articoli");
	printf("\n\nCodice     Nome                 Casa                Reparto  Prezzo  Quantita'\n\n");
	while (l != NULL) {
		stampaArticolo(l->info);
		l = l->next;
	}
}


/* Funzioni Punto 3: Modificare la quantità di un prodotto, dato il codice */

/*
 * Modifica la quantita di un prodotto della lista
 * parametri:
 * - l: lista di prodotti
 * - cod: codice prodotto
 * - quantita: nuova quantita
 *
 * Restituisce:
 * 1 se l'articolo è stato trovato nella lista, 0 altrimenti
 */
int ModificaQuantita(List l, char* cod, int quantita) {
	//TODO: da completare
	int trovato = 0;

	T_Prodotto aux;
	strcpy(aux.cod, cod);

	while ((l != NULL) && comparaCodice(&aux, &(l->info))>=0) {
		if (comparaCodice(&aux.cod, &(l->info.cod))) {
			l->info.quantita = quantita;
			trovato = 1;
			break;
		}
		l = l->next;
	}
	return trovato;
}

/*Funzioni Punto 4: prezzo massimo e minimo dei prodotti di un una determinata marca*/

/*
* Restituisce (tramite i due parametri pmax e pmin) il prezzo massimo e minimo degli articoli di una determinata marca
* Parametri:
* - l: puntatore alla lista prodotti
* - marca: puntatore alla marca di prodotti
* Parametri in uscita:
* - pmax: puntatore al prezzo massimo
* - pmin: puntatore al prezzo minimo
*
* restituisce:
* 1 se il prodotto è stato trovato almeno un prodotto della marca ricercata; 0 altrimenti
*/
int PrezzoMaxMin(List l, char* marca, float* pmax, float* pmin) {
	//TODO: da completare
	int trovato = 0;
	*pmax = 0;
	*pmin = FLT_MAX;

	while (l != NULL) {
		if (strcmp(l->info.marca, marca ) == 0) {
			trovato = 1;
			if (l->info.prezzo > *pmax) {
				*pmax = l->info.prezzo;
			}
			if (l->info.prezzo < *pmin) {
				*pmin = l->info.prezzo;
			}
		}
		l = l->next;
	}
	return trovato;
}


/* Funzioni Punto 5:
* Scrivere una funzione che restituisca in un opportuno vettore gli articoli di un determinato
* reparto passato come parametro
*/

/*
 * Restituisce un vettore di prodotti di un determinato reparto. La funzione restituisce tramite parametro la
 * dimensione del vettore creato.
 *
 * parametri:
 * - l: lista prodotti
 * - reparto: reparto da cercare
 *
 * Parametri in uscita:
 * - dim: dimensione del vettore creato
 *
 * restituisce:
 * - vettore di prodotti
 */
T_Prodotto* ArticoliReparto(List l, int reparto, int* dim) {
*dim=0; for (List n=l;n;n=n->next) if (n->info.reparto==reparto) ++*dim;
    if (!*dim) return NULL;
    T_Prodotto *v=malloc((size_t)*dim*sizeof *v); if (!v) { *dim=0; return NULL; }
    int i=0; for (;l;l=l->next) if (l->info.reparto==reparto) v[i++]=l->info; return v;
}

/*
 * Stampa un vettore di prodotti
 */
void VisualizzaArticoliVettore(T_Prodotto v[], int dim) {
	//TODO: da completare
	printf("Visualizzazione dati vettore\n");
	printf("\n\nCodice     Nome                 Casa                Reparto  Prezzo  Quantita'\n\n");
	for (int i = 0; i < dim; i++) {
		printf("%-10s %-20s %-20s %-8d %-8.2f %-8d\n", v[i].cod, v[i].nome, v[i].marca, v[i].reparto, v[i].prezzo,
		       v[i].quantita);
	}
}


/* Funzioni Punto 6: Scrivere una funzione che crei e restituisca in una lista l'elenco degli articoli aventi
 * quantità minore di un determinato valore passato in ingresso alla funzione
 *
 */

/*
 * Crea e restituisce una nuova lista di prodotti la cui quantità è minore di una soglia passata come parametro
 * parametri:
 * - l lista di prodotti
 * - soglia: quantita minima
 *
 * restituisce:
 * nuova lista dei prodotti la cui quantità è < della soglia
 */
List ArticoliQuantitaMinore(List l, int soglia) {
	//TODO: da completare
	List lista_articoli = NULL;

	while (l != NULL) {
		if (l->info.quantita < soglia) {
			InserisciInListaOrdinata(&lista_articoli, l->info);
		}
		l = l->next;
	}
	return lista_articoli;
}

/*Funzioni Punto 7: Scrivere una funzione che scriva su di un file di testo i dati di tutti gli articoli di una
 *determinata marca passata in ingresso alla funzione come parametro*/

int ScriviSuFile(List l, char* casa) {
char nome[256]; if (snprintf(nome,sizeof nome,"%s.txt",casa)>=(int)sizeof nome) return -1;
    FILE *f=fopen(nome,"w"); if (!f) return -1;
    int count=0,ok=1;
    for (;l;l=l->next) if (!strcmp(l->info.marca,casa)) {
        if (fprintf(f,"%s %s %s %d %.2f %d\n",l->info.cod,l->info.nome,l->info.marca,l->info.reparto,l->info.prezzo,l->info.quantita)<0) { ok=0; break; } ++count;
    }
    if (fclose(f)) ok=0;
    return ok ? count : -1;
}


/* Altre funzioni utili*/
/* cancella tutti gli elementi di una lista */
void CancellaLista(List* l) {
	//TODO: da completare

	List paux;
	if (*l != NULL) {
		paux = (*l)->next;
		free(*l);
		CancellaLista(&paux);
		*l = NULL;
	}
}

/************************
		 MAIN
*************************/

int  main(void) {

	List lista_prodotti = NULL;

	int scelta, esito;
	char cod[16];
	int nuovaquantita;
	int numero_letti = 0;
	char marca[64];
	float prezzomin, prezzomax;
	int reparto;
	int dim;
	T_Prodotto* vett_articoli=NULL;
	int soglia;
	List nuovalista = NULL;
	T_Prodotto articolo;



	do {
		printf("\n\nEsercitazione Liste Semplici\n");
		printf("*** Supermercato *** \n\n");

		printf("1. Leggi articoli da File\n");
		printf("2. Visualizza i dati di tutti gli articoli presenti\n");
		printf("3. Modifica quantita'\n");
		printf("4. Prezzo minimo massimo articoli di una marca\n");
		printf("5. Articoli di un reparto\n");
		printf("6. Elenco articoli con quantita' minore di ...\n");
		printf("7. Scrivi su file (di testo) articoli di una marca\n");

		printf("\n0. Uscita dal programma\n");

		printf("\nImmetti una scelta:    ");

		lab_scanf("%d", &scelta);
		lab_discard_line();

		switch (scelta) {
		case 1:
			numero_letti = CaricaProdotti(NOME_FILE_INPUT, &lista_prodotti);
			printf("\n\nSono stati letti %d prodotti", numero_letti);
			break;
		case 2:
			VisualizzaLista(lista_prodotti);
			break;
		case 3:
			printf("Immetti il codice dell'articolo: ");
			lab_scanf("%15s", cod);
			lab_discard_line();
			printf("\nIntroduci la nuova quantita' presente: ");
			lab_scanf("%d", &nuovaquantita);
			esito = ModificaQuantita(lista_prodotti, cod, nuovaquantita);
			if (esito)
				printf("Articolo presente - quantita' modificata\n");
			else
				printf("Articolo non presente\n");
			break;
		case 4:
			printf("Immetti la marcae: ");
			lab_scanf("%30[^\n]", marca);

			esito = PrezzoMaxMin(lista_prodotti, marca, &prezzomax, &prezzomin);
			if (esito)
				printf("Prezzo max: %.2f \t Prezzo min: %.2f \n", prezzomax, prezzomin);
			else
				printf("Articoli della marca %s non presenti\n", marca);
			break;

		case 5:
			printf("Immetti un reparto: ");
			lab_scanf("%d", &reparto);
			dim = 0;
			vett_articoli = ArticoliReparto(lista_prodotti, reparto, &dim);
			VisualizzaArticoliVettore(vett_articoli, dim);
			break;
		case 6:
			printf("Immetti una quantita' soglia: ");
			lab_scanf("%d", &soglia);

			nuovalista = ArticoliQuantitaMinore(lista_prodotti, soglia);
			printf("Visualizzazione dati estratti");
			VisualizzaLista(nuovalista);
			break;
		case 7:
			printf("Immetti la casa produttrice: ");
			lab_scanf("%30[^\n]", marca);
			lab_discard_line();

			ScriviSuFile(lista_prodotti, marca);
			break;
		case 0:
			break;
		default:
			printf("Comando errato, riprova!\n");
		}

	} while (scelta != 0);

	//deallocazione variabili dinamiche
	//TODO: da completare
	free(vett_articoli);
	CancellaLista(&nuovalista);
	CancellaLista(&lista_prodotti);
}