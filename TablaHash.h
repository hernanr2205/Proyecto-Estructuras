#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include <unordered_map>
#include <vector>

class TablaHash {
private:
    std::unordered_map<std::string, int> tabla;

public:
    TablaHash() = default;

    // Nombres que USA Juego.cpp
    void guardarPuntaje(const std::string& nombre, int puntaje);
    int obtenerPuntaje(const std::string& nombre) const;
    bool existeJugador(const std::string& nombre) const;
    void mostrarPuntajeJugador(const std::string& nombre) const;
    std::vector<std::pair<std::string, int>> obtenerPuntajesOrdenados() const;
    void mostrarTodos() const;
};

#endif