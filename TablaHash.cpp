#include "TablaHash.h"
#include <algorithm>
#include <iostream>

/**
 * Guarda o actualiza el puntaje de un jugador
 * Solo actualiza si el nuevo puntaje es MENOR (mejor)
 */
void TablaHash::guardarPuntaje(const std::string& nombre, int puntaje) {
    // Si el jugador no existe, agregarlo
    if (tabla.find(nombre) == tabla.end()) {
        tabla[nombre] = puntaje;
    }
    // Si existe, solo actualizar si el nuevo puntaje es menor
    else if (puntaje < tabla[nombre]) {
        tabla[nombre] = puntaje;
    }
}

/**
 * Obtiene el puntaje de un jugador
 * Retorna -1 si el jugador no existe
 */
int TablaHash::obtenerPuntaje(const std::string& nombre) const {
    auto it = tabla.find(nombre);
    if (it != tabla.end()) {
        return it->second;
    }
    return -1;  // Jugador no encontrado
}

/**
 * Verifica si un jugador existe en la tabla
 */
bool TablaHash::existeJugador(const std::string& nombre) const {
    return tabla.find(nombre) != tabla.end();
}

/**
 * Obtiene todos los puntajes ordenados de menor a mayor
 */
std::vector<std::pair<std::string, int>> TablaHash::obtenerPuntajesOrdenados() const {
    // Copiar todos los elementos a un vector
    std::vector<std::pair<std::string, int>> puntajes;
    for (const auto& par : tabla) {
        puntajes.push_back(par);
    }

    // Ordenar por puntaje (menor a mayor)
    std::sort(puntajes.begin(), puntajes.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });

    return puntajes;
}

/**
 * Muestra todos los puntajes en consola (ordenados)
 */
void TablaHash::mostrarTodos() const {
    if (tabla.empty()) {
        std::cout << "No hay puntajes guardados" << std::endl;
        return;
    }

    auto puntajes = obtenerPuntajesOrdenados();

    std::cout << "\n=== Tabla de Puntajes ===" << std::endl;
    int posicion = 1;
    for (const auto& par : puntajes) {
        std::cout << posicion << ". " << par.first << ": "
                  << par.second << " movimientos" << std::endl;
        posicion++;
    }
    std::cout << "=========================\n" << std::endl;
}