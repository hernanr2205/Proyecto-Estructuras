#include "Nodo.h"

/**
 * Constructor del Nodo
 * Inicializa la posición y valores por defecto
 */
Nodo::Nodo(int f, int c)
    : fila(f), columna(c), simbolo('o'), descubierta(false),
      tieneTesoro(false), tipoTesoro(""),
      arriba(nullptr), abajo(nullptr), izquierda(nullptr), derecha(nullptr),
      esMuroReal(false) {  // NUEVO: inicializar en false
}

/**
 * Asigna un tesoro a este nodo
 */
void Nodo::setTesoro(const std::string& tipo) {
    tieneTesoro = true;
    tipoTesoro = tipo;
}

/**
 * Remueve el tesoro de este nodo
 */
void Nodo::removerTesoro() {
    tieneTesoro = false;
    tipoTesoro = "";
}