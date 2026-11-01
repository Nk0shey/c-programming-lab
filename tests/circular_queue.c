#define main exercise_main
#include "../exercises/eser8magg/task01/CodaSequenziale.c"
#undef main
#include <assert.h>
int main(void) {

TipoCoda q;InitCoda(&q);int out;assert(OutCoda(&q,&out)==-1);
for(int i=0;i<DIM_MAX;++i)assert(InCoda(&q,i)==1);assert(CodaPiena(q));assert(InCoda(&q,99)==-1);
for(int i=0;i<5;++i){assert(OutCoda(&q,&out)==1);assert(out==i);}for(int i=DIM_MAX;i<DIM_MAX+5;++i)assert(InCoda(&q,i)==1);
for(int i=5;i<DIM_MAX+5;++i){assert(OutCoda(&q,&out)==1);assert(out==i);}assert(CodaVuota(q));

return 0;
}
