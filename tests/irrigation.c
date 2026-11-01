#define main exercise_main
#include "../exercises/compiti anni precedenti/compito 5/testo.c"
#undef main
#include <assert.h>
static void write_data(const char *file, const char *data) {
    FILE *f = fopen(file,"w"); assert(f); assert(fputs(data,f)>=0); assert(fclose(f)==0);
}
int main(void) {
    write_data("areas.txt","B 80\nA 20\n");
    write_data("zones.txt","Z1 3.5 0.5 1 40 A\nZ2 4 1 1 20 B\nZ3 5 1 0 10 A\n");
    elenco_aree p=carica_impianto("areas.txt","zones.txt");
    assert(p && !strcmp(p->codice,"A") && p->next && !strcmp(p->next->codice,"B"));
    assert(conta_zone_accese(p)==2 && cerca_area(p,"A")->num_zone==2);
    int n; zona *v=crea_vettore_zone_accese(p,&n); assert(v && n==2 && !v[0].next);free(v);
    indice t=calcola_e_costruisci_indice(p);assert(t && tempo_accensione_zona(t,"Z1")==30);
    assert(tempo_accensione_zona(t,"Z2")==-1 && tempo_accensione_zona(t,"Z3")==-1);
    assert(!aggiorna_zona(p,"missing",ACCESO,0.5));assert(!aggiorna_zona(p,"Z1",ACCESO,2));
    assert(aggiorna_zona(p,"Z3",ACCESO,0.5));libera_indice(&t);t=calcola_e_costruisci_indice(p);
    assert(tempo_accensione_zona(t,"Z3")==45);
    assert(aggiorna_zona(p,"Z1",SPENTO,-1));assert(cerca_zona(p,"Z1")->fattore_correzione==0.5f);
    libera_indice(&t);libera_impianto(&p);assert(!p && !t);libera_impianto(&p);libera_indice(&t);
    write_data("zones.txt","Z1 2 0.5 1 20 MISSING\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("zones.txt","Z1 2 0.5 1 20 A\nZ1 3 0.4 1 30 B\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("zones.txt","Z1 2 nan 1 20 A\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("zones.txt","Z1 2 0.5 1 101 A\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("zones.txt","Z1 2 0.5 1 20 A extra\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("zones.txt","Z1 2 0.5 1 20 A\n");write_data("areas.txt","A 10\nA 20\n");assert(!carica_impianto("areas.txt","zones.txt"));
    write_data("areas.txt","A 20\n");
    write_data("console.txt","invalid\n1\n2\n4\n5\nZ1\n3\nZ1 0 -1\n4\n5\nZ1\n1\n0\n");
    assert(freopen("console.txt","r",stdin));char *args[]={"irrigation","areas.txt","zones.txt",NULL};
    assert(exercise_main(3,args)==0);
    return 0;
}
