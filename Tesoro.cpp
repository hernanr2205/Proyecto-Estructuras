#include "Tesoro.h"
#include <cstdlib>

/**
 * Constructor del Tesoro
 */
Tesoro::Tesoro(Tipo t) : tipo(t) {
}

/**
 * Obtiene el nombre completo del tesoro
 */
std::string Tesoro::getNombre() const {
    switch (tipo) {
        case RUBI: return "Rubi";
        case DIAMANTE: return "Diamante";
        case PERLA: return "Perla";
        case AMBAR: return "Ambar";
        default: return "Desconocido";
    }
}

/**
 * Obtiene el símbolo del tesoro
 */
char Tesoro::getSimbolo() const {
    switch (tipo) {
        case RUBI: return 'R';
        case DIAMANTE: return 'D';
        case PERLA: return 'P';
        case AMBAR: return 'A';
        default: return '?';
    }
}

/**
 * Genera un tipo de tesoro aleatorio
 */
Tesoro::Tipo Tesoro::getTipoAleatorio() {
    int aleatorio = rand() % 4;
    return static_cast<Tipo>(aleatorio);
}

/**
 * Convierte un Tipo a string
 */
std::string Tesoro::tipoAString(Tipo t) {
    switch (t) {
        case RUBI: return "Rubi";
        case DIAMANTE: return "Diamante";
        case PERLA: return "Perla";
        case AMBAR: return "Ambar";
        default: return "Desconocido";
    }
}

/**
 * Convierte un string a Tipo
 */
Tesoro::Tipo Tesoro::stringATipo(const std::string& str) {
    if (str == "Rubi") return RUBI;
    if (str == "Diamante") return DIAMANTE;
    if (str == "Perla") return PERLA;
    if (str == "Ambar") return AMBAR;
    return RUBI; // Por defecto
}