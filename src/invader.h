#ifndef INVADER_H
#define INVADER_H

#define INVADER_WIDTH  30
#define INVADER_HEIGHT 30

typedef enum {
    // the small invader
    CRAB = 0,

    // the medium invader
    SQUID = 1,

    // the large invader
    OCTOPUS = 2,
} invader_type_t;

typedef struct {
    // the x coordinate of the invader's position
    int x;

    // the y coordinate of the invader's position
    int y;

    // the width of the invader
    int w;

    // the height of the invader
    int h;

    // type of the invader
    invader_type_t type;
} invader_t;

invader_t* invader_create(int x, int y, invader_type_t type);

void invader_destroy(invader_t* invader);

#endif // INVADER_H
