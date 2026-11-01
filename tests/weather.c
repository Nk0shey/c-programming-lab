#define main exercise_main
#include "../exercises/compiti anni precedenti/compito4/main.c"
#undef main
#include <assert.h>

int main(void){

ListaStazioni l=NULL;Albero t=crea_albero(&l,TEMPERATURA);assert(!t);dealloca_albero(&t);dealloca_lista(&l);
Rilevazione r={0};strcpy(r.timestamp,"2026-01-01_12:00");r.tipo=TEMPERATURA;r.valore=20;
t=inserisci_nodo(t,r);assert(t);dealloca_albero(&t);assert(!t);

return 0;
}
