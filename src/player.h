#ifndef PLAYER_H
#define PLAYER_H

#include <stddef.h>

typedef enum { NONE = 0, LEFT = 1, RIGHT = 2 } direction_t;

typedef struct {
    // x coordinate of the bullet position
    int x;

    // y coordinate of the bullet position
    int y;

    // movespeed  of the bullet
    int speed;
} bullet_t;

typedef struct {
    // x coordinate of the player position
    int x;

    // y coordinate of the player position
    int y;

    // movespeed  of the player
    int speed;

    // bullet of the player
    bullet_t* bullet;

    // direction of the player
    direction_t direction;
} player_t;

player_t* player_create(int x, int y);

void player_shoot(player_t* player);

void player_move(player_t* player, size_t delta_time);

void player_set_direction(player_t* player, direction_t direction);

void player_destroy(player_t* player);

#endif // PLAYER_H
