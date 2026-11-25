#ifndef HABITACION_H
#define HABITACION_H
#include "Personaje.h"
#include "Soldado.h"
#include "Bruja.h"
#include "Jugador.h"
#include <iostream>
#include <vector>


class Habitacion{
    private:
        int room, nivel;
        std::vector<Personaje*> enemigos;
        Jugador* jugador;
        int numeroEnemigos[2];
        bool habiaBoss;
    public:
        Habitacion(int room, Jugador* jugador, int numeroEnemigos[2]);
        ~Habitacion();
        void maldecirEnemigos(std::vector<Personaje*> enemigos);
        bool combate();
        void recompensas();
        static int calcularNivel(int room);
};

#endif