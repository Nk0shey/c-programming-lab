/*
 * Sviluppo di una applicazione in ANSI C per la gestione delle casse di un ufficio.
 *
 * Ogni cassa è operata da un impiegato, e contiene una coda di clienti prenotati.
 * Ogni operazione presenta una stima del tempo necessario.
 * In particolare:
 * Ogni Cliente presenta un nome e il tempo stimato per l'operazione;
 * Ogni Cassa presenta un ID, il nome dell'impiegato e una coda di Clienti
 *
 *Il file data.tex è organizzato nel seguente modo
* 5   //numero delle casse
0 Simone  //nome del responsabile della cassa 0
1 Laura
2 Salvatore
3 Andrea
4 Monica
16        //numero dei clienti
0 Rossi 1.0   //cognome del cliente, tempo delloperazione
0 Verdi 1.5
0 Ferrari 0.8
1 Russo 2.0
1 Bianchi 4
1 Romano 3
1 Gallo 2
2 Costa 1
2 Fontana 3
2 Conte 1.0
3 Serra 4.0
3 Farina 0.5
4 Gentile 0.5
4 Caruso 0.2
4 Morelli 0.1
4 Ferri 0.4

 * Implementare le seguenti funzioni:
 * 1) carica_casse: carica le casse dal file "data.txt" e le memorizza in un
 * array di casse
 * 2) tempo_stimato: restituisce un array contenente il tempo stimato per ogni cassa
 * 3) operazioni_lunghe: restituisce una lista contenente le operazioni con tempo stimato
 * più grande di un valore passato come parametro
 *4) creare un albero binario di ricerca ordinato rispetto alla durata delle operazione estraendo i dati dalle code delle casse.
* In ogni nodo memorizzare il nome del cliente e l'id della cassa.
* 5) Salvare i dati dell'albero in modo ordinato rispetto al tempo di elaborazione in un file testo
 * Completare, inoltre, il main con le variabili e le chiamate alle funzioni necessarie.
 *
 * La descrizione dettagliata di ogni funzione è riportata come commento immediatamente
 * prima della definizione della funzione nello scheletro di programma fornito.

* */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente_struct {
    char nome[32];
    float tempo_stimato;
} Cliente;

typedef struct nodo_cliente_struct {
    Cliente cliente;
    struct nodo_cliente_struct *succ;
} NodoCliente, *ListaClienti;

typedef struct coda_clienti {
    int numero_clienti;
    NodoCliente *primo, *ultimo;
} CodaClienti;

typedef struct cassa_struct {
    int id;
    char impiegato[32];
    CodaClienti coda;
} Cassa;


/*
 * Aggiunge un cliente alla coda dei clienti.
 * Restituisce 1 se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
 */
int aggiungi_cliente(CodaClienti *pcoda, Cliente cliente) {
    //DA IMPLEMENTARE
    NodoCliente *nuovo;
    if (pcoda == NULL) {
         return 0;
    }

    nuovo = (NodoCliente*)malloc(sizeof(NodoCliente));
    if (nuovo == NULL) {
        return 0;
    }

    nuovo->cliente = cliente;
    nuovo->succ = NULL;

    if (pcoda->primo == NULL) {
        pcoda->primo = nuovo;
        pcoda->ultimo = nuovo;
    } else {
        pcoda->ultimo->succ = nuovo;
        pcoda->ultimo = nuovo;
    }

    pcoda->numero_clienti++;
    return 1;
}

/*
 * Inizializza la coda passata per riferimento.
 */
void inizializza_coda(CodaClienti *pcoda) {
    pcoda->numero_clienti = 0;
    pcoda->primo = pcoda->ultimo = NULL;
}

/*
 * 1) carica_casse: carica le casse dal file "data.txt" e le memorizza in un
 * array di casse.
 * L'elemento i-esimo dell'array è una Cassa, contenente:
 * l'id della cassa, il nome dell'impiegato, ed una coda di Clienti
 *
 * L'array è composto da un numero di casse variabile,
 * indicato nella prima riga del file col seguente formato:
    NUMERO_CASSE(int)
 * Le successive NUMERO_CASSE righe avranno formato
    ID_CASSA(int) NOME_IMPIEGATO(string)

 * A seguire, il file contiene il numero atteso di righe, ognuna
 * corrispondente ad un cliente, nel seguente formato:
    NUMERO_CLIENTI(int)
 * Ognuna delle NUMERO_CLIENTI righe successive conterrà quindi:
    ID_CASSA(int) NOME_CLIENTE(string) TEMPO_PREVISTO(float)
 * Aggiungere il cliente alla posizione ID_CASSA-esima dell'array
 *
 * Parametri: nome del file
 * Restituisce: l'array delle casse (o NULL, in caso di errore),
 *               il numero di casse caricate (tramite parametro!)
 */
Cassa *carica_casse(char *nome_file, int *numero_casse) {
*numero_casse=0; FILE *f=fopen(nome_file,"r"); if (!f) return NULL;
    int dim,nclienti; Cassa *casse=NULL;
    if (fscanf(f,"%d",&dim)!=1 || dim<=0 || dim>10000) goto fail;
    casse=calloc((size_t)dim,sizeof *casse); if (!casse) goto fail;
    for (int i=0;i<dim;++i) if (fscanf(f,"%d %31s",&casse[i].id,casse[i].impiegato)!=2) goto fail;
    if (fscanf(f,"%d",&nclienti)!=1 || nclienti<0) goto fail;
    for (int i=0;i<nclienti;++i) {
        int k; Cliente c;
        if (fscanf(f,"%d %31s %f",&k,c.nome,&c.tempo_stimato)!=3 || k<0 || k>=dim || c.tempo_stimato<0 || !aggiungi_cliente(&casse[k].coda,c)) goto fail;
    }
    fclose(f); *numero_casse=dim; return casse;
fail:
    if (casse) { for (int i=0;i<dim;++i) { NodoCliente *n=casse[i].coda.primo; while (n) { NodoCliente *next=n->succ; free(n); n=next; } } free(casse); }
    fclose(f); return NULL;
}

/*
 * 2) tempo_stimato: crea un array contenente il tempo totale stimato per le operazioni di quella cassa
 * In particolare, restituisce un nuovo array che, per ogni cassa i, contiene il tempo totale delle operazioni
 * in coda nella cassa i
 *
 * Parametri: array delle casse e la sua dimensione dim
 * Restituisce: un array di float (di dimensione dim), dove in ogni posizione i è presente il tempo totale per la cassa i
 */
float *tempo_stimato(Cassa *casse, int dim) {
    // TODO Implementazione

    float *array;
    NodoCliente *aux;

    if (casse == NULL || dim <= 0) {
        return NULL;
    }

    array = (float*)malloc(dim * sizeof(float));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < dim; i++) {
        array[i] = 0;

        aux = casse[i].coda.primo;

        while (aux != NULL) {
            array[i] += aux->cliente.tempo_stimato;
            aux = aux->succ;
        }
    }




    return array;
}

/*
 * Data una lista, la funzione aggiunge un cliente.
 * La funzione restituisce 0 se l'operazione fallisce, 1 altrimenti
 */
int aggiungi_cliente_a_lista(ListaClienti *lista_clienti, Cliente cliente) {
    NodoCliente *aux = malloc(sizeof(NodoCliente));
    if (!aux) return 0;

    aux->cliente = cliente;
    aux->succ = *lista_clienti;

    *lista_clienti = aux;

    return 1;
}

/*
 * 3) operazioni_lunghe: crea e restituisce una lista di Clienti che devono effettuare operazioni
 * che prevedono un tempo più grande di un tempo minimo.
 * Le operazioni devono essere cercate tra tutte le casse.
 *
 * Parametri: array delle casse e la sua dimensione, tempo minimo
 * Restituisce: la lista risultante dei clienti
 */
ListaClienti operazioni_lunghe(Cassa *casse, int dim, float tempo_minimo) {
    // TODO Implementazione
    ListaClienti lista = NULL;
    NodoCliente *aux;
    NodoCliente *nuovo;
    if (casse == NULL || dim <= 0) {
        return NULL;
    }

    for (int i = 0; i < dim; i++) {
        aux = casse[i].coda.primo;
        while (aux != NULL) {
            if (aux->cliente.tempo_stimato > tempo_minimo) {
                nuovo = (NodoCliente*)malloc(sizeof(NodoCliente));
                if (!nuovo) {
                    while (lista) { NodoCliente *n = lista; lista = n->succ; free(n); }
                    return NULL;
                }
                nuovo->cliente = aux->cliente;
                nuovo->succ = lista;
                lista = nuovo;
            }
            aux = aux->succ;
        }
    }
    return lista;
}

/*
 * Dato un cliente, visualizza le sue informazioni
 */
void visualizza_cliente(Cliente cliente) {
    printf("\t - %s (%f)\n", cliente.nome, cliente.tempo_stimato);
}

/*
 * Data una catena di clienti, li visualizza
 */
void visualizza_clienti(NodoCliente *nodo) {
    while (nodo) {
        visualizza_cliente(nodo->cliente);
        nodo = nodo->succ;
    }
}

/*
 * Visualizza le informazioni di una cassa e i clienti prenotati
 */
void visualizza_cassa(Cassa *cassa) {
    printf("Cassa %d - %s:\n", cassa->id, cassa->impiegato);

    visualizza_clienti(cassa->coda.primo);
}

/*
 * Visualizza l'intero array di casse
 */
void visualizza_casse(Cassa *casse, int dim) {
    printf("Cassa ID - Impiegato\n");
    for (int i = 0; i < dim; i++) visualizza_cassa(&casse[i]);
}

/*
 * Disalloca una catena di nodi cliente
 */
void disalloca_clienti(NodoCliente **nodo) {
    // TODO Implementazione
    NodoCliente *successivo;
    NodoCliente *corrente;

    if (nodo == NULL || *nodo == NULL) return;

    corrente = *nodo;
    while (corrente != NULL) {
        successivo = corrente->succ;
        free(corrente);
        corrente = successivo;
    }

    *nodo = NULL;
}

/*
 * Disalloca l'array delle casse
 */
void dealloca_casse(Cassa **casse, int dim) {
    for (int i = 0; i < dim; i++) {
        disalloca_clienti(&((*casse)[i].coda.primo));
        (*casse)[i].coda.ultimo = NULL;
    }
    free(*casse);
    *casse = NULL;
}

/*
 * Struttura dati per il nodo dell'albero binario di ricerca
 */
typedef struct nodo_albero {
    Cliente cliente;
    int id_cassa;
    struct nodo_albero *sinistra, *destra;
} NodoAlbero, *Albero;

/*
 * Funzione per inserire un nodo nell'albero
 */
Albero inserisci_nodo(Albero radice, Cliente cliente, int id_cassa) {
    if (radice == NULL) {
        NodoAlbero *nuovo_nodo = (NodoAlbero *)malloc(sizeof(NodoAlbero));
        if (!nuovo_nodo) return NULL;
        nuovo_nodo->cliente = cliente;
        nuovo_nodo->id_cassa = id_cassa;
        nuovo_nodo->sinistra = nuovo_nodo->destra = NULL;
        return nuovo_nodo;
    }

    if (cliente.tempo_stimato < radice->cliente.tempo_stimato) {
        radice->sinistra = inserisci_nodo(radice->sinistra, cliente, id_cassa);
    } else {
        radice->destra = inserisci_nodo(radice->destra, cliente, id_cassa);
    }
    return radice;
}

/*
 * Funzione per creare l'albero dai dati delle casse
 */
Albero crea_albero(Cassa *casse, int dim) {
Albero radice=NULL;
    for (int i=0;i<dim;++i) for (NodoCliente *n=casse[i].coda.primo;n;n=n->succ) radice=inserisci_nodo(radice,n->cliente,casse[i].id);
    return radice;
}

/*
 * Funzione per salvare i dati dell'albero in un file di testo
 */
void salva_albero_su_file(FILE *file, Albero radice) {
if (!file || !radice) return;
    salva_albero_su_file(file,radice->sinistra);
    fprintf(file,"%d %s %.2f\n",radice->id_cassa,radice->cliente.nome,radice->cliente.tempo_stimato);
    salva_albero_su_file(file,radice->destra);
}

/*
 * Funzione per deallocare l'albero
 */
void dealloca_albero(Albero radice) {
    if (radice != NULL) {
        dealloca_albero(radice->sinistra);
        dealloca_albero(radice->destra);
        free(radice);
    }
}
int Menu() {
int scelta=0; printf("1 Carica | 2 Operazioni lunghe | 3 Tempi | 4 Albero | 5 Salva | 0 Esci: ");
    if (scanf("%d",&scelta)!=1) { return 0; }
    return scelta;
}

int main(void) {
Cassa *casse=NULL; int dim=0,scelta; Albero a=NULL;
    while ((scelta=Menu())!=0) {
        if (scelta==1) {
            char file[256]; if (scanf("%255s",file)!=1) break;
            int n; Cassa *nuove=carica_casse(file,&n);
            if (nuove) { dealloca_casse(&casse,dim); dealloca_albero(a); a=NULL; casse=nuove; dim=n; visualizza_casse(casse,dim); }
        } else if (scelta==2) {
            float soglia; if (scanf("%f",&soglia)!=1) break;
            ListaClienti l=operazioni_lunghe(casse,dim,soglia); visualizza_clienti(l); disalloca_clienti(&l);
        } else if (scelta==3) {
            float *v=tempo_stimato(casse,dim); if (v) { for (int i=0;i<dim;++i) printf("%d %.2f\n",casse[i].id,v[i]); free(v); }
        } else if (scelta==4) { dealloca_albero(a); a=crea_albero(casse,dim); }
        else if (scelta==5) { FILE *f=fopen("casse_output.txt","w"); if (f) { salva_albero_su_file(f,a); fclose(f); } }
    }
    dealloca_casse(&casse,dim); dealloca_albero(a); return 0;
}
