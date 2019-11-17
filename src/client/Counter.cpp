#include "Counter.h"
#include "TextureRepository.h"
#include "Texture.h"

#define SEM_INIT "../media/sprites/sem_1_red.png"
#define SEM_READY "../media/sprites/sem_2_red.png"
#define SEM_SET "../media/sprites/sem_3_red.png"
#define SEM_GO "../media/sprites/sem_all_green.png"

Counter::Counter(Window& window) :
window(window),
ready(window.createTextureFrom(SEM_READY)),
set(window.createTextureFrom(SEM_SET)),
go(window.createTextureFrom(SEM_GO)),
counter(0){
}

void Counter::count() {
    counter++;
}

void Counter::render(int x, int y){
    SDL_Rect r = {x, y, 200, 200};
    switch(counter){
        case 0:
            ready.render(r, 0);
            break;
        case 1:
            set.render(r, 0);
            break;
        case 2:
            go.render(r, 0);
            break;

    }
}
