#define main exercise_main
#include "../exercises/newSim1/main.c"
#undef main
#include <assert.h>

int main(void){

Laboratorio l={0};strcpy(l.codice_lab,"L1");PilaElaborate p=NULL;
assert(elabora_prossima_richiesta(&l,1,"L1",&p)==0);assert(elabora_prossima_richiesta(&l,1,"missing",&p)==0);
NodoRichiesta *n=calloc(1,sizeof *n);assert(n);strcpy(n->info.codice_richiesta,"R1");l.coda.primo=l.coda.ultimo=n;l.coda.num_richieste=1;
assert(elabora_prossima_richiesta(&l,1,"L1",&p)==1);assert(p && !strcmp(p->richiesta.codice_richiesta,"R1"));assert(!l.coda.primo && !l.coda.ultimo && !l.coda.num_richieste);free(p);

FILE *f = fopen("invalid_labs.txt", "w"); assert(f);
    fputs("1\nL1\n2\nL1 R1 S1 HARDWARE 1 10\nMISSING R2 S2 HARDWARE 1 20\n", f); fclose(f);
    unsigned count = 99;
    assert(!carica_laboratori("invalid_labs.txt", &count) && count == 0);
    return 0;
}
