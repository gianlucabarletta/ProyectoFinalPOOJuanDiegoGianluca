#ifndef BOMBA_H
#define BOMBA_H
#include "Objeto.h"
#include "Personaje.h"

//las bombas atacan a todos los enemigos y según su nivel hacen mas o menos daño

class Bomba : public Objeto{
private:
    float danio;

public:
    Bomba(int nivel);
    ~Bomba();
    bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos)override;
};

#endif