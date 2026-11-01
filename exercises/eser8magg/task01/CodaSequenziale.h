//
// Created by kozch on 07.06.2026.
//

#ifndef ESER8MAGG_CODASEQUENZIALE_H
#define ESER8MAGG_CODASEQUENZIALE_H

#define DIM_MAX 10
typedef int TipoElemCoda;
typedef struct Tipocoda {
    TipoElemCoda elementi[DIM_MAX];
    int primo, ultimo;
}TipoCoda;

void InitCoda(TipoCoda *);
int CodaVuota(TipoCoda);
int CodaPiena(TipoCoda);
void InizioCoda(TipoCoda, TipoElemCoda*);
int InCoda(TipoCoda*, TipoElemCoda);
int OutCoda(TipoCoda*, TipoElemCoda*);

#endif //ESER8MAGG_CODASEQUENZIALE_H