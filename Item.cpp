#include "Item.h"
#include <iostream>

Item::Item(int nivel){
    this->nivel = nivel;
}

Item::~Item(){}

std::string Item::getNombre(){
    return nombre;
}

int Item::getNivel() const{
    return nivel;
}