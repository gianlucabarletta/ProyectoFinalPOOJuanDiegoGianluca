#include "Objeto.h"
#include "Personaje.h"
#include "Debilitador.h"
#include <vector>
#include <iostream>

Debilitador::Debilitador(int nivel) : Objeto(nivel){
    nombre = "Debilitador";
}

Debilitador::~Debilitador(){
    std::cout<<"Has gastado todos tus debilitadores"<<std::endl;
}

bool Debilitador::usar(Personaje* jugador, std::vector<Personaje*>& enemigos){
    int i = 0;
    for (Personaje* p : enemigos){
        p->setVida(p->getVida()/2);
        i += 1;
    }
    jugador->setVida(jugador->getVida()+i*(4+nivel));
    std::cout<<"Has afectado a "<<i<<" enemigos, recuperaste "<< i*(4+nivel)<<" puntos de vida."<<std::endl;

    cantidad -= 1;
    if (cantidad <= 0){
        return false;
    }
    return true;
}


