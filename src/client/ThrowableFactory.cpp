#include "ThrowableFactory.h"
#include "BaseSprite.h"
#include "Throwable.h"
#include "Macros.h"

#define HEALTH_SPRITE "../media/sprites/health_sprite.png"
#define BOOST_SPRITE "../media/sprites/powerup.png"
#define OIL_SPRITE "../media/sprites/oil.png"

#define ROCK 0
#define MUD 1
#define HEALTH 2
#define OIL 3
#define BOOST 4

ThrowableFactory::ThrowableFactory(Window &window) :
window(window) { }

Throwable* ThrowableFactory::generateThrowable(int type) {
    if (type == ROCK) {
        BaseSprite sprite(window, HEALTH_SPRITE, 2 * STONE_RADIUS, 2 * STONE_RADIUS);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == MUD) {
        BaseSprite sprite(window, HEALTH_SPRITE, 10, 10);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == OIL) {
        BaseSprite sprite(window, OIL_SPRITE, 2 * OIL_RADIUS, 2 * OIL_RADIUS);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == HEALTH) {
        BaseSprite sprite(window, HEALTH_SPRITE, 20, 20);
        return new Throwable(std::move(sprite), false, 0, 0);
    }
    if (type == BOOST) {
        BaseSprite sprite(window, BOOST_SPRITE, 2 * BOOSTERS_RADIUS, 2 * BOOSTERS_RADIUS);
        return new Throwable(std::move(sprite), false, 0, 0);
    } else {
        throw std::runtime_error("Tipo de sprite inválido");
    }
}