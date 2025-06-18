#include "biblioteca.h"
#include "arbol.h"
Biblioteca::Biblioteca(string codigo, string nombre, string ciudad, float superficie, int cantidadLibros, int cantidadUsuarios)
{
    this->codigo = codigo;
    this->nombre = nombre;
    this->ciudad = ciudad;
    this->superficie = superficie;
    this->cantidadLibros = cantidadLibros;
    this->cantidadUsuarios = cantidadUsuarios;
}

void Biblioteca::mostrar()
{
    cout << "Biblioteca: " << this->codigo << " " <<  this->nombre << " " << this->ciudad << " " <<  this->superficie << " " <<  this->cantidadLibros << " " << this->cantidadUsuarios << endl;
}

string Biblioteca::getCodigo()
{
    return codigo;
}
string Biblioteca::getNombre()
{
    return nombre;
}

string Biblioteca::getCiudad()
{
    return ciudad;
}

float Biblioteca::getSuperficie()
{
    return superficie;
}

int Biblioteca::getCantidadLibros()
{
    return cantidadLibros;
}

int Biblioteca::getCantidadUsuarios()
{
    return cantidadUsuarios;
}
void Biblioteca::setCodigo(string nuevoCodigo)
{
    codigo = nuevoCodigo;
}

void Biblioteca::setNombre(string nuevoNombre)
{
    nombre = nuevoNombre;
}
void Biblioteca::setCiudad(string nuevaCiudad)
{
    ciudad = nuevaCiudad;
}
void Biblioteca::setSuperficie(float nuevaSuperficie)
{
    superficie = nuevaSuperficie;
}
void Biblioteca::setCantidadLibros(int nuevaCantidadLibros)
{
    cantidadLibros = nuevaCantidadLibros;
}
void Biblioteca::setCantidadUsuarios(int nuevaCantidadUsuarios)
{
    cantidadUsuarios = nuevaCantidadUsuarios;
}

int Biblioteca::cargarBibliotecas(string nombreArchivo,Arbol& arbol)
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
            infoBiblioteca.push_back(palabra);

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