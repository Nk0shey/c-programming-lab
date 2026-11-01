#define main exercise_main
#include "../exercises/newSim1/main.c"
#undef main
#include <assert.h>

int main(void){

Laboratorio l={0};strcpy(l.codice_lab,"L1");PilaElaborate p=NULL;
assert(elabora_prossima_richiesta(&l,1,"L1",&p)==0);assert(elabora_prossima_richiesta(&l,1,"missing",&p)==0);
NodoRichiesta *n=calloc(1,sizeof *n);assert(n);strcpy(n->info.codice_richiesta,"R1");l.coda.primo=l.coda.ultimo=n;l.coda.num_richieste=1;
assert(elabora_prossima_richiesta(&l,1,"L1",&p)==1);assert(p && !strcmp(p->richiesta.codice_richiesta,"R1"));assert(!l.coda.primo && !l.coda.ultimo && !l.coda.num_richieste);free(p);

return 0;
}
