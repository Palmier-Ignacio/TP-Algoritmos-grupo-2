#include <iostream>
#include <fstream>
#include "biblioteca.h"
#include "prestamo.h"
#include "auxiliares.h"
#include "tablaHash.h"
#include "arbol.h"
#include <vector>
#include <string>

using namespace std;

int main()
{

    vector<Prestamo *> prestamos = {};
    cargarPrestamos("prestamos.txt", prestamos);
    cout << "Prestamos cargados: " << endl;
    for (int i = 0; i < prestamos.size(); i++)
        prestamos[i]->mostrar();

    for (Prestamo *prest : prestamos)
        delete prest;
    prestamos.clear();
}