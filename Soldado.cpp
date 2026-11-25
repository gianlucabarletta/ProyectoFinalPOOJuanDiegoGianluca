#include "Personaje.h"
#include "Soldado.h"
#include <iostream>


Soldado::Soldado(int nivel) : Personaje(nivel){
    nombre = "Soldado";
    vida = 20+nivel*20;
    danio = nivel*10;
}



Soldado::~Soldado(){}

float Soldado::atacar(Personaje* atacado){
    float vidaRes = atacado->recibirDanio(danio);
    return vidaRes;
}
