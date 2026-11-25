#include "Personaje.h"
#include "Boss.h"
#include <iostream>

Boss::Boss(int nivel): Personaje(nivel){
    nombre = "|--JEFE--|";
    vida=100;
    danio = 0;
}

Boss::~Boss(){
    std::cout<<"Has eliminado al boss, bien hecho";
}

float Boss::atacar(Personaje* atacado){
    float danioFinal = atacado->getVida() / 2;
    return atacado->recibirDanio(danioFinal);
}