cmake_minimum_required(VERSION 4.0)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)  # ← Cambio aquí: de 11 a 14
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Todos los archivos están en la raíz del proyecto
set(SOURCES
        main.cpp
        Nodo.cpp
        Tesoro.cpp
        PilaTesoros.cpp
        Jugador.cpp
        Tablero.cpp
        TablaHash.cpp
        Juego.cpp
)

# Headers también en la raíz
set(HEADERS
        Nodo.h
        Tesoro.h
        PilaTesoros.h
        Jugador.h
        Tablero.h
        TablaHash.h
        Juego.h
)

# Ejecutable
add_executable(untitled1 ${SOURCES} ${HEADERS})