#ifndef CURA_H
#define CURA_H
#include "Objeto.h"
#include "Personaje.h"

//las curas incrementan la salud del jugador en un porcentaje que varía según el nivel del objeto.

class Cura : public Objeto{
public:
    Cura(int nivel);
    ~Cura();
    bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos)override;
};

#endif