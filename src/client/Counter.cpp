#include "Counter.h"

#define SEM_INIT "../media/sprites/sem_1_red.png"
#define SEM_READY "../media/sprites/sem_2_red.png"
#define SEM_SET "../media/sprites/sem_3_red.png"
#define SEM_GO "../media/sprites/sem_all_green.png"

Counter::Counter(Window& window) :
window(window),
preReady(window.createTextureFrom(SEM_INIT)),
ready(window.createTextureFrom(SEM_READY)),
set(window.createTextureFrom(SEM_SET)),
go(window.createTextureFrom(SEM_GO)),
counter(-1){
}

void Counter::count() {
    counter++;
}

void Counter::render(){
    SDL_Rect r = {(window.getWidth() / 2) - 100, 0, 200, 200};
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
