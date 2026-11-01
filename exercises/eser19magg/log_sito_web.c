#include "../../common/console.h"
/*esercitazione vettori di liste*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NOME_FILE "accessi.txt"
#define N 31
#define MAX_LENGHT 51

/* struttura dati Accesso */
typedef struct{
	int ora, minuti, secondi;
	char nome[MAX_LENGHT];
	int durata;
}T_Accesso;

/* definizione nodo Lista */
typedef struct StructLista {
	T_Accesso info;
	struct StructLista* next;
}TipoNodoLista;

/* definizione Lista */
typedef TipoNodoLista* List;


/* 1: Scrivere una funzione per l’inserimento in tale struttura di tutti i dati presenti nel file;
 * la funzione deve inoltre restituire il numero di elementi letti dal file;
*/

/* Funzione inserisci in testa Lista
 * Restituisce 1 se l'inserimento è stato effettuato correttamente; 0 altrimenti.
 */
int InserisciInTestaLista(List* l, T_Accesso elem) {
	
	//TODO: da completare

	List aux = malloc(sizeof(TipoNodoLista));
	if (aux == NULL) {
		printf("Errore allocazione");
		return 0;
	}
	aux->info = elem;
	aux->next = *l;
	*l = aux;
	return 1;
}

/*
 * Carica i dati dal file e li inserisce in un vettore di liste.
 * Parametri:
 * - vett: vettore di Liste
 * - nomeFile: nome del file contenente i dati
 *
 * Restituisce:
 * - numero di accessi letti dal file; -1 in caso di errore
 */
int LeggiDaFile(List vett[], char* nomeFile) {
	//TODO: da completare
	T_Accesso entry;
	int giorno;
	int num_accessi = 0;
	FILE *fp = fopen(nomeFile, "r");
	if (fp == NULL) {
		return -1;
	}
	while (fscanf(fp, "%d %d %d %d %s %d", &giorno, &entry.ora, &entry.minuti, &entry.secondi, entry.nome, &entry.durata) != EOF) {
		if (!InserisciInTestaLista(&vett[giorno - 1], entry)) {
			break;
		} num_accessi++;
	}
	fclose(fp);
	printf("\n\nCaricamento file completato");
	return num_accessi;
}

/* 2: Scrivere una funzione che visualizzi tutti i dati caricati in memoria. */

/* Stampa a video i dati di un accesso */
void StampaElemento(T_Accesso elem) {
	printf("\n%02d:%02d:%02d\t%s\t %d", elem.ora, elem.minuti, elem.secondi, elem.nome, elem.durata);
}

/* Stampa una lista di accessi (richiamando la funzione StampaElemento) */
void VisualizzaLista(List l) {
	
	//TODO: da completare
	while (l != NULL) {
		StampaElemento(l->info);
		l = l->next;
	}
}

/* 3: Scrivere una funzione che, dato in ingresso un nome utente, visualizzi tutti gli accessi effettuati */
/*
 * Dato un nome utente, la funzione stampa a video tutti gli accessi effettuati
 * Parametri:
 * - vett: vettore di liste
 * - nomeUtente: nome dell'utente da ricercare
 */
void stampaAccessiPerUtente(List vett[], int dim, char* nomeUtente) {
	
	//TODO: da completare

	int i;
	List aux;

	printf("\nhh:mm:ss\tUtente\tDurata");

	for (int i = 0; i < dim; i++) {
		aux = vett[i];
		printf("\n\tgiorno: %d", i + 1);
		while (aux != NULL) {
			if (strcmp(nomeUtente, aux->info.nome) == 0) {
				StampaElemento(aux->info);
			} aux = aux->next;
		}
	}
}

/* 4: Scrivere una funzione che, dato in ingresso un giorno, restituisca nome utente, orario di accesso e
 * durata del collegamento di durata maggiore nel giorno richiesto; */
void DurataMax(List l, T_Accesso* elemMax) {
	int dmax = 0;
	//TODO: da completare
	while (l != NULL) {
		if (l->info.durata > dmax) {
			dmax = l->info.durata;
			*elemMax = l->info;
		}
		l = l->next;
	}
}

/* 5: Scrivere una funzione che, dato in ingresso una fascia oraria ed un nome utente, restituisca la durata totale
 * ed il numero di collegamenti effettuati da quell’utente in quella fascia oraria; */
int TotaleAccessi(List vett[], int dim, int oraInizio, int oraFine, char* nomeUtente, int* dtotale) {
	List aux;
	int count = 0;
	*dtotale = 0;
	//TODO: da completare

	for (int i = 0; i < dim; i++) {
		aux = vett[i];
		while (aux != NULL) {
			if (strcmp(nomeUtente, aux->info.nome) == 0) {
				if (aux->info.ora >= oraInizio && aux->info.ora < oraFine) {
					*dtotale = *dtotale + aux->info.durata;
					count++;
				}
			} aux = aux->next;
		}
	}
	return count;
}


/* altre funzioni utili*/

//verifica se una lista e' vuota
int isEmpty(List l) {
	return (l == NULL);
}

//inizializza lista vuota
void emptyList(List* l) {
	*l = NULL;
}

//cancella tutti gli elementi della lista
void CancellaLista(List* l) {
	List paux;
	while (*l != NULL) {
		paux = *l;
		*l = (*l)->next;
		free(paux);
	}

	//TODO: da completare
}

/************** main *************/
int main(void) {
	int scelta, i, giorno, duratatot = 0, numaccessi = 0;
	int num_letture = 0;
	char utente[MAX_LENGHT];
	int orainizio, orafine; /* necessari per il punto 5 */
	T_Accesso accesso;

	/* inizializzazione delle 31 liste a lista vuota */

	//TODO: da completare
	List archivio[N];
	for (i = 0; i < N; i++) {
		emptyList(&archivio[i]);
	}
	
	
	do {
		printf("\n\nElaborazioni accessi Web\n\n");
		printf("\t1) Caricamento dati da file\n");
		printf("\t2) Visualizza tutti i dati\n");
		printf("\t3) Visualizza accessi per utente\n");
		printf("\t4) Ricerca utente con durata massima di collegamento\n");
		printf("\t5) Durata totale e numero collegamenti effettuati in una fascia oraria\n");
		printf("\t0) Esci\n");
		printf("\n\nInserisci scelta:   ");
		lab_scanf("%d", &scelta);
		lab_discard_line();

		switch (scelta) {
		case 1: /* leggi da file */
			num_letture = LeggiDaFile(archivio, NOME_FILE ); //archivio: nome del vettore di liste
			printf("\n Sono stati letti %d accessi", num_letture);
			break;
		case 2: /* visualizza il contenuto dell'intera struttura dati */
			
			//TODO: da completare
				for (i = 0; i < N; i++) {
					printf("\n\tgiorno: %d", i+1);
					printf("\noo:mm:ss\tUtente\t Durata");
					VisualizzaLista(archivio[i]);
				}

			break;
		case 3: /* stampa accessi per utente */
			
			//TODO: da completare
				printf("\nInserisci nome utente: ");
				lab_scanf("%50s", utente);
				stampaAccessiPerUtente(archivio, N, utente);

			break;
		case 4: /* dato un giorno, stampare nome utente e durata max collegamento
				1. acquisire da tastiera il giorno richiesto
				2. cercare l'accesso con durata max per il giorno richiesto
				3. stampare i dati a video */
			
			//TODO: da completare
				do {
					printf("\nInserisci il giorno 1-31: ");
					lab_scanf("%d", &giorno);
				} while (giorno < 0 || giorno > N);

				if(!isEmpty(archivio[giorno-1])){
					DurataMax(archivio[giorno - 1], &accesso);
					printf("\nUtente: %s", accesso.nome);
					printf("\nOra accesso: %d:%d:%d", accesso.ora, accesso.minuti, accesso.secondi);
					printf("\nDurata: %d", accesso.durata);
				}
				else
					printf("\n\tLista accessi di giorno %d vuota.", giorno);
				break;
		case 5: /* dati fascia oraria (ora inizio e ora fine) e nome utente,
				* stampare durata totale e num di collegamenti
				*/
			
			//TODO: da completare
			printf("\n\nInserisci ora inizio fascia oraria: ");
			lab_scanf("%d", &orainizio);
			printf("\n\nInserisci ora finale fascia oraria: ");
			lab_scanf("%d", &orafine);
			printf("\n\nInserisci l'utente: ");
			lab_scanf("%50s", utente);

			numaccessi = TotaleAccessi(archivio, N, orainizio, orafine, utente, &duratatot);

			printf("\nDurata totale collegamenti (in minuti): %d", duratatot);
			printf("\nNumero totale collegamenti: %d\n", numaccessi);
			break;

		case 0:
			printf("Uscita \n");
			break;

		default:
			printf("\n\nScelta errata! \n\n");
			break;
		}
	} while (scelta != 0);

	/* deallocazione liste */
	//TODO: da completare
	for (i = 0; i < N; i++) {
		CancellaLista(&archivio[i]);
	}
}