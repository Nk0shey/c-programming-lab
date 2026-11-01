#define main exercise_main
#include "../exercises/compiti anni precedenti/compito 8/main.c"
#undef main
#include <assert.h>

int main(void){

TPaziente a={0},b={0};strcpy(a.nome,"Ada");strcpy(a.cognome,"Demo");strcpy(a.reparto,"Test");a.stato=RICOVERATO;b=a;strcpy(b.nome,"Bob");
Albero t=NULL;inserisci_nodo_albero(&t,a,1);inserisci_nodo_albero(&t,b,1);assert(t->stanza==1 && t->dx->stanza==2);ListaPazientiReparto l=NULL;pazienti_reparto(t,&l,"Test");assert(l && l->next && !l->next->next);
while(l){NodoCodaPazienti *n=l;l=n->next;free(n);}libera_stanze(&t);assert(!t);

return 0;
}
