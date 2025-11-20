#include "Jugador.h"

/**
 * Constructor del Jugador
 * Inicializa el jugador con nombre y posición inicial
 * El puntaje y los tesoros empiezan en 0
 */
Jugador::Jugador(const std::string& n, Nodo* posInicial)
    : nombre(n), posicionActual(posInicial), puntaje(0), tesorosRecolectados(0) {
}