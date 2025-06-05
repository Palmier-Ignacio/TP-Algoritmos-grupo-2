#include "celda.h"

Celda::Celda() {
    this->valor = nullptr;
    this->estado = VACIO;
}


string Celda::getValor() { return valor; }
Estado Celda::getEstado() {  return estado; };
void Celda::setValor(string valorRecibido) {  this->valor = valorRecibido; };
void Celda::cambiarEstado(Estado estadoNuevo) { this->estado = estadoNuevo; };

