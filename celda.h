#ifndef CELDA_H_INCLUDED
#define CELDA_H_INCLUDED
#include "estado.h"

#include "biblioteca.h"

class Celda
{
private:
    string valor;
    Estado estado;

public:
    Celda();
    string getValor();
    Estado getEstado();
    void setValor(string valor);
    void cambiarEstado(Estado estadoNuevo);
};

#endif