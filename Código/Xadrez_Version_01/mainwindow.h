#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <cstdio>
#include <cstdlib>
#include <QAction>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QFormLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QLabel>
#include <QSpinBox>
#include <QStringList>
#include <QMessageBox>
#include <QPixmap>
#include <QMouseEvent>
#include <cstdlib>
#include <cstdio>
#include <QDir>
#include <QFile>
#include "peca.h"
#include "quadrado.h"
#include "tabuleiro.h"

/*Classes auxiliares*/

#include<QList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    /* Barra de Menu */
    QMenuBar *menu_bar;

    QMenu *arquivo;
    QAction *novo;
    QAction *abrir;
    QAction *salvar;
    QAction *sair;

    /*Teste do slot abrir*/
    QFileDialog *evento_abrir;

    QMenu *peca;
    QAction *inserir;
    QAction *remover;

    /* Tela de Inserir Peças*/
    QDialog *inserir_peca;
    QFormLayout *layout_inserir; //Objeto Layout de inserir peça
    QRadioButton *radio_torre;
    QRadioButton *radio_cavalo;
    QRadioButton *radio_bispo;
    QRadioButton *radio_dama;
    QSpinBox *caixa_linha_inserir;
    QSpinBox *caixa_coluna_inserir;
    QDialogButtonBox *botao_OkCancelar_inserir;

    /*Tela de Remover Peça*/
    QDialog* remover_peca;
    QFormLayout *layout_remover;
    QSpinBox *caixa_linha_remover;
    QSpinBox *caixa_coluna_remover;
    QDialogButtonBox *botao_OkCancelar_remover;

    /*Paint Event*/
    QPainter *Pintor;
    QList<Quadrado*>::iterator it; // Iterator para usar na Lista de Quadrados( Tabuleiro )
    Tabuleiro *Tab;

    /*Mensagem de erro*/
    QMessageBox* erro_messagem;

    /*Imagens das peças*/
    QPixmap *icone_peca;

    /*Coordenadas - MouseEvent*/
    int mx1;
    int my1;
    int mx2;
    int my2;

    /*Quadrados auxiliares para MouseEvent*/
    Quadrado *q1;
    Quadrado *q2;



public:
    explicit MainWindow(QWidget *parent = nullptr);
    void barraMenu();
    void atalhoBotoes();
    void conectoresSinais();
    void paintEvent(QPaintEvent *);
    //Sobrescrita da mouse event
    void mousePressEvent(QMouseEvent *event);   //Apertar
    void mouseReleaseEvent(QMouseEvent *event); //Arrastar e soltar
    bool limitesTabuleiro(); // Verifica Limite tabuleiro
    void determinaQuadrado();// Identifica quadrado clicado
    void clearTab(); //Metodo que tira todas as peças e reseta o tabuleiro


signals:

public slots:
    void abrirArquivo();
    void salvarArquivo();
    void inserirPeca();
    void removerPeca();
    void novoTabuleiro();
};

#endif // MAINWINDOW_H
