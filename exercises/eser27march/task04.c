#include "../../common/records.h"
#include <math.h>
//
// Created by Nikita on 10/05/2026.
//

#include <stdio.h>

#define STR_MAX 101
#define MAX_LIBRI 50

typedef struct {
    char titolo[STR_MAX];
    int anno;
    float prezzo;
} Libro;

void scambia_libri(Libro *a, Libro *b) {
    Libro temp = *a;
    *a = *b;
    *b = temp;
}

void ordina_libri(Libro v[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;

        while (j > 0 && v[j - 1].anno > v[j].anno) {
            scambia_libri(&v[j - 1], &v[j]);
            j--;
        }
    }
}

int main(void) {
    Libro catalogo[MAX_LIBRI];

    FILE *file_in = fopen("es_4_libri.txt", "r");
    FILE *file_out;

    if (file_in == NULL) {
        perror("Errore nell'apertura dei file");
        return 1;
    }

    int n = 0;

    char line[512], extra;
    int status;
    while ((status = lab_read_record(file_in, line, sizeof line)) == 1) {
        if (n >= MAX_LIBRI || sscanf(line, "%100s %d %f %c", catalogo[n].titolo, &catalogo[n].anno, &catalogo[n].prezzo, &extra) != 3 || !(isfinite(catalogo[n].prezzo) && catalogo[n].prezzo >= 0)) {
            fclose(file_in);
            return 1;
        }
        ++n;
    }
    if (status < 0) { fclose(file_in); return 1; }
    fclose(file_in);

    ordina_libri(catalogo, n);
    file_out = fopen("libri_ordinati.txt", "w");
    if (!file_out) return 1;

    for (int i = 0; i < n; i++) {
        if (fprintf(file_out, "%s %d %.2f\n",
                catalogo[i].titolo,
                catalogo[i].anno,
                catalogo[i].prezzo) < 0) { fclose(file_out); return 1; }
    }

    if (fclose(file_out) != 0) return 1;

    return 0;
}