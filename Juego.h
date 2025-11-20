#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include "Jugador.h"
#include "PilaTesoros.h"
#include "TablaHash.h"
#include <string>

/**
 * Clase Juego - Motor principal del juego
 *
 * Coordina todos los componentes:
 * - Tablero (lista enlazada)
 * - Jugador (posición y puntaje)
 * - Pila de tesoros
 * - Tabla hash de puntajes
 *
 * Maneja la lógica del juego, movimientos, efectos de tesoros y menús
 */
class Juego {
private:
    Tablero* tablero;
    Jugador* jugador;
    PilaTesoros* pilaTesoros;
    TablaHash* tablaPuntajes;

public:
    // Constructor
    Juego();

    // Destructor
    ~Juego();

    // Iniciar el juego (menú principal)
    void iniciar();

    // Iniciar una nueva partida
    void iniciarNuevoJuego();

    // Loop principal del juego
    void jugar();

    // Mover al jugador (W, A, S, D)
    void moverJugador(char direccion);

    // Manejar cuando el jugador encuentra un tesoro
    void encontrarTesoro(Nodo* nodo);

    // Usar un tesoro de la pila (tecla X)
    void usarTesoro();

    // Efectos de cada tesoro
    void aplicarEfectoRubi();
    void aplicarEfectoDiamante();
    void aplicarEfectoPerla();
    void aplicarEfectoAmbar();

    // Devolver tesoro usado al tablero
    void devolverTesoroAlTablero(const Tesoro& tesoro);

    // Finalizar partida y guardar puntaje
    void finalizarPartida();

    // Mostrar todos los puntajes
    void mostrarPuntajes();

    // Consultar puntaje de un jugador específico
    void consultarPuntajeJugador();
};

#endif // JUEGO_H