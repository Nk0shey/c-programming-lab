#define main exercise_main
#include "../exercises/compiti anni precedenti/compito3/main.c"
#undef main
#include <assert.h>
int main(void) {
    CodaMerce q; inizializzaCoda(&q,"CT"); Merce a={"M1","01-01-2026",2,"CT"},b={"M2","01-01-2026",3,"CT"};
    assert(aggiungiMerceInCoda(&q,a)==OK);assert(aggiungiMerceInCoda(&q,b)==OK);
    unsigned n;float peso;assert(quantificaMerce(&q,"CT",1,&n,&peso)==OK && n==2 && peso==5);
    Merce *v=estraiPrimeNMerci(&q,"CT",1,1,&n);assert(v && n==1 && !strcmp(v[0].codice,"M1"));free(v);
    v=estraiPrimeNMerci(&q,"CT",1,10,&n);assert(v && n==1 && !strcmp(v[0].codice,"M2"));free(v);assert(!q.primo && !q.ultimo && q.num_elementi==0);
    disallocaCoda(&q);return 0;
}
