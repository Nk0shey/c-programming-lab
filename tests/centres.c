#define main exercise_main
#include "../exercises/chat1/simulazione_centri_assistenza.c"
#undef main
#include <assert.h>
int main(void) {

ListaCentri l=NULL; PilaConsegne p=NULL;
assert(inserisci_centro_ordinato(&l,"B")); assert(inserisci_centro_ordinato(&l,"A")); assert(!inserisci_centro_ordinato(&l,"A"));
assert(!strcmp(l->info.codice,"A")); Pacco a={1,"Roma",2.5,3},b={2,"Roma",4,1};
assert(enqueue_pacco(&l->info.pacchi,a)); assert(enqueue_pacco(&l->info.pacchi,b));
assert(conta_pacchi_destinazione(l,"Roma")==2); assert(centro_piu_carico(l)==l);
assert(!rimuovi_centro_vuoto(&l,"A")); assert(consegna_pacco(l,"A","Demo",&p));
assert(p->info.pacco.id_pacco==1 && cerca_consegna(p,1)==p);
StatisticaCentro v[2]; assert(crea_statistiche(l,v,2)==2); ordina_statistiche(v,2); assert(v[0].peso_totale==4);
assert(consegna_pacco(l,"A","Demo",&p)); assert(!l->info.pacchi.ultimo); assert(rimuovi_centro_vuoto(&l,"A"));
dealloca_tutto(&l,&p); assert(!l && !p);
FILE *f=fopen("centres.txt","w"); assert(f); fputs("CT01\n",f); fclose(f);
f=fopen("parcels.txt","w"); assert(f); fputs("CT01 7 Roma 2.5 1\n",f); fclose(f);
assert(carica_dati(&l,"centres.txt","parcels.txt")); assert(l->info.pacchi.primo->info.id_pacco==7); dealloca_tutto(&l,&p);

return 0;
}
