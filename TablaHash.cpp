#include "TablaHash.h"
#include <iostream>
#include <algorithm>

void TablaHash::guardarPuntaje(const std::string& nombre, int puntaje) {
    auto it = tabla.find(nombre);

    if (it != tabla.end()) {
        if (puntaje < it->second) {
            std::cout << "\n¡Nuevo récord personal!" << std::endl;
            std::cout << "Puntaje anterior: " << it->second
                      << " -> Nuevo puntaje: " << puntaje << std::endl;
            it->second = puntaje;
        } else {
            std::cout << "\nNo superaste tu mejor puntaje (" << it->second << ")" << std::endl;
        }
    } else {
        tabla[nombre] = puntaje;
        std::cout << "\nPrimer puntaje registrado: " << puntaje << " puntos" << std::endl;
    }
}

int TablaHash::obtenerPuntaje(const std::string& nombre) const {
    auto it = tabla.find(nombre);
    if (it != tabla.end()) {
        return it->second;
    }
    return -1;
}

bool TablaHash::existeJugador(const std::string& nombre) const {
    return tabla.find(nombre) != tabla.end();
}

void TablaHash::mostrarPuntajeJugador(const std::string& nombre) const {
    if (existeJugador(nombre)) {
        int puntaje = obtenerPuntaje(nombre);
        std::cout << "\n=== PUNTAJE DEL JUGADOR ===" << std::endl;
        std::cout << "Jugador: " << nombre << std::endl;
        std::cout << "Mejor puntaje: " << puntaje << " puntos" << std::endl;
        std::cout << "===========================" << std::endl;
    } else {
        std::cout << "\nEl jugador '" << nombre << "' no tiene puntajes registrados." << std::endl;
    }
}

std::vector<std::pair<std::string, int>> TablaHash::obtenerPuntajesOrdenados() const {
    std::vector<std::pair<std::string, int>> puntajes;

    for (const auto& par : tabla) {
        puntajes.push_back(par);
    }

    std::sort(puntajes.begin(), puntajes.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second < b.second;
              });

    return puntajes;
}

void TablaHash::mostrarTodos() const {
    if (tabla.empty()) {
        std::cout << "\n=== TABLA DE PUNTAJES ===" << std::endl;
        std::cout << "No hay puntajes registrados aún." << std::endl;
        std::cout << "=========================" << std::endl;
        return;
    }

    std::vector<std::pair<std::string, int>> puntajes = obtenerPuntajesOrdenados();

    std::cout << "\n==========================================" << std::endl;
    std::cout << "         TABLA DE PUNTAJES" << std::endl;
    std::cout << "   (Menor puntaje = Mejor jugador)" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "  #  |  Jugador              |  Puntaje" << std::endl;
    std::cout << "-----|------------------------|----------" << std::endl;

    int posicion = 1;
    for (const auto& par : puntajes) {
        std::cout << "  ";
        if (posicion < 10) std::cout << " ";
        std::cout << posicion << "  |  " << par.first;

        int espacios = 21 - par.first.length();
        for (int i = 0; i < espacios; i++) {
            std::cout << " ";
        }

        std::cout << "|  " << par.second << std::endl;
        posicion++;
    }

    std::cout << "==========================================" << std::endl;
}