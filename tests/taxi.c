#define main exercise_main
#include "../exercises/eser12magg/taxi.c"
#undef main
#include <assert.h>
int main(void) {

ListaTaxi busy=NULL;CodaTaxi q={0};ListaCorse rides=NULL;T_Taxi t={"AA000AA","T1",100,0,DISPONIBILE};
assert(InCoda(&q,t)==1);T_Corsa r={"",2,10};assert(inserisci_nuova_corsa(&busy,&q,&rides,r));assert(busy && !q.primo && !q.ultimo);
assert(termina_corsa(&busy,&q,rides,"T1"));assert(!busy && q.primo->info.km_totali==120 && q.primo->info.passeggeri==2);
assert(!termina_corsa(&busy,&q,rides,"T1"));int dim;T_InfoTaxi *v=calcola_corse_per_taxi(busy,q,rides,&dim);assert(dim==1 && v[0].counter_corse==1);free(v);
CancellaTuttiCoda(&q);while(rides){NodoCorsa *n=rides;rides=n->next;free(n);}assert(!q.primo && !q.ultimo);

return 0;
}
