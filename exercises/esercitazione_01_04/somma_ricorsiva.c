#include <stdio.h>

int somma_n_interi(int x);   // прототип функции

int main(void) {
    int n=0, somma = -1;

    do {
        printf("Enter a positive number: ");
        if (scanf("%d", &n) != 1) return 1;
    } while (n < 0);
    if (n > 1000) { fputs("Maximum supported input: 1000\n", stderr); return 1; }
    somma = somma_n_interi(n);
    printf("The somma number is: %d\n", somma);
    return 0;

}

int somma_n_interi(int x) {
    if (x == 0) return 0;
    return x + somma_n_interi(x - 1);
}

