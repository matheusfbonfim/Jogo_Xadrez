#ifndef BISPO_H
#define BISPO_H
#include "peca.h"
#include "tabuleiro.h"

class Bispo:public Peca
{
public:
    Bispo();
    void movimentoCor(int i, int j);
    bool movimento(int q1Linha,int q1Coluna,int q2Linha, int q2Coluna);
};

#endif // BISPO_H
