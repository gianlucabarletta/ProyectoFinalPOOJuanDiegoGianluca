#ifndef ARMA_H
#define ARMA_H
#include "Item.h"
#include <iostream>
class Arma : public Item {
protected:
    float danio;
public:
    Arma(int nivel);
    ~Arma();
    void mostrarEnemigos(std::vector<Personaje*>& enemigos);
    Personaje* elegirEnemigo(std::vector<Personaje*>& enemigos);
};

#endif