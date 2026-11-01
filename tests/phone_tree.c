#define main exercise_main
#include "../exercises/eser3giugno/agenda_telefonica.c"
#undef main
#include <assert.h>
int main(void) {
    ABR a=NULL;
    TipoInfoAlbero x={'B',NULL},y={'A',NULL},z={'C',NULL};
    inserisci_nodo_ABR(&a,x);inserisci_nodo_ABR(&a,y);inserisci_nodo_ABR(&a,z);
    assert(ricerca_nodo_per_lettera(a,'A'));assert(ricerca_nodo_per_lettera(a,'C'));
    assert(!ricerca_nodo_per_lettera(a,'Z'));CancellaAlbero(&a);assert(!a);CancellaAlbero(&a);
    return 0;
}
