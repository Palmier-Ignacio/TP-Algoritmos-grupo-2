#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Biblioteca.h"
#include "Prestamo.h"
#include "arbol.h"
using namespace std;

int cargarBibliotecas(string nombreArchivo,Arbol& arbol)
{
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    int contadorBibliotecas=0;

    while (getline(archivo, linea))
    {
        contadorBibliotecas++;
        istringstream ss(linea);
        vector<string> infoBiblioteca;
        string palabra;

        // aca guardamos cada pslabra en un vector
        while (ss >> palabra)
        {
            infoBiblioteca.push_back(palabra);
        }

        // si estan todos los datos, se crea una biblioteca con las palabras de la linea
        if (infoBiblioteca.size() >= 6)
        {
            Biblioteca *bibliotecaCreada = new Biblioteca(
                infoBiblioteca[0],
                infoBiblioteca[1]+ " " +infoBiblioteca[2],
                infoBiblioteca[3],
                stoi(infoBiblioteca[4]),
                stoi(infoBiblioteca[5]),
                stoi(infoBiblioteca[6]));

            arbol.insertar(bibliotecaCreada);
        }
       
    }

    archivo.close();

    return contadorBibliotecas;
   
}


void cargarPrestamos(string nombreArchivo, vector<Prestamo*>& prestamos){
    ifstream archivo(nombreArchivo.c_str());
    string linea;
    while (getline(archivo, linea)){
        istringstream ss(linea);
        vector<string> infoPrestamo;
        string palabra;
        while (ss >> palabra){
            infoPrestamo.push_back(palabra);
        }
        if (infoPrestamo.size() >= 4){
            Prestamo *prestamoCreado = new Prestamo(
                infoPrestamo[0],
                infoPrestamo[1],
                infoPrestamo[2],
                infoPrestamo[3]);
            prestamos.push_back(prestamoCreado);
        }
    }
    archivo.close();
}

