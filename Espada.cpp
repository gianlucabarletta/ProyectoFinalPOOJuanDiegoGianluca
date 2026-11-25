#include "Item.h"
#include "Arma.h"
#include "Espada.h"
#include "Personaje.h"
#include <iostream>
#include <vector>

Espada::Espada(int nivel) : Arma(nivel){
    nombre = "Espada";
    danio =  nivel*5;
}

Espada::~Espada(){}

bool Espada::usar(Personaje* jugador, std::vector<Personaje*>& enemigos){
    float total = danio + jugador->getDanio();

    Personaje* objetivo = elegirEnemigo(enemigos);
    if (objetivo == nullptr) {
        return true;
    }
    objetivo->recibirDanio(total);
    std::cout<<"Golpeas a "<<objetivo->getNombre()<<" por "<<total<<" de dano."<<std::endl;

    objetivo = elegirEnemigo(enemigos);   // nullptr si ya no queda nadie vivo
    if (objetivo != nullptr){
        objetivo->recibirDanio(total);
        std::cout<<"Golpeas a "<<objetivo->getNombre()<<" por "<<total<<" de dano."<<std::endl;
    }
    return true;
}