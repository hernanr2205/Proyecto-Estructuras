#ifndef TESORO_H
#define TESORO_H

#include <string>

/**
 * Clase Tesoro - Representa un tesoro del juego
 *
 * Tipos de tesoros:
 * - RUBI: Reduce el puntaje a la mitad
 * - DIAMANTE: Elimina 2 muros del tablero
 * - PERLA: 50% reduce puntaje a 0, 50% lo duplica
 * - AMBAR: Teletransporta a una posición aleatoria
 */
class Tesoro {
public:
    enum Tipo {
        RUBI,
        DIAMANTE,
        PERLA,
        AMBAR
    };

private:
    Tipo tipo;

public:
    // Constructor
    Tesoro(Tipo t);

    // Getters
    Tipo getTipo() const { return tipo; }
    std::string getNombre() const;
    char getSimbolo() const;

    // Métodos estáticos
    static Tipo getTipoAleatorio();
    static std::string tipoAString(Tipo t);
    static Tipo stringATipo(const std::string& str);
};

#endif // TESORO_H