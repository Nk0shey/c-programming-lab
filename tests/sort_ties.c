#define main exercise_main
#include "../exercises/sim3/main.c"
#undef main
#include <assert.h>
int main(void) {
    Richiesta v[]={{"R1","A",1,10},{"R2","B",5,10},{"R3","C",3,20}};
    ordina_per_tempo(v,3);
    assert(!strcmp(v[0].id,"R3")); assert(!strcmp(v[1].id,"R2"));
    ordina_per_tempo(NULL,5); return 0;
}
