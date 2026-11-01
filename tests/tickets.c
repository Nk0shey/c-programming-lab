#define main exercise_main
#include "../exercises/es3/simulazione_m2_ticket.c"
#undef main
#include <assert.h>
int main(void) {

centro_t c;centro_init(c);ticket_t a={"T1","Ada","Reti","Router",1,2},b={"T2","Bob","Reti","Router",4,1};
assert(centro_put(c,a)==OK && centro_put(c,b)==OK);assert(!strcmp(cerca_reparto(c,"Reti")->info.codice,"T1"));
int dim;lista_t l=estrai_urgenti(c,2,&dim);assert(dim==1 && !strcmp(l->info.codice,"T1"));dealloca_estratti(&l);assert(!l);dealloca_centro(c);

return 0;
}
