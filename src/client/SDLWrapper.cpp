#include "SDLWrapper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void SDLWrapper::run() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* main = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface *track_surface = NULL, *car_surface = NULL;
    SDL_Rect rect_img = {0, 0, 100, 200};
    SDL_Point point = {50,0 };

    main = SDL_CreateWindow("Testing",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            0,0,
                            SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(main, -1,
                                  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    track_surface = IMG_Load("../media/sprites/test_map.png");
    car_surface = IMG_Load("../media/sprites/pitstop_car_1.png");

    SDL_Texture* track_sprite = SDL_CreateTextureFromSurface(renderer, track_surface);
    SDL_Texture* car_sprite = SDL_CreateTextureFromSurface(renderer, car_surface);
    int velocityX = 0;
    int velocityY = 0;
    bool cont = true;
    SDL_Event e;
    while (cont) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        velocityY -= 10;
                        break;
                    case SDLK_s:
                        velocityY += 10;
                        break;
                    case SDLK_a:
                        velocityX -= 10;
                        break;
                    case SDLK_d:
                        velocityX += 10;
                        break;
                    case SDLK_q:
                        cont = false;
                        break;
                }
            } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        velocityY += 10;
                        break;
                    case SDLK_s:
                        velocityY -= 10;
                        break;
                    case SDLK_a:
                        velocityX += 10;
                        break;
                    case SDLK_d:
                        velocityX -= 10;
                        break;
                }
            }
        }
        rect_img.y += velocityY;
        rect_img.x += velocityX;

        if (rect_img.y < 0)
            rect_img.y = 0;
        if (rect_img.x < 0)
            rect_img.x = 0;
        if (rect_img.x > 700)
            rect_img.x = 700;
        if (rect_img.y > 400)
            rect_img.y = 400;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, track_sprite, &rect_img, NULL);
        SDL_RenderCopy(renderer, car_sprite, NULL, &rect_img);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(main);
    SDL_Quit();
}

