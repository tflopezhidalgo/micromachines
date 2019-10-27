#ifndef MICROMACHINES_TEXTUREREPOSITORY_H
#define MICROMACHINES_TEXTUREREPOSITORY_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Texture.h"
#include <map>
#include <string>

// Genera un Singleton para cada textura, generandolas dentro de
// mapa y devolviendo una referencia a ella cuando se la necesita
// se llama al destructor de cada Textura para eliminarla cuando
// se la deja de usar

class TextureRepository {
private:
    static std::map<std::string, Texture> unique_textures;

public:
    static Texture& getTexture(const std::string& key,
                               Window& mainWindow);

};

#endif
