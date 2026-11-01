/***************************************************************************************************************
* ==== MODULO 2 =====
* 
* Implementare un programma ANSI C per la gestione dei voli di una compagnia aerea.
* 
* In un file di testo ("voli.txt") è memorizzato l'elenco dei voli con i loro rispettivi dati.
* In un altro file di testo ("biglietti.txt") è memorizzato l'elenco di tutti i biglietti venduti
* 
* I voli sono caratterizzati da un codice univoco, dal nome della compagnia aerea, dall'aeroporto di partenza, dall'aeroporto di arrivo,
* dall'orario di partenza e di arrivo (entrambi forniti nel fuso orario del luogo di partenza), dal costo del biglietto  
* e dalla lista dei passeggeri ordinata per posto assegnato.
* Le file dei posti sono numerate da "01" a "10"; ogni fila ha 4 posti, identificati dalle lettere 'A', 'B', 'C', 'D'.
* I posti devono essere ordinati in ordine crescente: "01A" < "01B" < "01C" < ...  < "10C" < "10D". 
* Si suppone quindi che ogni volo abbia esattamente 40 posti disponibili. 
* 
* Per ogni passeggero è memorizzato:
* - nome
* - cognome
* - posto assegnato
* - stato del check-in (0: non effettuato; 1: effettuato)
* 
* La struttura dati principale del programma è una lista di voli, dove ciascun nodo rappresenta un volo e contiene una lista ordinata
* dei passeggeri. 
* 
* 
* Il programma deve eseguire le seguenti operazioni: 
* 
* 2a. Caricare i dati dei voli e dei passeggeri dai due file e memorizzarli opportunamente in una lista di liste ordinate.
*     Ogni nodo della lista rappresenta un volo, e contiene la lista dei passeggeri di quel volo ordinata per posto crescente. 
* 
* 2b. Vendita biglietto: dato un codice volo, memorizzare l'acquisto di un nuovo biglietto e assegnare il primo posto disponibile
* 
* 2c. Restituire il numero totale di posti disponibili per ogni volo tramite vettore. 
*
* TEMPO: 120 minuti
* 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_VOLI "voli.txt"
#define FILE_BIGLIETTI "biglietti.txt"

#define STR_LEN 30
#define COD_LEN 4
#define FL_LEN 6

#define MAX_FILE_AEREO 10
#define MAX_POSTI_AEREO 40

/* Struttura dati biglietto */
typedef struct {
	char posto[COD_LEN];
	char nome[STR_LEN];
	char cognome[STR_LEN];
	unsigned int check_in; //0: non effettuato; 1: effettuato
}T_Biglietto;

/* Struttura dati nodo lista biglietti */
typedef struct nodo_biglietto {
	T_Biglietto prenotazione;
	struct nodo_biglietto* next;
}NodoListaBiglietto;

typedef NodoListaBiglietto* ListaBiglietti;

/* Struttura dati Volo */
typedef struct {
	char codice_volo[FL_LEN];
	float costo;
	char partenza[STR_LEN];
	char destinazione[STR_LEN];
	char orario_decollo[6];
	char orario_atterraggio[6];
	ListaBiglietti prenotazioni;
}T_Volo;

/* Struttura dati nodo lista Voli*/
typedef struct nodo_volo {
	T_Volo info;
	struct nodo_volo* next;
}NodoListaVolo;

typedef NodoListaVolo* ListaVoli;

/* Struttura dati stato volo;
* usata per contare i posti disponibili dei voli
*/
typedef struct {
	char codice_volo[FL_LEN];
	unsigned int posti_diponibili;
}stato_volo;



/* Cerca un nodo della lista dei voli in base al codice volo
* 
*  Parametri in ingresso:
*  - lista_voli: lista dei voli
*  - codice: codice del volo da ricercare
* 
*  Valore di ritorno:
*  - Puntatore al volo corrispondente, NULL se il volo non è stato trovato
*/
T_Volo* cerca_volo_codice(ListaVoli lista_voli, const char* codice) {
	if (lista_voli == NULL) return NULL;
	if (strcmp(lista_voli->info.codice_volo, codice) == 0) return &(lista_voli->info);
	return cerca_volo_codice(lista_voli->next, codice);
}



/*
* Inserisci una nuova prenotazione nella lista dei biglietti ordinata per posto assegnato
* 
* Parametri in ingresso:
* - lista_biglietti: lista dei biglietti di uno specifico volo
* - biglietto: dati del nuovo biglietto
* 
* Valore di ritorno:
* - 1 se l'inserimento è andato a buon fine, 0 altrimenti
*/
int aggiungi_prenotazione_ordinato(ListaBiglietti* lista_biglietti, T_Biglietto biglietto) {
	//TODO: da completare
	if (*lista_biglietti == NULL || strcmp((*lista_biglietti)->prenotazione.posto, biglietto.posto) > 0) {
		NodoListaBiglietto *nodo = (NodoListaBiglietto*)malloc(sizeof(NodoListaBiglietto));
		if (nodo == NULL) return 0;
		nodo->prenotazione = biglietto;
		nodo->next = *lista_biglietti;
		*lista_biglietti = nodo;
		return 1;
	} else return aggiungi_prenotazione_ordinato(&(*lista_biglietti)->next, biglietto);
}


/* Inserisci un nuovo volo in testa alla lista dei voli
* 
*  Parametri in ingresso:
*  - lista_voli: puntatore alla lista dei voli;
*  - volo: volo da aggiungere
* 
*  Valore di ritorno:
*  - 1 se l'aggiunta è andata a buon fine, 0 altrimenti
*/
int aggiungi_volo(ListaVoli* lista_voli, T_Volo volo) {

	NodoListaVolo* nodo = (NodoListaVolo*)malloc(sizeof(NodoListaVolo));
	if (nodo == NULL) return 0;

	nodo->info = volo;
	nodo->next = *lista_voli;
	*lista_voli = nodo;
	return 1;
}



/*
* Quesito 2a
* Carica i dati dai file e li inserisce nella lista di liste
*
* Il file voli.txt ha il seguente formato:
* codice_volo, partenza, destinazione, ora_decollo, ora_atterraggio, costo
*
* Esempio voli.txt :
* AZ123 FCO JFK 10:30 14:00 650.00
* BA456 LHR JFK 09:00 12:30 700.00
* ...
*
* Il file biglietti.txt ha il seguente formato:
* codice_volo, cognome, nome, posto, stato check-in
*
* Esempio biglietti.txt :
* AF654 Luca Blu 10B 1
* QR902 Elena Verde 12C 1
* ...
*
* Parametri in ingresso:
* - nome_file_voli: nome del file contenente i voli
* - nome_file_biglietti: nome del file contenente i biglietti
*
* Parametri in uscita:
* - lista_voli: puntatore alla lista dei voli
*
* Valore di ritorno:
* - numero di biglietti caricati
*/
int carica_dati(char* nome_file_voli, char* nome_file_biglietti, ListaVoli* lista_voli) {
	T_Volo volo;
	T_Biglietto biglietto;
	char codice_volo[FL_LEN];
	T_Volo* cerca_volo;
	int n_biglietti = 0;

	FILE* fp = fopen(nome_file_voli, "r");
	if (fp == NULL) return 0;

	//TODO: da completare
	while (fscanf(fp, "%s %s %s %s %s %f", volo.codice_volo, volo.partenza, volo.destinazione, volo.orario_decollo, volo.orario_atterraggio, &volo.costo ) == 6) {
		volo.prenotazioni = NULL;

		if (aggiungi_volo(lista_voli, volo) == 0) {
			fclose(fp);
			return n_biglietti;
		}
	}

	fclose(fp);

	fp = fopen(nome_file_biglietti, "r");
	if (fp == NULL) return n_biglietti;

	while (fscanf(fp, "%s %s %s %s %u", codice_volo, biglietto.cognome, biglietto.nome, biglietto.posto, &biglietto.check_in) == 5) {
		cerca_volo = cerca_volo_codice(*lista_voli, codice_volo);

		if (cerca_volo != NULL) {
			if (aggiungi_prenotazione_ordinato(&cerca_volo->prenotazioni, biglietto) == 1) {
				n_biglietti++;
			}
		}
	}
	fclose(fp);
	return n_biglietti;
}

/*
*  Funzione ricerca primo posto disponibile data una lista di prenotazioni
* 
*  Parametri in ingresso:
*  - lista_biglietti: lista delle prenotazioni di un dato volo
*  
*  Valore di ritorno:
*  - stringa corrispondente al primo posto disponibile, NULL se l'aereo è pieno
* 
*/
char* primo_posto_disponibile(ListaBiglietti lista_biglietti) {
	
	char* posto_disponibile = malloc(4);
	if (posto_disponibile == NULL) {
		printf("Errore allocazione variabile");
		return NULL;
	}
	char lettere[4] = { 'A', 'B', 'C', 'D' };
	
	for (int fila = 1; fila <= MAX_FILE_AEREO; fila++) {
		for (int j = 0; j < 4; j++) {
			sprintf(posto_disponibile, "%02d%c", fila, lettere[j]);
			if (lista_biglietti == NULL) return posto_disponibile;
			if (strcmp(posto_disponibile, lista_biglietti->prenotazione.posto) < 0)
				return posto_disponibile;
			else if (strcmp(posto_disponibile, lista_biglietti->prenotazione.posto) == 0)
				lista_biglietti = lista_biglietti->next;
		}
	}
	free(posto_disponibile);
	return NULL;

}


/* Quesito 2b
* Crea una nuova prenotazione per un volo
* 
* Parametri in ingresso:
* 
* - lista_voli : lista dei voli
* - codice_volo : codice del volo
* - cognome : cognome del passeggero
* - nome : nome del passeggero
* 
* Valore di ritorno:
* 
* puntatore al volo corrispondente, NULL se il volo non è stato trovato o se non ci sono posti disponibili
* 
*/
T_Volo* nuova_prenotazione(ListaVoli lista_voli, const char* codice_volo, const char* cognome, const char* nome) {
T_Volo *v=cerca_volo_codice(lista_voli,codice_volo);
    if (!v || strlen(cognome)>=sizeof ((T_Biglietto*)0)->cognome || strlen(nome)>=sizeof ((T_Biglietto*)0)->nome) return NULL;
    char *posto=primo_posto_disponibile(v->prenotazioni); if (!posto) return NULL;
    T_Biglietto b={0}; strcpy(b.cognome,cognome); strcpy(b.nome,nome); strcpy(b.posto,posto); free(posto);
    return aggiungi_prenotazione_ordinato(&v->prenotazioni,b) ? v : NULL;
}


/*
* Quesito 2c
* Calcola i posti disponibili per ogni volo e memorizza i dati in un vettore allocato dinamicamente
* 
* Parametri in ingresso:
* - lista_voli: lista dei voli
* 
* Parametri in uscita:
* - dim: dimensione del vettore
* 
* Valore di ritorno:
* - puntatore al vettore
* 
*/
stato_volo* calcola_posti_disponibili(ListaVoli lista_voli, int* dim ) {
*dim=0; for (ListaVoli l=lista_voli;l;l=l->next) ++*dim;
    if (!*dim) return NULL;
    stato_volo *v=calloc((size_t)*dim,sizeof *v); if (!v) { *dim=0; return NULL; }
    int i=0; for (;lista_voli;lista_voli=lista_voli->next,++i) {
        strcpy(v[i].codice_volo,lista_voli->info.codice_volo); unsigned n=0;
        for (ListaBiglietti b=lista_voli->info.prenotazioni;b;b=b->next) ++n;
        v[i].posti_diponibili=n<40 ? 40-n : 0;
    } return v;
}


void stampa_prenotazione(T_Biglietto b) {
	printf("\n %s %s %s %u", b.posto, b.cognome, b.nome, b.check_in);
}

void stampa_volo(T_Volo* volo) {
	printf("\n\nvolo: %s\t %s %s", volo->codice_volo, volo->partenza, volo->destinazione);
	printf("\nlista prenotazini: ");
	NodoListaBiglietto* nodo = volo->prenotazioni;

	while (nodo != NULL) {
		stampa_prenotazione(nodo->prenotazione);
		nodo = nodo->next;
	}

}


int main() {
	int scelta;
	int num_biglietti = 0;
	int dim = 0;

	char codice_volo[FL_LEN];
	char cognome[STR_LEN], nome[STR_LEN];
	T_Volo* volo;
	ListaVoli lista_voli = NULL;
	stato_volo* vettr;

	do {
		printf("\n\n *** MENU ***"
			"\n 1. Carica da file"
			"\n 2. Vendita biglietto"
			"\n 3. Biglietti disponibili"
			"\n 0. Esci"
			"\n\nScelta: ");
		scanf("%d", &scelta);

		switch(scelta) {
		case 1:
			num_biglietti = carica_dati(FILE_VOLI, FILE_BIGLIETTI, &lista_voli);
			printf("\nTotale biglietti caricati: %d\n", num_biglietti);
			NodoListaVolo* nlv = lista_voli;
			while (nlv != NULL) {
				stampa_volo(&nlv->info);
				nlv = nlv->next;
			}
			break;
		case 2:

			printf("Inserisci codice volo: ");
			scanf("%s", codice_volo);
			printf("Inserisci cognome: ");
			scanf("%s", cognome);
			printf("Inserisci nome: ");
			scanf("%s", nome);

			volo = nuova_prenotazione(lista_voli, codice_volo, cognome, nome);
			if (volo == NULL) 
				printf("\nPrenotazione fallita.");
			else 
				printf("\n Prenotazione avvenuta.");
			stampa_volo(volo);

			break;
		case 3:
			vettr = calcola_posti_disponibili(lista_voli, &dim);
			for (int i = 0; i < dim; i++) {
				printf("\n codice: %s  posti_disponibili: %u", vettr[i].codice_volo, vettr[i].posti_diponibili);
			}
			free(vettr);
			dim = 0;
			break;
		case 0:
			return 0;

		default:
			printf("\nScelta non valida");
		}
		
	} while (scelta);
}