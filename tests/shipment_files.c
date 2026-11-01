#define main exercise_main
#include "../exercises/eser8apr/spedizioni.c"
#undef main
#include <assert.h>
int main(void) {

int n=99; assert(!carica_consegne("missing.txt", &n) && n==0);
FILE *f=fopen("ship.txt","w"); assert(f); fputs("2\nCatania Roma A01 100 25\nRoma Napoli B02 100 100\n",f); fclose(f);
T_consegna *v=carica_consegne("ship.txt", &n); assert(v && n==2);
calcola_percentuale(v,n); assert(v[0].percentuale_percorsa==25 && v[1].percentuale_percorsa==100);
assert(consegne_da_fare("out.txt",v,n)==1);
#ifdef __linux__
assert(consegne_da_fare("/dev/full",v,n)==-1);
#endif
 free(v);
f=fopen("out.txt","r"); assert(f); char line[128]; assert(fgets(line,sizeof line,f)); assert(!strcmp(line,"Catania Roma A01 75\n")); assert(fgetc(f)==EOF); fclose(f);
const char *bad[]={"2\nA B C 10 2\n", "1\nA B C 0 0\n", "1\nA B C 10 11\n", "1\nA B C 10 2 extra\n", "1\nA B C 10 2\nextra\n", "-1\n", "2garbage\n", "1\nA B TOOLONGCODE 10 2\n"};
for (unsigned i=0;i<sizeof bad/sizeof *bad;i++) { f=fopen("bad.txt","w"); assert(f); fputs(bad[i],f); fclose(f); n=99; assert(!carica_consegne("bad.txt",&n) && n==0); }

return 0;
}
