#include <iostream>
#include <fstream>
//#include "tablaHash.h"
//#include "gestorBibliotecas.cpp"
#include <vector>
#include <string>

#include <sstream>


#include "crearGrafo.h"


using namespace std;



int main()
{
    //gestorBibliotecas();
    
    /* vector<Prestamo *> prestamos = {};
    cargarPrestamos("prestamos.txt", prestamos);
    cout << "Prestamos cargados: " << endl;
    for (int i = 0; i < prestamos.size(); i++)
        prestamos[i]->mostrar();

    for (Prestamo *prest : prestamos)
        delete prest;
    prestamos.clear(); */


    Grafo* grafo = crearGrafoDesdeArchivo("bibliotecasDistancias.txt");
    if (grafo) {
        cout << grafo->toString() << endl;
        delete grafo; // liberar memoria
    }
    return 0;
    
}