#include "TextureRepository.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <map>

std::map<std::string, Texture> TextureRepository::unique_textures;

using namespace std;

Texture& TextureRepository::getTexture(const string& key,
                                              Window& mainWindow) {
    if ( unique_textures.count(key) == 0 ) {
        SDL_Surface* aux_surface = IMG_Load(key.c_str());
        SDL_Texture* new_texture =
                SDL_CreateTextureFromSurface(mainWindow.getRenderer(),
                                             aux_surface);
        SDL_FreeSurface(aux_surface);
        if (!new_texture)
            throw runtime_error("No se pudo crear textura" + key);

        Texture unique_texture(new_texture, mainWindow);
        unique_textures.insert(pair<string, Texture>(key, move(unique_texture)));
    }
    return unique_textures.at(key);
}
