#include "peca.h"

Peca::Peca(int TP)
{
    tipo = TP;
}

//Retorna o tipo de Peça(por herança todas as classes)
int Peca::getTipoPeca()
{
    return tipo;
}

