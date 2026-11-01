#define main exercise_main
#include "../exercises/eser17apr/task03.c"
#undef main
#include <assert.h>

int main(void){

Lista l=NULL;Libro a={0};strcpy(a.cod,"A");strcpy(a.autore,"Demo");a.quantita=3;
assert(InserisciInTesta(&l,a));strcpy(a.cod,"B");assert(InserisciInTesta(&l,a));
assert(CercaPerNome(l,"Demo")==6);assert(CancellaLibroPerCodice(&l,"A")==1);assert(CancellaLibroPerCodice(&l,"missing")==-1);assert(CancellaTuttiPerAutore(&l,"Demo")==1);assert(!l);

return 0;
}
