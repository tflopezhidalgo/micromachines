#include "ThrowableFactory.h"
#include "BaseSprite.h"
#include "Throwable.h"
#include "Constants.h"
#include "Identifiers.h"

#define HEALTH_SPRITE "../media/sprites/health_sprite.png"
#define BOOST_SPRITE "../media/sprites/powerup.png"
#define OIL_SPRITE "../media/sprites/oil.png"

ThrowableFactory::ThrowableFactory(Window &window) :
window(window) { }

Throwable* ThrowableFactory::generateThrowable(EntityIdentifier type) {
    if (type == STONE) {
        BaseSprite sprite(window, HEALTH_SPRITE, 2 * STONE_RADIUS, 2 * STONE_RADIUS);
        return new Throwable(std::move(sprite), DEAD, 0, 0);
    }
    if (type == MUD) {
        BaseSprite sprite(window, HEALTH_SPRITE, 10, 10);
        return new Throwable(std::move(sprite), DEAD, 0, 0);
    }
    if (type == OIL) {
        BaseSprite sprite(window, OIL_SPRITE, 2 * OIL_RADIUS, 2 * OIL_RADIUS);
        return new Throwable(std::move(sprite), DEAD, 0, 0);
    }
    if (type == HEALTHBOOSTER) {
        BaseSprite sprite(window, HEALTH_SPRITE, 20, 20);
        return new Throwable(std::move(sprite), DEAD, 0, 0);
    }
    if (type == SPEEDBOOSTER) {
        BaseSprite sprite(window, BOOST_SPRITE, 2 * BOOSTERS_RADIUS, 2 * BOOSTERS_RADIUS);
        return new Throwable(std::move(sprite), DEAD, 0, 0);
    } else {
        throw std::runtime_error("Tipo de sprite inválido");
    }
}
