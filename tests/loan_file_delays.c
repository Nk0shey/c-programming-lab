#define main exercise_main
#include "../exercises/eser27march/task05.c"
#undef main
#include <assert.h>
int main(void) {

T_prestito v[2]; FILE *f=fopen("loans.txt","w"); assert(f); fputs("S1 Book P01 12 10\nS2 Other P02 3 10\n",f); fclose(f);
assert(carica_prestiti("loans.txt",v,2)==2); calcola_giorni_ritardo(v,2); assert(v[0].giorni_ritardo==2 && v[1].giorni_ritardo==0);
int count; conta_prestiti_regolari(v,2,&count); assert(count==1); assert(salva_ritardi("late.txt",v,2)==1);
#ifdef __linux__
assert(salva_ritardi("/dev/full",v,2)==-1);
#endif

v[0].giorni_trascorsi=5; calcola_giorni_ritardo(v,2); assert(v[0].giorni_ritardo==0);
assert(carica_prestiti("loans.txt",v,1)==-1);
f=fopen("bad.txt","w"); assert(f); fputs("S1 Book P01 -1 10\n",f); fclose(f); assert(carica_prestiti("bad.txt",v,2)==-1);

return 0;
}
