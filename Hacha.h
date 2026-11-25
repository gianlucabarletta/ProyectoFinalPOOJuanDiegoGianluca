#ifndef HACHA_H
#define HACHA_H
#include "Item.h"
#include "Arma.h"
#include "Personaje.h"
#include <iostream>

class Hacha : public Arma {
public:
    Hacha(int nivel);
    ~Hacha();
    bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos);

};

#endif