#include "Personaje.h"
#include <iostream>

Personaje::Personaje(int nivel){
    this->nivel = nivel;
    vida = 0;
    danio = 0;
}

Personaje::~Personaje(){
    std::cout<<nombre<<" ha sido eliminado"<<std::endl;
}

float Personaje::recibirDanio(float danio){
    vida -= danio;
    if (vida < 0) {
        vida = 0;
    }
    return vida;
}

void Personaje::serMaldito(){
    danio += 5;
}

std::string Personaje::getNombre()const{
    return nombre;
}
float Personaje::getVida()const{
    return vida;
}
float Personaje::getDanio()const{
    return danio;
}
int Personaje::getNivel()const{
    return nivel;
}


void Personaje::setVida(float vida){
    if (vida < 0){
        return;
    }
    this->vida = vida;
}