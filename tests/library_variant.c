#define main exercise_main
#include "../exercises/eser5giugno/testo.c"
#undef main
#include <assert.h>
int main(void) {

TListaLibri d=NULL,p=NULL; TAlberoLibri t=NULL; TLibro a={"B2","Title","giallo",2},b={"B1","Book","giallo",4};
assert(AggiungiLibro(&d,a)); assert(AggiungiLibro(&d,b)); assert(Prestito("B2",&d,&p)); assert(!Prestito("B2",&d,&p));
int dim; TLibro *v=EstraiLibriDiInteresse(d,5,"giallo",&dim); assert(dim==1 && !strcmp(v[0].codice,"B1"));free(v);
CreaAlberoBR(&t,d,p); assert(CercaNodoLibroPerCodice(t,a)); assert(CercaNodoLibroPerCodice(t,b));
DeallocaLista(&d); DeallocaLista(&p); DeallocaAlbero(&t); assert(!d && !p && !t);
FILE *f=fopen("books.txt","w");assert(f);fputs("B3 giallo Demo 2.50 disponibile\nB4 romanzo Test 3.00 prestato\n",f);fclose(f);
assert(CaricaLibri("books.txt",&d,&p));assert(d && p && !strcmp(d->info.titolo,"Demo"));DeallocaLista(&d);DeallocaLista(&p);

return 0;
}
