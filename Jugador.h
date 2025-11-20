#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Nodo.h"

/**
 * Clase Jugador - Representa al jugador del juego
 *
 * Almacena:
 * - Nombre del jugador
 * - Posición actual en el tablero (puntero a Nodo)
 * - Puntaje (número de movimientos realizados - menor es mejor)
 * - Cantidad de tesoros recolectados
 */
class Jugador {
private:
    std::string nombre;
    Nodo* posicionActual;
    int puntaje;
    int tesorosRecolectados;

public:
    // Constructor
    Jugador(const std::string& n, Nodo* posInicial);

    // Getters
    std::string getNombre() const { return nombre; }
    Nodo* getPosicionActual() const { return posicionActual; }
    int getPuntaje() const { return puntaje; }
    int getTesorosRecolectados() const { return tesorosRecolectados; }

    // Setters
    void setNombre(const std::string& n) { nombre = n; }
    void setPosicionActual(Nodo* pos) { posicionActual = pos; }
    void setPuntaje(int p) { puntaje = p; }
    void incrementarPuntaje() { puntaje++; }
    void incrementarTesoros() { tesorosRecolectados++; }
};

#endif // JUGADOR_H