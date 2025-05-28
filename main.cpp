#include <iostream>
#include <fstream>
#include "auxiliares.cpp"
#include "biblioteca.cpp"
#include "biblioteca.h"
#include "prestamo.h"
#include "auxiliares.cpp"

using namespace std;

int main()
{
     // preguntar al profe sobre el formato del archivo, si habia una palabra de mas..
    vector<Biblioteca*> bibliotecas= {};
    cargarBibliotecas("bibliotecas.txt", bibliotecas);

    cout << "Bibliotecas cargadas: " << endl;
    for (int i = 0; i < bibliotecas.size(); i++)
    {
        bibliotecas[i]->mostrar();
    } 

    // llibero memoria
    for (Biblioteca *biblio : bibliotecas)
    {
        delete biblio; 
    }

   bibliotecas.clear();

   vector<Prestamo*> prestamos = {};
   cargarPrestamos("prestamos.txt", prestamos);
   cout << "Prestamos cargados: " << endl;
   for (int i = 0; i < prestamos.size(); i++)
       prestamos[i]->mostrar();

  for (Prestamo *prest : prestamos)
       delete prest;
   prestamos.clear();
}