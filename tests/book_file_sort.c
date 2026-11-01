#include <string.h>
#define main exercise_main
#include "../exercises/eser27march/task04.c"
#undef main
#include <assert.h>
int main(void) {

Libro v[]={{"Later",2020,2},{"First",1990,1},{"Equal",2020,3}};
ordina_libri(v,3); assert(v[0].anno==1990 && !strcmp(v[1].titolo,"Later") && !strcmp(v[2].titolo,"Equal"));
ordina_libri(v,0); ordina_libri(v,1);

return 0;
}
