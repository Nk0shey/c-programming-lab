/* Irrigation exercise: ordered areas, zone lists and a search-tree index.
 * aree.txt: area_code rain_probability
 * zone.txt: zone_code flow correction_factor state humidity area_code
 * state: 0=off, 1=on; codes contain 1..10 alphanumeric characters.
 * Time follows the written exercise formula: (100-humidity)*correction_factor,
 * truncated to whole seconds; rain probability above 50 suppresses watering.
 * The historical sample output used a different, flow-weighted formula.
 */
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CODICE 11

typedef enum { SPENTO, ACCESO } Stato;
typedef struct Zona {
    char codice[MAX_CODICE];
    float portata, fattore_correzione;
    Stato stato;
    int umidita;
    struct Zona *next;
} zona, *elenco_zone;
typedef struct Area {
    char codice[MAX_CODICE];
    int num_zone, prob_pioggia;
    elenco_zone lista_zone;
    struct Area *next;
} area, *elenco_aree;
typedef struct NodoIndice {
    char codice_zona[MAX_CODICE];
    int tempo_accensione;
    struct NodoIndice *left, *right;
} nodo_indice, *indice;

static int codice_valido(const char *s) {
    if (!s || !*s || strlen(s) >= MAX_CODICE) return 0;
    for (; *s; ++s) if (!isalnum((unsigned char)*s)) return 0;
    return 1;
}
void libera_impianto(elenco_aree *p) {
    if (!p) return;
    while (*p) {
        area *a = *p; *p = a->next;
        while (a->lista_zone) { zona *z = a->lista_zone; a->lista_zone = z->next; free(z); }
        free(a);
    }
}
void libera_indice(indice *p) {
    if (!p || !*p) return;
    libera_indice(&(*p)->left); libera_indice(&(*p)->right);
    free(*p); *p = NULL;
}
area *crea_area(const char *codice, int prob_pioggia) {
    if (!codice_valido(codice) || prob_pioggia < 0 || prob_pioggia > 100) return NULL;
    area *a = calloc(1, sizeof *a); if (!a) return NULL;
    strcpy(a->codice, codice); a->prob_pioggia = prob_pioggia; return a;
}
elenco_aree inserisci_area(elenco_aree testa, area *nuova) {
    if (!nuova) return testa;
    area **p = &testa;
    while (*p && strcmp((*p)->codice, nuova->codice) < 0) p = &(*p)->next;
    if (*p && !strcmp((*p)->codice, nuova->codice)) return testa; /* caller retains duplicate */
    nuova->next = *p; *p = nuova; return testa;
}
area *cerca_area(elenco_aree testa, const char *codice) {
    if (!codice) return NULL;
    for (; testa; testa = testa->next) if (!strcmp(testa->codice, codice)) return testa;
    return NULL;
}
static zona *cerca_zona(elenco_aree p, const char *codice) {
    if (!codice) return NULL;
    for (; p; p = p->next) for (zona *z = p->lista_zone; z; z = z->next)
        if (!strcmp(z->codice, codice)) return z;
    return NULL;
}
int inserisci_zona(area *a, const char *codice, float portata, float fattore, Stato stato, int umidita) {
    if (!a || !codice_valido(codice) || !isfinite(portata) || portata <= 0 ||
        !isfinite(fattore) || fattore < 0 || fattore > 1 ||
        (stato != SPENTO && stato != ACCESO) || umidita < 0 || umidita > 100) return 0;
    for (zona *z = a->lista_zone; z; z = z->next) if (!strcmp(z->codice, codice)) return 0;
    zona *z = malloc(sizeof *z); if (!z) return 0;
    strcpy(z->codice, codice); z->portata = portata; z->fattore_correzione = fattore;
    z->stato = stato; z->umidita = umidita; z->next = a->lista_zone;
    a->lista_zone = z; ++a->num_zone; return 1;
}
/* A record occupies one line. Reject long, partial and extra-field records. */
static int leggi_riga(FILE *f, char *s, size_t n) {
    if (!fgets(s, (int)n, f)) return ferror(f) ? -1 : 0;
    if (!strchr(s, '\n') && !feof(f)) return -1;
    return 1;
}
static int solo_spazi(const char *s) {
    for (; *s; ++s) if (!isspace((unsigned char)*s)) return 0;
    return 1;
}
elenco_aree carica_impianto(const char *file_aree, const char *file_zone) {
    if (!file_aree || !file_zone) return NULL;
    FILE *fa = fopen(file_aree, "r"); if (!fa) return NULL;
    FILE *fz = fopen(file_zone, "r"); if (!fz) { fclose(fa); return NULL; }
    elenco_aree p = NULL; char line[512], code[11], ref[11]; int rc, prob, used;
    while ((rc = leggi_riga(fa, line, sizeof line)) == 1) {
        if (solo_spazi(line)) continue;
        used = 0;
        if (sscanf(line, "%10s %d %n", code, &prob, &used) != 2 || !used ||
            !solo_spazi(line + used) || cerca_area(p, code)) goto fail;
        area *a = crea_area(code, prob); if (!a) goto fail;
        p = inserisci_area(p, a);
    }
    if (rc < 0 || !p) goto fail;
    while ((rc = leggi_riga(fz, line, sizeof line)) == 1) {
        float flow, factor; int state, humidity;
        if (solo_spazi(line)) continue;
        used = 0;
        if (sscanf(line, "%10s %f %f %d %d %10s %n", code, &flow, &factor, &state, &humidity, ref, &used) != 6 ||
            !used || !solo_spazi(line + used) || cerca_zona(p, code)) goto fail;
        area *a = cerca_area(p, ref);
        if (!inserisci_zona(a, code, flow, factor, (Stato)state, humidity)) goto fail;
    }
    if (rc < 0) goto fail;
    fclose(fa); fclose(fz); return p;
fail:
    fclose(fa); fclose(fz); libera_impianto(&p); return NULL;
}
int conta_zone_accese(elenco_aree p) {
    int n = 0;
    for (; p; p = p->next) for (zona *z = p->lista_zone; z; z = z->next) if (z->stato == ACCESO) ++n;
    return n;
}
zona *crea_vettore_zone_accese(elenco_aree p, int *n) {
    if (!n) return NULL;
    *n = 0; int count = conta_zone_accese(p); if (!count) return NULL;
    zona *v = malloc((size_t)count * sizeof *v); if (!v) return NULL;
    for (; p; p = p->next) for (zona *z = p->lista_zone; z; z = z->next)
        if (z->stato == ACCESO) { v[*n] = *z; v[(*n)++].next = NULL; }
    return v;
}
int aggiorna_zona(elenco_aree p, const char *codice, Stato stato, float fattore) {
    if ((stato != SPENTO && stato != ACCESO) || !isfinite(fattore) || fattore > 1) return 0;
    zona *z = cerca_zona(p, codice); if (!z) return 0;
    z->stato = stato; if (fattore >= 0) z->fattore_correzione = fattore;
    return 1;
}
static int indice_put(indice *p, const char *codice, int tempo) {
    while (*p) {
        int cmp = strcmp(codice, (*p)->codice_zona);
        if (!cmp) { (*p)->tempo_accensione = tempo; return 1; }
        p = cmp < 0 ? &(*p)->left : &(*p)->right;
    }
    *p = calloc(1, sizeof **p); if (!*p) return 0;
    strcpy((*p)->codice_zona, codice); (*p)->tempo_accensione = tempo; return 1;
}
indice inserisci_nodo_indice(indice root, const char *codice, int tempo) {
    if (!codice_valido(codice) || tempo < 0) return root;
    indice_put(&root, codice, tempo); return root;
}
int calcola_tempo_accensione(area *a, zona *z) {
    if (!a || !z || a->prob_pioggia > 50 || z->stato != ACCESO) return 0;
    return (int)((100 - z->umidita) * z->fattore_correzione);
}
indice calcola_e_costruisci_indice(elenco_aree p) {
    indice root = NULL;
    for (; p; p = p->next) for (zona *z = p->lista_zone; z; z = z->next) {
        int t = calcola_tempo_accensione(p, z);
        if (t > 0 && !indice_put(&root, z->codice, t)) { libera_indice(&root); return NULL; }
    }
    return root;
}
int cerca_tempo_accensione(indice root, const char *codice) {
    if (!codice) return -1;
    while (root) {
        int cmp = strcmp(codice, root->codice_zona);
        if (!cmp) return root->tempo_accensione;
        root = cmp < 0 ? root->left : root->right;
    }
    return -1;
}
int tempo_accensione_zona(indice root, const char *codice) { return cerca_tempo_accensione(root, codice); }
void stampa_albero_indice(indice root) {
    if (!root) return;
    stampa_albero_indice(root->left);
    printf("Zona: %s, Tempo accensione: %d secondi\n", root->codice_zona, root->tempo_accensione);
    stampa_albero_indice(root->right);
}
static int input_line(char *s, size_t n) {
    if (!fgets(s, (int)n, stdin)) return 0;
    if (!strchr(s, '\n') && !feof(stdin)) {
        int c; while ((c = getchar()) != '\n' && c != EOF) { }
        s[0] = '\0';
    }
    return 1;
}
int main(int argc, char **argv) {
    const char *areas = argc > 1 ? argv[1] : "aree.txt";
    const char *zones = argc > 2 ? argv[2] : "zone.txt";
    elenco_aree p = NULL; indice tree = NULL; char line[256];
    for (;;) {
        printf("1 Carica | 2 Zone attive | 3 Modifica | 4 Indice | 5 Cerca | 0 Esci: \n");
        if (!input_line(line, sizeof line)) break;
        char *end; errno = 0; long choice = strtol(line, &end, 10);
        if (errno || end == line || !solo_spazi(end) || choice < 0 || choice > 5) { puts("Input non valido"); continue; }
        if (!choice) break;
        if (choice == 1) {
            elenco_aree fresh = carica_impianto(areas, zones);
            if (!fresh) { puts("Errore caricamento; dati precedenti conservati"); continue; }
            libera_impianto(&p); libera_indice(&tree); p = fresh; puts("Impianto caricato");
        } else if (!p) puts("Caricare prima l'impianto");
        else if (choice == 2) {
            int n; zona *v = crea_vettore_zone_accese(p, &n);
            if (!v && conta_zone_accese(p)) puts("Errore memoria");
            for (int i = 0; i < n; ++i) printf("%s %.2f %.2f %d\n", v[i].codice, v[i].portata, v[i].fattore_correzione, v[i].umidita);
            free(v);
        } else if (choice == 3) {
            char code[11]; int state, used = 0; float factor;
            puts("Codice stato(0/1) fattore(0..1; negativo=mantieni):");
            if (!input_line(line, sizeof line)) break;
            if (sscanf(line, "%10s %d %f %n", code, &state, &factor, &used) != 3 || !used || !solo_spazi(line + used) ||
                !aggiorna_zona(p, code, (Stato)state, factor)) puts("Modifica non valida");
            else { libera_indice(&tree); puts("Zona aggiornata; ricalcolare l'indice"); }
        } else if (choice == 4) {
            libera_indice(&tree); tree = calcola_e_costruisci_indice(p);
            stampa_albero_indice(tree);
        } else if (choice == 5) {
            char code[11]; int used = 0;
            puts("Codice zona:"); if (!input_line(line, sizeof line)) break;
            if (sscanf(line, "%10s %n", code, &used) != 1 || !used || !solo_spazi(line + used)) puts("Codice non valido");
            else printf("Tempo: %d\n", tempo_accensione_zona(tree, code));
        }
    }
    libera_impianto(&p); libera_indice(&tree); return 0;
}
