#define main exercise_main
#include "../exercises/compiti anni precedenti/compito7/Modulo2_Testo.c"
#undef main
#include <assert.h>
int main(void) {

FILE *f=fopen("cash.txt","w");assert(f);fputs("2\n0 Ada\n1 Bob\n3\n0 User1 4.5\n1 User2 2.0\n0 User3 1.5\n",f);fclose(f);
int dim;Cassa *c=carica_casse("cash.txt",&dim);assert(c && dim==2);float *v=tempo_stimato(c,dim);assert(v && v[0]==6 && v[1]==2);free(v);
Albero a=crea_albero(c,dim);assert(a);FILE *o=fopen("cash_out.txt","w");assert(o);salva_albero_su_file(o,a);fclose(o);
dealloca_albero(a);dealloca_casse(&c,dim);assert(!c);

return 0;
}
