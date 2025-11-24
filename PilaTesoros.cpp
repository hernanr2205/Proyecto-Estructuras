#include "PilaTesoros.h"
#include <iostream>

/**
 * Agrega un tesoro a la pila
 */
void PilaTesoros::push(const Tesoro& t) {
    pila.push(t);
}

/**
 * Retorna el tesoro sin sacarlo
 */
Tesoro PilaTesoros::top() const {
    return pila.top();
}

/**
 * Elimina el tesoro
 */
void PilaTesoros::pop() {
    if (!pila.empty()) {
        pila.pop();
    }
}

/**
 * Verifica si la pila está vacía
 */
bool PilaTesoros::estaVacia() const {
    return pila.empty();
}

/**
 * Retorna la cantidad de tesoros en la pila
 */
int PilaTesoros::size() const {
    return pila.size();
}

/**
 * Muestra todos los tesoros en la pila
 */
void PilaTesoros::mostrar() const {
    if (pila.empty()) {
        std::cout << "No tienes tesoros en la pila" << std::endl;
        return;
    }


    std::stack<Tesoro> temp = pila;
    std::stack<Tesoro> invertida;

    // Invertir la pila para mostrar de abajo hacia arriba
    while (!temp.empty()) {
        invertida.push(temp.top());
        temp.pop();
    }

    // Mostrar encabezado
    std::cout << "Mira los tesoros que llevas:" << std::endl;
    std::cout << "['#' '#']" << std::endl;

    // Mostrar cada tesoro
    while (!invertida.empty()) {
        Tesoro t = invertida.top();
        std::cout << "['#' '" << t.getSimbolo() << "' '#']" << std::endl;
        invertida.pop();
    }

    std::cout << "['#' '#']" << std::endl;
}