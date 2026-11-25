#ifndef GUARDADO_H
#define GUARDADO_H
#include <string>

class Jugador;


bool guardarPartida(const std::string& archivo, Jugador* jugador, int habitacion);


Jugador* cargarPartida(const std::string& archivo, int& habitacion);

#endif
