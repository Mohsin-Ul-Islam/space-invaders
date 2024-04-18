#ifndef GAME_H
#define GAME_H

#include "invader.h"
#include "player.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

// number of audio files
#define AUDIO_COUNT           8

// number of invaders
#define INVADERS_COUNT        30

// indices of the audio files
// these will be used in the audio file array
#define AUDIO_SHOOT           0
#define AUDIO_EXPLOSION       1
#define AUDIO_INVADER_CRAB    2
#define AUDIO_INVADER_SQUID   3
#define AUDIO_UFO_LOW_PITCH   4
#define AUDIO_UFO_HIGH_PITCH  5
#define AUDIO_INVADER_KILLED  6
#define AUDIO_INVADER_OCTOPUS 7

// options for SDL audio mixer
#define AUDIO_FREQUENCY       48000
#define AUDIO_CHANNELS        1
#define AUDIO_CHUNK_SIZE      2048

// options for SDL window
#define WINDOW_WIDTH          640
#define WINDOW_HEIGHT         480

typedef struct {
    // the game audio files
    Mix_Chunk* audio[AUDIO_COUNT];

    // player
    player_t* player;

    // the render rect of the game
    SDL_Rect* rect;

    // the invaders
    invader_t* invaders[INVADERS_COUNT];

    // the timer accumulater
    size_t timer;

    // the direction of the invaders moving collectively
    int invaders_direction;
} game_t;

// initialize the game entities
// returns a non zero code if an error is encountered
// for more error info use the `SDL_GetError()` function
int game_init();

// called once every frame to update the game logic
void game_tick(size_t delta_time);

// called once every frame to handle the game input
void game_handle_input(SDL_Event* evt);

// called once every frame to render the game entities
void game_render(SDL_Renderer* renderer);

// clean up & destroy the game entities
void game_destroy();

#endif // GAME_H
