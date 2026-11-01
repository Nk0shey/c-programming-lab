#include "../../common/records.h"
#include <stdio.h>
#include <stdlib.h>
#define STR_CITTA 51
#define STR_COD 8

#define NOME_FILE "Spedizioni.txt"

typedef struct {
    char citta_partenza[STR_CITTA];
    char citta_consegna[STR_CITTA];
    char codice_spedizione[STR_COD];
    int distanza_totale;
    int km_percorsi;
    float percentuale_percorsa;
}T_consegna;

T_consegna *carica_consegne(char *nome_file, int *n_consegne) {
    *n_consegne = 0;
    FILE *fp = fopen(nome_file, "r");
    if (!fp) return NULL;
    int count, status; char line[512], extra;
    if (lab_read_record(fp, line, sizeof line) != 1 ||
        sscanf(line, "%d %c", &count, &extra) != 1 || count <= 0 || count > 1000000) {
        fclose(fp); return NULL;
    }
    T_consegna *v = malloc((size_t)count * sizeof *v);
    if (!v) { fclose(fp); return NULL; }
    for (int i = 0; i < count; ++i) {
        T_consegna *c = &v[i];
        if (lab_read_record(fp, line, sizeof line) != 1 ||
            sscanf(line, "%50s %50s %7s %d %d %c", c->citta_partenza,
                   c->citta_consegna, c->codice_spedizione,
                   &c->distanza_totale, &c->km_percorsi, &extra) != 5 ||
            c->distanza_totale <= 0 || c->km_percorsi < 0 ||
            c->km_percorsi > c->distanza_totale) {
            free(v); fclose(fp); return NULL;
        }
        c->percentuale_percorsa = 0;
    }
    status = lab_read_record(fp, line, sizeof line);
    fclose(fp);
    if (status != 0) { free(v); return NULL; }
    *n_consegne = count;
    return v;
}

void calcola_percentuale(T_consegna *vettore_consegne, int n_consegne) {
    for (int i = 0; i < n_consegne; i++) {
        vettore_consegne[i].percentuale_percorsa = ((float) vettore_consegne[i].km_percorsi * 100) / ((float) vettore_consegne[i].distanza_totale);
    }
}

int consegne_da_fare(char nome_file[], T_consegna *vettore_consegne, int n_consegne) {
    int num_scritture = 0;
    FILE *fp = fopen(nome_file, "w");
    if (fp == NULL) {
        printf("Errore dell'appertura del file\n");
        return -1;
    }
    for (int i = 0; i < n_consegne; i++) {
        if (vettore_consegne[i].percentuale_percorsa < 100) {
            if (fprintf(fp, "%s %s %s %d\n", vettore_consegne[i].citta_partenza, vettore_consegne[i].citta_consegna, vettore_consegne[i].codice_spedizione, vettore_consegne[i].distanza_totale - vettore_consegne[i].km_percorsi) < 0) { fclose(fp); return -1; }
            num_scritture++;
        }
    }
    if (fclose(fp) != 0) return -1;
    return num_scritture;
}

int main(void) {
    T_consegna *vettore_consegne;
    int n_consegne;
    int n_scritture = 0;
    char nome_file_cons[STR_CITTA];

    vettore_consegne = carica_consegne(NOME_FILE, &n_consegne);
    if (!vettore_consegne) {
        printf("Errore nel caricamento delle consegne\n");
        return 1;
    }

    calcola_percentuale(vettore_consegne, n_consegne);

    for (int i=0; i<n_consegne; i++) {
        printf("%s %s %s %d %d %f\n", vettore_consegne[i].citta_partenza, vettore_consegne[i].citta_consegna, vettore_consegne[i].codice_spedizione,
            vettore_consegne[i].distanza_totale, vettore_consegne[i].km_percorsi, vettore_consegne[i].percentuale_percorsa);
    }
    printf("Inserisci il nome del file per salvare i dati: ");
    if (scanf("%50s", nome_file_cons) != 1) { free(vettore_consegne); return 1; }
    n_scritture = consegne_da_fare(nome_file_cons, vettore_consegne, n_consegne);
    printf("\nSono state effettute %d scritture", n_scritture);

    free(vettore_consegne);
    return n_scritture < 0 ? 1 : 0;

}