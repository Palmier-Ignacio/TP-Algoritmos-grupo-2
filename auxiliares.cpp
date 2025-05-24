#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Biblioteca.h"
using namespace std;

void cargarBibliotecas(string nombreArchivo,vector<Biblioteca*>& bibliotecas)
{
    ifstream archivo(nombreArchivo.c_str());
    string linea;

    while (getline(archivo, linea))
    {
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
                infoBiblioteca[1],
                infoBiblioteca[2],
                stof(infoBiblioteca[3]),
                stoi(infoBiblioteca[4]),
                stoi(infoBiblioteca[5]));

            bibliotecas.push_back(bibliotecaCreada);
        }
       
    }

    archivo.close();

   
}
