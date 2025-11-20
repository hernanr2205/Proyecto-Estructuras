#include "Tablero.h"
#include "Tesoro.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * Constructor del Tablero
 * Crea la lista múltiplemente enlazada y la inicializa
 */
Tablero::Tablero() : inicio(nullptr), filas(9), columnas(9) {
    // Inicializar semilla de números aleatorios
    srand(time(nullptr));

    // Construir el tablero
    crearNodos();
    enlazarNodos();
    colocarParedes();
    colocarMuros();
    colocarTesoros();
}

/**
 * Destructor del Tablero
 * Libera toda la memoria de los nodos
 */
Tablero::~Tablero() {
    // Recorrer todo el tablero y liberar cada nodo
    Nodo* filaActual = inicio;

    while (filaActual != nullptr) {
        Nodo* nodoActual = filaActual;
        filaActual = filaActual->getAbajo();  // Avanzar a la siguiente fila

        while (nodoActual != nullptr) {
            Nodo* siguiente = nodoActual->getDerecha();
            delete nodoActual;  // Liberar el nodo
            nodoActual = siguiente;
        }
    }
}

/**
 * Crea todos los nodos del tablero
 */
void Tablero::crearNodos() {
    // Vector temporal para facilitar la creación
    std::vector<std::vector<Nodo*>> nodosTemp(filas, std::vector<Nodo*>(columnas));

    // Crear todos los nodos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            nodosTemp[i][j] = new Nodo(i, j);
        }
    }

    // Guardar el nodo inicial
    inicio = nodosTemp[0][0];

    // Enlazar cada nodo con sus vecinos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            Nodo* actual = nodosTemp[i][j];

            // Conectar con el nodo de arriba
            if (i > 0) {
                actual->setArriba(nodosTemp[i-1][j]);
            }

            // Conectar con el nodo de abajo
            if (i < filas - 1) {
                actual->setAbajo(nodosTemp[i+1][j]);
            }

            // Conectar con el nodo de la izquierda
            if (j > 0) {
                actual->setIzquierda(nodosTemp[i][j-1]);
            }

            // Conectar con el nodo de la derecha
            if (j < columnas - 1) {
                actual->setDerecha(nodosTemp[i][j+1]);
            }
        }
    }
}

/**
 * Método vacío - el enlace se hace en crearNodos()
 */
void Tablero::enlazarNodos() {
    // Ya se hizo en crearNodos()
}

/**
 * Coloca las paredes del borde del tablero
 */
void Tablero::colocarParedes() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // Bordes del tablero
            if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1) {
                Nodo* nodo = getNodo(i, j);
                nodo->setSimbolo('#');
            }
        }
    }
}

/**
 * Coloca 16 muros aleatorios en el tablero (OCULTOS)
 * MODIFICADO: Los muros se marcan pero NO se muestran visualmente
 */
void Tablero::colocarMuros() {
    int murosColocados = 0;

    while (murosColocados < 16) {
        // Generar posición aleatoria (solo en casillas internas)
        int fila = rand() % (filas - 2) + 1;  // 1 a 7
        int col = rand() % (columnas - 2) + 1;  // 1 a 7

        Nodo* nodo = getNodo(fila, col);

        // Solo colocar si la casilla está vacía
        if (nodo->getSimbolo() == 'o' && !nodo->tieneTesoro_()) {
            nodo->setMuroOculto(true);  // ← CAMBIO: marcar como muro oculto
            // NO cambiar el símbolo, dejar como 'o'
            murosColocados++;
        }
    }
}

/**
 * Coloca 10 tesoros aleatorios en el tablero
 */
void Tablero::colocarTesoros() {
    int tesorosColocados = 0;

    while (tesorosColocados < 10) {
        // Generar posición aleatoria (solo en casillas internas)
        int fila = rand() % (filas - 2) + 1;  // 1 a 7
        int col = rand() % (columnas - 2) + 1;  // 1 a 7

        Nodo* nodo = getNodo(fila, col);

        // Solo colocar si la casilla está vacía y no tiene tesoro ni muro
        if (nodo->getSimbolo() == 'o' && !nodo->tieneTesoro_() && !nodo->tieneRealmenteMuro()) {
            // Generar tipo de tesoro aleatorio
            Tesoro::Tipo tipo = Tesoro::getTipoAleatorio();
            std::string nombreTesoro = Tesoro::tipoAString(tipo);
            nodo->setTesoro(nombreTesoro);
            tesorosColocados++;
        }
    }
}

/**
 * Obtiene un nodo específico navegando por la lista enlazada
 */
Nodo* Tablero::getNodo(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return nullptr;
    }

    Nodo* actual = inicio;

    // Navegar hacia abajo (filas)
    for (int i = 0; i < fila; i++) {
        actual = actual->getAbajo();
    }

    // Navegar hacia la derecha (columnas)
    for (int j = 0; j < columna; j++) {
        actual = actual->getDerecha();
    }

    return actual;
}

/**
 * Muestra el tablero completo en consola
 */
void Tablero::mostrar() const {
    Nodo* filaActual = inicio;

    std::cout << "\n";
    while (filaActual != nullptr) {
        Nodo* nodoActual = filaActual;

        while (nodoActual != nullptr) {
            std::cout << nodoActual->getSimbolo() << " ";
            nodoActual = nodoActual->getDerecha();
        }

        std::cout << std::endl;
        filaActual = filaActual->getAbajo();
    }
    std::cout << std::endl;
}

/**
 * Muestra el tablero con el jugador en su posición
 */
void Tablero::mostrarConJugador(Nodo* posicionJugador) const {
    Nodo* filaActual = inicio;

    std::cout << "\n";
    while (filaActual != nullptr) {
        Nodo* nodoActual = filaActual;

        while (nodoActual != nullptr) {
            // Si es la posición del jugador, mostrar 'P'
            if (nodoActual == posicionJugador) {
                std::cout << "P ";
            } else {
                std::cout << nodoActual->getSimbolo() << " ";
            }
            nodoActual = nodoActual->getDerecha();
        }

        std::cout << std::endl;
        filaActual = filaActual->getAbajo();
    }
    std::cout << std::endl;
}

/**
 * Obtiene todos los muros del tablero
 * MODIFICADO: Usa tieneRealmenteMuro() en vez de verificar el símbolo
 */
std::vector<Nodo*> Tablero::obtenerMuros() {
    std::vector<Nodo*> muros;

    Nodo* filaActual = inicio;
    while (filaActual != nullptr) {
        Nodo* nodoActual = filaActual;

        while (nodoActual != nullptr) {
            if (nodoActual->tieneRealmenteMuro()) {  // ← CAMBIO
                muros.push_back(nodoActual);
            }
            nodoActual = nodoActual->getDerecha();
        }

        filaActual = filaActual->getAbajo();
    }

    return muros;
}

/**
 * Obtiene todas las posiciones vacías (sin muro, sin pared, sin tesoro)
 */
std::vector<Nodo*> Tablero::obtenerPosicionesVacias() {
    std::vector<Nodo*> vacias;

    Nodo* filaActual = inicio;
    while (filaActual != nullptr) {
        Nodo* nodoActual = filaActual;

        while (nodoActual != nullptr) {
            // Vacía: no es pared, no es muro, no tiene tesoro
            if (!nodoActual->esPared() && !nodoActual->esMuro() &&
                !nodoActual->tieneTesoro_()) {
                vacias.push_back(nodoActual);
                }
            nodoActual = nodoActual->getDerecha();
        }

        filaActual = filaActual->getAbajo();
    }

    return vacias;
}