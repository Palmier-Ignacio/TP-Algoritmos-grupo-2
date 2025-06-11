#include "tablahash.h"
#include "celda.h"
#include "biblioteca.h"
#include <iostream>
#include <string>
using namespace std;
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
 
int TablaHash::buscarIndiceParaInsertar(const string &clave) 
{
    int indice = funcionHash(clave);
    int intentos = 0;

    while (intentos < tamanio)
    {
        Estado estado = tabla[indice].getEstado();

        if (estado != EN_USO || tabla[indice].getValor() == clave)
            return indice;

        indice = (indice + 1) % tamanio;
        intentos++;
    }
    return -1; // No se encontró un lugar válido
}

int TablaHash::buscarIndiceDeClave(const string &clave) 
{
    int indice = funcionHash(clave);
    int intentos = 0;

    while (intentos < tamanio)
    {
        Estado estado = tabla[indice].getEstado();

        if (estado == VACIO)
            return -1; // No está la clave, y no va a aparecer más adelante

        if (estado == EN_USO && tabla[indice].getValor() == clave)
            return indice;

        indice = (indice + 1) % tamanio;
        intentos++;
    }
    return -1; // No se encontró la clave
}


void TablaHash::insertar(string codigoBiblioteca)
{
    int indice = buscarIndiceParaInsertar(codigoBiblioteca);

    if (indice != -1)
    {
        tabla[indice].setValor(codigoBiblioteca);
        tabla[indice].cambiarEstado(EN_USO);
    }
    else
    {
        cout << "No se pudo insertar el código de la biblioteca: tabla llena o sin espacio válido.\n";
    }
}


void TablaHash::buscarBiblioteca(string codigoBiblioteca)
{
    int indice = buscarIndiceDeClave(codigoBiblioteca);

    if (indice != -1)
    {
        cout << "Biblioteca encontrada: " << tabla[indice].getValor() << endl;
    }
    else
    {
        cout << "La biblioteca no existe o fue borrada.\n";
    }
}

void TablaHash::mostrarBibliotecas(){
    cout << "Valores en Tabla: ";
    for(int i = 0; i<tamanio;i++){
        cout << tabla[i].getValor() <<", ";
    }
    cout << "] ";
};

