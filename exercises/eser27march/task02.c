#include "../../common/records.h"
#include <math.h>
#include <stdio.h>
#define STRLEN 31
#define MAX_STUDENTI 50

typedef struct {
    char nome[STRLEN];
    int matricola;
    float media;
}Studente;

void bonus_media(Studente *s) {
    if (s->media > 28.0) {
        s->media += 0.5;
        if (s->media > 30.0) {
            s->media = 30.0;
        }
    }
}

int main() {
    Studente studenti[MAX_STUDENTI];
    FILE* file_in = fopen("es_2_studenti.txt", "r");
    if (file_in == NULL) {
        printf("Errore nell'appertura del file!\n");
        return 1;
    }
    int n = 0;
    char line[512], extra;
    int status;
    while ((status = lab_read_record(file_in, line, sizeof line)) == 1) {
        if (n >= MAX_STUDENTI || sscanf(line, "%30s %d %f %c", studenti[n].nome, &studenti[n].matricola, &studenti[n].media, &extra) != 3 || !(isfinite(studenti[n].media) && studenti[n].media >= 0 && studenti[n].media <= 30)) {
            fclose(file_in);
            return 1;
        }
        ++n;
    }
    if (status < 0) { fclose(file_in); return 1; }
    fclose(file_in);

    FILE* file_out = fopen("es_2_studenti_bonus.txt", "w");
    if (file_out == NULL) {
        printf("Errore nell'appertura del file!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        bonus_media(&studenti[i]);
        if (fprintf(file_out, "%s %d %.2f\n", studenti[i].nome, studenti[i].matricola, studenti[i].media) < 0) { fclose(file_out); return 1; }
    }
    if (fclose(file_out) != 0) return 1;

    return 0;
}