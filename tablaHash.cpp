#include "tablahash.h"
#include "celda.h"
#include "biblioteca.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor de la clase TablaHash
// Inicializa la tabla con el tamaño especificado y reserva memoria para las celdas
TablaHash::TablaHash(int tamanio)
{
    this->tamanio = tamanio;
    tabla = new Celda[tamanio];
}

// Función hash simple que calcula el índice a partir de la suma de los caracteres del string
int TablaHash::funcionHash(const string &codigo)
{
    int hash = 0;
    for (char c : codigo)
        hash += c; // Suma los valores ASCII de los caracteres
    return hash % getTamanio(); // Devuelve el índice dentro del rango
}

// Destructor: libera la memoria reservada para la tabla
TablaHash::~TablaHash()
{
    delete[] tabla;
}

// Devuelve el tamaño de la tabla
int TablaHash::getTamanio() { return tamanio; }

// Busca un índice adecuado para insertar una nueva clave, considerando colisiones
int TablaHash::buscarIndiceParaInsertar(const string &clave) 
{
    int indice = funcionHash(clave);
    int intentos = 0;

    // Busca una posición libre o con la misma clave (para evitar duplicados)
    while (intentos < tamanio)
    {
        Estado estado = tabla[indice].getEstado();

        if (estado != EN_USO || tabla[indice].getValor() == clave)
            return indice;

        // Prueba la siguiente posición (resolución por sondeo lineal)
        indice = (indice + 1) % tamanio;
        intentos++;
    }

    return -1; // Tabla llena o sin espacio válido
}

// Busca el índice de una clave existente, o devuelve -1 si no está
int TablaHash::buscarIndiceDeClave(const string &clave) 
{
    int indice = funcionHash(clave);
    int intentos = 0;

    while (intentos < tamanio)
    {
        Estado estado = tabla[indice].getEstado();

        if (estado == VACIO)
            return -1; // Si está vacío, no hay posibilidad de que esté más adelante

        if (estado == EN_USO && tabla[indice].getValor() == clave)
            return indice;

        indice = (indice + 1) % tamanio;
        intentos++;
    }

    return -1; // No se encontró la clave
}

// Inserta un nuevo código de biblioteca en la tabla hash
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
        cout << "No se pudo insertar el codigo de la biblioteca: tabla llena o sin espacio valido.\n";
    }
}

// Elimina una biblioteca cambiando su estado a BORRADO y limpiando su valor
void TablaHash::eliminar(const string &clave)
{
    int indiceBiblio = buscarIndiceDeClave(clave);

    if (indiceBiblio != -1)
    {
        cout << "Se elimino con exito de la tabla la biblioteca con codigo: " << clave << "...\n";
        tabla[indiceBiblio].cambiarEstado(BORRADO);
        tabla[indiceBiblio].setValor("");
    }
    else
    {
        cout << "No se encontro la biblioteca en la tabla.\n";
    }
}

// Busca una biblioteca por su código y muestra el resultado
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

// Muestra el contenido de la tabla hash con sus estados (VACIO, EN_USO, BORRADO)
void TablaHash::mostrarBibliotecas()
{
    cout << "Valores en Tabla:\n";
    for (int i = 0; i < tamanio; i++)
    {
        cout << "Posicion " << i << ": " << tabla[i].getValor() << " (Estado: ";
        switch (tabla[i].getEstado())
        {
            case VACIO: cout << "VACIO"; break;
            case EN_USO: cout << "EN_USO"; break;
            case BORRADO: cout << "BORRADO"; break;
        }
        cout << ")\n";
    }
}

