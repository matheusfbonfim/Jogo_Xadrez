#include "bispo.h"

Bispo::Bispo():Peca(3)
{

}

void Bispo::movimentoCor(int i, int j)
{
    // Variavel local para percorrer o tabuleiro
    QList<Quadrado*>::iterator it;

    // Colocando no iterator o inicio do tabuleiro
    it=Tabuleiro::getInstancia()->getInicioTabuleiro();

    for(;it!=Tabuleiro::getInstancia()->getFinalTabuleiro();it++)
    {
        // Pintamos o movimento conforme o possivel movimento
        if(movimento(i,j,(*it)->getLinha(),(*it)->getColuna()))
        {
            (*it)->setBalde(2);
        }
    }
}

// Movimento e restrição do Bispo
bool Bispo::movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna)
{
    //  Esquema de tabuleiro
    //  ________________________
    // 0|__|__|__|__|__|__|__|_U|
    // 1|_E|__|__|__|__|__|_U|__|
    // 2|__|_E|__|__|__|_U|__|__|
    // 3|__|__|_E|__|_U|__|__|__|
    // 4|__|__|__|B_|__|__|__|__|
    // 5|__|__|_V|__|_P|__|__|__|
    // 6|__|_V|__|__|__|_P|__|__|
    // 7| 0  1  2  3  4  5  6  7

    // Variavel local para percorrer o tabuleiro
    QList<Quadrado*>::iterator it;

    // Colocando no iterator o inicio do tabuleiro
    it=Tabuleiro::getInstancia()->getInicioTabuleiro();

    // Se estiver na diagonal principal ou secundaria
    if( ( (q2Linha-q2Coluna)==(q1Linha-q1Coluna) ) || ((q2Linha+q2Coluna)==(q1Linha+q1Coluna) ))
    {
        //Possiveis movimentos e restrições
        for(;it!=Tabuleiro::getInstancia()->getFinalTabuleiro();it++)
        {
            // Diagonal E
            if(q2Linha<q1Linha && q2Coluna<q1Coluna && (*it)->getPeca()!=NULL && (*it)->getLinha()>q2Linha && (*it)->getLinha()<q1Linha && ((*it)->getLinha()-(*it)->getColuna())==(q1Linha-q1Coluna))
            {
                return false;
            }

            // Diagonal U
            if(q2Linha<q1Linha && q2Coluna>q1Coluna && (*it)->getPeca()!=NULL && (*it)->getLinha()>q2Linha && (*it)->getLinha()<q1Linha && ((*it)->getLinha()+(*it)->getColuna())==(q1Linha+q1Coluna))
            {
                return false;
            }

            //Diagonal V
            if(q2Linha>q1Linha && q2Coluna<q1Coluna && (*it)->getPeca()!=NULL && (*it)->getLinha()<q2Linha && (*it)->getLinha()>q1Linha && ((*it)->getLinha()+(*it)->getColuna())==(q1Linha+q1Coluna))
            {
                  return false;
            }

            //Diagonal P
            if(q2Linha>q1Linha && q2Coluna>q1Coluna && (*it)->getPeca()!=NULL && (*it)->getLinha()<q2Linha && (*it)->getLinha()>q1Linha && ((*it)->getLinha()-(*it)->getColuna())==(q1Linha-q1Coluna))
            {
                return false;
            }
        }

        return true;
   }
    return false;
}

