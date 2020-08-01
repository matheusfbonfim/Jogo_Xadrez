#ifndef QUADRADO_H
#define QUADRADO_H

#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QWidget>
#include "peca.h"

class Quadrado
{
public:
    Quadrado(double x,double y);
    double getX();
    double getY();
    QPen getCaneta();
    QBrush getBalde();
    int getLinha();
    int getColuna();

    void setBalde(int cor);
    void setLinha(int l);
    void setColuna(int c);

    //Getter e Setter - Peça
    Peca* getPeca();
    void setPeca(Peca*p);

    //Descontrutor
    ~Quadrado();

private:
    /* Parametros da estrutura do quadrado */
    QPen *caneta;
    QBrush *balde;

    /*Coordenadas iniciais de cada quadrado*/
    double x;
    double y;

    /*Indices dos quadrados*/
    int indice_linha;
    int indice_coluna;

    /*Peça no quadrado*/
    Peca* peca;
};

#endif // QUADRADO_H
