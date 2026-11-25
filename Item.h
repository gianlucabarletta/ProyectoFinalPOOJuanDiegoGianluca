#ifndef ITEM_H
#define ITEM_H
#include <vector>
#include "Personaje.h"

class Item{
protected:
    std::string nombre;
    int nivel;
public:
    Item(int nivel);
    virtual ~Item();
    virtual bool usar(Personaje* jugador, std::vector<Personaje*>& enemigos) = 0;
    std::string getNombre();
    int getNivel() const;

};

#endif