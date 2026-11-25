#ifndef OBJETO_H
#define OBJETO_H
#include <vector>
#include "Personaje.h"
#include "Item.h"



class Objeto : public Item{
protected:
    int cantidad;
public:
    Objeto(int nivel);
    virtual ~Objeto();
    void recoger();
    int getCantidad();


};

#endif