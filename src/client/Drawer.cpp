#include <zconf.h>
#include "ffmpeg/RecorderException.h"
#include "Drawer.h"
#include "Window.h"
#include "../common/Constants.h"
#include "ProtectedModel.h"

#define ERROR_RENDER "Render Read Pixeles error"

Drawer::Drawer(Window& main, ProtectedModel& model, ProtectedVector& pv) :
main(main),
model(model),
running(true),
pv(pv){ }

void Drawer::run() {

    SDL_Texture* videoTexture = SDL_CreateTexture(main.getRenderer(),
            SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    assert(videoTexture != NULL);
    long fixed_time = 1000 / 60; // segundos / frames

    while (running){
        std::vector<char> currentFrame(WINDOW_HEIGHT * WINDOW_WIDTH * 3);

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        this->main.clear();
        this->model.renderAll();
        this->main.update();

        main.setTarget(videoTexture);

        this->main.clear();
        this->model.renderAll();
        // Obtengo los bytes de la textura en el buffer
        int res = SDL_RenderReadPixels(main.getRenderer(), NULL,
                SDL_PIXELFORMAT_RGB24, currentFrame.data(), WINDOW_WIDTH * 3);
        if (res) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_RENDER, SDL_GetError(), NULL);
            throw RecorderException(ERROR_RENDER);
        }
        if (!pv.isClose()) {
            pv.push(currentFrame);
        }
        main.setTarget(NULL);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (duration.count() < fixed_time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(fixed_time - duration.count()));
        }
    }

    SDL_DestroyTexture(videoTexture);
}

void Drawer::stop() {
    running = false;
}

Drawer::~Drawer() {
    this->join();
}
