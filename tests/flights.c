#define main exercise_main
#include "../exercises/compiti anni precedenti/compito6/modulo2_testo.c"
#undef main
#include <assert.h>
int main(void) {

ListaVoli l=NULL; T_Volo v={0};strcpy(v.codice_volo,"F1");assert(aggiungi_volo(&l,v));
assert(nuova_prenotazione(l,"F1","Demo","Ada"));assert(!strcmp(l->info.prenotazioni->prenotazione.posto,"01A"));
assert(nuova_prenotazione(l,"F1","Demo","Bob"));assert(!strcmp(l->info.prenotazioni->next->prenotazione.posto,"01B"));
int dim;stato_volo *s=calcola_posti_disponibili(l,&dim);assert(dim==1 && s[0].posti_diponibili==38);free(s);
while(l){ListaVoli n=l;l=n->next;while(n->info.prenotazioni){ListaBiglietti b=n->info.prenotazioni;n->info.prenotazioni=b->next;free(b);}free(n);}

return 0;
}
