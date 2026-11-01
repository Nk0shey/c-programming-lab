#define main exercise_main
#include "../exercises/sim1706.2/main.c"
#undef main
#include <assert.h>
int main(void) {
    nodo_categoria_t c={0}; strcpy(c.info.codice_categoria,"C1");
    nodo_evento_ticket_t a={0},b={0},open={0};
    strcpy(a.info.id_ticket,"T1");strcpy(a.info.orario,"08:00");a.info.stato=APERTO;
    b.info=a.info;strcpy(b.info.orario,"09:00");b.info.stato=CHIUSO;
    open.info=a.info;strcpy(open.info.id_ticket,"T2");a.next=&b;b.next=&open;c.info.eventi.primo=&a;c.info.eventi.ultimo=&open;
    int n=99;statistica_ticket_t *v=calcola_tempi_risoluzione(&c,&n);
    assert(v && n==1 && v[0].minuti_risoluzione==60);free(v);
    assert(!calcola_tempi_risoluzione(NULL,&n) && n==0);
    return 0;
}
