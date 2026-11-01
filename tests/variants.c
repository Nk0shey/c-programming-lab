#define main exercise_main
#include "../exercises/sim24aug/simulazione_finale_adt_tutte_varianti.c"
#undef main
#include <assert.h>
int main(void) {

V4_CodaOrdini q={0}; V4_Collo a={"C1",2},b={"C2",3},out;
assert(!v4_pop_collo_primo_ordine(&q,&out)); assert(v4_enqueue_ordine(&q,"O1","Roma"));
assert(v4_push_collo(q,"O1",a)); assert(v4_push_collo(q,"O1",b)); assert(!v4_completa_primo_ordine(&q));
assert(v4_pop_collo_primo_ordine(&q,&out) && !strcmp(out.id,"C2"));
assert(v4_pop_collo_primo_ordine(&q,&out) && !strcmp(out.id,"C1")); assert(v4_completa_primo_ordine(&q)); assert(!q.primo && !q.ultimo);
assert(v4_enqueue_ordine(&q,"O2","Roma")); assert(v4_push_collo(q,"O2",a)); v4_dealloca_tutto(&q);
V5_PilaSnapshot p=NULL; V5_Modifica m={1,"A"},n={2,"B"};
assert(!v5_pop_snapshot(&p)); assert(v5_push_snapshot(&p,1)); assert(v5_aggiungi_modifica_in_fondo(p,m)); assert(v5_aggiungi_modifica_in_fondo(p,n));
assert(p->info.modifiche->info.id==1 && p->info.modifiche->next->info.id==2);
assert(v5_rimuovi_modifica(p,1)); assert(!v5_rimuovi_modifica(p,9)); v5_dealloca_tutto(&p); assert(!p);
V6_PilaTurni t=NULL; V6_Intervento i={"I1",1,"Demo"},j;
assert(v6_push_turno(&t,1,"Ada")); assert(v6_enqueue_intervento(t,i)); assert(!v6_chiudi_turno(&t));
assert(v6_dequeue_intervento(t,&j) && !strcmp(j.id,"I1")); assert(!t->info.interventi.ultimo); assert(v6_chiudi_turno(&t));
assert(v6_push_turno(&t,2,"Bob")); assert(v6_enqueue_intervento(t,i)); v6_dealloca_tutto(&t); assert(!t);
B_Coda c={0}; for (int k=1;k<=3;++k) { B_Nodo *n=malloc(sizeof *n); assert(n); n->info.valore=k; n->next=NULL; if(c.ultimo)c.ultimo->next=n;else c.primo=n;c.ultimo=n; }
assert(bonus_inverti_coda_con_pila(&c)); int k=3; while(c.primo){B_Nodo *n=c.primo;assert(n->info.valore==k--);c.primo=n->next;free(n);} assert(k==0);

return 0;
}
