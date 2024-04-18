#include <SDL2/SDL_rect.h>
#include <stdint.h>
#include <stdio.h>

#include "game.h"
#include "player.h"

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

game_t* game;

int
game_init() {
    // make sure the game is treated as singleton
    if (game != NULL) {
        return 0;
    }

    game = malloc(sizeof(game_t));

    game->player = player_create(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    game->audio[AUDIO_SHOOT] = Mix_LoadWAV("assets/audio/shoot.wav");
    if (game->audio[AUDIO_SHOOT] == NULL) {
        return 1;
    }

    game->audio[AUDIO_EXPLOSION] = Mix_LoadWAV("assets/audio/explosion.wav");
    if (game->audio[AUDIO_EXPLOSION] == NULL) {
        return 1;
    }

    game->audio[AUDIO_INVADER_CRAB] = Mix_LoadWAV("assets/audio/fastinvader1.wav");
    if (game->audio[AUDIO_INVADER_CRAB] == NULL) {
        return 1;
    }

    game->audio[AUDIO_INVADER_SQUID] = Mix_LoadWAV("assets/audio/fastinvader2.wav");
    if (game->audio[AUDIO_INVADER_SQUID] == NULL) {
        return 1;
    }

    game->audio[AUDIO_INVADER_OCTOPUS] = Mix_LoadWAV("assets/audio/fastinvader3.wav");
    if (game->audio[AUDIO_INVADER_OCTOPUS] == NULL) {
        return 1;
    }

    game->audio[AUDIO_INVADER_KILLED] = Mix_LoadWAV("assets/audio/invaderkilled.wav");
    if (game->audio[AUDIO_INVADER_KILLED] == NULL) {
        return 1;
    }

    game->audio[AUDIO_UFO_LOW_PITCH] = Mix_LoadWAV("assets/audio/ufo_lowpitch.wav");
    if (game->audio[AUDIO_UFO_LOW_PITCH] == NULL) {
        return 1;
    }

    game->audio[AUDIO_UFO_HIGH_PITCH] = Mix_LoadWAV("assets/audio/ufo_highpitch.wav");
    if (game->audio[AUDIO_UFO_HIGH_PITCH] == NULL) {
        return 1;
    }

    return 0;
}

void
game_handle_input(SDL_Event* evt) {
    if (evt->type == SDL_KEYDOWN) {
        if (evt->key.keysym.sym == SDLK_SPACE) {
            Mix_PlayChannel(-1, game->audio[AUDIO_SHOOT], 0);
        } else if (evt->key.keysym.sym == SDLK_a) {
            player_set_direction(game->player, LEFT);
        } else if (evt->key.keysym.sym == SDLK_d) {
            player_set_direction(game->player, RIGHT);
        }
    } else if (evt->type == SDL_KEYUP) {
        if (evt->key.keysym.sym == SDLK_a || evt->key.keysym.sym == SDLK_d) {
            player_set_direction(game->player, NONE);
        }
    }
}

void
game_tick(size_t delta_time) {
    player_move(game->player, delta_time);
}

void
game_render(SDL_Renderer* renderer) {
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) < 0) {
        printf("%s", SDL_GetError());
        exit(1);
    }

    SDL_Rect rect;
    rect.w = 20;
    rect.h = 20;
    rect.x = game->player->x;
    rect.y = game->player->y;

    SDL_RenderDrawRect(renderer, &rect);
}

void
game_destroy() {
    if (game == NULL) {
        return;
    }

    player_destroy(game->player);

    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_SHOOT]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_EXPLOSION]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_INVADER_CRAB]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_UFO_LOW_PITCH]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_INVADER_SQUID]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_INVADER_KILLED]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_UFO_HIGH_PITCH]);
    SDL_FreeWAV((uint8_t*)game->audio[AUDIO_INVADER_OCTOPUS]);

    free(game);
    game = NULL;
}
