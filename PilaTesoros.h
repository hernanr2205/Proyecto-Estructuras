#ifndef PILATESOROS_H
#define PILATESOROS_H

#include "Tesoro.h"
#include <stack>

/**
 * Clase PilaTesoros - Pila LIFO para almacenar tesoros
 *
 * Usa std::stack de STL
 * Operaciones:
 * - push: agregar tesoro al tope
 * - pop: remover tesoro del tope
 * - top: ver tesoro del tope
 * - size: cantidad de tesoros
 * - estaVacia: verificar si hay tesoros
 */
class PilaTesoros {
private:
    std::stack<Tesoro> pila;

public:
    // Constructor por defecto
    PilaTesoros() = default;

    // Agregar tesoro al tope
    void push(const Tesoro& t);

    // Obtener tesoro del tope (sin sacarlo)
    Tesoro top() const;

    // Remover tesoro del tope
    void pop();

    // Verificar si está vacía
    bool estaVacia() const;

    // Obtener cantidad de tesoros
    int size() const;

    // Mostrar todos los tesoros
    void mostrar() const;
};

#endif // PILATESOROS_H