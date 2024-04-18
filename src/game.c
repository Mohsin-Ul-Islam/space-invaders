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
    game->rect = malloc(sizeof(SDL_Rect));
    game->timer = 0;
    game->player = player_create(WINDOW_WIDTH / 2 - 60 / 2, WINDOW_HEIGHT - 40);
    game->invaders_direction = 1;

    for (int i = 0; i < INVADERS_COUNT; i++) {
        game->invaders[i] = invader_create((i % 10) * INVADER_WIDTH, (i / 10) * INVADER_HEIGHT, CRAB);
    }

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
            if (game->player->bullet->speed == 0) {
                Mix_PlayChannel(-1, game->audio[AUDIO_SHOOT], 0);
            }
            player_shoot(game->player);
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

    game->timer += delta_time;
    if (game->timer >= 1000) {
        game->timer = 0;

        if (game->invaders[9]->x > WINDOW_WIDTH - INVADER_WIDTH || game->invaders[0]->x < 0) {
            game->invaders_direction = -game->invaders_direction;
        }

        for (int i = 0; i < INVADERS_COUNT; i++) {
            game->invaders[i]->x += 4 * game->invaders_direction;
        }
    }
}

void
game_render(SDL_Renderer* renderer) {
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) < 0) {
        printf("%s", SDL_GetError());
        exit(1);
    }

    game->rect->x = game->player->x;
    game->rect->y = game->player->y;
    game->rect->w = game->player->w;
    game->rect->h = game->player->h;
    SDL_RenderDrawRect(renderer, game->rect);

    game->rect->x = game->player->bullet->x;
    game->rect->y = game->player->bullet->y;
    game->rect->w = game->player->bullet->w;
    game->rect->h = game->player->bullet->h;
    SDL_RenderDrawRect(renderer, game->rect);

    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) < 0) {
        printf("%s", SDL_GetError());
        exit(1);
    }

    game->rect->w = INVADER_WIDTH - 4;
    game->rect->h = INVADER_HEIGHT - 4;
    for (int i = 0; i < INVADERS_COUNT; i++) {
        game->rect->x = game->invaders[i]->x;
        game->rect->y = game->invaders[i]->y;

        SDL_RenderDrawRect(renderer, game->rect);
    }
}

void
game_destroy() {
    if (game == NULL) {
        return;
    }

    free(game->rect);
    game->rect = NULL;

    player_destroy(game->player);

    for (int i = 0; i < INVADERS_COUNT; i++) {
        invader_destroy(game->invaders[i]);
    }

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
