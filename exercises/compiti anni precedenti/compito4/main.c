/***********************************************************************************************************
* === MODULO 2 ===
* TEMPO: 120 minuti
*
* Implementare in ANSI C un programma per la gestione di una rete di stazioni meteorologiche,
* ciascuna dotata di una serie di sensori che registrano periodicamente dati ambientali.
*
* Ogni stazione è identificata da un codice (es. "CT", "RM", "MI") ed è associata a una coda di
* rilevazioni meteorologiche in ordine di acquisizione.
*
* Ogni rilevazione è caratterizzata da:
* - un timestamp (es.: "2025-06-01_14:30")
* - un tipo di sensore, rappresentato con un intero:
*     0 = temperatura
*     1 = pressione
*     2 = umidità
* - un valore rilevato (float)
*
* Le stazioni sono memorizzate in una lista. Se una stazione non è ancora presente, viene aggiunta dinamicamente in testa.
* Ogni nodo della lista rappresenta una stazione meteorologica e contiene:
*   - il codice della stazione
*   - una coda contenente le rilevazioni
*   - la lunghezza corrente della coda (numero di rilevazioni presenti)
*
* Il programma deve implementare le seguenti funzionalità:
*
* 1. Caricare i dati da un file di testo "dati.txt" e memorizzarli in una lista di code.
*    Ogni riga del file contiene: codice_stazione, timestamp, tipo_sensore (intero), valore.
*    Se una stazione non è ancora presente, deve essere aggiunta dinamicamente.
*
* 2. Dato un codice stazione, quantificare il numero di rilevazioni per ciascun tipo di sensore.
*
* 3. Restituire il codice di tutte le stazioni che hanno registrato un valore di temperatura superiore a una soglia
*    (passata come parametro) per almeno 3 rilevazioni consecutive, tramite vettore dinamico di stringhe.
*
* 4. Creare un albero binario di ricerca ordinato per timestamp, contenente tutte le rilevazioni di un tipo
*    specifico di sensore (passato da parametro) di tutte le stazioni.
*
* 5. Salvare in ordine crescente di timestamp tutte le rilevazioni contenute nell'albero e con valore maggiore di una soglia
*    (passata come parametro), in un file di testo "albero.txt".
*
* 6. Deallocare la memoria allocata dinamicamente per la lista di stazioni e l'albero.
*
***** FUNZIONI DA IMPLEMENTARE *****
*
* -  unsigned int carica_dati(const char* nome_file, ListaStazioni* lista)
* -  int* conta_rilevazioni_per_tipo(ListaStazioni lista, const char* codice_stazione)
* -  char** stazioni_alta_temperatura(ListaStazioni* lista, float soglia, unsigned int* num_stazioni)
* -  Albero crea_albero(ListaStazioni* lista, TipoSensore tipo)
* -  void salva_albero_file(Albero a, FILE* f_out, float soglia)
* -  void dealloca_lista(ListaStazioni *lista)
* -  void dealloca_albero(Albero *a)
*
*Usando il valori presenti nei file di esempio i risultati attesi sono:

*Carica Dati:
	Caricate 8 stazioni.
	Stazione: PA, Numero rilevazioni: 3
	  Rilevazione: 2025-06-02_07:30, Tipo: Temperatura, Valore: 27.20
	  Rilevazione: 2025-06-02_08:00, Tipo: Pressione, Valore: 65.00
	  Rilevazione: 2025-06-02_08:15, Tipo: Umidita, Valore: 1010.00
	Stazione: GE, Numero rilevazioni: 4
	  Rilevazione: 2025-06-02_07:00, Tipo: Pressione, Valore: 75.00
	  Rilevazione: 2025-06-02_08:00, Tipo: Temperatura, Valore: 21.70
	  Rilevazione: 2025-06-02_08:30, Tipo: Temperatura, Valore: 22.10
	  Rilevazione: 2025-06-02_09:00, Tipo: Umidita, Valore: 1012.00
	Stazione: TO, Numero rilevazioni: 3
	  Rilevazione: 2025-06-02_08:00, Tipo: Temperatura, Valore: 19.40
	  Rilevazione: 2025-06-02_08:15, Tipo: Umidita, Valore: 1009.70
	  Rilevazione: 2025-06-02_08:30, Tipo: Pressione, Valore: 80.50
	Stazione: NA, Numero rilevazioni: 3
	  Rilevazione: 2025-06-01_10:00, Tipo: Temperatura, Valore: 28.50
	  Rilevazione: 2025-06-01_11:00, Tipo: Umidita, Valore: 1011.20
	  Rilevazione: 2025-06-01_12:00, Tipo: Temperatura, Valore: 29.30
	Stazione: FI, Numero rilevazioni: 4
	  Rilevazione: 2025-06-01_09:20, Tipo: Umidita, Valore: 1010.50
	  Rilevazione: 2025-06-01_09:40, Tipo: Temperatura, Valore: 23.00
	  Rilevazione: 2025-06-01_10:00, Tipo: Pressione, Valore: 60.00
	  Rilevazione: 2025-06-01_10:20, Tipo: Temperatura, Valore: 24.50
	Stazione: RM, Numero rilevazioni: 4
	  Rilevazione: 2025-06-01_08:15, Tipo: Umidita, Valore: 1012.30
	  Rilevazione: 2025-06-01_08:45, Tipo: Temperatura, Valore: 25.00
	  Rilevazione: 2025-06-01_09:15, Tipo: Temperatura, Valore: 26.20
	  Rilevazione: 2025-06-01_09:45, Tipo: Temperatura, Valore: 27.00
	Stazione: CT, Numero rilevazioni: 4
	  Rilevazione: 2025-06-01_08:00, Tipo: Temperatura, Valore: 22.50
	  Rilevazione: 2025-06-01_09:00, Tipo: Pressione, Valore: 68.00
	  Rilevazione: 2025-06-01_10:00, Tipo: Temperatura, Valore: 23.10
	  Rilevazione: 2025-06-01_11:00, Tipo: Umidita, Valore: 1013.50
	Stazione: MI, Numero rilevazioni: 5
	  Rilevazione: 2025-06-01_07:30, Tipo: Pressione, Valore: 70.10
	  Rilevazione: 2025-06-01_08:00, Tipo: Temperatura, Valore: 19.80
	  Rilevazione: 2025-06-01_08:30, Tipo: Umidita, Valore: 1011.00
	  Rilevazione: 2025-06-01_09:00, Tipo: Temperatura, Valore: 20.30
	  Rilevazione: 2025-06-01_09:30, Tipo: Temperatura, Valore: 21.10
*
*
* Stazioni con temperatura alta:
Inserisci soglia temperatura: [10]
Stazioni con temperatura superiore a 10.00 per almeno 3 rilevazioni consecutive:
RM
MI
***********************************************************************************************************/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_INPUT "dati.txt"
#define FILE_OUTPUT "albero.txt"

#define STR_LEN 17
#define NUM_TIPI_SENSORE 3 // Numero di tipi di sensore (temperatura, umidita, pressione)
#define NUM_RILEVAZIONI_CONSECUTIVE 3 // Numero minimo di rilevazioni consecutive per considerare una temperatura alta

/* strutture dati Rilevazioni */
typedef enum {
	TEMPERATURA,
	UMIDITA,
	PRESSIONE
}TipoSensore;

const char* sensore_to_string(TipoSensore tipo) {
	const char* sensori[] = { "Temperatura", "Umidita", "Pressione" };
	return (tipo >= 0 && tipo < NUM_TIPI_SENSORE) ? sensori[tipo] : "Sconosciuto";
}


typedef struct {
	char timestamp[STR_LEN]; // formato "YYYY-MM-DD_hh:mm"
	TipoSensore tipo;
	float valore;
}Rilevazione;

/* Strutture dati coda rilevazioni */
typedef struct nodo_rilevazione {
	Rilevazione rilevazione;
	struct nodo_rilevazione* next;
}NodoRilevazione;

typedef struct {
	NodoRilevazione* primo;
	NodoRilevazione* ultimo;
	unsigned int num_rilevazioni; // numero di rilevazioni nella coda
}CodaRilevazioni;

/* Struttura dati lista stazioni */
typedef struct nodo_stazione {
	char codice[STR_LEN];
	CodaRilevazioni coda;
	struct nodo_stazione* next;
}NodoStazione;

typedef NodoStazione* ListaStazioni;

/* inizializza una coda di rilevazioni */
void inizializza_coda(CodaRilevazioni* coda) {
	coda->primo = NULL;
	coda->ultimo = NULL;
	coda->num_rilevazioni = 0;
}

/* Inserisci una nuova rilevazione nella coda di una stazione
*
* Parametri in ingresso:
* - coda: puntatore alla coda di rilevazioni della stazione
* - r: la rilevazione da aggiungere
*
* Valore di ritorno:
* 1 se l'inserimento è avvenuto con successo, 0 altrimenti
*/
int aggiungi_rilevazione(CodaRilevazioni* coda, Rilevazione r) {
	NodoRilevazione* nuovo_nodo = (NodoRilevazione*)malloc(sizeof(NodoRilevazione));
	if (nuovo_nodo == NULL) {
		printf("Errore allocazione memoria.");
		return 0;
	}
	nuovo_nodo->rilevazione = r;
	nuovo_nodo->next = NULL;

	if (coda->primo == NULL)
		coda->primo = nuovo_nodo;
	else
		coda->ultimo->next = nuovo_nodo;

	coda->ultimo = nuovo_nodo;
	coda->num_rilevazioni++;
	return 1;
}

/*
* Aggiunge una nuova stazione alla lista di stazioni.
* * Parametri in ingresso:
* - lista: puntatore alla lista di stazioni
* - codice: codice della stazione da aggiungere
*
* Valore di ritorno:
* 1 se l'aggiunta è avvenuta con successo, 0 altrimenti

*/
int aggiungi_stazione(ListaStazioni* lista, const char* codice) {
	NodoStazione* nuovo_nodo = (NodoStazione*)malloc(sizeof(NodoStazione));
	if (nuovo_nodo == NULL) {
		printf("Errore allocazione memoria.");
		return 0;
	}
	strcpy(nuovo_nodo->codice, codice);
	nuovo_nodo->next = *lista;

	inizializza_coda(&nuovo_nodo->coda);
	*lista = nuovo_nodo;

	return 1;
}

/*
* Cerca un nodo stazione nella lista di stazioni.
*
* Parametri in ingresso:
* - lista: puntatore alla lista di stazioni
* - codice: codice della stazione da cercare
*
* Valore di ritorno:
* - puntatore al nodo stazione se trovato, NULL altrimenti
*/
NodoStazione* trova_stazione(ListaStazioni lista, const char* codice) {
	if (lista == NULL) return NULL;
	if (!strcmp(lista->codice, codice)) return lista;
	return trova_stazione(lista->next, codice);
}

/* Quesito 1
* Carica i dati dal file e li memorizza nella lista di stazioni.
*
* Il file di input ha il seguente formato:
* codice_stazione timestamp tipo_sensore valore.
* Esempio:
*
* MI 2025-06-01_07:30 2 70.1
* CT 2025-06-01_08:00 0 22.5
* MI 2025-06-01_08:00 0 19.8
* CT 2025-06-01_09:00 2 68.0
* RM 2025-06-01_08:15 1 1012.3
* ...
*
* Parametri in ingresso:
* - nome_file: nome del file da cui caricare i dati
*
* Parametri in uscita:
* - lista: puntatore alla lista di stazioni in cui memorizzare i dati
*
* Valore di ritorno:
* - numero di stazioni caricate
*/
unsigned int carica_dati(const char* nome_file, ListaStazioni* lista) {

	FILE* file = fopen(nome_file, "r");
	if (file == NULL) {
		printf("Errore apertura file %s", nome_file);
		return 0;
	}
	// TODO: Da completare
	Rilevazione r;
	char codice_stazione[STR_LEN];
	unsigned int num_stazioni = 0;
    int tipo_letto;
	while(fscanf(file, "%s %s %d %f", codice_stazione, r.timestamp, &tipo_letto, &r.valore) == 4) {
        if (tipo_letto < 0 || tipo_letto >= NUM_TIPI_SENSORE) continue;
        r.tipo = (TipoSensore)tipo_letto;
		NodoStazione*stazione = trova_stazione(*lista, codice_stazione);
		if (stazione == NULL) {
			if (!aggiungi_stazione(lista, codice_stazione)) {
				fclose(file);
				return num_stazioni;
			}
			stazione = *lista;
			num_stazioni++;
		}
		if (!aggiungi_rilevazione(&stazione->coda, r)) {
			fclose(file);
			return num_stazioni;
		}
	}
	fclose(file);
	return num_stazioni;
}


/* Stampa le stazioni e le loro rilevazioni */
void stampa_stazioni_rilevazioni(ListaStazioni* lista) {

	NodoStazione* aux = *lista;
	while (aux != NULL) {
		printf("Stazione: %s, Numero rilevazioni: %u\n", aux->codice, aux->coda.num_rilevazioni);
		NodoRilevazione* r = aux->coda.primo;
		while (r != NULL) {
			printf("  Rilevazione: %s, Tipo: %s, Valore: %.2f\n", r->rilevazione.timestamp, sensore_to_string(r->rilevazione.tipo), r->rilevazione.valore);
			r = r->next;
		}
		aux = aux->next;
	}
}



/* Quesito 2
* Conta il numero di rilevazioni per tipo di sensore e restituisce un array dinamico
*
* Parametri in ingreso:
* - lista: lista di stazioni
* - codice_stazione: codice della stazione per cui contare le rilevazioni
*
* Valore di ritorno:
* - puntatore al vettore che contiene il numero di rilevazioni per tipo di sensore
*/
int* conta_rilevazioni_per_tipo(ListaStazioni lista, const char* codice_stazione) {

	// TODO: Da completare
	NodoStazione *stazione = trova_stazione(lista, codice_stazione);
	if (stazione == NULL) {
		printf("Stazione %s non trovata\n", codice_stazione);
		return NULL;
	}

	int* contatori = calloc(NUM_TIPI_SENSORE, sizeof(int));
	if (contatori == NULL) {
		printf("Errore allocazione memoria.");
		return NULL;
	}

	NodoRilevazione* nodo = stazione->coda.primo;
	while (nodo != NULL) {
		contatori[nodo->rilevazione.tipo]++;
		nodo = nodo->next;
	}
	return contatori;
}

/* Quesito 3
*
* Costruisce il vettore dei codici delle stazioni che hanno registrato un valore di temperatura superiore ad una certa soglia
*    per almeno 3 rilevazioni consecutive.
*
* Parametri in ingresso:
*	- lista: puntatore alla lista di stazioni
*   - soglia: valore di soglia per la temperatura
*
* Parametri in uscita:
*	- num_stazioni: puntatore al numero di stazioni trovate
*
* Valore di ritorno:
* - puntatore al vettore di stringhe contenente i codici delle stazioni che soddisfano la condizione
*  Se non ci sono stazioni che soddisfano la condizione, il valore restituito è NULL e num_stazioni è 0.
*
*
* NOTA:
*  La funzione restituisce un vettore dinamico di stringhe (char**), dove ogni stringa è il codice di una stazione.
*  Il vettore e ogni singola stringa al suo interno devono essere allocati dinamicamente.
*/
char** stazioni_alta_temperatura(ListaStazioni* lista, float soglia, unsigned int* num_stazioni) {

	// TODO: Da completare

	*num_stazioni = 0;
	NodoStazione* aux = *lista;
	while (aux != NULL) {
		NodoRilevazione* r = aux->coda.primo;
		int cont = 0;
		while (r != NULL) {
			if (r->rilevazione.tipo == TEMPERATURA && r->rilevazione.valore > soglia) {
				cont++;
			} else
				cont = 0;
			if (cont == NUM_RILEVAZIONI_CONSECUTIVE) {
				(*num_stazioni)++;
				break;
			}
			r = r->next;
		}
		aux = aux->next;
	}

	if (*num_stazioni == 0) {

		return NULL;
	}

	char** codici_stazioni = (char**) malloc((*num_stazioni) * sizeof(char*));
	if (codici_stazioni == NULL) {
		printf("Errore allocazione memoria.");
		*num_stazioni = 0;
		return NULL;
	}

	aux = *lista;
	int index = 0;
	while (aux != NULL) {
		NodoRilevazione* r = aux->coda.primo;
		int cont = 0;
		while (r != NULL) {
			if (r->rilevazione.tipo == TEMPERATURA) {
				if (r->rilevazione.tipo == TEMPERATURA && r->rilevazione.valore > soglia) {
					cont++;
				} else
					cont = 0;
				if (cont == NUM_RILEVAZIONI_CONSECUTIVE) {
					codici_stazioni[index] = (char*)malloc(STR_LEN * sizeof(char));
					if (codici_stazioni[index] == NULL) {
						printf("Errore allocazione memoria.");
						for (int i = 0; i<index; i++) {
							free(codici_stazioni[i]);
						}
						free(codici_stazioni);
						*num_stazioni = 0;
						return NULL;
					}
					strcpy(codici_stazioni[index++], aux->codice);
					break;
				}
			}
			r = r->next;
		}
		aux = aux->next;
	}
	return codici_stazioni;
}



/* struttura dati albero */
typedef struct nodo_albero {
	Rilevazione rilevazione;
	struct nodo_albero* sx;
	struct nodo_albero* dx;
}NodoAlbero;

typedef NodoAlbero* Albero;

/* Inizializza un albero di ricerca */
void inizializza_albero(Albero* albero) {
	*albero = NULL;
}



/* Quesito 4*/
/*
* Inserisce un nodo nell'albero
*/
Albero inserisci_nodo(Albero radice, Rilevazione r) {

	if (radice == NULL) {
		NodoAlbero* nuovo_nodo = (NodoAlbero*) malloc(sizeof(NodoAlbero));
		if (nuovo_nodo == NULL) {
			printf("Errore allocazione memoria.");
			return NULL;
		}
		nuovo_nodo->rilevazione = r;
		nuovo_nodo->sx = nuovo_nodo->dx = NULL;
		return nuovo_nodo;
	}
	if (strcmp(radice->rilevazione.timestamp, r.timestamp) > 0)
		radice->sx = inserisci_nodo(radice->sx, r);
	else if (strcmp(radice->rilevazione.timestamp, r.timestamp) < 0)
		radice->dx = inserisci_nodo(radice->dx, r);
	return radice;
}


/* Crea l'albero dai dati delle rilevazioni.
*
* Parametri in ingresso:
* - lista: puntatore alla lista di stazioni
* - tipo: tipo di sensore per cui creare l'albero
*
* Valore di ritorno:
* - puntatore all'albero di ricerca creato
*/
Albero crea_albero(ListaStazioni* lista, TipoSensore tipo) {

	// TODO: Da completare
	Albero albero = NULL;
	NodoStazione* aux = *lista;
	while (aux != NULL) {
		NodoRilevazione *r = aux->coda.primo;
		while (r != NULL) {
			if (r->rilevazione.tipo == tipo) {
				albero = inserisci_nodo(albero, r->rilevazione);
			}
			r = r->next;
		}
		aux = aux->next;
	}
	return albero;
}



/*
* Quesito 5
* Salva, in ordine di timestamp crescente, le rilevazioni dell'albero in un file, filtrando per soglia.
*
* Parametri in ingresso:
* - a: albero di ricerca contenente le rilevazioni
* - f_out: puntatore al file di output
* - soglia: valore di soglia per filtrare le rilevazioni
*
*/
void salva_albero_file(Albero a, FILE* f_out, float soglia){

	//TODO: Da completare
	if (a == NULL) {
		return;
	}
	salva_albero_file(a->sx, f_out, soglia);
	if (a->rilevazione.valore >= soglia) {
		fprintf(f_out, "%s %s %f\n", a->rilevazione.timestamp, sensore_to_string(a->rilevazione.tipo), a->rilevazione.valore);
	}
	salva_albero_file(a->dx, f_out, soglia);
}



/*
* Quesito 6
* Deallocare la memoria allocata dinamicamente per la lista di stazioni e l'albero.
*
*/


/*
* Dealloca la memoria allocata per la lista di stazioni e le loro rilevazioni.
*
* Parametri in ingresso:
* - lista: puntatore alla lista di stazioni
*/
void dealloca_lista(ListaStazioni *lista) {
	// TODO: Da completare
	while (*lista != NULL) {
		NodoStazione*next = (*lista)->next;
		NodoRilevazione *r = (*lista)->coda.primo;
		while (r != NULL) {
			NodoRilevazione*r_next = r->next;
			free(r);
			r = r_next;
		}
		free(*lista);
		*lista = next;
	}
}


/*
* Dealloca la memoria allocata per l'albero di ricerca
*
* Parametri in ingresso:
* - a: puntatore all'albero di ricerca da deallocare
*/
void dealloca_albero(Albero *a) {
if (!a || !*a) return;
    dealloca_albero(&(*a)->sx); dealloca_albero(&(*a)->dx); free(*a); *a=NULL;
}





int menu() {

	int scelta;
	printf("\n*** MENU *** \n"
		"1. Carica dati da file\n"
		"2. Conta rilevazioni per tipo\n"
		"3. Stazioni con temperatura alta\n"
		"4. Crea albero di ricerca\n"
		"5. Salva rilevazioni sopra soglia su file\n"
		"0. Esci\n"
		"Inserisci scelta: "
	);
	scanf("%d", &scelta);
	return scelta;
}



int main() {
	ListaStazioni lista_stazioni = NULL;
	unsigned int num_stazioni = 0;
	char codice_stazione[STR_LEN];
	int scelta;
	float valore_soglia;
	char** vettore_stazioni = NULL;
	Albero albero = NULL;
	TipoSensore tipo_sensore;
	FILE* f_out;

	do {
		scelta = menu();

		switch (scelta) {
		case 1:
			if (lista_stazioni != NULL) {
				dealloca_lista(&lista_stazioni); // Dealloca la lista se già esiste
			}
			num_stazioni = carica_dati(FILE_INPUT, &lista_stazioni);
			printf("Caricate %u stazioni.\n", num_stazioni);
			stampa_stazioni_rilevazioni(&lista_stazioni);
			break;
		case 2:
			printf("Inserisci codice stazione: ");
			scanf("%s", codice_stazione);
			int* conteggi = conta_rilevazioni_per_tipo(lista_stazioni, codice_stazione);
			if (conteggi) {
				printf("Rilevazioni per tipo:\n");
				for (int i = 0; i < NUM_TIPI_SENSORE; i++) {
					printf("%s: %d\n", sensore_to_string(i), conteggi[i]);
				}
				free(conteggi);
			}
			break;
		case 3:
			printf("Inserisci soglia temperatura: ");
			scanf("%f", &valore_soglia);
			vettore_stazioni = stazioni_alta_temperatura(&lista_stazioni, valore_soglia, &num_stazioni);
			if (vettore_stazioni != NULL) {
				printf("Stazioni con temperatura superiore a %.2f per almeno %d rilevazioni consecutive:\n", valore_soglia, NUM_RILEVAZIONI_CONSECUTIVE);
				for (unsigned int i = 0; i < num_stazioni; i++) {
					printf("%s\n", vettore_stazioni[i]);
					free(vettore_stazioni[i]);
				}
				free(vettore_stazioni);
			} else {
				printf("Nessuna stazione trovata.\n");
			}
			break;
		case 4:
			do {
				printf("Inserisci tipo di sensore (%d: %s, %d: %s, %d: %s): ", TEMPERATURA, sensore_to_string(TEMPERATURA), UMIDITA, sensore_to_string(UMIDITA), PRESSIONE, sensore_to_string(PRESSIONE));
				int tipo_input;
                if (scanf("%d", &tipo_input) != 1) tipo_input = 0;
                tipo_sensore = (TipoSensore)tipo_input;
			} while (tipo_sensore < 0 || tipo_sensore >= NUM_TIPI_SENSORE);
			dealloca_albero(&albero); // Dealloca l'albero se già esiste
			albero = crea_albero(&lista_stazioni, tipo_sensore);
			printf("Albero creato.\n");
			break;
		case 5:
			f_out = fopen(FILE_OUTPUT, "w+");
			if (f_out == NULL) {
				printf("Errore apertura file %s", FILE_OUTPUT);
				break;
			}
			printf("Inserisci valore soglia: ");
			scanf("%f", &valore_soglia);
			salva_albero_file(albero, f_out, valore_soglia);
			fclose(f_out);
			printf("File salvato\n");
			break;
		case 0:
			printf("Uscita dal programma\n");
			break;
		default:
			printf("Scelta non valida\n");
			break;
		}
	} while (scelta != 0);

	//Deallocazione memoria
	dealloca_lista(&lista_stazioni);
	dealloca_albero(&albero);
}