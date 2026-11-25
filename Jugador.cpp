#include "Personaje.h"
#include "Jugador.h"
#include<iostream>
#include<vector>
#include "Item.h"
#include "Espada.h"
#include <cmath>

Jugador::Jugador(int nivel, std::string nombre, bool inventarioInicial): Personaje(nivel){
    this->nivel = 1;
    this->nombre = nombre;
    vida = 100;
    danio = 30;
    armadura = 1;
    xp = 0;
    for (int i = 0; i <5; i++){
        inventario[i] = nullptr;
    }
    if (inventarioInicial){
        inventario[0] = new Espada(1);   // al cargar una partida el inventario viene del archivo
    }
}

Jugador::~Jugador(){
    for (Item* it:inventario){
        delete it;
    }
}

float Jugador::atacar(Personaje* atacado){return 0;}

float Jugador::recibirDanio(float danio){
    vida -= danio/armadura;
    if (vida < 0) vida = 0;
    vida = std::round(vida * 100.0f) / 100.0f;
    return vida;
}

Item* Jugador::getObInventario(int i){
    if (i < 0 || i >= 5) return nullptr;
    return inventario[i];
}

void Jugador::incrementarArmadura(){
    armadura += 0.2f;
    std::cout<<"Has incrementado la calidad de tu armadura, ahora el daño que recibes se divide por "<<armadura<<std::endl;
}

void Jugador::agregarInventario(int espacio, Item* nuevoItem){
    if (espacio < 0 || espacio >= 5) return;
    inventario[espacio] = nuevoItem;
}

void Jugador::desecharInventario(int espacio){
    if (espacio < 0 || espacio >= 5) return;
    delete inventario[espacio];
    inventario[espacio] = nullptr;
}


float Jugador::getArmadura(){ 
    return armadura; 
}
float Jugador::getXp(){ 
    return xp; 
}


void Jugador::setArmadura(float armadura){ 
    this->armadura = armadura; 
}
void Jugador::setXp(float xp){ 
    this->xp = xp; 
}
void Jugador::setNivel(int nivel){ 
    this->nivel = nivel; 
}
void Jugador::setDanio(float danio){ 
    this->danio = danio; 
}
