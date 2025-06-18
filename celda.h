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
    //pos: devuelve el valor que tiene guardada la celda
    string getValor();
    //pos: devuelve el estado que tiene la celda
    Estado getEstado();
    //pos: cambia el valor que tiene guardado la celda
    void setValor(string valor);
    //pos: cambia el estado que tiene la celda
    void cambiarEstado(Estado estadoNuevo);
};

#endif