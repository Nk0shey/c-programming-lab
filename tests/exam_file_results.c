#define main exercise_main
#include "../exercises/eser27march/task06.c"
#undef main
#include <assert.h>
int main(void) {

T_Studente v[4]={{"S1","C",20,22,0,0.70f,NON_SUPERATO,0}, {"S2","C",30,30,0,0.80f,NON_SUPERATO,0}, {"S3","C",17,25,0,0.90f,NON_SUPERATO,0}, {"S4","C",18,18,0,0.60f,NON_SUPERATO,0}};
calcola_esiti(v,4); assert(v[0].voto_finale==23 && v[0].voto1==20); assert(v[1].voto_finale==31); assert(v[2].esito==NON_SUPERATO && v[3].esito==NON_SUPERATO);
calcola_esiti(v,4); assert(v[0].voto_finale==23 && v[0].voto1==20);
T_Studente best; assert(trova_esito_massimo(v,4,"C",&best) && !strcmp(best.matricola,"S2")); assert(!trova_esito_massimo(v,4,"X",&best));
float mean; assert(calcola_media_presenze_promossi(v,4,&mean) && fabsf(mean-0.75f)<1e-6f); assert(!calcola_media_presenze_promossi(v,0,&mean));
assert(salva_insufficienti("failed.txt",v,4)==2);
#ifdef __linux__
assert(salva_insufficienti("/dev/full",v,4)==-1);
#endif
 assert(salva_matricole_media_superiore("ids.txt",v,4,20)==3);
FILE *f=fopen("ids.txt","r"); assert(f); char ids[100]={0}; assert(fread(ids,1,sizeof ids-1,f)>0); fclose(f); assert(!strcmp(ids,"S1\nS2\nS3\n"));
f=fopen("in.txt","w"); assert(f); fputs("S1 C 20 22 0.70\nS2 C 30 30 0.80\n",f); fclose(f); assert(carica_esiti("in.txt",v,1)==-1); assert(carica_esiti("in.txt",v,4)==2);
f=fopen("bad.txt","w"); assert(f); fputs("S1 C 31 22 0.70\n",f); fclose(f); assert(carica_esiti("bad.txt",v,4)==-1);

return 0;
}
