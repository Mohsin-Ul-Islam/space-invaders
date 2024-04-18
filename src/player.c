#include <stdio.h>
#include <stdlib.h>

#include "player.h"

player_t*
player_create(int x, int y) {
    player_t* player = malloc(sizeof(player_t));
    player->bullet = malloc(sizeof(bullet_t));

    player->x = x;
    player->y = y;
    player->speed = 80;
    player->direction = NONE;

    player->bullet->x = 0;
    player->bullet->y = 0;
    player->bullet->speed = 15;

    return player;
}

void
player_move(player_t* player, size_t delta_time) {
    if (player->direction == NONE) {
        return;
    }

    int sign = player->direction == LEFT ? -1 : 1;
    player->x = player->x + (player->speed * ((float)delta_time / 1000) * sign);

    if (player->x <= 0) {
        player->x = 0;
    }

    if (player->x + 20 >= 640) {
        player->x = 640 - 20;
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
