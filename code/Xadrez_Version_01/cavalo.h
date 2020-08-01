#ifndef CAVALO_H
#define CAVALO_H
#include "peca.h"

class Cavalo:public Peca
{
public:
    Cavalo();
    void movimentoCor(int i, int j);
    bool movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna);
};

#endif // CAVALO_H
