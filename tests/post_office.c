#define main exercise_main
#include "../exercises/chat1/esercizio2-testo.c"
#undef main
#include <assert.h>
int main(void) {

Coda c={0}; TListaOperazione l=NULL; TCliente a={"Ada","Demo"},b={"Bob","Demo"},out;
assert(!eliminaCoda(&c,&out)); assert(AggiungiCliente(&c,a)); assert(AggiungiCliente(&c,b));
assert(Operazione(&c,"pacco",&l)); assert(!strcmp(l->info.nome,"Ada"));
assert(eliminaCoda(&c,&out) && !strcmp(out.nome,"Bob")); assert(!c.primo && !c.ultimo);
int *v=ContaNumeroDiOperazioni(l); assert(v && v[0]==0 && v[1]==1 && v[2]==0); free(v);
DisallocaLista(&l); assert(!l); DisallocaCoda(&c);

return 0;
}
