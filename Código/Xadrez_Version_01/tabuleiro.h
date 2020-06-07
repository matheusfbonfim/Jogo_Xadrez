#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "quadrado.h"
#include "torre.h"
#include "cavalo.h"
#include "bispo.h"
#include "dama.h"

#include <QMessageBox>
#include <QList>

#define ERRO 5

class Tabuleiro
{ 
private:
    /*Singleton*/
    //Define ponteiro para o unico objeto
    static Tabuleiro *instancia;
    //Requisitos para o singleton
    Tabuleiro();
    Tabuleiro(const Tabuleiro &t); // Construtor de copia
    Tabuleiro operator=(Tabuleiro t); // Sobrecarga do operador =

    /*Lista de quadrados que formará o tabuleiro*/
    QList<Quadrado*> quadrados;

    /*Variaveis para as coordenadas*/
    int x;
    int y;
    int x_aux;
    int y_aux;

public:
    // Metodo que cria ou retorna o único objeto da classe Tabuleiro
    static Tabuleiro *getInstancia();

    //Iteratores da lista de quadrados
    QList<Quadrado*>::iterator getInicioTabuleiro();
    QList<Quadrado*>::iterator getFinalTabuleiro();
    QList<Quadrado*>::iterator it;

    //Metodos que irão inserir e remover as peças da lista de quadrados
    void criaPeca(int linha_,int colu_, int tipo);
    void destroePeca(int linh, int col);

    //Metodo que limpa cores e retorna as cores iniciais do tabuleiro
    void coresTabuleiro();
};

#endif // TABULEIRO_H
