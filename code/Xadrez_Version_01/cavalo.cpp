#include "cavalo.h"
#include "peca.h"
#include "tabuleiro.h"

Cavalo::Cavalo():Peca(2)
{

}

// Movimento do cavalo, recebendo o tabuleiro
void Cavalo::movimentoCor(int i, int j)
{
    // Variavel local para percorrer o tabuleiro
    QList<Quadrado*>::iterator it;

    // Colocando no iterator o inicio do tabuleiro
    it=Tabuleiro::getInstancia()->getInicioTabuleiro();

    for(;it!=Tabuleiro::getInstancia()->getFinalTabuleiro();it++)
    {
        if(movimento(i,j,(*it)->getLinha(),(*it)->getColuna()))
        {
            (*it)->setBalde(2);
        }
    }
}

bool Cavalo::movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna)
{
    //  Esquema de tabuleiro
    //  ________________________
    // 0|__|__|__|__|__|__|__|__|
    // 1|__|__|__|__|__|__|__|__|
    // 2|__|__|_A|__|_B|__|__|__|
    // 3|__|_E|__|__|__|_D|__|__|
    // 4|__|__|__|C_|__|__|__|__|
    // 5|__|_H|__|__|__|_I|__|__|
    // 6|__|__|_G|__|_F|__|__|__|
    // 7| 0  1  2  3  4  5  6  7


    //Verifica se esta na posição A
    if( q1Linha==(q2Linha+2) && q1Coluna==(q2Coluna+1) )
    {
        return true;
    }

    //Verifica se esta na posição B
    if( q1Linha==(q2Linha+2) && q1Coluna==(q2Coluna-1) )
    {
        return true;
    }

    //Verifica se esta na posição D
    if( q1Linha==(q2Linha+1) && q1Coluna==(q2Coluna-2) )
    {
        return true;
    }

    //Verifica se esta na posição E
    if( q1Linha==(q2Linha+1) && q1Coluna==(q2Coluna+2) )
    {
        return true;
    }

    //Verifica se esta na posição H
    if( q1Linha==(q2Linha-1) && q1Coluna==(q2Coluna+2) )
    {
        return true;
    }

    //Verifica se esta na posição G
    if( q1Linha==(q2Linha-2) && q1Coluna==(q2Coluna+1) )
    {
        return true;
    }

    //Verifica se esta na posição F
    if( q1Linha==(q2Linha-2) && q1Coluna==(q2Coluna-1) )
    {
        return true;
    }

    //Verifica se esta na posição I
    if( q1Linha==(q2Linha-1) && q1Coluna==(q2Coluna-2) )
    {
        return true;
    }

    return false;
}
