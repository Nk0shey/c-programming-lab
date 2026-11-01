#define main exercise_main
#include "../exercises/es1/main.c"
#undef main
#include <assert.h>

int main(void){

ListaRider l=NULL;NodoRider r={0};NodoOrdine a={0},b={0};
strcpy(a.info.codice_cliente,"C1");a.info.importo=5;strcpy(b.info.codice_cliente,"C1");b.info.importo=7;a.next=&b;r.info.ordini.primo=&a;r.info.ordini.ultimo=&b;l=&r;
Albero t=crea_albero_clienti(&l);cliente_t *c=cerca_cliente_ABR(t,"C1");assert(c && c->numero_ordini==2 && c->importo_totale==12);assert(!cerca_cliente_ABR(t,"absent"));
FILE *f=fopen("clients.txt","w");assert(f);salva_albero_file(t,f);fclose(f);dealloca_ABR(&t);assert(!t);

return 0;
}
