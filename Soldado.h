#ifndef SOLDADO_H
#define SOLDADO_H
#include "Personaje.h"

//el soldado es un tipo de enemigo simple, solo ataca y recibe daño, sin ninguna cualidad especial, un daño constante de 10 puntos de daño

class Soldado : public Personaje{
public:
    Soldado(int nivel);
    ~Soldado();
    float atacar(Personaje* atacado) override;
};



#endif