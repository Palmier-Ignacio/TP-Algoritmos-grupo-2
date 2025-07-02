#include "GestorBibliotecas.h"
#include <iostream>
#include <windows.h>
#include <limits>

using namespace std;
GestorBibliotecas::GestorBibliotecas()
    : tablaBiblioteca(Biblioteca::cargarBibliotecas("bibliotecas.txt", arbolBibliotecas) / 0.8) // lista de inicializacion x el constructor de la tabla
{
    arbolBibliotecas.recorreEInsertaEnTabla(arbolBibliotecas.getRaiz(), tablaBiblioteca);

    grafo = Grafo::crearDesdeArchivo("bibliotecasDistancias.txt");
    if (grafo)
        grafo->floydWarshall();

    Prestamo::cargarPrestamos("prestamos.txt", prestamos);
}

GestorBibliotecas::~GestorBibliotecas()
{
    arbolBibliotecas.liberar(arbolBibliotecas.getRaiz());
    delete grafo;
    for (Prestamo *p : prestamos)
        delete p;
}

void GestorBibliotecas::ejecutar()
{
    char operacion;
    bool seguir = true;

    do
    {
        mostrarMenu();
        cin >> operacion;
        operacion = tolower(operacion);

        switch (operacion)
        {
        case 'a':
            opcionCargarBiblioteca();
            break;
        case 'b':
            opcionBuscarBiblioteca();
            break;
        case 'c':
            opcionEliminarBiblioteca();
            break;
        case 'd':
            opcionMostrarBibliotecas();
            break;
        case 'e':
            opcionCalcularDistancia();
            break;
        case 'f':
            opcionTotalPrestamosPeriodo();
            break;
        case 'g':
            opcionAltaCargaSemanal();
            break;
        case 'h':
            opcionPrestamosPorISBN();
            break;
        case 'i':
            opcionMostrarTablaHash();
            break;
        case 'j':
            seguir = false;
            break;
        default:
            cout << "Opcion no valida" << endl;
        }
        Sleep(3000);
    } while (seguir);
}

void GestorBibliotecas::mostrarMenu()
{
    cout << endl
         << "Ingrese una opcion: \n"
         << "A) Cargar biblioteca\n"
         << "B) Buscar biblioteca\n"
         << "C) Eliminar biblioteca\n"
         << "D) Mostrar bibliotecas\n"
         << "E) Calcular distancia\n"
         << "F) Total prestamos por periodo\n"
         << "G) Alta carga semanal\n"
         << "H) Prestamos por ISBN\n"
         << "I) Mostrar tabla hash\n"
         << "J) Salir\n"
         << "Opcion: ";
}

void GestorBibliotecas::opcionCargarBiblioteca()
{
    cout << "La opcion que usted eligio es A)" << endl;
    string codigo;
    string nombre;
    string ciudad;
    float superficie;
    int cantidadLibros;
    int cantidadUsuarios;
    cout << "Por favor, ingrese el codigo de la biblioteca que desea cargar: " << std::endl;
    cin >> codigo;
    cout << "Por favor, ingrese el nombre de la biblioteca que desea cargar: " << std::endl;
    cin >> nombre;
    cout << "Por favor, ingrese la ciudad de la biblioteca que desea cargar: " << std::endl;
    cin >> ciudad;
    cout << "Por favor, ingrese la superficie de la biblioteca que desea cargar: " << std::endl;
    cin >> superficie;
    cout << "Por favor, ingrese la cantidad de libros de la biblioteca que desea cargar: " << std::endl;
    cin >> cantidadLibros;
    cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea cargar: " << std::endl;
    cin >> cantidadUsuarios;

    Biblioteca *bibliotecaACargar = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
    if (arbolBibliotecas.insertar(bibliotecaACargar))
    {
        cout << "Se añadio con exito al arbol la biblioteca con codigo: " << bibliotecaACargar->getCodigo() << endl;
    }
    else
    {
        cout << "No se pudo añadir la biblioteca en el arbol." << endl;
    }

    tablaBiblioteca.insertar(codigo);
}

void GestorBibliotecas::opcionBuscarBiblioteca()
{
    std::cout << "La opcion que usted eligio es B)" << std::endl;
    string codigoBibliotecaABuscar;
    int cantUsuariosBiblioteca;
    cout << "Por favor, ingrese el codigo de la biblioteca que desea buscar: ";
    cin >> codigoBibliotecaABuscar;
    cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea buscar: ";
    cin >> cantUsuariosBiblioteca;
    arbolBibliotecas.buscar(arbolBibliotecas.getRaiz(), codigoBibliotecaABuscar, cantUsuariosBiblioteca);
    tablaBiblioteca.buscarBiblioteca(codigoBibliotecaABuscar);
}

void GestorBibliotecas::opcionEliminarBiblioteca()
{
    std::cout << "La opcion que usted eligio es C)" << std::endl;
    string codigoBibliotecaABorrar;
    int cantUsuariosBiblioteca;
    cout << "Por favor, ingrese el codigo de la biblioteca que desea eliminar: ";
    cin >> codigoBibliotecaABorrar;
    cout << "Por favor, ingrese la cantidad de usuarios de la biblioteca que desea eliminar: ";
    cin >> cantUsuariosBiblioteca;
    bool seBorroEnArbol = arbolBibliotecas.borrar(codigoBibliotecaABorrar, cantUsuariosBiblioteca);
    if (seBorroEnArbol)
        tablaBiblioteca.eliminar(codigoBibliotecaABorrar);
}

void GestorBibliotecas::opcionMostrarBibliotecas()
{
    std::cout << "La opcion que usted eligio es D)" << std::endl;
    arbolBibliotecas.inorden(arbolBibliotecas.getRaiz());
}

void GestorBibliotecas::opcionCalcularDistancia()
{
    cout << "Ingrese biblioteca origen: ";
    string origen;
    cin >> origen;
    cout << "Ingrese biblioteca destino: ";
    string destino;
    cin >> destino;

    int idxOrigen = grafo->obtenerIndicePorNombre(origen);
    int idxDestino = grafo->obtenerIndicePorNombre(destino);

    if (idxOrigen == -1 || idxDestino == -1)
    {
        cout << "Alguna biblioteca no fue encontrada." << endl;
        return;
    }

    // Obtener distancia mínima
    double distancia = grafo->obtenerDistancia(idxOrigen, idxDestino);

    if (distancia == std::numeric_limits<double>::infinity())
    {
        cout << "No hay camino entre las bibliotecas." << endl;
        return;
    }
    cout << "Distancia minima: " << distancia << endl;

    // Obtener camino mínimo
    vector<string> camino = grafo->obtenerCaminoMinimo(idxOrigen, idxDestino);
    cout << "Camino minimo: ";
    for (const auto &biblio : camino)
    {
        cout << biblio;
        if (&biblio != &camino.back())
            cout << " -> ";
    }
    cout << endl;
}

void GestorBibliotecas::opcionTotalPrestamosPeriodo()
{
    std::cout << "La opcion que usted eligio es F)" << std::endl;
    string codigoBiblioteca;
    string fechaInicio;
    string fechaFin;

    cout << "Por favor, ingrese el codigo de la biblioteca: ";
    cin >> codigoBiblioteca;

    cout << "Por favor, ingrese la fecha de inicio (YYYYMMDD): ";
    cin >> fechaInicio;

    cout << "Por favor, ingrese la fecha de fin (YYYYMMDD): ";
    cin >> fechaFin;

    // Si la biblioteca fue encontrada, llamamos al método totalPrestamosDeBiblioteca_Durante_
    int totalPrestamos = Prestamo::totalPrestamosDeBiblioteca_Durante_(prestamos, codigoBiblioteca, fechaInicio, fechaFin);
    if (totalPrestamos >= 0)
    {
        cout << "Total de prestamos de la biblioteca " << codigoBiblioteca << " durante el periodo "
             << fechaInicio << " a " << fechaFin << ": " << totalPrestamos << endl;
    }
    else
        cout << "No se encontraron prestamos para la biblioteca con codigo: " << codigoBiblioteca << endl;
}

void GestorBibliotecas::opcionAltaCargaSemanal()
{
    std::cout << "La opcion que usted eligio es G)" << std::endl;
    int cantidadDePrestamos;

    cout << "Por favor, ingrese la cantidad de prestamos que desea considerar para alta carga: ";
    cin >> cantidadDePrestamos;

    vector<string> bibliotecasConAltaCarga = Prestamo::detectarBibliotecasConAltaCargaSemanal(prestamos, cantidadDePrestamos);
    if (bibliotecasConAltaCarga.empty())
    {
        cout << "No se encontraron bibliotecas con alta carga de prestamos." << endl;
    }
    else
    {
        cout << "Bibliotecas con alta carga de prestamos: " << endl;
        for (const string &codigo : bibliotecasConAltaCarga)
        {
            cout << codigo << endl;
        }
    }
}

void GestorBibliotecas::opcionPrestamosPorISBN()
{
    std::cout << "La opcion que usted eligio es H)" << std::endl;
    string idUsuario;
    cout << "Por favor, ingrese el DNI del usuario: ";
    cin >> idUsuario;
    vector<Prestamo> prestamosUsuario = Prestamo::obtenerPrestamosDeUsuarioPorISBN(prestamos, idUsuario);
    if (prestamosUsuario.empty())
        cout << "No se encontraron prestamos para el DNI del usuario: " << idUsuario << endl;
    else
    {
        cout << "Prestamos encontrados para el usuario con DNI " << idUsuario << ":" << endl;
        for (Prestamo &prestamo : prestamosUsuario)
            cout << "ISBN: " << prestamo.getISBN() << endl;
    }
}

void GestorBibliotecas::opcionMostrarTablaHash()
{
    std::cout << "La opcion que usted eligio es I)" << std::endl;
    tablaBiblioteca.mostrarBibliotecas();
}
