#include "Bomba.h"
#include "Personaje.h"
#include "Objeto.h"
#include<iostream>
#include<vector>

Bomba::Bomba(int nivel): Objeto(nivel){
    nombre = "Bomba";
    danio = 15;
}

Bomba::~Bomba(){
    std::cout<<"Has gastado todas tus bombas"<<std::endl;
}

bool Bomba::usar(Personaje* jugador, std::vector<Personaje*>& enemigos){
    float total = danio + nivel*5;
    for (Personaje* p: enemigos){
        p->recibirDanio(total);
    }
    std::cout<<"La bomba hace "<<total<<" de dano a todos los enemigos."<<std::endl;

    cantidad -= 1;
    return cantidad > 0;
}