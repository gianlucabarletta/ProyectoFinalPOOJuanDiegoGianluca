#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <limits>
#include <cstdlib>
#include "Personaje.h"
#include "Soldado.h"
#include "Bruja.h"
#include "Boss.h"
#include "Jugador.h"
#include "Item.h"
#include "Objeto.h"
#include "Debilitador.h"
#include "Cura.h"
#include "Bomba.h"
#include "Arma.h"
#include "Espada.h"
#include "Hacha.h"
#include "Habitación.h"
#include "Guardado.h"

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


struct OpcionHabitacion {
    int numeroEnemigos[2];   
};

static OpcionHabitacion generarOpcion(int habitacion, std::mt19937& gen){
    OpcionHabitacion op;
    int maxSoldados = 1 + habitacion / 10 + 1;           
    op.numeroEnemigos[0] = std::uniform_int_distribution<int>(1, maxSoldados)(gen);
    op.numeroEnemigos[1] = (habitacion >= 3) ? std::uniform_int_distribution<int>(0, 1)(gen) : 0;
    return op;
}

static bool sonIguales(const OpcionHabitacion& a, const OpcionHabitacion& b){
    return a.numeroEnemigos[0] == b.numeroEnemigos[0] && a.numeroEnemigos[1] == b.numeroEnemigos[1];
}

static std::vector<OpcionHabitacion> generarOpciones(int habitacion, std::mt19937& gen){
    std::vector<OpcionHabitacion> opciones;
    int intentos = 0;
    while (opciones.size() < 3){
        OpcionHabitacion nueva = generarOpcion(habitacion, gen);
        bool repetida = false;
        for (const OpcionHabitacion& o : opciones){
            if (sonIguales(o, nueva)) repetida = true;
        }
        
        if (!repetida || intentos >= 30){
            opciones.push_back(nueva);
        }
        intentos++;
    }
    return opciones;
}

static void mostrarOpciones(int habitacion, const std::vector<OpcionHabitacion>& opciones){
    std::cout<<"\n===== HABITACION "<<habitacion<<" (nivel "<<Habitacion::calcularNivel(habitacion)<<") ====="<<std::endl;
    std::cout<<"Elige por que puerta quieres entrar:"<<std::endl;
    for (size_t i = 0; i < opciones.size(); i++){
        std::cout<<"  "<<i+1<<") ";
        std::cout<<opciones[i].numeroEnemigos[0]<<" Soldado(s)";
        if (opciones[i].numeroEnemigos[1] >= 1){
            std::cout<<", 1 Bruja";
        }
        if (habitacion % 5 == 0){
            std::cout<<", 1 JEFE";      
        }
        std::cout<<std::endl;
    }
}

static int elegirOpcion(int cantidad){
    while (true){
        std::cout<<"Tu eleccion: ";
        int n = leerEntero();
        if (n >= 1 && n <= cantidad) return n - 1;
        std::cout<<"Opcion invalida."<<std::endl;
    }
}

static const char* ARCHIVO_GUARDADO = "partida.txt";

int main(){
    int respuesta, habitacion = 1;
    Jugador* jugador = nullptr;
    std::cout<<"Bienvenido al juego bla bla"<<std::endl;
    while (true){
        std::cout<<"1. Continuar\n2. Nueva partida\n";
        respuesta = leerEntero();
        if (respuesta == 2){
            std::string nombre;
            std::cout<<"Ingrese el nombre de su jugador: ";
            std::cin>>nombre;
            jugador = new Jugador(1, nombre);
            break;
        } else if (respuesta == 1){
            jugador = cargarPartida(ARCHIVO_GUARDADO, habitacion);
            if (jugador != nullptr){
                std::cout<<"Partida cargada. Bienvenido de vuelta, "<<jugador->getNombre()<<"."<<std::endl;
                break;
            }
            std::cout<<"Aun no hay partidas guardadas."<<std::endl;
        } else {
            std::cout<<"Ingrese una opcion valida."<<std::endl;
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    while (true){
        
        std::vector<OpcionHabitacion> opciones = generarOpciones(habitacion, gen);
        mostrarOpciones(habitacion, opciones);
        int elegida = elegirOpcion((int)opciones.size());
        int numeroEnemigos[2] = {opciones[elegida].numeroEnemigos[0], opciones[elegida].numeroEnemigos[1]};

        bool gano;
        {
            Habitacion habi(habitacion, jugador, numeroEnemigos);
            gano = habi.combate();
            if (gano){
                habi.recompensas();
            }
        }
        if (!gano){
            std::cout<<"Has muerto en la habitación "<<habitacion<<". Fin del juego."<<std::endl;
            break;
        }

        
        std::cout<<"\n1. Siguiente habitación\n2. Salir\n";
        if (leerEntero() == 2){
            break;
        }

        habitacion += 1;
    }
    delete jugador;   

    return 0;
}
