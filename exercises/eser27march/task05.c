#include "../../common/records.h"
#include <math.h>
//
// Created by Nikita on 10/05/2026.
//

#include<stdio.h>
#define MAX_PRESTITI 100
#define STR_MAX 51
#define COD_MAX 6
#define NOME_FILE_INPUT "es_5_prestiti_libri.txt"
#define NOME_FILE_OUTPUT "es_5_ritardi_prestiti.txt"
typedef struct {
    char matricola[STR_MAX];
    char titolo[STR_MAX];
    char codice_prestito[COD_MAX];
    int giorni_consentiti;
    int giorni_trascorsi;
    int giorni_ritardo;
} T_prestito;

int carica_prestiti(char nome_file[], T_prestito v[], int max) {
    FILE *file;
    int n = 0;

    file = fopen(nome_file, "r");

    if (file == NULL) {
        perror("ERRORE apertura file");
        return -1;
    }

    char line[512], extra;
    int status;
    while ((status = lab_read_record(file, line, sizeof line)) == 1) {
        if (n >= max || sscanf(line, "%50s %50s %5s %d %d %c", v[n].matricola, v[n].titolo, v[n].codice_prestito, &v[n].giorni_trascorsi, &v[n].giorni_consentiti, &extra) != 5 || !(v[n].giorni_trascorsi >= 0 && v[n].giorni_consentiti >= 0)) {
            fclose(file);
            return -1;
        }
        v[n].giorni_ritardo = 0;
        ++n;
    }
    if (status < 0) { fclose(file); return -1; }
    fclose(file);
    return n;
}

void calcola_giorni_ritardo(T_prestito v[], int n) {
    int i = 0;
    int giorni_ritardo = 0;
    for (i = 0; i < n; i++) {
        giorni_ritardo = v[i].giorni_trascorsi - v[i].giorni_consentiti;
        v[i].giorni_ritardo = giorni_ritardo > 0 ? giorni_ritardo : 0;
    }
}

int salva_ritardi(char nome_file[], T_prestito v[], int n) {
    FILE *file;
    int i, cont = 0;
    file = fopen(nome_file, "w");
    if (file == NULL) {
        printf("\n\nERRORE apertura file");
        return -1;
    }
    for (i = 0; i < n; i++) {
        if (v[i].giorni_ritardo > 0) {
            if (fprintf(file, "%s %s %s %d\n", v[i].matricola, v[i].titolo,
                    v[i].codice_prestito,
                    v[i].giorni_ritardo) < 0) { fclose(file); return -1; }
            cont++;
        }
    }
    if (fclose(file) != 0) return -1;
    return cont;
}

void conta_prestiti_regolari(T_prestito v[], int n, int *num_regolari) {
    *num_regolari = 0;

    for (int i = 0; i < n; i++) {
        if (v[i].giorni_ritardo == 0) {
            (*num_regolari)++;
        }
    }
}

void stampa_prestito(T_prestito p) {
    printf("%s %s %s %d %d %d\n",
           p.matricola,
           p.titolo,
           p.codice_prestito,
           p.giorni_trascorsi,
           p.giorni_consentiti,
           p.giorni_ritardo);
}

void stampa_vettore(T_prestito v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d) ", i + 1);
        stampa_prestito(v[i]);
    }
}

int main() {
    T_prestito vettore_prestiti[MAX_PRESTITI];
    int n;
    int num_regolari;
    int num_ritardi;

    n = carica_prestiti(NOME_FILE_INPUT, vettore_prestiti, MAX_PRESTITI);
    if (n == -1) {
        printf("Errore nell'apertura del file %s\n", NOME_FILE_INPUT);
        return 1;
    }

    printf("Numero di prestiti caricati: %d\n\n", n);
    calcola_giorni_ritardo(vettore_prestiti, n);
    printf("Prestiti aggiornati:\n");
    stampa_vettore(vettore_prestiti, n);
    num_ritardi = salva_ritardi(NOME_FILE_OUTPUT, vettore_prestiti, n);
    if (num_ritardi == -1) {
        printf("\nErrore nell'apertura del file %s\n", NOME_FILE_OUTPUT);
        return 1;
    }
    conta_prestiti_regolari(vettore_prestiti, n, &num_regolari);
    printf("\nRecord scritti nel file %s: %d\n", NOME_FILE_OUTPUT, num_ritardi);
    printf("Numero di prestiti regolari: %d\n", num_regolari);

    return 0;
}