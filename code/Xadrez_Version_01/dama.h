#ifndef DAMA_H
#define DAMA_H
#include "peca.h"
#include "tabuleiro.h"

class Dama:public Peca
{
public:
    Dama();
    void movimentoCor(int i, int j);
    bool movimento(int q1Linha,int q1Coluna,int q2Linha, int q2Coluna);
};

#endif // DAMA_H
