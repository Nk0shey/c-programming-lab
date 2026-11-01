#define main exercise_main
#include "../exercises/eser17apr/task02.c"
#undef main
#include <assert.h>
int main(void) { List l=NULL; CancellaLista(&l); assert(cons(&l,1)); assert(cons(&l,2)); CancellaLista(&l); assert(!l); return 0; }
