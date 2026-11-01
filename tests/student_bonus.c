#define main exercise_main
#include "../exercises/eser27march/task02.c"
#undef main
#include <assert.h>
int main(void) {

Studente s={"Demo",1,28}; bonus_media(&s); assert(s.media==28);
s.media=28.5f; bonus_media(&s); assert(s.media==29);
s.media=29.9f; bonus_media(&s); assert(s.media==30);

return 0;
}
