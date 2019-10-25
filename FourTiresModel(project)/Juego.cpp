//
// Created by leobellaera on 17/10/19.
//

#include <iostream>
#include "Juego.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

Juego::Juego(Vector2i resolucion, std::string titulo) {
    updatee = false;

    fps = 60.f;

    ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
    ventana->setFramerateLimit(fps);

    evento = new Event;

    reloj = new Clock();
    tiempo1 = new Time();

    config.emplace("maxForwardSpeed", 800.f);
    config.emplace("maxBackwardSpeed", 40.f);
    config.emplace("maxDriveForce", 400.f);
    config.emplace("maxLateralImpulse", 40.f);
    config.emplace("framesPerSecond", 60.f);

    world = new World(100.f, 100.f, config);
    car = world->addCar(50.f, 50.f);

    cargarImagenes();
    set_zoom();
    iniciar_fisica();
    gameLoop();
}

void Juego::cargarImagenes() {
    txt_auto = new Texture;
    txt_fondo = new Texture;

    txt_auto->loadFromFile("auto.png");
    txt_fondo->loadFromFile("fondo.jpg");

    sprite_auto = new Sprite;
    sprite_fondo = new Sprite;

    sprite_auto->setTexture(*txt_auto);
    sprite_fondo->setTexture(*txt_fondo);

    sprite_auto->setOrigin({txt_auto->getSize().x / 2.f, txt_auto->getSize().y / 2.f});
    sprite_fondo->setOrigin({txt_fondo->getSize().x / 2.f, txt_fondo->getSize().y / 2.f});

    sprite_fondo->setPosition({50.f, 50.f});
    sprite_fondo->setScale({500.f/txt_fondo->getSize().x, 500.f/txt_fondo->getSize().y});

    // Scales defined in Car.cpp
    sprite_auto->setScale({12.f / txt_auto->getSize().x, 20.f / txt_fondo->getSize().y });
}

void Juego::set_zoom() {
    camara = new View;
    camara->setSize({500.f, 500.f});
    camara->setCenter({50.f, 50.f});
    ventana->setView(*camara);
}

void Juego::iniciar_fisica() {

}

void Juego::gameLoop() {
    while (ventana->isOpen()) {
        *tiempo1 = reloj->getElapsedTime();
        if (tiempo2 + (1.f/fps) < tiempo1->asSeconds()) {
            ventana->clear();
            procesar_eventos();
            actualizar_fisica();
            dibujar();
            ventana->display();
        }
    }
}

void Juego::actualizar_fisica() {
    if (!updatee) car->move(0);
    //QUE EL AUTO RECIBA SU CARBODY POR PUNTERO!
    world->step();
    updatee = false;
}

void Juego::dibujar() {
    ventana->draw(*sprite_fondo);
    sprite_auto->setPosition({car->getPosition().x, car->getPosition().y});
    sprite_auto->setRotation(rad2deg(car->getAngle()));
    ventana->draw(*sprite_auto);
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
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            car->move(LEFT);
            updatee = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            car->move(RIGHT);
            updatee = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            car->move(UP);
            updatee = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            car->move(DOWN);
            updatee = true;
        }
}
