#define main exercise_main
#include "../exercises/esercitazione_01_04/somma_ricorsiva.c"
#undef main
#include <assert.h>
int main(void) {
assert(somma_n_interi(0)==0); assert(somma_n_interi(1)==1); assert(somma_n_interi(10)==55); assert(somma_n_interi(1000)==500500);
return 0;
}
