#ifndef PERSONAJE_H
#define PERSONAJE_H
#include<iostream>

class Personaje {
    protected:
        std::string nombre;
        float vida, danio;
        int nivel;

    public:
        Personaje(int nivel);
        virtual ~Personaje();
        virtual float atacar(Personaje* atacado) = 0;
        virtual float recibirDanio(float danio);
        virtual void serMaldito();
        std::string getNombre()const;
        float getVida()const;
        float getDanio()const;
        int getNivel()const;
        void setVida(float vida);
};

#endif