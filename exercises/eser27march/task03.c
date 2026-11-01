#include "../../common/records.h"
#include <math.h>
//
// Created by Nikita on 10/05/2026.
//
#include<stdio.h>
#define STRING_MAX 31
#define RIL_MAX 50
typedef struct {
    char citta[STRING_MAX];
    float temperatura;
    float umidita;
} Rilevazione;

void analizza_dati(Rilevazione v[], int n, float *p_max, float *p_media) {
    if (n <= 0) {
        *p_max = 0;
        *p_media = 0;
        return;
    }

    *p_max = v[0].temperatura;
    float somma_temperatura = v[0].temperatura;
    for (int i = 1; i < n; i++) {
        if (v[i].temperatura > *p_max) {
            *p_max = v[i].temperatura;
        }
        somma_temperatura += v[i].temperatura;
    }

    *p_media = somma_temperatura / n;
}

int main() {
    Rilevazione rilevazioni[RIL_MAX];
    FILE *file = fopen("es_3_meteo.txt", "r");
    if (file == NULL) {
        printf("Errore nella apertura del file\n");
        return 1;
    }
    int n = 0;
    char line[512], extra;
    int status;
    while ((status = lab_read_record(file, line, sizeof line)) == 1) {
        if (n >= RIL_MAX || sscanf(line, "%30s %f %f %c", rilevazioni[n].citta, &rilevazioni[n].temperatura, &rilevazioni[n].umidita, &extra) != 3 || !(isfinite(rilevazioni[n].temperatura) && isfinite(rilevazioni[n].umidita) && rilevazioni[n].umidita >= 0 && rilevazioni[n].umidita <= 100)) {
            fclose(file);
            return 1;
        }
        ++n;
    }
    if (status < 0) { fclose(file); return 1; }
    fclose(file);

    float temperatura_max, temperatura_media;
    analizza_dati(rilevazioni, n, &temperatura_max, &temperatura_media);
    printf("Temperatura max: %.2f\n", temperatura_max);
    printf("Temperatura media: %.2f\n", temperatura_media);
    return 0;
}