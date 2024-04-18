#ifndef INVADER_H
#define INVADER_H

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

    // type of the invader
    invader_type_t type;
} invader_t;

#endif // INVADER_H
