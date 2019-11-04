#include "ThrowableFactory.h"
#include "BaseSprite.h"
#include "Throwable.h"

#define ROCK "ROCK"
#define MUD "MUD"
#define HEALTH "HEALTH"
#define OIL "OIL"
#define BOOST "BOOST"

#define HEALTH_SPRITE "../media/sprites/health_sprite.png"
#define BOOST_SPRITE "../media/sprites/powerup.png"
#define OIL_SPRITE "../media/sprites/oil.png"

ThrowableFactory::ThrowableFactory(Window &window) :
window(window) { }

Throwable* ThrowableFactory::generateThrowable(std::string &type) {
    if (type == ROCK) {
        BaseSprite sprite(window, HEALTH_SPRITE, 10, 10);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == MUD) {
        BaseSprite sprite(window, HEALTH_SPRITE, 10, 10);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == OIL) {
        BaseSprite sprite(window, OIL_SPRITE, 20, 20);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == HEALTH) {
        BaseSprite sprite(window, HEALTH_SPRITE, 20, 20);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == BOOST) {
        BaseSprite sprite(window, BOOST_SPRITE, 20, 20);
        return new Throwable(std::move(sprite), false, 0, 0);
    } else {
        throw std::runtime_error("Tipo de sprite inválido");
    }
}