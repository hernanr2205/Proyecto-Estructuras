#ifndef PILATESOROS_H
#define PILATESOROS_H

#include "Tesoro.h"
#include <stack>

/**
 * Almacenar tesoros
 * - push agregar tesoro
 * - pop remover tesoro
 * - top ver tesoro
 * - size cantidad de tesoros
 * - estaVacia verificar si hay tesoros
 */
class PilaTesoros {
private:
    std::stack<Tesoro> pila;

public:
    // Constructor por defecto
    PilaTesoros() = default;

    // Agregar tesoro
    void push(const Tesoro& t);

    // Obtener tesoro
    Tesoro top() const;

    // Remover tesoro
    void pop();

    // Verificar si está vacía
    bool estaVacia() const;

    // Obtener cantidad de tesoros
    int size() const;

    // Mostrar todos los tesoros
    void mostrar() const;
};

#endif // PILATESOROS_H