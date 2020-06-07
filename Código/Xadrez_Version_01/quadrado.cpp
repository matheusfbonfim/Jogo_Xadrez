#include "quadrado.h"

Quadrado::Quadrado(double x_,double y_)
{
    x = x_;
    y = y_;
    caneta = new QPen(Qt::black); // Cria a caneta com contorno preto
    peca = NULL;
}

//Retorna a coordenada X do quadrado
double Quadrado::getX()
{
    return x;
}

//Retorna a coordenada Y do quadrado
double Quadrado::getY()
{
    return y;
}

// Retorna a caneta
QPen Quadrado::getCaneta()
{
    return *caneta;
}

// Retorna o balde de tinta
QBrush Quadrado::getBalde()
{
   return *balde;
}

// Setar o balde conforme a tinta
void Quadrado::setBalde(int cor)
{
    if(cor==1)
    {
        balde = new QBrush(Qt::white);
    }
    else if(cor == 0)
    {
        balde = new QBrush(Qt::lightGray);
    }
    else
    {
        delete balde;
        balde = new QBrush(Qt::green);
    }
}

//Setar o indice da Coluna
void Quadrado::setColuna(int c)
{
    indice_coluna = c;
}

//Setar o indice da Linha
void Quadrado::setLinha(int l)
{
    indice_linha = l;
}

// Retornar o indice da linha
int Quadrado::getLinha()
{
    return indice_linha;
}

//Retornar o indice da coluna
int Quadrado::getColuna()
{
    return indice_coluna;
}

//Retorna a peça inserida no quadrado
Peca* Quadrado::getPeca()
{
    return peca;
}

//Seta a peca do quadrado
void Quadrado::setPeca(Peca* p)
{
    peca = p;
}

//Desconstrutor
Quadrado::~Quadrado()
{
    free(caneta);
    free(balde);
}
