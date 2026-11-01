#define main exercise_main
#include "../exercises/eser6magg/task03/task3.c"
#undef main
#include <assert.h>
#include "../exercises/eser6magg/task03/PilaCollegata.c"
int main(void){

assert(VerificaCorrettezza("([]{})"));assert(!VerificaCorrettezza(")"));assert(!VerificaCorrettezza("([)]"));assert(!VerificaCorrettezza("(("));assert(VerificaCorrettezza(""));
Pila p=NULL;assert(TerminaPila(&p));assert(Push(&p,'(')==1);assert(TerminaPila(&p) && !p);

return 0;
}
