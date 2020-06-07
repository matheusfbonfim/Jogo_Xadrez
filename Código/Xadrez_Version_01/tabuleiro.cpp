#include "tabuleiro.h"
#include<QDebug>

Tabuleiro *Tabuleiro::instancia = nullptr;

Tabuleiro::Tabuleiro()
{
    x = 50; // Coordenadas iniciais fixa
    y = 50;
    x_aux = x;
    y_aux = y;

    int i=0,j=0; // Variaveis para percorrer/criar o tabuleiro

    // Inserção dos parametros do tabuleiro
    for(i = 0 ; i < 8; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            /*Criando e inserindo um quadrado na lista*/
            quadrados.push_back(new Quadrado(x_aux,y_aux));

            /*Setando a cor do quadrado*/
            quadrados.back()->setBalde((i%2)==(j%2));

            /*Coordenadas p/ colocar 8 quadrados por linha*/
            x_aux += x;
            if((j+1) % 8 == 0 && j!=0)
            {
                x_aux = x;
                y_aux += y;
            }

            /*Insercao dos indices nos quadrados*/
            quadrados.back()->setLinha(i);
            quadrados.back()->setColuna(j);
        }
    }
}

//Metodo estatico para acesso do singleton
Tabuleiro *Tabuleiro::getInstancia()
{
    if(instancia==NULL)
       instancia= new Tabuleiro();
    return instancia;
}

// Retorna o inicio da lista para percorrer
QList<Quadrado*>::iterator Tabuleiro::getInicioTabuleiro()
{
    return (quadrados.begin());
}

// Retorna o final da lista para percorrer
QList<Quadrado*>::iterator Tabuleiro::getFinalTabuleiro()
{
    return (quadrados.end());
}

//Adiciona Peça no tabuleiro
void Tabuleiro::criaPeca(int linha_,int colu_, int tipo)
{
    // Percorrendo a lista de quadrados criada
    for( it=quadrados.begin() ; it!= quadrados.end() ; it++)
    {
        //Identificando a linha e coluna
        if((*it)->getLinha() == linha_ && (*it)->getColuna() == colu_ )
        {
            if((*it)->getPeca() != NULL)
            {
               throw ERRO;
            }
            else
            {
                // Conforme o tipo, será setado no quadrado o tipo da Peça
                if(tipo==1)
                {
                    (*it)->setPeca(new Torre());
                }
                else if(tipo==2)
                {
                    (*it)->setPeca(new Cavalo());
                }
                else if(tipo==3)
                {
                    (*it)->setPeca(new Bispo());
                }
                else
                {
                    (*it)->setPeca(new Dama());
                }
            }
        }
    }
}

//Remove Peça no tabuleiro
void Tabuleiro::destroePeca(int linh, int col)
{
    // Percorrendo a lista de quadrados criada
    for( it=quadrados.begin() ; it!= quadrados.end() ; it++)
    {
        //Identificando a linha e coluna
        if((*it)->getLinha() == linh && (*it)->getColuna() == col )
        {
            //Identificar se o local de remoção está NULL
            if((*it)->getPeca() == NULL)
            {

                throw ERRO;
            }
            else
            {
                delete (*it)->getPeca();
                (*it)->setPeca(NULL); //Setando a peça como NULL(Sem Peça)
            }
        }
    }
}

// Limpa cores (verdes) e retorna as cores inicial do tabuleiro
void Tabuleiro::coresTabuleiro()
{
    // Percorrendo todo tabuleiro
    for(it = quadrados.begin() ; it!=quadrados.end(); it++)
    {
            /*Setando a cor do quadrado*/
            (*it)->setBalde((*it)->getLinha() % 2 == (*it)->getColuna() % 2);
    }
}




