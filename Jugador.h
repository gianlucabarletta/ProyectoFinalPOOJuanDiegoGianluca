#ifndef JUGADOR_H
#define JUGADOR_H
#include "Personaje.h"
#include<iostream>
#include<vector>
#include "Item.h"

class Jugador : public Personaje{
private:
    float armadura, xp;
    Item* inventario[5];
public:
    Jugador(int nivel, std::string nombre, bool inventarioInicial = true);
    ~Jugador();
    float atacar(Personaje* atacado);
    float recibirDanio(float danio)override;
    float getArmadura();
    float getXp();
    void setArmadura(float armadura);
    void setXp(float xp);
    void setNivel(int nivel);
    void setDanio(float danio);
    Item* getObInventario(int i);
    void incrementarArmadura();
    void agregarInventario(int espacio, Item* nuevoItem);
    void desecharInventario(int espacio);

};

#endif