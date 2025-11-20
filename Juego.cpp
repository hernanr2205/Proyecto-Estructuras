#include "Juego.h"
#include <iostream>
#include <cstdlib>

/**
 * Constructor del Juego
 * Inicializa los componentes principales
 */
Juego::Juego() : tablero(nullptr), jugador(nullptr), pilaTesoros(nullptr), tablaPuntajes(nullptr) {
    // Crear el tablero
    tablero = new Tablero();

    // Crear la tabla de puntajes (persiste entre partidas)
    tablaPuntajes = new TablaHash();
}

/**
 * Destructor del Juego
 * Libera toda la memoria
 */
Juego::~Juego() {
    delete tablero;
    delete jugador;
    delete pilaTesoros;
    delete tablaPuntajes;
}

/**
 * Menú principal del juego
 */
void Juego::iniciar() {
    int opcion;

    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "      JUEGO DE LABERINTOS" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Jugar" << std::endl;
        std::cout << "2. Ver tabla de puntajes" << std::endl;
        std::cout << "3. Consultar puntaje de un jugador" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                iniciarNuevoJuego();
                break;
            case 2:
                mostrarPuntajes();
                break;
            case 3:
                consultarPuntajeJugador();
                break;
            case 4:
                std::cout << "\n¡Gracias por jugar!" << std::endl;
                break;
            default:
                std::cout << "\nOpcion invalida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 4);
}

/**
 * Inicia una nueva partida
 * MODIFICADO: El jugador aparece en posición ALEATORIA
 */
void Juego::iniciarNuevoJuego() {
    // Limpiar jugador y pila anteriores si existen
    if (jugador != nullptr) {
        delete jugador;
        jugador = nullptr;
    }
    if (pilaTesoros != nullptr) {
        delete pilaTesoros;
        pilaTesoros = nullptr;
    }

    // Crear nuevo tablero
    delete tablero;
    tablero = new Tablero();

    // Pedir nombre del jugador
    std::string nombre;
    std::cout << "\n========================================" << std::endl;
    std::cout << "Ingrese su nombre: ";
    std::cin >> nombre;

    // ← CAMBIO: Crear jugador en posición ALEATORIA
    std::vector<Nodo*> posicionesValidas = tablero->obtenerPosicionesVacias();

    Nodo* posicionInicial = nullptr;
    if (!posicionesValidas.empty()) {
        int indice = rand() % posicionesValidas.size();
        posicionInicial = posicionesValidas[indice];
        std::cout << "\nPosicion inicial: (" << posicionInicial->getFila()
                  << ", " << posicionInicial->getColumna() << ")" << std::endl;
    } else {
        // Fallback: si no hay posiciones vacías, usar (1,1)
        posicionInicial = tablero->getNodo(1, 1);
        std::cout << "\nPosicion inicial: (1, 1)" << std::endl;
    }

    jugador = new Jugador(nombre, posicionInicial);

    // Crear pila de tesoros
    pilaTesoros = new PilaTesoros();

    // Mostrar instrucciones
    std::cout << "\n========================================" << std::endl;
    std::cout << "       INSTRUCCIONES" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "W - Mover arriba" << std::endl;
    std::cout << "S - Mover abajo" << std::endl;
    std::cout << "A - Mover izquierda" << std::endl;
    std::cout << "D - Mover derecha" << std::endl;
    std::cout << "X - Usar tesoro" << std::endl;
    std::cout << "T - Ver tesoros" << std::endl;
    std::cout << "Q - Abandonar partida" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nObjetivo: Encuentra los 10 tesoros ocultos" << std::endl;
    std::cout << "Puntaje = movimientos (menor es mejor)" << std::endl;
    std::cout << "\nNOTA: Los muros estan OCULTOS. Se revelaran" << std::endl;
    std::cout << "      cuando intentes atravesarlos." << std::endl;
    std::cout << "\nPresione Enter para comenzar...";
    std::cin.ignore();
    std::cin.get();

    // Iniciar el juego
    jugar();
}

/**
 * Loop principal del juego
 */
void Juego::jugar() {
    char accion;

    while (jugador->getTesorosRecolectados() < 10) {
        // Mostrar tablero con jugador
        tablero->mostrarConJugador(jugador->getPosicionActual());

        // Mostrar información
        std::cout << "========================================" << std::endl;
        std::cout << "Jugador: " << jugador->getNombre() << std::endl;
        std::cout << "Puntaje: " << jugador->getPuntaje() << " movimientos" << std::endl;
        std::cout << "Tesoros: " << jugador->getTesorosRecolectados() << "/10" << std::endl;
        std::cout << "Tesoros en pila: " << pilaTesoros->size() << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Accion (W/A/S/D/X/T/Q): ";
        std::cin >> accion;

        // Convertir a mayúscula
        accion = toupper(accion);

        // Procesar acción
        switch (accion) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                moverJugador(accion);
                break;
            case 'X':
                usarTesoro();
                break;
            case 'T':
                pilaTesoros->mostrar();
                std::cout << "\nPresione Enter para continuar...";
                std::cin.ignore();
                std::cin.get();
                break;
            case 'Q':
                std::cout << "\nPartida abandonada." << std::endl;
                return;
            default:
                std::cout << "\nAccion invalida. Use W/A/S/D/X/T/Q" << std::endl;
        }
    }

    // ¡Victoria!
    finalizarPartida();
}

/**
 * Mueve al jugador en una dirección
 * MODIFICADO: Revela los muros cuando el jugador intenta atravesarlos
 */
void Juego::moverJugador(char direccion) {
    Nodo* posicionActual = jugador->getPosicionActual();
    Nodo* destino = nullptr;

    // Obtener nodo destino según la dirección
    switch (direccion) {
        case 'W':
            destino = posicionActual->getArriba();
            break;
        case 'S':
            destino = posicionActual->getAbajo();
            break;
        case 'A':
            destino = posicionActual->getIzquierda();
            break;
        case 'D':
            destino = posicionActual->getDerecha();
            break;
    }

    // Validar movimiento
    if (destino == nullptr) {
        std::cout << "\n¡No puedes moverte en esa direccion!" << std::endl;
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    if (destino->esPared()) {
        std::cout << "\n¡No puedes atravesar una pared!" << std::endl;
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // ← CAMBIO IMPORTANTE: Revelar el muro cuando intentan atravesarlo
    if (destino->esMuro()) {
        destino->setSimbolo('|');  // Revelar el muro visualmente
        std::cout << "\n========================================" << std::endl;
        std::cout << "  ¡Hay un muro bloqueando el camino!" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "El muro ha sido revelado en el mapa." << std::endl;
        std::cout << "Posicion del muro: (" << destino->getFila()
                  << ", " << destino->getColumna() << ")" << std::endl;
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Mover al jugador
    jugador->setPosicionActual(destino);
    jugador->incrementarPuntaje();

    // Marcar casilla como descubierta
    if (!destino->estaDescubierta()) {
        destino->setDescubierta(true);
        destino->setSimbolo(' ');
    }

    // Verificar si hay tesoro
    if (destino->tieneTesoro_()) {
        encontrarTesoro(destino);
    }
}

/**
 * Maneja cuando el jugador encuentra un tesoro
 */
void Juego::encontrarTesoro(Nodo* nodo) {
    // Obtener tipo de tesoro
    std::string tipoString = nodo->getTipoTesoro();
    Tesoro::Tipo tipo = Tesoro::stringATipo(tipoString);
    Tesoro tesoro(tipo);

    // Mostrar mensaje
    std::cout << "\n========================================" << std::endl;
    std::cout << "  ¡Has encontrado un tesoro: " << tesoro.getNombre() << "!" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Posicion: (" << nodo->getFila() << ", " << nodo->getColumna() << ")" << std::endl;

    // Agregar a la pila
    pilaTesoros->push(tesoro);

    // Remover del nodo
    nodo->removerTesoro();

    // Incrementar contador
    jugador->incrementarTesoros();

    std::cout << "Tesoros recolectados: " << jugador->getTesorosRecolectados() << "/10" << std::endl;
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Usa un tesoro de la pila
 */
void Juego::usarTesoro() {
    // Verificar que haya tesoros
    if (pilaTesoros->estaVacia()) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  ¡No tienes tesoros para usar!" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Recolecta tesoros del mapa primero." << std::endl;
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore();
        std::cin.get();
        return;
    }

    // Obtener tesoro del tope
    Tesoro tesoro = pilaTesoros->top();

    std::cout << "\n========================================" << std::endl;
    std::cout << "  Usando tesoro: " << tesoro.getNombre() << std::endl;
    std::cout << "========================================" << std::endl;

    // Aplicar efecto según el tipo
    switch (tesoro.getTipo()) {
        case Tesoro::RUBI:
            aplicarEfectoRubi();
            break;
        case Tesoro::DIAMANTE:
            aplicarEfectoDiamante();
            break;
        case Tesoro::PERLA:
            aplicarEfectoPerla();
            break;
        case Tesoro::AMBAR:
            aplicarEfectoAmbar();
            break;
    }

    // Sacar de la pila
    pilaTesoros->pop();

    // Devolver al tablero
    devolverTesoroAlTablero(tesoro);

    std::cout << "\nEl tesoro ha sido devuelto al tablero." << std::endl;
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Efecto del Rubí: Reduce puntaje a la mitad
 */
void Juego::aplicarEfectoRubi() {
    int puntajeAnterior = jugador->getPuntaje();
    int puntajeNuevo = puntajeAnterior / 2;
    jugador->setPuntaje(puntajeNuevo);

    std::cout << "\n¡Rubi brillante!" << std::endl;
    std::cout << "Efecto: Reduce puntaje a la mitad" << std::endl;
    std::cout << "Puntaje: " << puntajeAnterior << " -> " << puntajeNuevo << " movimientos" << std::endl;
}

/**
 * Efecto del Diamante: Elimina 2 muros aleatorios
 * MODIFICADO: Elimina el muro completamente (visual y lógico)
 */
void Juego::aplicarEfectoDiamante() {
    std::vector<Nodo*> muros = tablero->obtenerMuros();

    if (muros.size() >= 2) {
        // Eliminar primer muro
        int indice1 = rand() % muros.size();
        Nodo* muro1 = muros[indice1];
        muro1->setSimbolo(' ');
        muro1->setMuroOculto(false);

        // Eliminar segundo muro (diferente al primero)
        std::vector<Nodo*> murosRestantes = tablero->obtenerMuros();
        if (!murosRestantes.empty()) {
            int indice2 = rand() % murosRestantes.size();
            Nodo* muro2 = murosRestantes[indice2];
            muro2->setSimbolo(' ');
            muro2->setMuroOculto(false);

            std::cout << "\n¡Diamante poderoso!" << std::endl;
            std::cout << "Efecto: Elimina 2 muros del tablero" << std::endl;
            std::cout << "Muro 1 eliminado en: (" << muro1->getFila() << ", " << muro1->getColumna() << ")" << std::endl;
            std::cout << "Muro 2 eliminado en: (" << muro2->getFila() << ", " << muro2->getColumna() << ")" << std::endl;
        }
    } else if (muros.size() == 1) {
        Nodo* muro = muros[0];
        muro->setSimbolo(' ');
        muro->setMuroOculto(false);
        std::cout << "\n¡Diamante poderoso!" << std::endl;
        std::cout << "Efecto: Elimina 1 muro (solo quedaba uno)" << std::endl;
        std::cout << "Muro eliminado en: (" << muro->getFila() << ", " << muro->getColumna() << ")" << std::endl;
    } else {
        std::cout << "\n¡Diamante poderoso!" << std::endl;
        std::cout << "Efecto: Elimina 2 muros del tablero" << std::endl;
        std::cout << "No quedan muros para eliminar." << std::endl;
    }
}

/**
 * Efecto de la Perla: 50% puntaje a 0, 50% duplicar
 */
void Juego::aplicarEfectoPerla() {
    int aleatorio = rand() % 2;  // 0 o 1
    int puntajeAnterior = jugador->getPuntaje();

    if (aleatorio == 0) {
        // ¡Suerte! Puntaje a 0
        jugador->setPuntaje(0);
        std::cout << "\n¡Perla brillante de la suerte!" << std::endl;
        std::cout << "Efecto: Reduce puntaje a 0 (¡buena suerte!)" << std::endl;
        std::cout << "Puntaje: " << puntajeAnterior << " -> 0 movimientos" << std::endl;
    } else {
        // Mala suerte, duplicar
        int puntajeNuevo = puntajeAnterior * 2;
        jugador->setPuntaje(puntajeNuevo);
        std::cout << "\n¡Perla oscura de la mala suerte!" << std::endl;
        std::cout << "Efecto: Duplica el puntaje (mala suerte)" << std::endl;
        std::cout << "Puntaje: " << puntajeAnterior << " -> " << puntajeNuevo << " movimientos" << std::endl;
    }
}

/**
 * Efecto del Ámbar: Teletransporte a posición aleatoria
 */
void Juego::aplicarEfectoAmbar() {
    std::vector<Nodo*> posicionesVacias = tablero->obtenerPosicionesVacias();

    if (!posicionesVacias.empty()) {
        Nodo* posicionAnterior = jugador->getPosicionActual();

        int indice = rand() % posicionesVacias.size();
        Nodo* nuevaPosicion = posicionesVacias[indice];

        jugador->setPosicionActual(nuevaPosicion);

        std::cout << "\n¡Ambar magico!" << std::endl;
        std::cout << "Efecto: Teletransporte aleatorio" << std::endl;
        std::cout << "Posicion anterior: (" << posicionAnterior->getFila()
                  << ", " << posicionAnterior->getColumna() << ")" << std::endl;
        std::cout << "Nueva posicion: (" << nuevaPosicion->getFila()
                  << ", " << nuevaPosicion->getColumna() << ")" << std::endl;
    } else {
        std::cout << "\n¡Ambar magico!" << std::endl;
        std::cout << "Efecto: Teletransporte aleatorio" << std::endl;
        std::cout << "No hay posiciones disponibles para teletransporte." << std::endl;
    }
}

/**
 * Devuelve un tesoro usado al tablero en posición aleatoria
 */
void Juego::devolverTesoroAlTablero(const Tesoro& tesoro) {
    std::vector<Nodo*> posicionesVacias = tablero->obtenerPosicionesVacias();

    if (!posicionesVacias.empty()) {
        int indice = rand() % posicionesVacias.size();
        Nodo* nodo = posicionesVacias[indice];

        std::string tipoString = Tesoro::tipoAString(tesoro.getTipo());
        nodo->setTesoro(tipoString);
    }
}

/**
 * Finaliza la partida y guarda el puntaje
 */
void Juego::finalizarPartida() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "          ¡FELICIDADES!" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Has encontrado los 10 tesoros" << std::endl;
    std::cout << "\nJugador: " << jugador->getNombre() << std::endl;
    std::cout << "Puntaje final: " << jugador->getPuntaje() << " movimientos" << std::endl;

    // Verificar si es récord personal
    std::string nombre = jugador->getNombre();
    int puntaje = jugador->getPuntaje();

    if (tablaPuntajes->existeJugador(nombre)) {
        int puntajeAnterior = tablaPuntajes->obtenerPuntaje(nombre);
        if (puntaje < puntajeAnterior) {
            std::cout << "\n¡NUEVO RECORD PERSONAL!" << std::endl;
            std::cout << "Puntaje anterior: " << puntajeAnterior << " movimientos" << std::endl;
            std::cout << "Mejoraste por: " << (puntajeAnterior - puntaje) << " movimientos" << std::endl;
        } else if (puntaje == puntajeAnterior) {
            std::cout << "\nIgualaste tu mejor puntaje." << std::endl;
        } else {
            std::cout << "\nNo superaste tu mejor puntaje." << std::endl;
            std::cout << "Tu mejor puntaje: " << puntajeAnterior << " movimientos" << std::endl;
        }
    } else {
        std::cout << "\n¡Primera partida registrada!" << std::endl;
    }

    // Guardar puntaje
    tablaPuntajes->guardarPuntaje(nombre, puntaje);

    std::cout << "========================================" << std::endl;
    std::cout << "\nPresione Enter para volver al menu...";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Muestra la tabla completa de puntajes
 */
void Juego::mostrarPuntajes() {
    std::cout << "\n";
    tablaPuntajes->mostrarTodos();
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

/**
 * Consulta el puntaje de un jugador específico
 */
void Juego::consultarPuntajeJugador() {
    std::string nombre;
    std::cout << "\n========================================" << std::endl;
    std::cout << "Ingrese el nombre del jugador: ";
    std::cin >> nombre;

    if (tablaPuntajes->existeJugador(nombre)) {
        int puntaje = tablaPuntajes->obtenerPuntaje(nombre);
        std::cout << "\n========================================" << std::endl;
        std::cout << "Jugador: " << nombre << std::endl;
        std::cout << "Mejor puntaje: " << puntaje << " movimientos" << std::endl;
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << nombre << " no ha jugado aun" << std::endl;
        std::cout << "========================================" << std::endl;
    }

    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}
