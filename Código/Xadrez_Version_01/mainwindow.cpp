#include "mainwindow.h"
#include<iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Status da Janela
    setGeometry(450,100,500,500);
    setWindowTitle("Xadrez");

    // Definição da barra de menu
    barraMenu();

    // Atalho para as ações
    atalhoBotoes();

    //SLOTS - Sinais
    conectoresSinais();

    // Inicializando o tabuleiro que será usado (Singleton)
    Tab = Tabuleiro::getInstancia();

    //Variavel auxiliar Mouse Event
    q1 = NULL;
    q2 = NULL;
}

//paintEvent - Desenhar
void MainWindow::paintEvent(QPaintEvent *)
{
    /*Definicao do pintor*/
    Pintor = new QPainter(this);

    /*Definicao do iterator - inicio da lista*/
    it = Tab->getInicioTabuleiro();

    for(int i = 0 ; it != Tab->getFinalTabuleiro() ; it++)
    {
        /*Definindo os parametros do pintor conforme quadrados da lista*/
        Pintor->setPen((*it)->getCaneta());
        Pintor->setBrush((*it)->getBalde());

        /*Desenhando o quadrado*/
        Pintor->drawRect( (*it)->getX() , (*it)->getY() ,50,50);

        /*Inserir a figura da peça especifica*/
        if((*it)->getPeca()!=NULL)
        {
            if((*it)->getPeca()->getTipoPeca()==1)
            {
                icone_peca=new QPixmap("torre.png");
                Pintor->drawPixmap((*it)->getX(),(*it)->getY(),50,50,*icone_peca);
            }
            else if((*it)->getPeca()->getTipoPeca()==2)
            {
                icone_peca=new QPixmap("cavalo.png");
                Pintor->drawPixmap((*it)->getX(),(*it)->getY(),50,50,*icone_peca);
            }
            else if((*it)->getPeca()->getTipoPeca()==3)
            {
                icone_peca=new QPixmap("bispo.png");
                Pintor->drawPixmap((*it)->getX(),(*it)->getY(),50,50,*icone_peca);
            }
            else
            {
                icone_peca=new QPixmap("dama.png");
                Pintor->drawPixmap((*it)->getX(),(*it)->getY(),50,50,*icone_peca);
            }
        }

        /*Colocando no tabuleiro os indices*/
        if((*it)->getColuna() == 0)
        {
            Pintor->drawText((*it)->getX() - 20,(*it)->getY() + 30,QString::number((*it)->getLinha()));
            i++;
        }
        if((*it)->getLinha() == 7)
        {
            Pintor->drawText((*it)->getX()+18,(*it)->getY() + 75,QString::number((*it)->getColuna()));
        }
        update();
    }
}

// Definição da Barra de Menus
void MainWindow::barraMenu()
{
    //Barra de Menus
    menu_bar = new QMenuBar(this);
    menu_bar->setGeometry(0,0,10000,25);

    //Opções de menus
    arquivo = new QMenu("&Arquivo",this);
    peca = new QMenu("&Peça",this);

    //Adicionar menus a barra
    menu_bar->addMenu(arquivo);
    menu_bar->addMenu(peca);

    //Criar ações aos menus
    novo = new QAction("&Novo",this);
    abrir = new QAction("&Abrir",this);
    salvar = new QAction("&Salvar",this);
    sair = new QAction("&Sair",this);

    inserir = new QAction("&Inserir",this);
    remover = new QAction("&Remover",this);

    //Adicionar ações aos menus
    arquivo->addAction(novo);
    arquivo->addAction(abrir);
    arquivo->addAction(salvar);
    arquivo->addAction(sair);

    peca->addAction(inserir);
    peca->addAction(remover);
}

//Conectores de Sinais
void MainWindow::conectoresSinais()
{
    //Menu Arquivo
    connect(sair,SIGNAL(triggered(bool)),this, SLOT(close()));// Fecha a janela
    connect(abrir,SIGNAL(triggered(bool)),this, SLOT(abrirArquivo()));// Não ta pegando no Linux
    connect(novo,SIGNAL(triggered(bool)),this,SLOT(novoTabuleiro())); // Limpa as peças do tabuleiro
    connect(salvar,SIGNAL(triggered(bool)),this, SLOT(salvarArquivo()));

    // Menu Peça
    connect(inserir,SIGNAL(triggered(bool)),this, SLOT(inserirPeca()));
    connect(remover,SIGNAL(triggered(bool)),this, SLOT(removerPeca()));
}

//Atalhos dos Botões - Action Menus
void MainWindow::atalhoBotoes()
{
    /* Atalhos - Ações do arquivo*/
    novo->setShortcut(tr("Ctrl+N"));
    abrir->setShortcut(tr("Ctrl+O"));
    salvar->setShortcut(tr("Ctrl+S"));
    sair->setShortcut(tr("Alt+F4"));

    /*Atalhos - Ações do Peça*/
    inserir->setShortcut(tr("F5"));
    remover->setShortcut(tr("F6"));
}

//Abrir arquivo
void MainWindow::abrirArquivo()
{
    // Filtro para o tipo de dado a ser selecionado
    QString filtro= "(*.ram)";

    // Armazena o local e o nome do arquivo clicado
    QString abrirArquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivo",QDir::homePath(),filtro);

    //Ponteiro para o arquivo
    FILE *ptr;

    //Abre o arquivo
    ptr = fopen(abrirArquivo.toStdString().c_str(),"r");

    if(ptr == NULL)
    {
        erro_messagem = new QMessageBox(this);
        erro_messagem->setWindowTitle("ERRO");
        erro_messagem->setText("Erro de leitura do arquivo ou arquivo não selecionado");
        erro_messagem->show();
    }
    else
    {
        char info[5];

        //Limpa o tabuleiro
        novoTabuleiro();

        //Lê e cria peca conforme as informações do arquivo
        while(fscanf(ptr," %[^\n]s", info) != EOF)
            Tab->criaPeca((atoi(&info[0])) ,(atoi(&info[2])),(atoi(&info[4])));
        fclose(ptr);
    }
}


//Salvar Arquivo
void MainWindow::salvarArquivo()
{
    // Filtro para o tipo de dado a ser selecionado
    QString filtro= "(*.ram)";

    // Armazena o local e o nome do arquivo
    QString abrirArquivo = QFileDialog::getSaveFileName(this,"Salvar Arquivo",QDir::homePath(),filtro);

    //Ponteiro para o arquivo
    FILE *ptr;

    ptr = fopen(abrirArquivo.toStdString().c_str(),"w");

    if(ptr == nullptr)
    {
        erro_messagem = new QMessageBox(this);
        erro_messagem->setWindowTitle("ERRO");
        erro_messagem->setText("Erro de leitura do arquivo");
        erro_messagem->show();
    }
    else
    {
        it = Tab->getInicioTabuleiro();
        for(; it != Tab->getFinalTabuleiro(); it++)
        {
            if((*it)->getPeca() != NULL)
            {
                fprintf(ptr, "%d %d %d\n", (*it)->getLinha() , (*it)->getColuna() , (*it)->getPeca()->getTipoPeca());
            }
        }
        fclose(ptr);
    }
}

//Menu Arquivo - Novo - Clear Tabuleiro
void MainWindow::novoTabuleiro()
{
    clearTab();
}

//Inserir a peca - Menu Peça
void MainWindow::inserirPeca()
{
    //Criar a caixa de inserir Peça
    inserir_peca = new QDialog(this);
    inserir_peca->setFixedSize(sizeHint());//Centralizar no meio
    inserir_peca->setWindowTitle("Xadrez");

    //Cria os botões de seleção
    radio_torre = new QRadioButton(tr("Torre"), inserir_peca);
    radio_torre->setChecked(true); //Seleciona torre inicialmente
    radio_cavalo = new QRadioButton(tr("Cavalo"));
    radio_bispo = new QRadioButton(tr("Bispo"));
    radio_dama = new QRadioButton(tr("Dama"));

    //Cria a caixa de texto
    caixa_linha_inserir = new QSpinBox(inserir_peca);
    caixa_coluna_inserir = new QSpinBox(inserir_peca);

    //Cria o botão de cancelar e ok
    botao_OkCancelar_inserir = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(botao_OkCancelar_inserir, SIGNAL(accepted()), inserir_peca, SLOT(accept()));
    connect(botao_OkCancelar_inserir, SIGNAL(rejected()), inserir_peca, SLOT(reject()));

    //Adiciona todos os elementos no layout
    layout_inserir = new QFormLayout(inserir_peca);
    layout_inserir->addRow(radio_torre);
    layout_inserir->addRow(radio_cavalo);
    layout_inserir->addRow(radio_bispo);
    layout_inserir->addRow(radio_dama);
    layout_inserir->addRow(new QLabel("Linha:"));
    layout_inserir->addRow(caixa_linha_inserir);
    caixa_linha_inserir->setMinimum(0);
    caixa_linha_inserir->setMaximum(7);
    layout_inserir->addRow(new QLabel("Coluna:"));
    layout_inserir->addRow(caixa_coluna_inserir);
    caixa_coluna_inserir->setMinimum(0);
    caixa_coluna_inserir->setMaximum(7);
    layout_inserir->addRow(botao_OkCancelar_inserir);

    inserir_peca->setLayout(layout_inserir);

    //Cria Peca
    if(inserir_peca->exec() == QDialog::Accepted && q1==NULL)
    {
        //Se for gerado uma erro na inserção, ir para o try catch
        try
        {
             // Checagem do tipo de peça selecionada e inserção conforme as linhas e colunas
             if(radio_torre->isChecked())
             {
                Tab->criaPeca(caixa_linha_inserir->value(), caixa_coluna_inserir->value(),1);
             }
             else if(radio_cavalo->isChecked())
             {
                Tab->criaPeca(caixa_linha_inserir->value(), caixa_coluna_inserir->value(),2);
             }
             else if(radio_bispo->isChecked())
             {
                Tab->criaPeca(caixa_linha_inserir->value(), caixa_coluna_inserir->value(),3);
             }
             else
             {
                Tab->criaPeca(caixa_linha_inserir->value(), caixa_coluna_inserir->value(),4);
             }
        }
        catch(int erro)
        {
                erro_messagem = new QMessageBox(this);
                erro_messagem->setWindowTitle("ERRO");
                erro_messagem->setText("Já existe uma peça inserida");
                erro_messagem->show();
         }
    }
    else
    {
        erro_messagem = new QMessageBox(this);
        erro_messagem->setWindowTitle("ERRO");
        erro_messagem->setText("Não é possivel remover durante o movimento");
        erro_messagem->show();

    }

    update();
}

// Remover Peça - Menu peça
void MainWindow::removerPeca()
{
    //Criar a caixa de inserir Peça
    remover_peca = new QDialog(this);
    remover_peca->setFixedSize(sizeHint());//Centralizar no meio
    remover_peca->setWindowTitle("Xadrez");

    //Cria a caixa de texto
    caixa_linha_remover = new QSpinBox(remover_peca);
    caixa_coluna_remover = new QSpinBox(remover_peca);

    //Cria o botão de cancelar e ok
    botao_OkCancelar_remover = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(botao_OkCancelar_remover, SIGNAL(accepted()), remover_peca, SLOT(accept()));
    connect(botao_OkCancelar_remover, SIGNAL(rejected()), remover_peca, SLOT(reject()));

    //Adiciona todos os elementos no layout
    layout_remover = new QFormLayout(remover_peca);
    layout_remover->addRow(new QLabel("Linha:"));
    layout_remover->addRow(caixa_linha_remover);
    caixa_linha_remover->setMinimum(0);
    caixa_linha_remover->setMaximum(7);
    layout_remover->addRow(new QLabel("Coluna:"));
    layout_remover->addRow(caixa_coluna_remover);
    caixa_coluna_remover->setMinimum(0);
    caixa_coluna_remover->setMaximum(7);
    layout_remover->addRow(botao_OkCancelar_remover);

    remover_peca->setLayout(layout_remover);

    //Remoção da peça
    if(remover_peca->exec()== QDialog::Accepted)
    {
        //Remoção na linha especifica e tratamento de erro
        try
        {
            if(q1==NULL) // Caso queira remover com a peça selecionada
            {
                Tab->destroePeca(caixa_linha_remover->value(),caixa_coluna_remover->value());
            }
            else
            {
                erro_messagem = new QMessageBox(this);
                erro_messagem->setWindowTitle("ERRO");
                erro_messagem->setText("Não é possivel remover durante o movimento");
                erro_messagem->show();
            }
        }
        catch(int erro)
        {
            erro_messagem = new QMessageBox(this);
            erro_messagem->setWindowTitle("Erro");
            erro_messagem->setText("Não existe peça para remover");
            erro_messagem->show();
        }
    }   
}

//MouseEvent - Pontos clicados ou pressionado
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mx1 = event->x();
    my1 = event->y();
}

//MouseEvent - Mouse despressionado
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mx2 = event->x();
    my2 = event->y();

    //Verifica o limite do tabuleiro
    if(limitesTabuleiro())
    {
        determinaQuadrado();
    }
}

//Limites Tabuleiro
bool MainWindow::limitesTabuleiro()
{
    if(mx2==mx1 && my1==my2) // Verifica se tem o clique (Press==Release)
    {
        //Verifica se o clique ta dentro do tabuleiro
        if( (mx1 >= (*(Tab->getInicioTabuleiro()))->getX() ) && (mx1 <= (*(--Tab->getFinalTabuleiro()))->getX() +50 ) )
        {
            if( ( my1 >= (*(Tab->getInicioTabuleiro()))->getY() ) && (my1 <= (*(--Tab->getFinalTabuleiro()))->getY()+50) )
            {
                return true; // Retorna se ta dentro do tabuleiro e ocorreu clique mesmo
            }
        }
    }
    return false;
}

//Identica qual quadrado foi clicado e inicializa a variavel auxiliar quadrado q1 e realiza movimento no clique
void MainWindow::determinaQuadrado()
{
    it = Tab->getInicioTabuleiro();

    for( ; it != Tab->getFinalTabuleiro() ; it++)
    {
        // Identificando o clique e o quadrado clicado
        if(mx1 >= (*it)->getX() && mx1<= ( (*it)->getX() + 50 ))
        {
            if(my1 >= (*it)->getY() && my1<= ( (*it)->getY() + 50 ))
            {
                //Armazenando o movimento - Clique no quadrado q1 e colocando em q2
                // Verifica se o quadrado que foi clicado não é o mesmo (q1=q1)
                if(q1 != NULL && q2 == NULL && q1!=(*it))
                {
                   q2 = *it;

                   //Verificando se o movimento é válido para peça clicada e executa o movimento
                   if( q1->getPeca()->movimento(q1->getLinha(),q1->getColuna(),q2->getLinha(),q2->getColuna()) )
                   {
                       q2->setPeca(q1->getPeca());
                       q1->setPeca(NULL);
                       Tab->coresTabuleiro(); // Limpa cores do tabuleiro
                   }
                   else // Senão retorna um erro e reseta o q2
                   {
                       erro_messagem = new QMessageBox(this);
                       erro_messagem->setWindowTitle("ERRO");
                       erro_messagem->setText("Movimento Inválido");
                       erro_messagem->show();

                       q2=NULL;
                   }
                 }

                // Atribuindo a variavel q1 o endereço do quadrado clicado, dado que q1 é NULL
                // Considera-se que há uma peça no quadrado clicado
                if( (q1 == NULL) && (q2 == NULL) & ( (*it)->getPeca()!=NULL) )
                {
                      q1 = *it;
                      it=NULL;
                      q1->getPeca()->movimentoCor(q1->getLinha(),q1->getColuna()); // Identificado a peça e pintando no tabuleiro seu possivel movimento
                      break;
                }
                else if(q1==(*it)) // Verifica se o segundo clique foi no proprio q1, assim retoma o tabuleiro inicial
                {
                    q1=NULL;
                    Tab->coresTabuleiro();
                }
            } 
        }
    }

    //Se o movimento foi feito, os quadrados auxiliares são resetados
    if(q1!=NULL && q2!=NULL)
    {
        q1=NULL;
        q2=NULL;
    }
}

// Retira todas as peças do tabuleiro
void MainWindow::clearTab()
{
    it = Tab->getInicioTabuleiro();
    if(q1==NULL)
    {
        for( ; it != Tab->getFinalTabuleiro() ; it++)
        {
            (*it)->setPeca(NULL);
        }
    }
    else
    {
        erro_messagem = new QMessageBox(this);
        erro_messagem->setWindowTitle("ERRO");
        erro_messagem->setText("Não pode criar um novo tabuleiro durante o movimento");
        erro_messagem->show();
    }
}
