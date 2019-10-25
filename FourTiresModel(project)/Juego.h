//
// Created by leobellaera on 17/10/19.
//

#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "Car.h"
#include "CollisionsProcessor.h"
#include "World.h"

using namespace sf;

#ifndef TESTING_JUEGO_H
#define TESTING_JUEGO_H


class Juego {
public:
    Juego(Vector2i resolucion, std::string titulo);
    void cargarImagenes();
    void set_zoom();
    void iniciar_fisica();
    void actualizar_fisica();
    void gameLoop();
    void dibujar();
    float deg2rad(float deg);
    float rad2deg(float rad);
    void procesar_eventos();

private:
    std::map<std::string, float> config;
    Texture* txt_fondo;
    Texture* txt_auto;

    Sprite* sprite_fondo;
    Sprite* sprite_auto;

    RenderWindow* ventana;
    View* camara;
    Event* evento;

    World* world;
    Car* car;

    float fps;
    Clock* reloj;
    Time* tiempo1;
    float tiempo2;

    bool updatee;

};

#endif //TESTING_JUEGO_H
