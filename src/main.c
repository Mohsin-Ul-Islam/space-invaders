#include <stdbool.h>
#include <stdio.h>

#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

int
main() {
    // initialize the SDL audio and video subsystems
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // create the SDL window
    SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
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

    // open the SDL audio mixer
    if (Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_S16SYS, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) < 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // initialize the game
    game_init();

    // loop control variable
    bool done = false;

    // the maximum frame rate of the game
    size_t frame_rate = 60;

    // the time elapsed since the last frame
    size_t elapsed = 0;

    // the start of the frame time
    size_t start;

    // the game loop
    while (!done) {
        start = SDL_GetTicks64();

        // handle input
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                done = true;
                break;
            }

            game_handle_input(&evt);
        }

        game_tick(elapsed);

        // set the render clearing color
        if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0) {
            printf("%s", SDL_GetError());
            return 1;
        }

        // clear the screen
        if (SDL_RenderClear(renderer) < 0) {
            printf("%s", SDL_GetError());
            return 1;
        }

        // game render
        game_render(renderer);

        // render the contents
        SDL_RenderPresent(renderer);

        // cap the frame rate
        elapsed = elapsed + (SDL_GetTicks64() - start);
        if (elapsed > 1000 / frame_rate) {
            SDL_Delay(elapsed - 1000 / frame_rate);
            elapsed = 0;
        }
    }

    // clean up & release resources
    game_destroy();

    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
