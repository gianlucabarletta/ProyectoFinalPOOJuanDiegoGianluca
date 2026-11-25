#include "Cura.h"
#include "Objeto.h"
#include "Personaje.h"
#include<iostream>
#include<vector>

Cura::Cura(int nivel):Objeto(nivel){
    nombre = "Cura";
}

Cura::~Cura(){
    std::cout<<"Has gastado todas tus curas"<<std::endl;
}

bool Cura::usar(Personaje* jugador, std::vector<Personaje*>& enemigos){
    float factor = 1.1f + 0.2f*nivel;
    jugador->setVida(jugador->getVida()*factor);

    std::cout<<"Has recuperado "<<(factor-1)*100<<"%"<<" de la vida que tenias."<<std::endl;

    cantidad -= 1;
    return cantidad > 0;
}
