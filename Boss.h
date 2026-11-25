#ifndef BOSS_H
#define BOSS_H
#include "Personaje.h"

//el jefe final, lo que hace es aparecer junto a demás enemigos y sus ataques en lugar de hacer un numero específico de daño, lo que hacen es quitar la mitad de la vida del jugador, por consecuencia, el potenciamiento de la bruja no hace efecto en ellos.  Aparecerán cada 5 habitaciones

class Boss : public Personaje{
    public:
    Boss(int nivel);
    ~Boss();
    float atacar(Personaje* atacado)override;
};

#endif