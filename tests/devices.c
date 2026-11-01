#define main exercise_main
#include "../exercises/chat1/fdp_2026_07_13_M2new_turno1_test.c"
#undef main
#include <assert.h>
int main(void) {

assert(differenza_minuti("23:30","00:30")==60); assert(differenza_minuti("25:00","00:00")==-1);
lista_dispositivi_t l=NULL; dispositivo_t d={0};strcpy(d.id_dispositivo,"D1");strcpy(d.nome,"Demo");d.potenza_kw=2;
assert(aggiungi_dispositivo_testa(&l,d)==OK);
evento_t a={"E1","23:30",ACCESO},b={"E2","00:30",SPENTO};
assert(accoda_evento(&l->info.eventi,a)==OK);assert(accoda_evento(&l->info.eventi,b)==OK);
assert(cerca_evento_spegnimento(l->info.eventi.primo->next));assert(!cerca_evento_spegnimento(NULL));
int dim;statistica_t *v=calcola_consumo_periodi(l,&dim);assert(dim==1 && v[0].minuti==60 && v[0].consumo==2.0);
assert(salva_statistiche_filtrate("stats.txt",v,dim,1,30)==1);assert(salva_statistiche_filtrate("empty.txt",v,dim,3,30)==0);
free(v);dealloca_dispositivi(&l);assert(!l);
FILE *f=fopen("devices.txt","w");assert(f);fputs("D1 Demo 2\n",f);fclose(f);
f=fopen("events.txt","w");assert(f);fputs("D1 E1 08:00 ACCESO\nD1 E2 09:00 SPENTO\n",f);fclose(f);
assert(carica_dati("devices.txt","events.txt",&l)==OK);v=calcola_consumo_periodi(l,&dim);assert(dim==1 && v[0].consumo==2);free(v);dealloca_dispositivi(&l);

return 0;
}
