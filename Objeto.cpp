#include "Objeto.h"
#include "Item.h"

#include <iostream>




Objeto::Objeto(int nivel): Item(nivel){
    cantidad = 1;
}

Objeto::~Objeto(){}

void Objeto::recoger(){
    cantidad += 1;
}

int Objeto::getCantidad(){
    return cantidad;
}
