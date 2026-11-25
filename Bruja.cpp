#include "Personaje.h"
#include "Soldado.h"
#include "Bruja.h"
#include <iostream>
#include <vector>

Bruja::Bruja(int nivel) : Personaje(nivel){
    nombre = "Bruja";
    this->vida = 50;
    this->danio = 10;
    this->potenciador = 1;
}

Bruja::~Bruja(){}

float Bruja::atacar(Personaje* atacado){
    float danioFinal = danio + 2*potenciador;
    float vidaRes = atacado->recibirDanio(danioFinal);
    return vidaRes;
}

void Bruja::maldicion(std::vector<Personaje*>& enemigos){
    int i = 0;
    for (Personaje* p : enemigos){
        {
            if (p == this){
                continue;
            }
        }
        i += 1;
        p->serMaldito();
    }
    potenciador +=i;
}

int Bruja::getPotenciador(){
    return potenciador;
}