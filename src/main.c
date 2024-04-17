#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int
main() {
    // initialize the SDL audio and video subsystems
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // create the SDL window
    SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                                          SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // create the SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // set the render clearing color
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // loop control variable
    bool done = false;

    // the game loop
    while (!done) {

        // handle input
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                done = true;
                break;
            }
        }

        // clear the screen
        if (SDL_RenderClear(renderer) < 0) {
            printf("%s", SDL_GetError());
            return 1;
        }

        // render the contents
        SDL_RenderPresent(renderer);
    }

    // clean up & release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
