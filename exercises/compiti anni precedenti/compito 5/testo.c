/******************************************************************************
 * ===== MODULO 2 =====
 *
 * Implementare un programma in linguaggio ANSI C per l'automatizzazione di un impianto
 * di irrigazione industriale.
 *
 * L'impianto è suddiviso in un certo numero di aree, ciascuna composta da più zone.
 *
 * Ogni zona è dotata di un sensore di umidità, mentre ogni area dispone di un sensore
 * per la stima della probabilità di pioggia nelle 24 ore successive.
 *
 * Struttura dei dati:
 *
 * AREA:
 *      - Codice alfanumerico (massimo 10 caratteri)
 *      - Numero di zone presenti
 *      - Probabilità di pioggia nelle 24 ore successive (valore compreso tra 0 e 100)
 *
 * ZONA:
 *      - Codice alfanumerico (massimo 10 caratteri)
 *      - Portata in litri/minuto
 *      - Fattore di correzione (valore compreso tra 0 e 1)
 *      - Stato (acceso/spento)
 *      - Tasso di umidità (valore compreso tra 0 e 100)
 *
 * IMPIANTO:
 *      L'impianto è rappresentato come una lista ordinata di aree, ordinate in base
 *      al codice alfanumerico. Ogni area contiene la lista collegata di zone appartenenti
 *      all'area.
 *
 * INDICE:
 *      Lo storico è strutturato come un albero binario di ricerca delle zone, dove la
 *      chiave di ricerca è il codice alfanumerico. Ogni nodo dell'albero contiene il
 *      tempo previsto di accensione della zona corrispondente.
 *
 *      Nota: se la probabilità di pioggia associata all'area di appartenenza della zona
 *      è superiore al 50%, il tempo di accensione è pari a zero. Altrimenti, viene
 *      calcolato con la seguente formula:
 *
 *          tempo_accensione = (100 - umidità) * fattore_correzione
 *
 *      dove:
 *          - umidità: valore percentuale della zona (0 100)
 *          - fattore_correzione: coefficiente tra 0 e 1
 *
 * Il programma deve svolgere le seguenti operazioni:
 *
 * 1.
 *      Inizializzare la struttura dati dell'impianto, leggendo i dati dai file forniti
 *      in ingresso, con il seguente formato:
 *          - File *aree.txt*: ogni riga contiene (codice area, probabilità di pioggia)
 *          - File *zone.txt*: ogni riga contiene (codice zona, portata, fattore di correzione, stato, umidità, codice area)
 *
 * 2.
 *      Creare l'elenco delle zone attualmente attive (stato "acceso") e restituirlo
 *      come un vettore dinamicamente allocato di strutture *ZONA*.
 *
 * 3.
 *      Permettere la modifica dello stato di una zona e, opzionalmente, del suo
 *      fattore di correzione.
 *
 * 4.
 *      Calcolare il tempo di accensione (in secondi) per ciascuna zona attiva e
 *      memorizzare il valore ottenuto nell'albero binario.
 *      Nel caso il tempo di accensione è zero, non deve essere inserito nell'albero.
 *      Il calcolo viene effettuato secondo la formula specificata sopra.
 *
 * 5.
 *      Implementare una funzione che, dato il codice di una zona, restituisce il tempo
 *      previsto di accensione della zona, se presente nell'albero binario.
 * 
 * Nota: il programma deve essere in grado di gestire errori di input e situazioni
 *       improprie, come ad esempio:
 *	   - File non trovati o con formato errato
 *	   - Codici di aree o zone non validi
 *	   - Tentativi di modifica dello stato di una zona inesistente
 * 	   - Errori di allocazione dinamica della memoria

 *
 * funzioni richieste:
Quesito 1:
elenco_aree inserisci_area(elenco_aree testa, area* nuova) 
elenco_aree carica_impianto(const char* file_aree, const char* file_zone)
Quesito 2
int conta_zone_accese(elenco_aree impianto) 
zona* crea_vettore_zone_accese(elenco_aree impianto, int* out_num_zone)
Quesito 3
int aggiorna_zona(elenco_aree impianto, const char* codice_zona, Stato nuovo_stato, float nuovo_fattore) {
Quesito 4
indice calcola_e_costruisci_indice(elenco_aree impianto)
Quesito 5
int tempo_accensione_zona(indice albero, const char* codice_zona)

 * Usando il valori presenti nei file di esempio i risultati attesi sono:
 
 Zone accese:
  Codice: Z019, Portata: 4.60, Fattore: 0.95, Umidita: 38
  Codice: Z014, Portata: 3.60, Fattore: 0.65, Umidita: 40
  Codice: Z008, Portata: 3.50, Fattore: 0.60, Umidita: 45
  Codice: Z001, Portata: 4.50, Fattore: 1.00, Umidita: 40
  Codice: Z023, Portata: 2.80, Fattore: 0.55, Umidita: 55
  Codice: Z018, Portata: 4.00, Fattore: 0.30, Umidita: 48
  Codice: Z013, Portata: 4.20, Fattore: 0.75, Umidita: 70
  Codice: Z007, Portata: 4.10, Fattore: 1.00, Umidita: 50
  Codice: Z022, Portata: 2.50, Fattore: 0.60, Umidita: 50
  Codice: Z017, Portata: 3.30, Fattore: 0.85, Umidita: 55
  Codice: Z012, Portata: 3.10, Fattore: 0.50, Umidita: 55
  Codice: Z021, Portata: 3.70, Fattore: 0.70, Umidita: 28
  Codice: Z016, Portata: 2.60, Fattore: 0.45, Umidita: 65
  Codice: Z011, Portata: 2.80, Fattore: 0.80, Umidita: 60
  Codice: Z005, Portata: 2.70, Fattore: 0.85, Umidita: 60
  Codice: Z020, Portata: 3.90, Fattore: 0.90, Umidita: 30
  Codice: Z015, Portata: 3.00, Fattore: 0.70, Umidita: 50
  Codice: Z010, Portata: 4.70, Fattore: 0.90, Umidita: 25
  Codice: Z009, Portata: 2.90, Fattore: 0.55, Umidita: 35
  Codice: Z003, Portata: 3.80, Fattore: 1.00, Umidita: 20

Albero tempi di accensione:
Zona: Z001, Tempo accensione: 270 secondi
Zona: Z005, Tempo accensione: 91 secondi
Zona: Z007, Tempo accensione: 205 secondi
Zona: Z008, Tempo accensione: 115 secondi
Zona: Z011, Tempo accensione: 89 secondi
Zona: Z013, Tempo accensione: 94 secondi
Zona: Z014, Tempo accensione: 140 secondi
Zona: Z018, Tempo accensione: 62 secondi
Zona: Z019, Tempo accensione: 270 secondi
Zona: Z021, Tempo accensione: 186 secondi
Zona: Z023, Tempo accensione: 69 secondi
 * 
 ******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS     // Necessario per l'uso di funzioni non sicure in Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODICE 11  // 10 caratteri + '\0'

typedef enum { SPENTO, ACCESO } Stato;

typedef struct Zona {
    char codice[MAX_CODICE];
    float portata;              // litri al minuto
    float fattore_correzione;   // float da 0.0 a 1.0
    Stato stato;                // acceso/spento
    int umidita;                // intero 1 100
    struct Zona* next;          // prossima zona nella stessa area
} zona, *elenco_zone;

typedef struct Area {
    char codice[MAX_CODICE];
    int num_zone;               // numero di zone in quest'area
    int prob_pioggia;           // intero 1 100
    elenco_zone lista_zone;     // lista collegata delle zone
    struct Area* next;          // prossima area nell'impianto
} area, *elenco_aree;

typedef struct NodoIndice {
    char codice_zona[MAX_CODICE];  // chiave dell'albero (codice alfanumerico)
    int tempo_accensione;          // tempo di accensione in secondi
    struct NodoIndice* left;       // sottoalbero sinistro
    struct NodoIndice* right;      // sottoalbero destro
} nodo_indice, *indice;

// Funzioni per la gestione delle aree e delle zone
// Crea una nuova area
area* crea_area(const char* codice, int prob_pioggia) {
    area* nuova = (area*)malloc(sizeof(area));
    if (!nuova) return NULL;

    strcpy(nuova->codice, codice);
    nuova->prob_pioggia = prob_pioggia;
    nuova->num_zone = 0;
    nuova->lista_zone = NULL;
    nuova->next = NULL;

    return nuova;
}

// Inserisce l'area nella lista in ordine alfanumerico
// La funzione inserisce l'area in ordine alfanumerico nella lista di aree
elenco_aree inserisci_area(elenco_aree testa, area* nuova) {
	// TODO Da implementare: inserisce l'area in ordine alfanumerico
    if (!testa || strcmp(nuova->codice, testa->codice) > 0) {
        nuova->next = testa;
        return testa;
    }

    elenco_aree curr = testa;
    while (curr->next && strcmp(nuova->codice, curr->next->codice) > 0) {
        curr = curr->next;
    }

    nuova->next = curr->next;
    curr->next = nuova;
    return testa;
}

// Cerca un'area per codice
area* cerca_area(elenco_aree testa, const char* codice) {
    while (testa) {
        if (strcmp(testa->codice, codice) == 0) return testa;
        testa = testa->next;
    }
    return NULL;
}

// Crea e inserisce una zona nella lista di un'area
int inserisci_zona(area* a, const char* codice, float portata, float fattore, Stato stato, int umidita) {
    if (!a) return 0;

    zona* nuova = (zona*)malloc(sizeof(zona));
    if (!nuova) return 0;

    strcpy(nuova->codice, codice);
    nuova->portata = portata;
    nuova->fattore_correzione = fattore;
    nuova->stato = stato;
    nuova->umidita = umidita;
    nuova->next = a->lista_zone;

    a->lista_zone = nuova;
    a->num_zone++;
    return 1;
}

// Quesito 1
// Carica impianto da file
//  file_aree: ogni riga contiene il codice dell'area a la probabilità di pioggia
//  file_zone: ogni riga contiene il codice della zona, portata, fattore di correzione, stato, 
//              umidità e codice area
//  parametri:
//      file_aree:  nome del file che contiene i dati delle aree
//      file_zone:  nome del file che contiene i dati delle zone
//  return:
//      lista di liste che rappresenta l'impianto

elenco_aree carica_impianto(const char* file_aree, const char* file_zone) {
    elenco_aree impianto = NULL;

	// TODO Da implementare: carica le aree e le zone dai file
    FILE* f_aree = fopen(file_aree, "r");
    if (f_aree == NULL) {
        perror("Errore aperta non existe");
        return NULL;
    }

    char codice_area[MAX_CODICE];
    int prob;
    while (fscanf(f_aree, "%s%d", codice_area, &prob) == 2) {
        area * nuova = crea_area(codice_area, prob);
        if (nuova == NULL) {
            continue;
        }
        impianto = inserisci_area(impianto, nuova);
    }
    fclose(f_aree);

    FILE* f_zone = fopen(file_zone, "r");
    if (f_zone == NULL) {
        perror("Errore aperta non existe");
        return NULL;
    }

    char codice_zone[MAX_CODICE], codice_area_ref[MAX_CODICE];
    float portata, fattore;
    int stato, umidita;

    while (fscanf(f_zone, "%s %f %f %d %d %s", codice_zone, &portata, &fattore, &stato, &umidita, codice_area_ref) == 6) {
        area *a = cerca_area(impianto, codice_area_ref);
        if (!a) {
            fprintf(stderr, "Area %s non trovata per zona %s\n", codice_area_ref, codice_zone);
            continue;
        }
        inserisci_zona(a, codice_zone, portata, fattore, stato ? ACCESO : SPENTO, umidita);
    }
    fclose(f_zone);

    return impianto;
}

// Quesito 2
// Conta le zone accese nell'impianto
//  parametri:
//      impianto:  lista di aree che rappresenta l'impianto
//  return:
//      numero di zone accese
//      Se non ci sono zone accese, ritorna 0

int conta_zone_accese(elenco_aree impianto) {
	// da implementare: conta le zone accese nell'impianto
    int count = 0;
    while (impianto) {
        zona *z = impianto->lista_zone;
        while (z) {
            if (z->stato == ACCESO) {
                count++;
            }
            z = z->next;
        }
        impianto = impianto->next;
    }
    return count;
}

// Quesito 2
// Crea un vettore dinamico di zone accese
//  parametri:
//      impianto:       lista di aree che rappresenta l'impianto
//      out_num_zone:   puntatore a intero per restituire il numero di zone accese
//  return:
//      vettore di zone accese, allocato dinamicamente
//      Se non ci sono zone accese, ritorna NULL e *out_num_zone = 0
zona* crea_vettore_zone_accese(elenco_aree impianto, int* out_num_zone) {
    int count = conta_zone_accese(impianto);
	// da implementare: crea un vettore dinamico di zone accese

    if (count == 0) {
        *out_num_zone = 0;
        return NULL;
    }

    zona* vettore = (zona*)malloc(count * sizeof(zona));
    if (!vettore) {
        perror("Errore allocazione nodo indice");
        *out_num_zone = 0;
        return NULL;
    }

    int i = 0;
    while (impianto) {
        zona* z = impianto->lista_zone;
        while (z) {
            if (z->stato == ACCESO) {
                vettore[i] = *z;
                vettore[i].next = NULL;
                i++;
            }
            z = z->next;
        }
        impianto = impianto->next;
    }
    *out_num_zone = count;
    return vettore;
}

// Quesito 3
// Aggiorna lo stato di una zona e, opzionalmente, il fattore di correzione.
// Nota che i parametri sono opzionali: se il nuovo_fattore è negativo, non viene aggiornato.
// e che i valori di nuovo_fattore devono essere compresi tra 0.0 e 1.0.
//  parametri:
//      impianto:       lista di aree che rappresenta l'impianto
//      codice_zona:    codice della zona da aggiornare
//      nuovo_stato:    nuovo stato della zona (SPENTO o ACCESO)
//      nuovo_fattore:  nuovo fattore di correzione (opzionale, se negativo non viene aggiornato)
//  return:
//      1 se la zona è stata trovata e aggiornata, 0 altrimenti

int aggiorna_zona(elenco_aree impianto, const char* codice_zona, Stato nuovo_stato, float nuovo_fattore) {
    // da implementare
    while (impianto) {
        zona* z = impianto->lista_zone;
        while (z) {
            if (strcmp(z->codice, codice_zona) == 0) {
                z->stato = nuovo_stato;
                if (nuovo_fattore >= 0.0 && nuovo_fattore <= 1.0) {
                    z->fattore_correzione = nuovo_fattore;
                }
                return 1; // zona trovata e aggiornata
            }
            z = z->next;
        }
        impianto = impianto->next;
    }
    return 0; // zona non trovata
}

// Quesito 4
// Inserisce un nodo nell'albero binario di ricerca delle zone attive

indice inserisci_nodo_indice(indice root, const char* codice_zona, int tempo_accensione) {
    if (root == NULL) {
        indice nuovo = (indice)malloc(sizeof(nodo_indice));
        if (!nuovo) {
            perror("Errore allocazione nodo indice");
            return NULL;
        }
        strcpy(nuovo->codice_zona, codice_zona);
        nuovo->tempo_accensione = tempo_accensione;
        nuovo->left = nuovo->right = NULL;
        return nuovo;
    }

    int cmp = strcmp(codice_zona, root->codice_zona);
    if (cmp < 0) {
        root->left = inserisci_nodo_indice(root->left, codice_zona, tempo_accensione);
    }
    else if (cmp > 0) {
        root->right = inserisci_nodo_indice(root->right, codice_zona, tempo_accensione);
    }
    else {
        root->tempo_accensione = tempo_accensione; // aggiornamento se già presente
    }
    return root;
}
int calcola_tempo_accensione(area* a, zona* z) {
	if (a->prob_pioggia > 50) {
		return 0; // nessun tempo di accensione se probabilità di pioggia > 50%
	}
	return (int)((100 - z->umidita) * z->portata * z->fattore_correzione);
}
// Quesito 4
// Calcola il tempo di accensione per ogni zona attiva e costruisce l'albero 
// binario di ricerca
//  parametri:
//      impianto:  lista di aree che rappresenta l'impianto
//  return:
//      albero binario di ricerca delle zone attive, con chiave il codice della zona

indice calcola_e_costruisci_indice(elenco_aree impianto) {
    indice root = NULL;

    while (impianto) {
        int prob_pioggia = impianto->prob_pioggia;
        zona* z = impianto->lista_zone;

        while (z) {
            int	tempo = calcola_tempo_accensione(impianto, z);
            if ((z->stato == ACCESO) && tempo > 0)
                root = inserisci_nodo_indice(root, z->codice, tempo);

            z = z->next;
        }
        impianto = impianto->next;
    }

    return root;
}

// Quesito 5
// Cerca il tempo di accensione di una zona nell'albero binario di ricerca
//  parametri:
//      root:          radice dell'albero binario di ricerca
//      codice_zona:   codice della zona da cercare
//  return:
//      tempo di accensione in secondi se trovato, -1 altrimenti

int cerca_tempo_accensione(indice root, const char* codice_zona) {
	// da implementare: cerca il tempo di accensione di una zona nell'albero binario
    while (root) {
        int cmp = strcmp(codice_zona, root->codice_zona);
        if (cmp == 0) {
            return root->tempo_accensione;
        }
        else if (cmp < 0) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return -1;
}

void stampa_albero_indice(indice root) {
    if (root == NULL)
        return;

    stampa_albero_indice(root->left);
    printf("Zona: %s, Tempo accensione: %d secondi\n", root->codice_zona, root->tempo_accensione);
    stampa_albero_indice(root->right);
}

int main() {
    elenco_aree impianto = NULL;
    zona* vettore_zone_accese = NULL;
    int num_zone_accese = 0;
    indice albero_indice = NULL;

    int scelta;
    char buffer_codice[MAX_CODICE];
    int nuovo_stato_int;
    float nuovo_fattore;

    do {
        printf("\n--- Menu Impianto Irrigazione ---\n");
        printf("1. Carica dati impianto da file\n");
        printf("2. Visualizza zone accese\n");
        printf("3. Modifica stato/fattore di correzione di una zona\n");
        printf("4. Calcola e visualizza tempi di accensione\n");
        printf("5. Cerca tempo di accensione di una zona\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        if (scanf("%d", &scelta) != 1) {
            printf("Input non valido.\n");
            while (getchar() != '\n'); // pulisci buffer
            continue;
        }

        switch (scelta) {
        case 1:
            if (impianto) {
                printf("Attenzione: impianto già caricato, liberare prima (non implementato).\n");
            }
            else {
				// Inserire il codice per caricare l'impianto dai file
            }
            break;

        case 2:
            if (!impianto) {
                printf("Impianto non caricato.\n");
                break;
            }
            if (vettore_zone_accese) {
                free(vettore_zone_accese);
                vettore_zone_accese = NULL;
                num_zone_accese = 0;
            }
			// inserire il codice per creare il vettore delle zone accese

            if (num_zone_accese == 0) {
                printf("Nessuna zona accesa.\n");
            }
            else {
                printf("Zone accese:\n");
                for (int i = 0; i < num_zone_accese; i++) {
                    printf("  Codice: %s, Portata: %.2f, Fattore: %.2f, Umidita: %d\n",
                        vettore_zone_accese[i].codice,
                        vettore_zone_accese[i].portata,
                        vettore_zone_accese[i].fattore_correzione,
                        vettore_zone_accese[i].umidita);
                }
            }
            break;

        case 3:
            if (!impianto) {
                printf("Impianto non caricato.\n");
                break;
            }
			// Inserire il codice per modificare lo stato di una zona
            break;

        case 4:
            if (!impianto) {
                printf("Impianto non caricato.\n");
                break;
            }
            albero_indice = calcola_e_costruisci_indice(impianto);
            printf("Albero tempi di accensione:\n");
            stampa_albero_indice(albero_indice);
            break;

        case 5:
            if (!albero_indice) {
                printf("Albero tempi non costruito. Esegui prima opzione 4.\n");
                break;
            }
			// Inserire il codice per cercare il tempo di accensione di una zona
            break;

        case 0:
            printf("Uscita...\n");
            break;

        default:
            printf("Scelta non valida.\n");
        }

    } while (scelta != 0);

    // Libera memoria (non implementato qui)

    if (vettore_zone_accese)
        free(vettore_zone_accese);

    // Qui aggiungere funzioni per liberare impianto e albero

    return 0;
}
