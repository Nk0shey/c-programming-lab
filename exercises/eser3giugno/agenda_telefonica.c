#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/******* strutture dati *******/

#define STR_LENGHT 25
#define NMB_LENGHT 12

#define CELLULARE 1
#define FISSO 0

typedef struct {
	char cognome[STR_LENGHT];
	char nome[STR_LENGHT];
	char numero[NMB_LENGHT];
	int tipo; // 1 CELLULARE, 0 FISSO
}Persona;

typedef struct nodoLista {
	Persona info;
	struct nodoLista* next;
}TipoNodoLista;

typedef TipoNodoLista* ListaPersone;


/*ABR*/
typedef char Lettera;

typedef struct {
	Lettera lettera;
	ListaPersone lista_persone;
}TipoInfoAlbero;

typedef struct nodoAlbero {
	TipoInfoAlbero info;
	struct nodoAlbero* destro;
	struct nodoAlbero* sinistro;
}NodoAlbero;

typedef NodoAlbero* ABR;




void InitAlbero(ABR* a) {
	*a = NULL;
}

int isEmpty(ABR a) {
	return a == NULL;
}




/*punto 1: leggi da file*/

int compara_per_lettera(Lettera a, Lettera b) {
	return a - b;
}

int compara_cognome_nome(Persona a, Persona b) {
	int compare = strcmp(a.cognome, b.cognome);
	if (compare == 0)
		return strcmp(a.nome, b.nome);
	return compare;

}

/*
* ricerca_nodo_per_lettera
* cerca (se esiste) il nodo dell'albero che corrisponde ad una
* determinata lettera, passata come parametro
*/

ABR ricerca_nodo_per_lettera(ABR albero, Lettera l) {
	ABR sottoalbero;
	if (albero == NULL) {
		sottoalbero = NULL;
	}
	else if (compara_per_lettera(albero->info.lettera, l) == 0) {
		sottoalbero = albero;
	} else if (compara_per_lettera(albero->info.lettera, l) > 0) {
		sottoalbero = ricerca_nodo_per_lettera(albero->sinistro, l);
	} else
		sottoalbero = ricerca_nodo_per_lettera(albero->destro, l);

	return sottoalbero;
	//da completare
}

/*
* genitore
* trova il nodo genitore per la lettera passata come parametro
*/
ABR genitore(ABR albero, Lettera iniziale) {
ABR pred=NULL;
    while (albero) { pred=albero; albero=iniziale<albero->info.lettera ? albero->sinistro : albero->destro; }
    return pred;
}

/*
* costruisciAlbero
* costruisce un nuovo albero, avente come radice l'elemento fornito,
* e come figli i due sottoalberi forniti in ingresso
*/
ABR costruisciAlbero(TipoInfoAlbero elem, ABR sx, ABR dx) {
	ABR aux;

	aux = (ABR)malloc(sizeof(NodoAlbero));
	if (aux == NULL) {
		printf("Errore allocazione");
		exit(1);
	}
	aux -> info = elem;
	aux -> sinistro = sx;
	aux -> destro = dx;
	return aux;
}


/* inserisci_nodo_ABR
* inserisci un nuovo nodo in un ABR - versione iterativa
*/
void inserisci_nodo_ABR(ABR* albero, TipoInfoAlbero elem) {
	ABR aux, prec;

	aux = costruisciAlbero(elem, NULL, NULL);
	if (*albero == NULL) {
		*albero = aux;
	}
	else {
		prec = genitore(*albero, elem.lettera);

		if (compara_per_lettera(elem.lettera, prec->info.lettera) > 0) {
			prec->destro = aux;
		} else
			prec->sinistro = aux;
	}
	//da completare
}

/* InserisciInListaOrdinata
* inserisce i dati di una nuova persona ina una lista ordinata
* per cognome-nome
*/
int InserisciInListaOrdinata(ListaPersone* pl, Persona elem) {
	//da completare
	TipoNodoLista* precedente, *corrente;
	TipoNodoLista* paux;
	paux = malloc(sizeof(TipoNodoLista));	
	if (paux == NULL) {
		printf("Errore allocazione");
		exit(1);
	}

	paux -> info = elem;
	if (*pl == NULL) {
		paux -> next = NULL;
		*pl = paux;
	}
	else if (compara_cognome_nome(elem, (*pl) -> info) < 0) {
		paux -> next = *pl;
		*pl = paux;
	} else {
		precedente = *pl;
		corrente = precedente->next;
		while ((corrente != NULL) && compara_cognome_nome(elem, corrente->info) > 0) {
			precedente = corrente;
			corrente = precedente->next;
		}
		paux->next = corrente;
		precedente->next = paux;
	}
	return 1;
}


/* aggiungi_numero
* aggiunge un nuovo numero nell'agenda
* 1. viene prima identificato il nodo corrispondente alla lettera inziale del cognome
* 2a. se il nodo non esiste, viene creato il nodo a aggiunto all'albero
* 2b. i dati della nuova persona vengono aggiunti nella lista dei numeri associati a quel nodo.
*/
void aggiungi_numero(ABR* agenda, Persona p) {

	//da completare

	/* 
	Per poter aggiungere una persona all'agenda, dobbiamo prima verificare se il nodo della lettera corrispondente 
	e' gia' presente nell'albero o meno. 

	1. cercare il nodo della lettera corrispondente
	2. se il nodo non esiste, bisogna crearlo
	3. se esiste, basta aggiungere un nuovo elemento alla sua lista di persone
	*/

	TipoInfoAlbero elem;
	Lettera iniziale = p.cognome[0];
	ABR nodo_lettera = ricerca_nodo_per_lettera(*agenda, iniziale);
	if (nodo_lettera == NULL) {
		elem.lettera = iniziale;
		elem.lista_persone = NULL;
		InserisciInListaOrdinata(&elem.lista_persone, p);
		inserisci_nodo_ABR(agenda, elem);
	}  else {
		InserisciInListaOrdinata(&nodo_lettera->info.lista_persone, p);
	}
}


/* LeggiDaFile
* legge le informazioni dal file di testo e popola l'albero opportunamente.
*/
void LeggiDaFile(ABR* agenda) {

	//da completare

	char nome_file[STR_LENGHT];
	Persona elem;
	FILE* fp;

	printf("Inserire il nome do arquivo: ");
	scanf("%s", nome_file);
	fp = fopen(nome_file, "r");
	if (fp != NULL) {
		while (fscanf(fp, "%s %s %s %d\n", elem.cognome, elem.nome, elem.numero, &elem.tipo) != EOF) {
			aggiungi_numero(agenda, elem);
		}
		fclose(fp);
		printf("Caricamento avvenuto");
	} else
			printf("Errore apertura file");
}



/*punto 2: stampa numeri telefonici in ordine*/

/* stampa_Persona
* stampa i dati di una persona a schermo
*/
void stampa_Persona(Persona p) {
	printf("\n%s %s %s ", p.cognome, p.nome, p.numero);
	if (p.tipo == FISSO)
		printf(" fisso");
	else printf(" cellulare");
}

/* VisitaLista
* scorre i nodi di una lista e stampa i dati delle persone
*/
void VisitaLista(ListaPersone lp) {
	//da completare
	while (lp != NULL) {
		stampa_Persona(lp->info);
		lp = lp->next;
	}
}

/* stampaNodo
*  stampa l'etichetta di un nodo dell'albero
* (in questo caso, la lettera iniziale e la lista
* dei numeri associati)
*/
void stampaNodo(TipoInfoAlbero info) {
	//da completare
	printf("\n\n Lettera: %c", info.lettera);
	VisitaLista(info.lista_persone);
}


/* stampaNumeriInOrdine
* Visita l'albero in maniera simmetrica e
* stampa l'etichetta di ogni nodo
*/
void StampaNumeriInOrdine(ABR albero) {
	//da completare
	if (!isEmpty(albero)) {
		StampaNumeriInOrdine(albero->sinistro);
		stampaNodo(albero->info);
		StampaNumeriInOrdine(albero->destro);
	}
}


/*punto 3: inserisci persona*/

/* InserisciPersona
* inserisci una nuova persona nell'albero,
* inserendo i dati da tastiera.
*/
void InserisciPersona(ABR* agenda) {

	//da completare
	Persona elem;
	int tipo;
	printf("Inserisci nuovo numero: ");
	printf("Inserisci cognome: ");
	scanf("%s", elem.cognome);

	printf("\nInserisci nome: ");
	scanf("%s", elem.nome);


	printf("\nInserisci numero:");
	scanf("%s", elem.numero);
	do {
		printf("\nInserisci 0 per fisso, 1 per cellulare: ");
		scanf("%d", &tipo);
	} while ((tipo < 0) || (tipo > 1));
	elem.tipo = tipo;

	aggiungi_numero(agenda, elem);
}


/*punto 4:modifica numero*/

/*RicercaInLista
* cerca il nodo che corrisponde alla persona p
* dentro una lista ordinata.
*/
TipoNodoLista* RicercaInLista(ListaPersone lista, Persona p) {
	//da completare
	while (lista != NULL) {
		if (compara_cognome_nome(lista->info, p) == 0)
			return lista;
		lista = lista->next;
	}
	return NULL;
}


/* ModifcaNumero
* modifica il numero di una persona memorizzata in agenda,
* inserendo i dati da tastiera.
*/
void ModificaNumero(ABR agenda) {

	//da completare

	/*
	1. inserire i dati (cognome e nome) della persona di cui si vuole modificare il numero
	2. cercare nell'albero il nodo corrispondente 
	3. cercare nella lista del nodo, la persona corrispondente
	4. se la persona viene trovata, aggiornare il numero
	*/

	Persona elem;
	int tipo;

	printf("\nModifica numero esistente");
	printf("\nInserisci cognome: ");
	scanf("%s", elem.cognome);
	printf("\nInserisci nome: ");
	scanf("%s", elem.nome);
	printf("\nInserisci numero:");
	scanf("%s", elem.numero);

	do {
		printf("\nInserisci 0 per fisso, 1 per cellulare: ");
		scanf("%d", &tipo);
	} while ((tipo < 0) || (tipo > 1));
	elem.tipo = tipo;

	ABR nodo_lettera = ricerca_nodo_per_lettera(agenda, elem.cognome[0]);
	if (nodo_lettera == NULL) {
		printf("\nNessuna corrispondenza trovata");
		return;
	}

	TipoNodoLista *aux = RicercaInLista(nodo_lettera->info.lista_persone, elem);
	if (aux == NULL) {
		printf("\nNessuna corrispondenza trovata");
		return;
	}

	strcpy(aux->info.numero, elem.numero);
	aux->info.tipo = elem.tipo;
	printf("\nNumero aggiornato");
}

//punto 5: cerca persona dato un numero

/* RicercaListaDatoNumero
* visita i nodi di una lista alla ricerca del nodo (se esiste)
* che ha il numero desiderato
*/
TipoNodoLista* RicercaInListaDatoNumero(ListaPersone lista, char* numero) {
	//da completare
	while (lista != NULL) {
		if (strcmp(lista->info.numero, numero) == 0) {
			return lista;
		} lista = lista->next;
	} return NULL;
}

/* analizzaNodo
* cerca all'interno di un nodo dell'albero
* la persona che ha il numero desiderato
*/
int analizzaNodo(TipoInfoAlbero info, char* numero) {
	int trovato = 0;
	TipoNodoLista* aux = RicercaInListaDatoNumero(info.lista_persone, numero);
	if (aux != NULL) {
		printf("\nTROVATO! %s, %s, %s", aux->info.cognome, aux->info.nome, aux->info.numero);
		trovato = 1;
	}
	return trovato;
}

/* CercaPersonaInAlbero
* Visita Simmetrica dell'albero alla ricerca
* della persona che ha il numero desiderato
* la funzione restitusice 1 se il numero e' stato trovato, 0 altrimenti
*/
int CercaPersonaInAlbero(ABR albero, char* numero) {
	//da completare
	int trovato = 0;
	if (!isEmpty(albero)) {
		trovato = CercaPersonaInAlbero(albero->sinistro, numero);
		if (trovato) return trovato;
		trovato = analizzaNodo(albero->info, numero);
		if (trovato) return trovato;
		trovato = CercaPersonaInAlbero(albero->destro, numero);
	}
	return trovato;
}

/* CercaPersonaDatoNumero
* Avvia la Ricerca all'interno dell'albero
* dopo aver acquisito da tastiera il numero da ricercare.
*/
void CercaPersonaDatoNumero(ABR albero) {

	//da completare

	//1. Inserire il numero ca cercare
	//2. Visti l'albero alla ricerca del numero da cercare
	char numero[STR_LENGHT];
	int trovato = 0;
	printf("Inserisci numero: ");
	scanf("%s", numero);

	trovato = CercaPersonaInAlbero(albero, numero);
	if (!trovato) {
		printf("\nNessuna corrispondenza trovata");
	}
	
}



//punto 6: scrivi su file


/* VisitaListaESalva
* visita i nodi di una lista di persone e salva i dati in un file
* di testo, qualora la condizione richiesta sia verificata.
*/
void VisitaListaESalva(ListaPersone lp, char *nome_file, int tipo) {
	
	//da completare
	//1. aprire il file in modalita append
	//2. scorrere la lista di numeri
	//3. salvare nel file i numeri
	//4. chiudere il file
	FILE* fp;
	fp = fopen(nome_file, "a");
	if (fp == NULL) {
		printf("Errore apertura file");
		return;
	}
	while (lp != NULL) {
		if (lp->info.tipo == tipo) {
			fprintf(fp, "%s %s %s %d\n", lp->info.cognome, lp->info.nome, lp->info.numero, lp->info.tipo);
		}
		lp = lp->next;
	}
	fclose(fp);
}


/* ScriviVisitaSimmetrica
* visitaSimmetrica dei nodi dell'albero e salvataggio
* dei dati su un file di testo.
*/
void ScriviVisitaSimmetrica(ABR albero, char* nome_file, int tipo) {
	if (!isEmpty(albero)) {
		ScriviVisitaSimmetrica(albero->sinistro, nome_file, tipo);
		VisitaListaESalva(albero->info.lista_persone, nome_file, tipo);
		ScriviVisitaSimmetrica(albero->destro, nome_file, tipo);
	}
}

/* ScriviSuFile
* avvia la scrittura dei dati dell'albero su file di testo,
* dopo aver acquisito da tastiera il nome del file.
*/
void ScriviSuFile(ABR albero) {

	//da completare
	//1. inserire da tastiera il nome da dare al file e il tipo di numeri da memorizzare
	//2. visitare l'albero e salvare (tramite la funzione ScriviVisitaSimmetrica)
	int tipo;
	char nome_file[STR_LENGHT];
	printf("\nInserisci nome file: ");
	scanf("%s", nome_file);
	do {
		printf("\nInserisci 0 per fisso, 1 per cellulare: ");
		scanf("%d", &tipo);
		while (getchar() != '\n');
	} while ((tipo < 0) || (tipo > 1));

	ScriviVisitaSimmetrica(albero, nome_file, tipo);
	
}


int CancellaLista(ListaPersone* pl) {
if (!pl) return 0;
    while (*pl) { ListaPersone n=*pl; *pl=n->next; free(n); }
    return 1;
}


int CancellaAlbero(ABR* albero) {
if (!albero || !*albero) return 1;
    CancellaAlbero(&(*albero)->sinistro); CancellaAlbero(&(*albero)->destro);
    CancellaLista(&(*albero)->info.lista_persone); free(*albero); *albero=NULL; return 1;
}



int main(void) {

	ABR agenda;
	int scelta;

	//inizializza albero
	InitAlbero(&agenda);

	do {
		printf("\n\nGestione Agenda Telefonica\n\n");
		printf("\n1. Carica da File");
		printf("\n2. Stampa tutti i numeri");
		printf("\n3. Inserisci nuovo numero");
		printf("\n4. Modifica numero telefonico");
		printf("\n5. Cerca per numero telefonico");
		printf("\n6. Salva su file");

		printf("\n0. Esci");
		do {
			printf("\n Inserisci scelta: ");
			scanf("%d", &scelta);
			while (getchar() != '\n');
		} while ((scelta < 0) || (scelta > 6));

		switch (scelta) {
		case 1:
			//punto 1: leggi da file
			LeggiDaFile(&agenda);
			break;
		case 2:
			//punto 2: stampa numeri telefonici in ordine
			StampaNumeriInOrdine(agenda);
			break;
		case 3:
			//punto 3: inserisci persona nell'archivio
			InserisciPersona(&agenda);
			//StampaNumeriInOrdine(agenda);
			break;
		case 4:
			//punto 4: modifica di un numero dato nome e cognome
			ModificaNumero(agenda);
			//StampaNumeriInOrdine(agenda);
			break;
		case 5:
			//punto 5: cerca persona dato il numero
			CercaPersonaDatoNumero(agenda);
			break;
		case 6:
			//punto 6: scrivi su file i numeri
			ScriviSuFile(agenda);
			break;
		case 0:
			break;
		default:
			printf("\n scelta Errata");
		}
	} while (scelta != 0);




	//TODO Deallocare l'albero
	CancellaAlbero(&agenda);
	return 0;
}