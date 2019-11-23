#include "ObjectFactory.h"
#include "Sprite.h"
#include "Throwable.h"
#include "Constants.h"
#include "Identifiers.h"
#include "StaticObject.h"

#define HEALTH_SPRITE "../media/sprites/health_sprite.png"
#define BOOST_SPRITE "../media/sprites/powerup.png"
#define OIL_SPRITE "../media/sprites/oil.png"
#define MUD_SPRITE "../media/sprites/mud_sprite.png"
#define ROCK_SPRITE "../media/sprites/rock_sprite.png"
#define FLY_SPRITE "../media/sprites/throwable_sprite.png"
#define GRANDSTAND_SPRITE "../media/sprites/public_sprite.png"

ObjectFactory::ObjectFactory(Window &window) :
window(window) { }

Object* ObjectFactory::generateObject(EntityIdentifier type) {
    Sprite onFlySprite(window, FLY_SPRITE, 2 * PROJECTILE_RADIUS , 2 * PROJECTILE_RADIUS);
    if (type == STONE) {
        Sprite sprite(window, ROCK_SPRITE, 2 * STONE_RADIUS, 2 * STONE_RADIUS);
        return new Throwable(std::move(sprite), std::move(onFlySprite), DEAD, 0, 0);
    }
    if (type == MUD) {
        Sprite sprite(window, MUD_SPRITE, MUD_HEIGHT, MUD_WIDTH);
        return new Throwable(std::move(sprite), std::move(onFlySprite), DEAD, 0, 0);
    }
    if (type == OIL) {
        Sprite sprite(window, OIL_SPRITE, 2 * OIL_RADIUS, 2 * OIL_RADIUS);
        return new Throwable(std::move(sprite), std::move(onFlySprite), DEAD, 0, 0);
    }
    if (type == HEALTHBOOSTER) {
        Sprite sprite(window, HEALTH_SPRITE, 2 * BOOSTERS_RADIUS, 2 * BOOSTERS_RADIUS);
        return new Throwable(std::move(sprite), std::move(onFlySprite), DEAD, 0, 0);
    }
    if (type == SPEEDBOOSTER) {
        Sprite sprite(window, BOOST_SPRITE, 2 * BOOSTERS_RADIUS, 2 * BOOSTERS_RADIUS);
        return new Throwable(std::move(sprite), std::move(onFlySprite), DEAD, 0, 0);
    } if (type == GRANDSTAND) {
        Sprite sprite(window, GRANDSTAND_SPRITE, GRANDSTAND_HEIGHT, GRANDSTAND_WIDTH);
        return new StaticObject(std::move(sprite));
    } else {
        throw std::runtime_error("Tipo de sprite inválido");
    }
}
