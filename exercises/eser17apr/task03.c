//
// Created by kozch on 01.06.2026.
//

/* Esercizio 3: libreria
* Si vuole scrivere un programma per la gestione delle informazioni relative a libri custoditi in una biblioteca.
* Di ciascun libro si vuole memorizzare:
* - un codice alfanumerico (stringa di max 10 caratteri)
* - il nome dell’autore (stringa di max 40 caratteri)
* - il titolo del libro (stringa di max 40 caratteri)
* - la quantità di copie disponibili
* - il prezzo
*
* 0) Progettare le strutture di dati adatte a mantenere le informazioni di ogni libro. In particolare,
*    utilizzare una lista realizzata tramite strutture e puntatori.
* 1) Realizzare una funzione che legga da standard input i dati di un libro e li inserisca in modo opportuno
*    all’interno della lista dei libri.
* 2) Scrivere una funzione che, dato in ingresso il codice di un libro, effettui l’aggiornamento della quantità
*    di quel libro a seguito di un prestito. La funzione dovrà stampare su schermo un messaggio di errore se non
*    ci sono copie disponibili (Es. “Impossibile effettuare prestito…”); nel caso ci siano copie disponibili,
*    dovrà aggiornare il campo quantità e stamparlo a video.
* 3) Scrivere una funzione che stampi su schermo tutti i titoli dei libri scritti da un autore, il cui nome viene
*    inserito da tastiera e passato come parametro alla funzione. La funzione inoltre deve restituire il numero totale
*    di copie di libri di quell’autore.
* 4) Scrivere una funzione che effettui la cancellazione dalla lista di un libro il cui codice viene inserito da
*    tastiera e passato come parametro alla funzione.
* 5) Scrivere una funzione che effettui la cancellazione dalla lista di tutti i libri di un determinato autore il
*    cui nome viene inserito da tastiera e passato come parametro alla funzione
* 6) Scrivere una funzione che stampi su schermo tutti i titoli dei libri aventi prezzo inferiore ad un valore
*    inserito da tastiera e passato come parametro alla funzione.
* 7) Realizzare una funzione che scriva su un file di TESTO tutti i codici e i titoli dei libri di cui attualmente
*    non c’è disponibilità (il nome del file viene passato come parametro alla funzione).
* 8) Realizzare una funzione che scriva su un file BINARIO tutti i dati dei libri contenuti nella lista
*    (il nome del file viene passato come parametro alla funzione).
* 9) Realizzare una funzione che legga da un file BINARIO (che si suppone creato come al punto 8 del presente
*    esercizio) i dati dei libri e li inserisca in nella lista (il nome del file viene passato come parametro
*    alla funzione).
* 10) Realizzare una funzione che permetta di visualizzare i dati di tutti i libri presenti nella lista.
* 11) Realizzare una funzione che cancelli (liberando la memoria) tutti i libri presenti nella lista
*
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define STRING_LENGHT 41
#define COD_LENGHT 11

 /* Punto 0 */
typedef struct {
	char cod[COD_LENGHT];
	char autore[STRING_LENGHT];
	char titolo[STRING_LENGHT];
	int quantita;
	float prezzo;
}Libro;

typedef struct nodoLista {
	Libro info;
	struct nodoLista* next;
}TipoNodoLista;

typedef TipoNodoLista* Lista;

/* Punto 1*/

/*
 * InserisciInTesta: inserisce un nuovo libro in testa alla lista di libri
 * parametri:
 * - l: puntatore alla lista di libri
 * - elem: libro da inserire
 *
 * restituisce:
 * - 1 se l'inserimento è andato a buon fine, -1 altrimenti
 */
int InserisciInTesta(Lista* l, Libro elem) {
	Lista aux;
	aux = (Lista) malloc(sizeof(TipoNodoLista));
	if (aux == NULL) {
		printf("Errore allocazione");
		return -1;
	}
	aux -> info = elem;
	aux -> next = *l;
	*l = aux;
	return 1;
	//da implementare a cura dello studente
}

/*
 * InserisciNuovoLibro: legge da tastiera i dati del nuovo libro e lo inserisce nella lista di libri.
 * parametri:
 * - l: puntatore alla lista di libri
 *
* restituisce:
 * - 1 se l'inserimento è andato a buon fine, -1 altrimenti
 */
int InserisciNuovoLibro(Lista *l) {
	//da implementare a cura dello studente
	Libro nuovo_libro;
	printf("\nInserisci codice:");
	scanf("%[^\n]s", nuovo_libro.cod);
	while (getchar() != '\n');
	printf("\nInserisci nome autore:");
	scanf("%[^\n]s", nuovo_libro.autore);
	while (getchar() != '\n');
	printf("\nInserisci il titolo:");
	scanf("%[^\n]s", nuovo_libro.titolo);
	while (getchar() != '\n');
	printf("\nInserisci quantita:");
	scanf("%d", &nuovo_libro.quantita);
	printf("\nInserisci prezzo:");
	scanf("%f", &nuovo_libro.prezzo);

	return InserisciInTesta(l, nuovo_libro);
}

/* Punto 2*/

/* EffettuaPrestito: dato il codice di un libro, effettua un prestito
 * parametri:
 * - l: lista di libri
 * - cod: stringa codice libro da prestare
 */
void EffettuaPrestito(Lista l, char* cod) {
	//da implementare a cura dello studente
	int trovato = 0;
	while ((l != NULL) && (trovato=!0)) {
		if (strcmp(l->info.cod, cod) == 0) {
			if (l->info.quantita > 0) {
				l->info.quantita--;
				printf("\nLibro prestato!");
			} else {
				printf("\nNon ci sono le copie del libro richiesto");
			}
		}
		l = l->next;
	}
	if (!trovato) {
		printf("\nLibro non trovato!");
	}
}

/* Punto 3*/
/*
 * CercaPerNome: stampa a video tutti i libri di un certo autore, dato il nome dell'autore
 * parametri:
 * - l: lista di libri
 * - nome_autore: nome dell'autore
 *
 * restituisce:
 * il numero totale di copie di libri di quell'autore
 */
int CercaPerNome(Lista l, char* nome_autore) {
int count=0; for (;l;l=l->next) if (!strcmp(l->info.autore,nome_autore)) { count+=l->info.quantita; printf("%s %d\n",l->info.titolo,l->info.quantita); } return count;
}

/* Punto 4*/

/*
 * CancellaLibroPerCodice: cancella un libro dalla lista dato il codice del libro.
 * parametri:
 * - l: puntatore alla lista di libri
 * - cod_libro: codice del libro da cancellare
 *
 * restituisce:
 * 1 se il libro è stato cancellato, -1 altrimenti
 */
int CancellaLibroPerCodice(Lista* l, char* cod_libro) {
while (*l && strcmp((*l)->info.cod,cod_libro)) l=&(*l)->next;
    if (!*l) return -1;
    Lista n=*l; *l=n->next; free(n); return 1;
}

/* Punto 5*/
/*
 * CancellaTuttiPerAutore: cancella dalla lista tutti i libri di un dato autore.
 * parametri:
 * - l: puntatore alla lista dei libri
 * - nome_autore: nome dell'autore di cui si vuole cancellare i libri
 *
 */
int CancellaTuttiPerAutore(Lista* l, char* nome_autore) {
int count=0;
    while (*l) { if (!strcmp((*l)->info.autore,nome_autore)) { Lista n=*l; *l=n->next; free(n); ++count; } else l=&(*l)->next; }
    return count;
}

/* Punto 6*/
/*
 * StampaLibriPrezzoInferiore: stampa a video tutti i libri il cui prezzo è inferiore al prezzo dato.
 * parametri:
 * - l: lista di libri
 * - prz: prezzo target
 */
void StampaLibriPrezzoInferiore(Lista l, int prz) {
	//da implementare a cura dello studente
	while (l != NULL) {
		if (l->info.prezzo < prz) {
			printf("\n cod: %s, titolo: %s, prezzo: %f", l->info.cod, l->info.titolo, l->info.prezzo);
		}
		l = l->next;
	}
}

/* Punto 7*/
/*
 * ScriviFileNonDisponibili: salva su file di testo tutti i libri non disponibili.
 * parametri:
 * - l: lista di libri
 * - nome_file: nome del file di testo in cui salvare le info.
 */
void ScriviFileNonDisponibili(Lista l, char* nome_file) {
FILE *f=fopen(nome_file,"w"); if (!f) return;
    for (;l;l=l->next) if (l->info.quantita==0) fprintf(f,"%s %s\n",l->info.cod,l->info.titolo);
    fclose(f);
}

/* Punto 8 */
/*
 * ScriviFileBinario: salva in un file binario tutti i dati dei libri contenuti nella lista.
 * (la scrittura nel file binario avviene libro-per-libro)
 * parametri:
 * - l: lista di libri
 * - nome_file: nome del file binario
 */
void ScriviFileBinario(Lista l, char* nome_file) {
	//da implementare a cura dello studente
	FILE* fp;
	if (l != NULL) {
		fp = fopen(nome_file, "wb");
		if (fp == NULL) {
			printf("\nErrore apertura file");
			return;
		}
		while (l != NULL) {
			fwrite(l->info.titolo, sizeof(Libro), 1, fp);
			l = l->next;
		}
		fclose(fp);
		printf("\nFile creato");
		return;
	}
	printf("\nLista vuota.");
}

/* Punto 9*/
/*
 * LeggiFileBinario: legge da file binario la lista dei libri presenti
 * parametri:
 * - l: puntatore alla lista di libri
 * - nome_file: nome del file binario
 */
void LeggiFileBinario(Lista* l, char* nome_file) {
	//da implementare a cura dello studente
	FILE* fp;
	Libro nuovo_libro;
	int num_read = 0;
	int count = 0;
	fp = fopen(nome_file, "rb");
	if (fp == NULL) {
		printf("\nErrore apertura file");
		return;
	}
	do {
		num_read = fread(&nuovo_libro, sizeof(Libro), 1, fp);
		if (num_read > 0) {
			if (InserisciInTesta(l, nuovo_libro) == -1)
				break;
			count++;
		}
	}while (!feof(fp));
	fclose(fp);
	printf("\nDati letti e memorizzati in Lista, letti %d records", count);
}

/* Punto 10 */
/*
 * StampaLibro: stampa un libro a video
 * parametri:
 * - l: libro da stampare
 */
void StampaLibro(Libro l) {
	//da implementare a cura dello studente
	printf("\n%s, %s, %s, %f, %d", l.cod, l.titolo, l.autore, l.prezzo, l.quantita);
}

/*
 * StampaLista: stampa a video una lista di libri
 * parametri:
 * - l: lista di libri
 */
void StampaLista(Lista l) {
	//da implementare a cura dello studente
	printf("\nCodice, Titolo, Autore, prezzo, quantita");
	while (l != NULL) {
		StampaLibro(l->info);
		l = l->next;
	}
	printf("\n ** FINE LISTA **\n\n");
}

/* Punto 11 */
/*
 * Cancella Lista: cancella (e dealloca) una lista
 * parametri:
 * - l: lista di libri
 */
void CancellaLista(Lista* l) {
	//da implementare a cura dello studente
	Lista paux;
	while (*l != NULL) {
		paux = *l;
		*l = (*l)->next;
		free(paux);
	}
	printf("\nLista cancellata.");
}


/*main*/

int main(void) {

	Lista libreria = NULL;
	Libro elem;
	int scelta = -1;
	char codice[COD_LENGHT];
	char autore[STRING_LENGHT];
	char nome_file[STRING_LENGHT];
	int prezzo;


	do {
		printf("\n **** LIBRERIA ****");
		printf("\n1. Inserisci Nuovo Libro");
		printf("\n2. Prestito Libro");
		printf("\n3. Stampa Libri per autore");
		printf("\n4. Cancella Libro per codice");
		printf("\n5. Cancella Libri per autore");
		printf("\n6. Stampa Libri < prezzo");
		printf("\n7. Salva su file Libri non disponibili");
		printf("\n8. Salva dati su file binario ");
		printf("\n9. Leggi da file binario");
		printf("\n10. Stampa lista libri");
		printf("\n11. Cancella lista libri");
		printf("\n\n0. Esci");
		printf("\n\tscelta: ");

		scanf("%d", &scelta);
		while (getchar() != '\n');
		switch (scelta) {
		case 1:
			InserisciNuovoLibro(&libreria);
			break;
		case 2:
			printf("\nInserisci codice libro: ");
			scanf("%[^\n]s", codice);
			while (getchar() != '\n');
			EffettuaPrestito(libreria, codice);
			break;
		case 3:
			printf("\nInserisci nome autore: ");
			scanf("%[^\n]s", autore);
			while (getchar() != '\n');
			CercaPerNome(libreria, autore);
			break;
		case 4:
			printf("\nInserisci codice libro: ");
			scanf("%[^\n]s", codice);
			while (getchar() != '\n');
			CancellaLibroPerCodice(&libreria, codice);
			break;
		case 5:
			printf("\nInserisci nome autore: ");
			scanf("%[^\n]s", autore);
			while (getchar() != '\n');
			CancellaTuttiPerAutore(&libreria, autore);
			break;
		case 6:
			printf("\nInserisci prezzo: ");
			scanf("%d", &prezzo);
			StampaLibriPrezzoInferiore(libreria, prezzo);
			break;
		case 7:
			printf("\nInserisci nome file: ");
			scanf("%[^\n]s", nome_file);
			while (getchar() != '\n');
			ScriviFileNonDisponibili(libreria, nome_file);
			break;
		case 8:
			printf("\nInserisci nome file:");
			scanf("%[^\n]s", nome_file);
			while (getchar() != '\n');
			ScriviFileBinario(libreria, nome_file);
			break;
		case 9:
			printf("\nInserisci nome file: ");
			scanf("%[^\n]s", nome_file);
			while (getchar() != '\n');
			LeggiFileBinario(&libreria, nome_file);
			break;
		case 10:
			StampaLista(libreria);
			break;
		case 11:
		case 0:
			CancellaLista(&libreria);
			break;
		default:
			printf("\nscelta errata.");

		}
	} while (scelta != 0);

	return 0;
}