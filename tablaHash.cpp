#include "tablahash.h"
#include "celda.h"
#include "biblioteca.h"
#include <string>
TablaHash::TablaHash(int tamanio)
{
    this->tamanio = tamanio;
    // tabla = new Celda[tamanio];
}
int TablaHash::funcionHash(const string &codigo)
{
    int hash = 0;
    for (char c : codigo)
        hash += c;
    return hash % getTamanio();
}

TablaHash::~TablaHash()
{
}

int TablaHash::getTamanio() { return tamanio; }
/* 
int TablaHash::buscarIndiceDisponible(const string &clave, bool paraInsertar) const
{
    int indice = funcionHash(clave);
    int original = indice;
    int intentos = 0;

    while (intentos < tamanio)
    {
        Estado estado = tabla[indice].getEstado();

        if (paraInsertar)
        {
            if (estado != EN_USO || tabla[indice].getValor() == clave)
                return indice;
        }
        else
        {
            if (estado == VACIO)
                return -1; // No existe
            if (estado == EN_USO && tabla[indice].getValor() == clave)
                return indice;
        }

        indice = (indice + 1) % tamanio;
        intentos++;
    }
    return -1;
} */

void TablaHash::insertar(string codigoBiblioteca)
{
    int clave = funcionHash(codigoBiblioteca);

    int cuantasVueltasDio = 0;
    // dsps calcular
    // ver biblio repetida

    while (tabla[clave].getEstado() == EN_USO && cuantasVueltasDio < 3)
    {
        if (clave > tamanio - 1)
        {
            clave = clave - tamanio - 1;
            cuantasVueltasDio++;
        }
        else
        {
            clave += clave;
        }
    }

    if (tabla[clave].getEstado() != EN_USO)
    {
        tabla[clave].cambiarEstado(EN_USO);
        tabla[clave].setValor(codigoBiblioteca);
    }
    else
    {
        cout << "No se pudo insertar el codigo de la biblioteca";
    }
};

void TablaHash::buscarBiblioteca(string codigoBiblioteca)
{
    int clave = funcionHash(codigoBiblioteca);
    int cuantasVueltasDio = 0;
    int puntero = 0;
    if (tabla[clave].getValor() == codigoBiblioteca)
    {
        cout << tabla[clave].getValor();
    }
    else if (tabla[clave].getEstado() == VACIO)
    {
        cout << "No existe la biblioteca";
    }
    else
    {
        clave += clave;
        while (tabla[clave].getValor() != codigoBiblioteca && cuantasVueltasDio < 3)
        { // hacer método de hash para casos especiales
            if (clave > tamanio - 1)
            {
                clave = clave - tamanio - 1;
                cuantasVueltasDio++;
            }
            else
            {
                clave += clave;
            }
        };
        if (cuantasVueltasDio == 2)
        {
            cout << "La biblioteca fue borrada";
        }
        else
        {
            cout << tabla[clave].getValor();
        };
    };
};
