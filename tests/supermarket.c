#define main exercise_main
#include "../exercises/eser5magg/supermercato.c"
#undef main
#include <assert.h>
int main(void) {

List l=NULL;T_Prodotto a={"A","Demo","Brand",1,2.0,3},b={"B","Other","Brand",2,4.0,1};
assert(InserisciInListaOrdinata(&l,b));assert(InserisciInListaOrdinata(&l,a));
assert(ModificaQuantita(l,"B",7)==1 && l->next->info.quantita==7 && l->info.quantita==3);
assert(ModificaQuantita(l,"A",5)==1 && l->info.quantita==5);
assert(ModificaQuantita(l,"Z",8)==0); assert(ModificaQuantita(l,"A",-1)==0);int dim;T_Prodotto *v=ArticoliReparto(l,1,&dim);assert(dim==1 && !strcmp(v[0].cod,"A"));free(v);
v=ArticoliReparto(l,9,&dim);assert(!v && dim==0);assert(ScriviSuFile(l,"Brand")==2);CancellaLista(&l);assert(!l);
FILE *f=fopen("products.txt","w");assert(f);fputs("C Test Demo 1 3.0 5\n",f);fclose(f);assert(CaricaProdotti("products.txt",&l)==1);CancellaLista(&l);

return 0;
}
