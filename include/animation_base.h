#ifndef _ANIMATION_BASE_H_
#define _ANIMATION_BASE_H_

struct frame_t {
    int sheet;
    int off_x;
    int off_y;
};

struct animation_t {
    int count;
    int cur;
    struct frame_t *frames;
};

#endif

