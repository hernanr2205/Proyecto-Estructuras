#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include <unordered_map>
#include <vector>

/**
 * Clase TablaHash - Sistema de almacenamiento de puntajes
 *
 * Usa std::unordered_map para guardar pares (nombre, puntaje)
 * Permite:
 * - Guardar el puntaje de un jugador
 * - Consultar el puntaje de un jugador específico
 * - Obtener todos los puntajes ordenados de menor a mayor
 * - Verificar si un jugador ya tiene puntaje guardado
 *
 * Recuerda: Menor puntaje = mejor (menos movimientos)
 */
class TablaHash {
private:
    std::unordered_map<std::string, int> tabla;

public:
    // Constructor
    TablaHash() = default;

    // Guardar o actualizar el puntaje de un jugador
    void guardarPuntaje(const std::string& nombre, int puntaje);

    // Obtener el puntaje de un jugador
    int obtenerPuntaje(const std::string& nombre) const;

    // Verificar si un jugador ya tiene puntaje guardado
    bool existeJugador(const std::string& nombre) const;

    // Obtener todos los puntajes ordenados de menor a mayor
    std::vector<std::pair<std::string, int>> obtenerPuntajesOrdenados() const;

    // Mostrar todos los puntajes guardados (ordenados)
    void mostrarTodos() const;
};

#endif // TABLAHASH_H