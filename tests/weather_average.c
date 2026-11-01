#define main exercise_main
#include "../exercises/eser27march/task03.c"
#undef main
#include <assert.h>
int main(void) {

Rilevazione v[]={{"A",10,20},{"B",20,30},{"C",30,40}};
float max,mean; analizza_dati(v,3,&max,&mean); assert(max==30 && mean==20);
analizza_dati(v,1,&max,&mean); assert(max==10 && mean==10);
v[0].temperatura=-10; v[1].temperatura=-20;
analizza_dati(v,2,&max,&mean); assert(max==-10 && mean==-15);
analizza_dati(v,0,&max,&mean); assert(max==0 && mean==0);

return 0;
}
