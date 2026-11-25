#ifndef DEBILITADOR_H
#define DEBILITADOR_H
#include "Objeto.h"
#include "Personaje.h"
#include <vector>
#include <iostream>

//el debilitador le quita un porcentaje de la vida a todos los enemigos y cura un poco al jugador por cada enemigo al que afecta, los valores del daño y la cura varía segun los niveles.

class Debilitador : public Objeto{
public:
    Debilitador(int nivel);
    ~Debilitador();
    bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos)override;
};

#endif