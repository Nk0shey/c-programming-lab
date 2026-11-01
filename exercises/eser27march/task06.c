#include "../../common/records.h"
//
// Created by Nikita on 11/05/2026.
//
#define MAX_STUDENTI 100
#define STR_LEN 50
#define NOME_FILE_INPUT "es_6_esito_esami.txt"
#define NOME_FILE_OUTPUT "insufficienti.txt"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { NON_SUPERATO, SUPERATO } T_esito;

typedef struct {
    char matricola[MAX_STUDENTI];
    char codice_corso[MAX_STUDENTI];
    int voto1;
    int voto2;
    float media;
    float perc_presenze;
    T_esito esito;
    int voto_finale;
}T_Studente;

int carica_esiti(char *nome_file, T_Studente v[], int max) {
    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        printf("Errore apertura file\n");
        return -1;
    }
    int n = 0;
    char line[512], extra;
    int status;
    while ((status = lab_read_record(file, line, sizeof line)) == 1) {
        if (n >= max || sscanf(line, "%99s %99s %d %d %f %c", v[n].matricola, v[n].codice_corso, &v[n].voto1, &v[n].voto2, &v[n].perc_presenze, &extra) != 5 || !(v[n].voto1 >= 0 && v[n].voto1 <= 30 && v[n].voto2 >= 0 && v[n].voto2 <= 30 && isfinite(v[n].perc_presenze) && v[n].perc_presenze >= 0 && v[n].perc_presenze <= 1)) {
            fclose(file);
            return -1;
        }
        v[n].media = 0; v[n].esito = NON_SUPERATO; v[n].voto_finale = 0;
        ++n;
    }
    if (status < 0) { fclose(file); return -1; }
    fclose(file);
    return n;
}

int arrotonda_intero(float x) {
    return(int)round(x);
}

/* The supplied source has no grading prompt. Preserve its explicit rule:
 * both marks >=18 and mean >18, add 2 and cap at 31. Attendance is reported
 * separately. A different course policy requires the original assignment. */
void calcola_esiti(T_Studente v[], int n) {
    int i;
    int voto_tmp;

    for (i = 0; i < n; i++) {
        v[i].media = (v[i].voto1 + v[i].voto2) / 2.0f;
        if (v[i].voto1 >= 18 && v[i].voto2 >= 18 && v[i].media > 18.0f) {
            v[i].esito = SUPERATO;
            voto_tmp = arrotonda_intero(v[i].media + 2.0f);

            if (voto_tmp > 31) {
                voto_tmp = 31;
            }

            v[i].voto_finale = voto_tmp;

        } else {
            v[i].esito = NON_SUPERATO;
            v[i].voto_finale = 0;
        }
    }
}

int salva_insufficienti(char *nome_file, T_Studente v[], int n) {
    FILE *file = fopen(nome_file, "w");
    if (file == NULL) {
        printf("Errore apertura file\n");
        return -1;
    }
    int i, cont = 0;
    for (i = 0; i < n; i++) {
        if (v[i].esito == NON_SUPERATO) {
            if (fprintf(file, "%s %s %.2f %.2f\n", v[i].matricola, v[i].codice_corso, v[i].media, v[i].perc_presenze) < 0) { fclose(file); return -1; }
            cont++;
        }
    }
    if (fclose(file) != 0) return -1;
    return cont;
}

int trova_esito_massimo(T_Studente v[], int n, char *codice_corso, T_Studente *max_esito) {
    int i;
    int trovato = 0;
    int pos_max = -1;

    for (i = 0; i < n; i++) {
        if (strcmp(v[i].codice_corso, codice_corso) == 0) {
            if (!trovato || v[i].voto_finale > v[pos_max].voto_finale) {
                pos_max = i;
                trovato = 1;
            }
        }
    }

    if (!trovato) {
        return 0;
    }

    *max_esito = v[pos_max];
    return 1;
}

int calcola_media_presenze_promossi(T_Studente v[], int n, float *media_presenze) {
    int i, cont = 0;
    float somma = 0.0f;
    for (i = 0; i < n; i++) {
        if (v[i].esito == SUPERATO) {
            somma += v[i].perc_presenze;
            cont++;
        }
    }
    if (cont == 0) return 0;
    *media_presenze = somma / cont;
    return 1;
}

int salva_matricole_media_superiore(char *nome_file, T_Studente v[], int n, float soglia) {
    FILE *file = fopen(nome_file, "w");
    if (file == NULL) {
        printf("Errore apertura file\n");
        return -1;
    }

    int i, cont = 0;
    for (i = 0; i < n; i++) {
        if (v[i].media > soglia) {
            if (fprintf(file, "%s\n", v[i].matricola) < 0) { fclose(file); return -1; }
            cont++;
        }
    }
    if (fclose(file) != 0) return -1;
    return cont;
}

int aggiorna_voti_studente(T_Studente v[], int n, char matricola[]) {
    int nuovo_voto1, nuovo_voto2;
    int i;

    for (i = 0; i < n; i++) {
        if (strcmp(v[i].matricola, matricola) == 0) {
            printf("Inserisci il nuovo voto (1): ");
            if (scanf("%d", &nuovo_voto1) != 1) {
                return 0;
            }

            printf("Inserisci il nuovo voto (2): ");
            if (scanf("%d", &nuovo_voto2) != 1) {
                return 0;
            }

            if (nuovo_voto1 < 0 || nuovo_voto1 > 30 || nuovo_voto2 < 0 || nuovo_voto2 > 30) return 0;
            v[i].voto1 = nuovo_voto1;
            v[i].voto2 = nuovo_voto2;
            calcola_esiti(v, n);
            return 1;
        }
    }

    return 0;
}

void stampa_esito_testuale(T_esito esito) {
    if (esito == SUPERATO) {
        printf("SUPERATO");
    } else {
        printf("NON_SUPERATO");
    }
}

void stampa_studente(T_Studente s) {
    printf("%s %s %d %d %.2f %.2f ",
           s.matricola,
           s.codice_corso,
           s.voto1,
           s.voto2,
           s.perc_presenze,
           s.media);

    stampa_esito_testuale(s.esito);
    printf(" %d\n", s.voto_finale);
}


void stampa_vettore(T_Studente v[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d) ", i + 1);
        stampa_studente(v[i]);
    }
}

int menu(void) {
    int scelta;

    printf("\n*** MENU ***\n");
    printf("1 - Lettura dei dati da file\n");
    printf("2 - Visualizzazione di tutti gli elementi caricati\n");
    printf("3 - Salvataggio degli insufficienti su file\n");
    printf("4 - Ricerca dell'esame con voto finale massimo dato un codice corso\n");
    printf("5 - Calcolo della presenza media dei promossi\n");
    printf("6 - Salvataggio delle matricole con media superiore a una soglia\n");
    printf("7 - Aggiornamento dei voti di uno studente data la matricola\n");
    printf("0 - Uscita\n");
    printf("Scelta: ");

    if (scanf("%d", &scelta) != 1) {
        return -1;
    }
    return scelta;
}

int main(void) {
    T_Studente vettore_studenti[MAX_STUDENTI];
    int scelta;
    int n = 0;
    int dati_caricati = 0;
    int num_iscritti;
    T_Studente max_esito;
    char codice_corso[STR_LEN];
    float media_presenze;
    char nome_file_out[STR_LEN];
    float soglia;
    char matricola[STR_LEN];


    do {
        scelta = menu();
        if (scelta == -1) break;

        switch (scelta) {
            case 1:
                dati_caricati = 0;
                n = carica_esiti(NOME_FILE_INPUT, vettore_studenti, MAX_STUDENTI);
                if (n == -1) {
                    printf("Errore apertura file %s\n", NOME_FILE_INPUT);
                }
                else {
                    calcola_esiti(vettore_studenti, n);
                    dati_caricati = 1;
                    printf("Caricati %d record dal file %s\n", n, NOME_FILE_INPUT);
                }
                break;
            case 2:
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                } else {
                    stampa_vettore(vettore_studenti, n);
                }
                break;
            case 3:
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                }
                else {
                    num_iscritti = salva_insufficienti(NOME_FILE_OUTPUT, vettore_studenti, n);
                    if (num_iscritti == -1) {
                        printf("Errore apertura file %s\n", NOME_FILE_OUTPUT);
                    } else {
                        printf("Scritti %d record nel file %s\n", num_iscritti, NOME_FILE_OUTPUT);
                    }
                }
                break;
            case 4: {
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                }
                else {
                    printf("Inserisci il codice corso: ");
                    if (scanf("%49s", codice_corso) != 1) {
                        printf("Errore nell'acquisizione del codice del corso\n");
                        break;
                    }
                    if (trova_esito_massimo(vettore_studenti, n, codice_corso, &max_esito)) {
                        printf("Esito massimo per il corso %s\n:", codice_corso);
                        stampa_studente(max_esito);
                    } else {
                        printf("Nessun studente trovato per il corso %s\n", codice_corso);
                    }
                }
                break;
            }
            case 5: {
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                }
                else {
                    if (calcola_media_presenze_promossi(vettore_studenti, n, &media_presenze)) {
                        printf("Media presenze: %.2f\n", media_presenze);
                    } else {
                        printf("Nessun studente promosso presente nel vettore");
                    }
                }
                break;
            }
            case 6: {
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                }
                else {
                    printf("Inserisci il nome del file di output: ");
                    if (scanf("%49s", nome_file_out) != 1) {
                        printf("Errore nell'acquisizione del nome del file");
                        break;
                    }
                    printf("Inserisci la soglia: ");
                    if (scanf("%f", &soglia) != 1) {
                        printf("Errore nell'acquisizione della soglia");
                        break;
                    }

                    num_iscritti = salva_matricole_media_superiore(nome_file_out, vettore_studenti, n, soglia);
                    if (num_iscritti == -1) {
                        printf("Errore apertura file %s\n", nome_file_out);
                    } else {
                        printf("Scritte %d matricole nel file %s\n", num_iscritti, nome_file_out);
                    }
                }
                break;
            }
            case 7: {
                if (!dati_caricati) {
                    printf("Caricare prima i dati da file.\n");
                }
                else {
                    printf("Inserisci la matricola dello studente");
                    if (scanf("%49s", matricola) != 1) {
                        printf("Errore nell'acquisizione della matricola");
                        break;
                    }
                    if (aggiorna_voti_studente(vettore_studenti, n, matricola)) {
                        printf("Voti aggiornati correttamente\n");
                    } else {
                        printf("Studente non trovato oppure errore nell'aggiornamento.\n");
                    }
                }
                break;
            }
            case 0:
                printf("Uscita dal programma\n");
                break;

            default:
                printf("Scelta non valida");
        }
    } while (scelta != 0);

    return 0;
}