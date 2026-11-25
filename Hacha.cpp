#include "Item.h"
#include "Arma.h"
#include "Hacha.h"
#include "Personaje.h"
#include <iostream>
#include <vector>

Hacha::Hacha(int nivel) : Arma(nivel){
    nombre = "Hacha";
    danio =  nivel*5;
}

Hacha::~Hacha(){}

bool Hacha::usar(Personaje* jugador, std::vector<Personaje*>& enemigos){
    mostrarEnemigos(enemigos);

    int atacado1, atacado2;
    std::cout<<"Ingrese el numero del enemigo que quiere atacar: ";
    std::cin>>atacado1;

    enemigos[atacado1-1]->recibirDanio(danio+jugador->getDanio());
    return true;
}