#include "Item.h"
#include "Arma.h"
#include "Personaje.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

static int leerEntero(){
    int x;
    if (!(std::cin >> x)){
        if (std::cin.eof()) std::exit(0);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return x;
}

Arma::Arma(int nivel) : Item(nivel){
    danio = 0;
}

Arma::~Arma(){
    std::cout<<"Has soltado tu "<<nombre<<" de nivel "<<nivel<<"."<<std::endl;
}

void Arma::mostrarEnemigos(std::vector<Personaje*>& enemigos){
    std::cout<<"Lista enemigos: "<<std::endl;
    int i = 1;
    for (Personaje* p : enemigos){
        if (p->getVida() <= 0){
            continue;
        }
        std::cout<<i<<": "<<p->getNombre()<<" (vida "<<p->getVida()<<")"<<std::endl;
        i += 1;
    }
}

Personaje* Arma::elegirEnemigo(std::vector<Personaje*>& enemigos){
    std::vector<Personaje*> vivos;
    for (Personaje* p : enemigos){
        if (p->getVida() > 0) vivos.push_back(p);
    }
    if (vivos.empty()) return nullptr;

    mostrarEnemigos(enemigos);
    while (true){
        std::cout<<"Ingrese el numero del enemigo que quiere atacar: ";
        int n = leerEntero();
        if (n >= 1 && n <= (int)vivos.size()){
            return vivos[n-1];
        }
        std::cout<<"Numero invalido."<<std::endl;
    }
}