#include "walk_animation.h"

#include <stdlib.h>

#include "sheet.h"

static int walk_frames[] = {
    RIGHT_WALK1,
    RIGHT_WALK2,
    RIGHT_WALK1,
    RIGHT_WALK2,
    RIGHT_WALK1,
    LEFT_WALK1,
    LEFT_WALK2,
    LEFT_WALK1,
    LEFT_WALK2,
    LEFT_WALK1,
};
static int walk_frames_count = sizeof(walk_frames) / sizeof(int);

struct animation_t walk_animation;

void init_walk_animation() {
    walk_animation.count = walk_frames_count;
    walk_animation.cur = 0;
    walk_animation.frames = (struct frame_t*)malloc(sizeof(struct frame_t)*walk_frames_count);

    int pivot = walk_frames_count / 2;
    for (int i = 0; i < walk_frames_count; i++) {
        walk_animation.frames[i].sheet = walk_frames[i];
        walk_animation.frames[i].off_y = 0;

        if (i == pivot) {
            walk_animation.frames[i].off_x = pivot;
        }
        else if (i < pivot) {
            walk_animation.frames[i].off_x = i;
        }
        else {
            walk_animation.frames[i].off_x = walk_frames_count - i - 1;
        }
    }
}

