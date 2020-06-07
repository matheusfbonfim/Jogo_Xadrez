#ifndef TORRE_H
#define TORRE_H
#include "peca.h"
#include "tabuleiro.h"

class Torre:public Peca
{
private:

public:
    Torre();
    void movimentoCor(int i, int j);
    bool movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna);
};

#endif // TORRE_H
