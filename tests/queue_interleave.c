#define main exercise_main
#include "../exercises/eser8magg/task02-03/task03.c"
#undef main
#include "../exercises/eser8magg/task02-03/CodaCoollegata.c"
#include <assert.h>
#include <string.h>
int main(void) {
    FILE *f = fopen("queue_input.txt","w"); assert(f);
    fputs("1\n3\n-1\n2\n4\n6\n-1\n",f); fclose(f);
    assert(freopen("queue_input.txt","r",stdin));
    assert(freopen("queue_output.txt","w",stdout));
    assert(exercise_main()==0); fflush(stdout);
    f = fopen("queue_output.txt","r"); assert(f);
    char result[1024]; size_t n=fread(result,1,sizeof result-1,f); result[n]='\0';fclose(f);
    assert(strstr(result,"coda_3: 12346"));
    return 0;
}
