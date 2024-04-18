
#include "invader.h"
#include <stdlib.h>

invader_t*
invader_create(int x, int y, invader_type_t type) {
    invader_t* invader = malloc(sizeof(invader_t));

    invader->x = x;
    invader->y = y;
    invader->w = INVADER_WIDTH;
    invader->h = INVADER_HEIGHT;
    invader->type = type;

    return invader;
}

void
invader_destroy(invader_t* invader) {
    free(invader);
    invader = NULL;
}
