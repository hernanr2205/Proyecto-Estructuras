#ifndef NODO_H
#define NODO_H

#include <string>

/**
 * Clase Nodo - Representa una casilla del tablero
 *
 * Cada nodo conoce:
 * - Su posición (fila, columna)
 * - Su contenido (símbolo)
 * - Si ha sido descubierta
 * - Si contiene un tesoro (oculto)
 * - Sus 4 vecinos (arriba, abajo, izquierda, derecha)
 */
class Nodo {
private:
    int fila;
    int columna;
    char simbolo;
    bool descubierta;
    bool tieneTesoro;
    std::string tipoTesoro;
    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;
    bool esMuroReal;  // NUEVO: indica si hay un muro oculto

public:
    // Constructor
    Nodo(int f, int c);

    // Getters de posición
    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    // Getters y setters de símbolo
    char getSimbolo() const { return simbolo; }
    void setSimbolo(char s) { simbolo = s; }

    // Getters y setters de descubierta
    bool estaDescubierta() const { return descubierta; }
    void setDescubierta(bool d) { descubierta = d; }

    // Métodos de tesoro
    bool tieneTesoro_() const { return tieneTesoro; }
    std::string getTipoTesoro() const { return tipoTesoro; }
    void setTesoro(const std::string& tipo);
    void removerTesoro();

    // Getters y setters de vecinos
    Nodo* getArriba() const { return arriba; }
    Nodo* getAbajo() const { return abajo; }
    Nodo* getIzquierda() const { return izquierda; }
    Nodo* getDerecha() const { return derecha; }

    void setArriba(Nodo* n) { arriba = n; }
    void setAbajo(Nodo* n) { abajo = n; }
    void setIzquierda(Nodo* n) { izquierda = n; }
    void setDerecha(Nodo* n) { derecha = n; }

    // Métodos de verificación
    bool esPared() const { return simbolo == '#'; }
    bool esMuro() const { return esMuroReal; }  // MODIFICADO
    bool esVacio() const { return simbolo == 'o' || simbolo == ' '; }

    // NUEVO: para manejar muros ocultos
    bool tieneRealmenteMuro() const { return esMuroReal; }
    void setMuroOculto(bool valor) { esMuroReal = valor; }
};

#endif // NODO_H