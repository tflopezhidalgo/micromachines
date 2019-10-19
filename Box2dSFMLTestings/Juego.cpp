//
// Created by leobellaera on 17/10/19.
//

#include "Juego.h"
#include "Border.h"
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

Juego::Juego(Vector2i resolucion, std::string titulo) {

    fps = 60.f;
    tiempoFrame = 1.f / fps;

    ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
    ventana->setFramerateLimit(fps);

    evento = new Event;

    cargarImagenes();
    set_zoom();
    iniciar_fisica();
    gameLoop();
}

void Juego::cargarImagenes() {
    txt_auto = new Texture;
    txt_fondo = new Texture;
    txt_borde = new Texture;

    txt_auto->loadFromFile("auto.png");
    txt_fondo->loadFromFile("fondo.jpg");
    txt_borde->loadFromFile("borde3.png");

    sprite_auto = new Sprite;
    sprite_fondo = new Sprite;
    sprite_borde = new Sprite;

    sprite_auto->setTexture(*txt_auto);
    sprite_fondo->setTexture(*txt_fondo);
    sprite_borde->setTexture(*txt_borde);

    sprite_auto->setOrigin({txt_auto->getSize().x / 2.f, txt_auto->getSize().y / 2.f});
    sprite_fondo->setOrigin({txt_fondo->getSize().x / 2.f, txt_fondo->getSize().y / 2.f});
    sprite_borde->setOrigin({txt_borde->getSize().x / 2.f, txt_borde->getSize().y / 2.f});

    sprite_fondo->setPosition({50.f, 50.f});
    sprite_fondo->setScale({100.f/txt_fondo->getSize().x, 100.f/txt_fondo->getSize().y});

    // Scales defined in Car.cpp
    sprite_auto->setScale({3.f / txt_auto->getSize().x, 1.5f / txt_fondo->getSize().y });

    sprite_borde->setPosition({50.f, 50.f});
    sprite_borde->setScale({100.f / txt_borde->getSize().x, 100.f / txt_borde->getSize().y });
}

void Juego::set_zoom() {
    camara = new View;
    camara->setSize({100.f, 100.f});
    camara->setCenter({50.f, 50.f});
    ventana->setView(*camara);
}

void Juego::iniciar_fisica() {
    mundo = new b2World(b2Vec2(0.f, 0.f));
    car = new Car(mundo);
    borde = new Border(mundo, 50,50);
}

void Juego::gameLoop() {
    while (ventana->isOpen()) {
        ventana->clear();
        procesar_eventos();
        actualizar_fisica();
        dibujar();
        ventana->display();
    }
}

void Juego::actualizar_fisica() {
    mundo->Step(tiempoFrame, 8, 8);
    mundo->ClearForces();
}

void Juego::dibujar() {
    ventana->draw(*sprite_fondo);

    sprite_auto->setPosition({car->getPosition().x, car->getPosition().y});
    sprite_auto->setRotation(rad2deg(car->getAngle()));
    ventana->draw(*sprite_auto);

    ventana->draw(*sprite_borde);
}

float Juego::deg2rad(float deg) {
    float pi = 3.14;
    return deg*pi / 180;
}

float Juego::rad2deg(float rad) {
    float pi = 3.14;
    return rad/pi * 180;
}

void Juego::procesar_eventos() {
    car->updateFriction();
    while (ventana->pollEvent(*evento)) {
        switch (evento->type) {
            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    car->update(LEFT);
                }
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    car->update(RIGHT);
                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    car->update(UP);
                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    car->update(DOWN);
                }
        }
    }
}
