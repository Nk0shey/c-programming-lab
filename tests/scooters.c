#define main exercise_main
#include "../exercises/chat1/testo.c"
#undef main
#include <assert.h>
int main(void) {

TListaMonopattini a=NULL,b=NULL; TMonopattino m={"S2",40},n={"S1",10};
assert(InserisciInListaOrdinata(&a,m)); assert(InserisciInListaOrdinata(&a,n));
assert(!strcmp(a->info.codice,"S1")); assert(!Noleggia("missing",&a,&b));
assert(Noleggia("S2",&a,&b)); assert(b && !b->next && !strcmp(b->info.codice,"S2"));
int dim; TMonopattino *v=EstraiConAutonomia(a,5,&dim); assert(dim==1 && v[0].autonomia==10); free(v);
v=EstraiConAutonomia(a,100,&dim); assert(!v && dim==0);
DisallocaLista(a); DisallocaLista(b);

return 0;
}
