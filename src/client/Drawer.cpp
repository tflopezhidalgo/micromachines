#include <zconf.h>
#include "Drawer.h"
#include "Window.h"
#include "ProtectedModel.h"

#define BUFFER_WIDTH 352        // Mandar a Constants.h
#define BUFFER_HEIGHT 288

Drawer::Drawer(Window& main, ProtectedModel& model, ProtectedVector& pv) :
main(main),
model(model),
running(true),
pv(pv){ }

void Drawer::run() {

    SDL_Texture* videoTexture = SDL_CreateTexture(main.getRenderer(),
            SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    std::vector<char> currentFrame(BUFFER_HEIGHT * BUFFER_WIDTH * 3);
    long fixed_time = 1000 / 60; // segundos / frames
    while (running){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        this->main.clear();
        this->model.renderAll();
        this->main.update();

        main.setTarget(videoTexture);
        this->model.renderAll();
        SDL_RenderReadPixels(main.getRenderer(), NULL,
                SDL_PIXELFORMAT_RGB24, currentFrame.data(), BUFFER_WIDTH * 3);

        main.setTarget(NULL);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < fixed_time)
            std::this_thread::sleep_for(std::chrono::milliseconds(fixed_time - duration.count()));
    }
}

void Drawer::stop() {
    running = false;
}
