#ifndef PECA_H
#define PECA_H

//Definição das peças
/*
Torre 1
Cavalo 2
Bispo 3
Dama 4
*/

class Peca
{
protected:
    int tipo;

public:
    Peca(int TP);
    virtual int getTipoPeca();
    virtual void movimentoCor(int i, int j)= 0; // Metodo virtual puro para peças // Pintar possivel movimento
    virtual bool movimento(int q1x,int q1y, int q2x,int q2y)=0;
};

#endif // PECA_H
