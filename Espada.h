#ifndef ESPADA_H
#define ESPADA_H
#include "Item.h"
#include "Arma.h"
#include "Personaje.h"
#include <iostream>

class Espada : public Arma {
public:
    Espada(int nivel);
    ~Espada();
    bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos);

};

#endif