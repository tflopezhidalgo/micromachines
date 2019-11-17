#include "Counter.h"
#include "TextureRepository.h"
#include "Texture.h"

#define SEM_INIT "../media/sprites/sem_1_red.png"
#define SEM_READY "../media/sprites/sem_2_red.png"
#define SEM_SET "../media/sprites/sem_3_red.png"
#define SEM_GO "../media/sprites/sem_all_green.png"

Counter::Counter(Proxy *proxy, Window& window) :
window(window) {
    this->proxy = proxy;
    textures.push_back(&window.createTextureFrom(SEM_INIT));
    textures.push_back(&window.createTextureFrom(SEM_SET));
    textures.push_back(&window.createTextureFrom(SEM_GO));
}

void Counter::count() {
    int counter = 1;
    for (Texture* txt : textures) {
        proxy->receiveMessage();            // Ojo que genera race condition con el drawe
        ++counter;
        SDL_Rect rect = {0,0, 300, 300};
        txt->render(rect, 0);
    }
}
