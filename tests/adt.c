#define main exercise_main
#include "../exercises/chat1/simulazione_adt_vettori_liste_pile_code.c"
#undef main
#include <assert.h>
int main(void) {

Lista ordered=NULL; Elemento first={5,"X",1}; assert(inserisci_ordinato_lista(&ordered,first)); assert(!inserisci_ordinato_lista(&ordered,first)); dealloca_lista(&ordered);
Lista l=NULL; Pila p=NULL; Coda c={0}; VettoreElementi v; inizializza_vettore(&v);
Elemento a={1,"A",3},b={2,"B",5},out;
assert(!dequeue(&c,&out)); assert(enqueue(&c,a)); assert(enqueue(&c,b));
assert(front(c,&out) && out.id==1); assert(sposta_coda_in_vettore(&c,&v,1)==1);
assert(v.n==1 && v.dati[0].id==1); assert(dequeue(&c,&out) && out.id==2); assert(!c.ultimo);
assert(inserisci_testa_lista(&l,a)); assert(inserisci_testa_lista(&l,b));
assert(trasferisci_prioritari_lista_pila(&l,&p,4)==1); assert(l && l->info.id==1 && !l->next);
svuota_pila_in_coda(&p,&c); assert(!p && c.primo->info.id==2);
assert(estrai_massimo_vettore(&v,&out) && out.id==1); assert(!estrai_massimo_vettore(&v,&out));
dealloca_lista(&l); dealloca_pila(&p); dealloca_coda(&c); assert(!l && !c.primo && !c.ultimo);

return 0;
}
