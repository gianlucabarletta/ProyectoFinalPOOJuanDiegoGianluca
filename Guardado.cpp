#include "Guardado.h"
#include "Jugador.h"
#include "Item.h"
#include "Objeto.h"
#include "Espada.h"
#include "Hacha.h"
#include "Debilitador.h"
#include "Cura.h"
#include "Bomba.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

static const char* ENCABEZADO = "POO_RPG_GUARDADO 1";
static const int ESPACIOS = 5;


static Item* crearItemPorNombre(const std::string& nombre, int nivel){
    if (nombre == "Espada")      return new Espada(nivel);
    if (nombre == "Hacha")       return new Hacha(nivel);
    if (nombre == "Debilitador") return new Debilitador(nivel);
    if (nombre == "Cura")        return new Cura(nivel);
    if (nombre == "Bomba")       return new Bomba(nivel);
    return nullptr;
}

static bool nombreItemValido(const std::string& nombre){
    return nombre == "Espada" || nombre == "Hacha" || nombre == "Debilitador" || nombre == "Cura"   || nombre == "Bomba";
}

bool guardarPartida(const std::string& archivo, Jugador* jugador, int habitacion){
    std::ofstream out(archivo);
    if (!out){
        return false;
    }

    out<<ENCABEZADO<<"\n";
    out<<"nombre "<<jugador->getNombre()<<"\n";
    out<<"habitacion "<<habitacion<<"\n";
    out<<"nivel "<<jugador->getNivel()<<"\n";
    out<<"vida "<<jugador->getVida()<<"\n";
    out<<"danio "<<jugador->getDanio()<<"\n";
    out<<"armadura "<<jugador->getArmadura()<<"\n";
    out<<"xp "<<jugador->getXp()<<"\n";

    for (int i = 0; i < ESPACIOS; i++){
        Item* it = jugador->getObInventario(i);
        if (it == nullptr){
            out<<"slot "<<i<<" vacio\n";
            continue;
        }
        
        int cantidad = 1;
        Objeto* obj = dynamic_cast<Objeto*>(it);
        if (obj != nullptr){
            cantidad = obj->getCantidad();
        }
        out<<"slot "<<i<<" "<<it->getNombre()<<" "<<it->getNivel()<<" "<<cantidad<<"\n";
    }
    out<<"FIN\n";

    return out.good();
}

Jugador* cargarPartida(const std::string& archivo, int& habitacion){
    std::ifstream in(archivo);
    if (!in){
        std::cout<<"No se encontro ninguna partida guardada ("<<archivo<<")."<<std::endl;
        return nullptr;
    }


    std::string nombre;
    int hab = 0, nivel = 0;
    float vida = 0, danio = 0, armadura = 0, xp = 0;
    bool completo = false;

    struct SlotGuardado {
        bool ocupado = false;
        std::string nombre;
        int nivel = 0;
        int cantidad = 0;
    };
    std::vector<SlotGuardado> slots(ESPACIOS);

    std::string linea;
    std::getline(in, linea);
    if (!linea.empty() && linea.back() == '\r') linea.pop_back();
    if (linea != ENCABEZADO){
        std::cout<<"El archivo de guardado no es valido o es de otra version."<<std::endl;
        return nullptr;
    }

    int numeroLinea = 1;
    while (std::getline(in, linea)){
        numeroLinea++;
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();
        if (linea.empty()) continue;

        std::istringstream ss(linea);
        std::string clave;
        ss>>clave;
        bool ok = true;

        if (clave == "nombre"){
            ss>>std::ws;
            std::getline(ss, nombre);          
            ok = !nombre.empty();
        } else if (clave == "habitacion"){
            ok = static_cast<bool>(ss>>hab) && hab >= 1;
        } else if (clave == "nivel"){
            ok = static_cast<bool>(ss>>nivel) && nivel >= 1;
        } else if (clave == "vida"){
            ok = static_cast<bool>(ss>>vida) && vida > 0;
        } else if (clave == "danio"){
            ok = static_cast<bool>(ss>>danio) && danio >= 0;
        } else if (clave == "armadura"){
            ok = static_cast<bool>(ss>>armadura) && armadura >= 1;
        } else if (clave == "xp"){
            ok = static_cast<bool>(ss>>xp) && xp >= 0;
        } else if (clave == "slot"){
            int i;
            std::string nombreItem;
            ok = static_cast<bool>(ss>>i>>nombreItem) && i >= 0 && i < ESPACIOS;
            if (ok && nombreItem != "vacio"){
                int nivelItem, cantidad;
                ok = static_cast<bool>(ss>>nivelItem>>cantidad) && nombreItemValido(nombreItem)
                     && nivelItem >= 1 && cantidad >= 1;
                if (ok){
                    slots[i].ocupado = true;
                    slots[i].nombre = nombreItem;
                    slots[i].nivel = nivelItem;
                    slots[i].cantidad = cantidad;
                }
            }
        } else if (clave == "FIN"){
            completo = true;
            break;
        } else {
            ok = false;
        }

        if (!ok){
            std::cout<<"Archivo de guardado danado (linea "<<numeroLinea<<"): \""<<linea<<"\""<<std::endl;
            return nullptr;
        }
    }

    if (!completo || nombre.empty() || hab < 1 || nivel < 1 || vida <= 0){
        std::cout<<"El archivo de guardado esta incompleto."<<std::endl;
        return nullptr;
    }

    
    Jugador* jugador = new Jugador(1, nombre, false);
    jugador->setNivel(nivel);
    jugador->setVida(vida);
    jugador->setDanio(danio);
    jugador->setArmadura(armadura);
    jugador->setXp(xp);

    for (int i = 0; i < ESPACIOS; i++){
        if (!slots[i].ocupado) continue;
        Item* it = crearItemPorNombre(slots[i].nombre, slots[i].nivel);
        Objeto* obj = dynamic_cast<Objeto*>(it);
        if (obj != nullptr){
            for (int c = 1; c < slots[i].cantidad; c++){
                obj->recoger();                  
            }
        }
        jugador->agregarInventario(i, it);
    }

    habitacion = hab;
    return jugador;
}
