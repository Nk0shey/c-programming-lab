//
// Created by kozch on 07.06.2026.
//

#ifndef ESER8MAGG_CODACOOLLEGATA_H
#define ESER8MAGG_CODACOOLLEGATA_H

typedef int TipoElemCoda;
typedef struct NodoCoda {
    TipoElemCoda info;
    struct NodoCoda *next;
}TipoNodoCoda;

typedef struct {
    TipoNodoCoda *primo;
    TipoNodoCoda *ultimo;
}TipoCoda;

void InitCoda(TipoCoda *);
int CodaVuota(TipoCoda);
int InizioCoda(TipoCoda*, TipoElemCoda*);
int InCoda(TipoCoda*, TipoElemCoda);
int OutCoda(TipoCoda*, TipoElemCoda*);


#endif //ESER8MAGG_CODACOOLLEGATA_H