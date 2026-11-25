#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <string>
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

static void eliminarMuertos(std::vector<Personaje*>& v){
    for (auto it = v.begin(); it != v.end(); ){
        if ((*it)->getVida() <= 0){
            delete *it;
            it = v.erase(it);
        } else {
            ++it;
        }
    }
}

static void mostrarInventario(Jugador* jugador){
    std::cout<<"Inventario"<<std::endl;
    for (int i = 0; i < 5; i++){
        Item* it = jugador->getObInventario(i);
        if (it == nullptr){
            std::cout<<i+1<<") espacio vacio"<<std::endl;
            continue;
        }
        std::cout<<i+1<<") "<<it->getNombre()<<" (nivel "<<it->getNivel()<<")";
        Objeto* obj = dynamic_cast<Objeto*>(it);
        if (obj != nullptr){
            std::cout<<" x"<<obj->getCantidad();
        }
        std::cout<<std::endl;
    }
}

static std::string nombreItem(int tipo){
    switch (tipo){
        case 1: return "Espada";
        case 2: return "Hacha";
        case 3: return "Debilitador";
        case 4: return "Cura";
        default: return "Bomba";
    }
}

static Item* crearItem(int tipo, int nivel){
    switch (tipo){
        case 1: return new Espada(nivel);
        case 2: return new Hacha(nivel);
        case 3: return new Debilitador(nivel);
        case 4: return new Cura(nivel);
        default: return new Bomba(nivel);
    }
}

int Habitacion::calcularNivel(int room){
    if (room < 10) {
        return 1;
    }
    if (room < 20) {
        return 2;
    }
    if (room < 30) {
        return 3;
    }
    return 4;
}

Habitacion::Habitacion(int room, Jugador* jugador, int numeroEnemigos[2]){
    this->room = room;
    this->jugador = jugador;
    nivel = calcularNivel(room);

    
    for (int i = 0; i < 2; i++){
        this->numeroEnemigos[i] = numeroEnemigos[i];
    }

    
    for (int i = 0; i < numeroEnemigos[0]; i++){
        enemigos.push_back(new Soldado(nivel));
    }
    if (numeroEnemigos[1] >= 1){
        enemigos.push_back(new Bruja(nivel));
    }

    std::cout<<"//////////////INGRESANDO A LA HABITACION "<<room<<"\\\\\\\\\\\\\\"<<std::endl;
    std::cout<<std::endl;

    
    if (room % 5 == 0){
        enemigos.push_back(new Boss(nivel));
        std::cout<<"HAS ENCONTRADO A UN JEFE, BUENA SUERTE"<<std::endl;
        habiaBoss = true;
    } else {
        habiaBoss = false;
    }
}


Habitacion::~Habitacion(){
    std::cout<<"Has salido de la habitación "<<room<<std::endl;
    for (Personaje* p: enemigos){
        delete p;
    }
}

void Habitacion::maldecirEnemigos(std::vector<Personaje*> enemigos){
    for (Personaje* p : enemigos){
        Bruja* esbruja = dynamic_cast<Bruja*>(p);
        if (esbruja != nullptr){
            esbruja->maldicion(enemigos);
        }
    }
}

bool Habitacion::combate(){
    maldecirEnemigos(enemigos);
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true){
        std::cout<<"\n--- Tu vida: "<<jugador->getVida()<<" ---"<<std::endl;
        mostrarInventario(jugador);
        std::cout<<"¿Que objeto de tu inventario vas a usar?"<<std::endl;

        
        int objetoUsar;
        while (true){
            objetoUsar = leerEntero() - 1;
            if (objetoUsar < 0 || objetoUsar >= 5){
                std::cout<<"Ese espacio en tu inventario no existe, ingresa nuevamente: "<<std::endl;
            } else if (jugador->getObInventario(objetoUsar) == nullptr){
                std::cout<<"En ese espacio no tienes nada en tu inventario, ingresa nuevamente: "<<std::endl;
            } else {
                break;
            }
        }

        if (!(jugador->getObInventario(objetoUsar)->usar(jugador, enemigos))){
            jugador->desecharInventario(objetoUsar);
        }

        eliminarMuertos(enemigos);
        if (enemigos.empty()){
            return true;
        }

        
        std::vector<Personaje*> atacantes = enemigos;
        std::shuffle(atacantes.begin(), atacantes.end(), gen);
        size_t cuantos = std::min<size_t>(2, atacantes.size());
        for (size_t i = 0; i < cuantos; i++){
            atacantes[i]->atacar(jugador);
            if (jugador->getVida() <= 0){
                return false;
            }
        }
    }
}

void Habitacion::recompensas(){
    if (habiaBoss){
        jugador->incrementarArmadura();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, 5);
    int tipo = distrib(gen);
    std::string nombre = nombreItem(tipo);

    std::cout<<"\nHas encontrado: "<<nombre<<" de nivel "<<nivel<<". ¿Quieres tomarlo? (si/no): ";
    std::string respuesta;
    std::cin>>respuesta;
    std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (respuesta != "si" && respuesta != "sí" && respuesta != "s"){
        return;
    }

    
    for (int i = 0; i < 5; i++){
        Objeto* obj = dynamic_cast<Objeto*>(jugador->getObInventario(i));
        if (obj != nullptr && obj->getNombre() == nombre && obj->getNivel() == nivel){
            obj->recoger();
            std::cout<<"Ahora tienes x"<<obj->getCantidad()<<" "<<nombre<<"."<<std::endl;
            return;
        }
    }

    
    int espacio = -1;
    for (int i = 0; i < 5; i++){
        if (jugador->getObInventario(i) == nullptr){
            espacio = i;
            break;
        }
    }

    
    if (espacio == -1){
        std::cout<<"No tienes espacio en tu inventario, elige un Item del que deshacerte:"<<std::endl;
        mostrarInventario(jugador);
        while (true){
            std::cout<<"Que objeto quieres eliminar (0 para no tomar el nuevo): ";
            int n = leerEntero();
            if (n == 0){
                return;
            } else if (n < 1 || n > 5){
                std::cout<<"Ese numero de espacio no existe en tu inventario, elige otro."<<std::endl;
            } else {
                espacio = n - 1;
                jugador->desecharInventario(espacio);
                break;
            }
        }
    }

    jugador->agregarInventario(espacio, crearItem(tipo, nivel));
}