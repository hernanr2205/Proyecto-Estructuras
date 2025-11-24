#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo.h"
#include <vector>

/**
 * Clase Tablero  Lista múltiplemente enlazada que representa el laberinto
 *
 * Características:
 * - Tamaño 9x9 casillas
 * - Cada nodo está conectado con sus 4 vecinos arriba, abajo, izquierda, derecha
 * - Contiene paredes #, espacios vacíos o, muros | y tesoros ocultos
 * - 16 muros colocados aleatoriamente OCULTOS al inicio
 * - 10 tesoros ocultos distribuidos aleatoriamente
 *
 * NO usa arreglos - solo punteros para navegar entre nodos
 */
class Tablero {
private:
    Nodo* inicio;  // Esquina superior izquierda (0,0)
    int filas;
    int columnas;

public:
    // Constructor (crea el tablero)
    Tablero();

    // Destructor (libera memoria)
    ~Tablero();

    // Obtener un nodo específico (navegando desde inicio)
    Nodo* getNodo(int fila, int columna);

    // Obtener el nodo de inicio
    Nodo* getInicio() const { return inicio; }

    // Obtener dimensiones
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }

    // Mostrar el tablero completo
    void mostrar() const;

    // Mostrar el tablero con el jugador en una posición
    void mostrarConJugador(Nodo* posicionJugador) const;

    // Obtener todos los muros del tablero
    std::vector<Nodo*> obtenerMuros();

    // Obtener posiciones vacías (sin muro, sin pared, sin tesoro)
    std::vector<Nodo*> obtenerPosicionesVacias();

    // ⬇️⬇️⬇️ NUEVOS MÉTODOS AGREGADOS ⬇️⬇️⬇️

    // Descubre una casilla (cambia de 'o' a ' ')
    void descubrirCasilla(int fila, int columna);

    // Vuelve a ocultar todas las casillas descubiertas
    void taparCasillas();

    // Obtiene una posición aleatoria válida (sin pared, muro o tesoro)
    Nodo* obtenerPosicionAleatoria();

    // Elimina muros aleatorios (efecto del tesoro Diamante)
    void eliminarMurosAleatorios(int cantidad);

private:
    // Crear todos los nodos del tablero
    void crearNodos();

    // Conectar los nodos entre sí (lista enlazada)
    void enlazarNodos();

    // Colocar las paredes del borde
    void colocarParedes();

    // Colocar 16 muros aleatorios (OCULTOS)
    void colocarMuros();

    // Colocar 10 tesoros aleatorios
    void colocarTesoros();
};

#endif // TABLERO_H