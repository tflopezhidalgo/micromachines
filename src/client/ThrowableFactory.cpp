#include "ThrowableFactory.h"
#include "BaseSprite.h"
#include "Throwable.h"

#define ROCK "ROCK"
#define MUD "MUD"
#define HEALTH "HEALTH"
#define OIL "OIL"
#define BOOST "BOOST"

#define HEALTH_SPRITE "../media/sprites/health_sprite.png"

ThrowableFactory::ThrowableFactory(Window &window) :
window(window) { }

Throwable* ThrowableFactory::generateThrowable(std::string &type) {
    if (type == ROCK) {
        BaseSprite sprite(window, HEALTH_SPRITE, 100, 100);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == MUD) {
        BaseSprite sprite(window, HEALTH_SPRITE, 100, 100);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == OIL) {
        BaseSprite sprite(window, HEALTH_SPRITE, 100, 100);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == HEALTH) {
        BaseSprite sprite(window, HEALTH_SPRITE, 100, 100);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == BOOST) {
        BaseSprite sprite(window, HEALTH_SPRITE, 100, 100);
        return new Throwable(std::move(sprite), false, 0, 0);
    } else {
        throw std::runtime_error("Tipo de sprite inválido");
    }
}