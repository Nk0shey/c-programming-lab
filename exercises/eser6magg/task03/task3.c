//
// Created by kozch on 04.06.2026.
//

#include <stdio.h>
#include "PilaCollegata.h"

#define MAX_LEN 51

int isParentesiAperta(char c) {
    if (c == '{' || c == '[' || c == '(')
        return 1;
    else
        return 0;
}

int isParentesiChiusa(char c) {
    if (c == '}' || c == ']' || c == ')')
        return 1;
    else
        return 0;
}

int Corrisponde(char aperta, char chiusa) {
    switch (aperta) {
        case '{':
            if (chiusa == '}')
                return 1;
            break;
        case '[':
            if (chiusa == ']')
                return 1;
            break;
        case '(':
            if (chiusa == ')')
                return 1;
            break;
    }
    return 0;
}

int VerificaCorrettezza(char *s) {
Pila p; InitPila(&p);
    int ok = 1;
    for (int i = 0; s[i] && ok; ++i) {
        if (isParentesiAperta(s[i])) ok = Push(&p, s[i]) == 1;
        else if (isParentesiChiusa(s[i])) {
            TipoElemPila c;
            ok = Pop(&p, &c) == 1 && Corrisponde(c, s[i]);
        }
    }
    ok = ok && PilaVuota(p);
    TipoElemPila c;
    while (Pop(&p, &c) == 1) { }
    return ok;
}

int main(void) {
char s[MAX_LEN];
    printf("Inserisci espressione: ");
    if (!fgets(s, sizeof s, stdin)) return 1;
    printf("%s\n", VerificaCorrettezza(s) ? "Corretta" : "NON corretta");
    return 0;
}