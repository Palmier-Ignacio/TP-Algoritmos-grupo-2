#include "nodo.h"

Nodo::Nodo(Biblioteca* biblio) {
    this->biblioteca = biblio;
    this->siguiente = nullptr;
}
