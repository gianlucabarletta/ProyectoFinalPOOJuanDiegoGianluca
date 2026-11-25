#ifndef BRUJA_H
#define BRUJA_H
#include "Personaje.h"
#include "Soldado.h"
#include <iostream>
#include <vector>


//la bruja potencia el ataque de los demas enemigos en la habitación y por cada enemigo al que potencia, su daño incrementa de igual manera, solo puede haber una bruja como maximo en cada habitación

class Bruja : public Personaje{
private:
    int potenciador;
public:
    Bruja(int nivel);
    ~Bruja();
    float atacar(Personaje* atacado) override;
    void maldicion(std::vector<Personaje*>& enemigos);
    int getPotenciador();

};

#endif