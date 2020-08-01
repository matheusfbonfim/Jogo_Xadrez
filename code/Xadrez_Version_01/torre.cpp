#include "torre.h"

Torre::Torre():Peca(1)
{

}

//Pintar de verde possivel movimento
void Torre::movimentoCor(int i,int j)
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

//Metodo que verifica se o movimento é válido
bool Torre::movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna)
{
    // Variavel local para percorrer o tabuleiro
    QList<Quadrado*>::iterator it;

    //Se estiver na mesma linha ou mesma coluna
    if(q1Linha == q2Linha || q1Coluna == q2Coluna )
    {
        // Colocando no iterator o inicio do tabuleiro
        it=Tabuleiro::getInstancia()->getInicioTabuleiro();

        //Possiveis movimentos e restrições
        for(;it!=Tabuleiro::getInstancia()->getFinalTabuleiro();it++)
        {
            // Acima da torre
            if(q2Linha<q1Linha && (*it)->getPeca()!=NULL && (*it)->getLinha()>q2Linha && (*it)->getLinha()<q1Linha && (*it)->getColuna()==q1Coluna)
            {
                return false;
            }

            //Abaixo da torre
            if(q2Linha>q1Linha && (*it)->getPeca()!=NULL && (*it)->getLinha()<q2Linha && (*it)->getLinha()>q1Linha && (*it)->getColuna()==q1Coluna)
            {
                return false;
            }

            //Lado esquerdo
            if(q2Coluna<q1Coluna && (*it)->getPeca()!=NULL && (*it)->getColuna()>q2Coluna && (*it)->getColuna()<q1Coluna && (*it)->getLinha()==q1Linha)
            {
                return false;
            }

            //Lado direito
            if(q2Coluna>q1Coluna && (*it)->getPeca()!=NULL && (*it)->getColuna()<q2Coluna && (*it)->getColuna()>q1Coluna && (*it)->getLinha()==q1Linha)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

