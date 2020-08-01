#include "dama.h"

Dama::Dama():Peca(4)
{

}

void Dama::movimentoCor(int i, int j)
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

bool Dama::movimento(int q1Linha, int q1Coluna,int q2Linha, int q2Coluna)
{
    // Variavel local para percorrer o tabuleiro
    QList<Quadrado*>::iterator it;

    // Colocando no iterator o inicio do tabuleiro
    it=Tabuleiro::getInstancia()->getInicioTabuleiro();

    //Junção do movimento do bispo e torre
    if(  (( (q2Linha-q2Coluna)==(q1Linha-q1Coluna) ) || ((q2Linha+q2Coluna)==(q1Linha+q1Coluna) )) || (q1Linha == q2Linha || q1Coluna == q2Coluna )   )
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
