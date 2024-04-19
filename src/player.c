#include <stdio.h>
#include <stdlib.h>

#include "player.h"

player_t*
player_create(int x, int y) {
    player_t* player = malloc(sizeof(player_t));
    player->bullet = malloc(sizeof(bullet_t));

    player->x = x;
    player->y = y;
    player->w = 60;
    player->h = 20;
    player->speed = 5;
    player->direction = NONE;

    player->bullet->x = player->x + player->w / 2;
    player->bullet->y = player->y - player->h - 4;
    player->bullet->w = 2;
    player->bullet->h = 14;
    player->bullet->speed = 0;

    return player;
}

void
player_move(player_t* player, size_t delta_time) {
    player->bullet->y = player->bullet->y - player->bullet->speed * delta_time / 10;
    if (player->bullet->y < 0) {
        player->bullet->x = player->x + player->w / 2;
        player->bullet->y = player->y - player->h - 4;
        player->bullet->speed = 0;
    }

    if (player->direction == NONE) {
        return;
    }

    int sign = 0;
    if (player->direction == LEFT) {
        sign = -1;
    } else if (player->direction == RIGHT) {
        sign = 1;
    }

    player->x = player->x + (player->speed * (delta_time / 10) * sign);
    if (player->x < 0) {
        player->x = 0;
    }

    if (player->x > 640 - player->w) {
        player->x = 640 - player->w;
    }

    if (player->bullet->speed == 0) {
        player->bullet->x = player->x + player->w / 2;
        player->bullet->y = player->y - player->h - 4;
    }
}

void
player_shoot(player_t* player) {
    if (player->bullet->speed == 0) {
        player->bullet->speed = 10;
    }
}

void
player_set_direction(player_t* player, direction_t direction) {
    player->direction = direction;
}

void
player_destroy(player_t* player) {
    free(player->bullet);
    player->bullet = NULL;

    free(player);
    player = NULL;
}
