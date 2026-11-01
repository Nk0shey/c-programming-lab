/******************************************************************************
 *  (vendite): Quantità vendute di P prodotti in N negozi
 *
 *  Funzionalità:
 *   1a) Carica i dati da "Modulo1.txt" in strutture allocate dinamicamente
 *   1b) Calcola min, max, media per NEGOZIO e stampa a video
 *   1c) Calcola min, max, media per PRODOTTO e salva su "Modulo1_OUT.txt"
 *
 *  Formato file "Modulo1.txt":
 *    <num_prodotti> <num_negozi>
 *    <NomeNegozio> q1 q2 ... qP
 *    (una riga per ciascun negozio)
 *
 *  Esempio:
 *    6 4
 *    Centro  90 70 80 60 100 70
 *    Nord    50 60 50 70  60 50
 *    Est     80 90 70 80  90 80
 *    Sud     30 40 50 60  50 40

 ******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOME_FILE "DATI.txt"
#define NOME_FILE_DA_CONSEGNARE "RISULTATI.txt"

#define STR_LEN 50

/* Dato di base: un negozio con il suo nome e le vendite dei P prodotti */
typedef struct {
    char negozio[STR_LEN];
    int *vendite;   // dimensione = num_prodotti
} T_rigaVendite;

/* Statistiche per riga (negozio) */
typedef struct {
    char nome[STR_LEN];
    int min;
    int max;
    float media;
} T_statistiche;

/* Libera tutte le vendite e il vettore dei negozi */
static void libera_vendite(T_rigaVendite *v, unsigned n_negozi) {
 //da implementare
    if (!v) return;
    for (unsigned i = 0; i < n_negozi; i++) {
        free(v[i].vendite);
        v[i].vendite = NULL;
    }
}

 /*carica i dati da file e alloca:
 *   - un array di T_rigaVendite lungo N (negozi)
 *   - per ciascun negozio, un array di P interi con le vendite
 *  Ritorna N (numero negozi caricati) e valorizza *pNum_prodotti con P
 */
unsigned carica_vendite_da_file(const char *nome_file,
                                T_rigaVendite **righe,
                                unsigned *pNum_prodotti) {
    //da implementare
    if (!nome_file || !righe || !pNum_prodotti) {
        return 0;
    }

    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
        return 0;
    }

    unsigned num_prodotti = 0, num_negozi = 0;
    if (fscanf(fp, "%u %u", &num_prodotti, &num_negozi) != 2) {
        fprintf(stderr, "Intestazione file non valida.\n");
        fclose(fp);
        return 0;
    }
    if (num_prodotti == 0 || num_negozi == 0) {
        fprintf(stderr, "Valori non validi: num_prodotti=%u, num_negozi=%u\n",
                num_prodotti, num_negozi);
        fclose(fp);
        return 0;
    }

    T_rigaVendite *arr =(T_rigaVendite*) calloc(num_negozi, sizeof(T_rigaVendite));
    if (!arr) {
        fprintf(stderr, "Memoria insufficiente per l'array negozi.\n");
        fclose(fp);
        return 0;
    }

    unsigned caricati = 0;
    for (unsigned i = 0; i < num_negozi; i++) {
        if (fscanf(fp, "%s", arr[i].negozio) != 1) {
            fprintf(stderr, "Errore nel leggere il nome del negozio alla riga %u.\n", i + 2);
            break;
        }

        arr[i].vendite = malloc(num_prodotti * sizeof(int));
        if (!arr[i].vendite) {
            fprintf(stderr, "Memoria insufficiente per le vendite del negozio %s.\n", arr[i].negozio);
            break;
        }

        bool ok = true;
        for (unsigned j = 0; j < num_prodotti; j++) {
            if (fscanf(fp, "%d", &arr[i].vendite[j]) != 1) {
                fprintf(stderr, "Dato non valido per negozio %s (prodotto %u).\n",
                        arr[i].negozio, j + 1);
                ok = false;
                break;
            }
        }

        if (!ok) {
            free(arr[i].vendite);
            arr[i].vendite = NULL;
            break;
        }

        caricati++;
    }

    fclose(fp);

    if (caricati == 0) {
        libera_vendite(arr, num_negozi);
        return 0;
    }

    if (caricati < num_negozi) {
        for (unsigned i = caricati; i < num_negozi; i++) {
            free(arr[i].vendite);
            arr[i].vendite = NULL;
        }
        T_rigaVendite *tmp = (T_rigaVendite*)realloc(arr, caricati * sizeof(T_rigaVendite));
        if (tmp) arr = tmp;
    }

    *righe = arr;
    *pNum_prodotti = num_prodotti;
    return caricati;
}

/*
*  Per ogni negozio calcolare min, max, media delle P vendite.
 *  Restituisce un array di T_statistiche lungo n_negozi.
 */
T_statistiche* calcola_statistiche_negozi(T_rigaVendite *vet,
                                          unsigned n_negozi,
                                          unsigned num_prodotti) {

    T_statistiche *stat = (T_statistiche*)malloc(n_negozi * sizeof(T_statistiche));
    if (!stat) {
        return NULL;
    }
    for (unsigned i = 0; i < n_negozi; i++) {
        int min = vet[i].vendite[0];
        int max = vet[i].vendite[0];
        long somma = 0;

        for (unsigned j = 1; j < num_prodotti; j++) {
            int q = vet[i].vendite[j];
            if (q < min) min = q;
            if (q > max) max = q;
            somma += q;
        }

        strncpy(stat[i].nome, vet[i].negozio, STR_LEN - 1);
        stat[i].nome[STR_LEN - 1] = '\0';
        stat[i].min = min;
        stat[i].max = max;
        stat[i].media = (float)somma / (float)num_prodotti;
    }

    return stat;

}



/*
 *  Calcolare min, max, media per ciascun prodotto (colonna)
 *  e scrivere su NOME_FILE_DA_CONSEGNARE nel formato:
 *    Prodotto1 min max media
 *    Prodotto2 min max media
 *    ...
 *  Media con 2 cifre decimali.
 */
bool statistiche_per_prodotto_su_file(const char *nomefile,
                                      T_rigaVendite *vet,
                                      unsigned n_negozi,
                                      unsigned num_prodotti) {

    FILE *fp = fopen(nomefile, "w");
    if (!fp) {
        return false;
    }

    for (unsigned n = 0; n < num_prodotti; n++) {
        int min = vet[0].vendite[n];
        int max = vet[0].vendite[n];
        long somma = 0;

        for (unsigned j = 1; j < n_negozi; j++) {
            int q = vet[j].vendite[n];
            if (q < min) min = q;
            if (q > max) max = q;
            somma += q;
        }

        float media = (float) somma / (float) num_prodotti;
        fprintf(fp, "Prodotto%u %d %d %.2f\n", n+1, min, max, media);
    }

    //da completare
    fclose(fp);
    return true;
}

int main(void) {
    T_rigaVendite *righe = NULL;
    unsigned n_negozi = 0;
    unsigned num_prodotti = 0;

    //Caricamento  dell'array dei negozi

    n_negozi = carica_vendite_da_file(NOME_FILE, &righe, &num_prodotti);
    if (n_negozi == 0) {
        printf("Errore nella lettura del file o nessun dato caricato\n");
        return 1;
    }

    //calcola_statistiche_negozi per ogni negozio e caricale su un array


    T_statistiche *stat_negozi = calcola_statistiche_negozi(righe, n_negozi, num_prodotti);
    if (!stat_negozi) {
        libera_vendite(righe, n_negozi);
        return 1;
    }

    //Stampa a video: NomeNegozio min max media */

    for (unsigned i = 0; i < n_negozi; i++) {
        printf("%s %d %d %.2f\n",
               stat_negozi[i].nome,
               stat_negozi[i].min,
               stat_negozi[i].max,
               stat_negozi[i].media);
    }

    // Salva le statistiche per prodotto su file

    if (!statistiche_per_prodotto_su_file(NOME_FILE_DA_CONSEGNARE, righe, n_negozi, num_prodotti)) {
        printf("Errore nella scrittura del file di uscita\n");
    }

    /* Deallocazione */
    libera_vendite(righe, n_negozi);
    free(righe);

    return 0;
}