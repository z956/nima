#include "animation.h"

#include <ncurses.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#include "sheet.h"
#include "walk_animation.h"

static int check_hw(int h, int w) {
    return h >= limit_sheet_h && w >= limit_sheet_w;
}
static void print_warn(int h, int w) {
    char warn[1024];
    sprintf(warn, "Window size should be at least %dx%d.", limit_sheet_w, limit_sheet_h);
    mvprintw(h / 2, (w - strlen(warn)) / 2, "%s", warn);
}
static void print_animation(int h, int w) {
    int head_h = h - 2 - max_sheet_h;
    int head_w = (w - max_sheet_w)/2;

    int cur = walk_animation.cur;
    struct frame_t *frame = &walk_animation.frames[cur];
    int idx = frame->sheet;
    struct sheet *frame_sheet = &nima_sheets[idx];
    for (int i = 0; i < frame_sheet->count; i++) {
        mvprintw(head_h + i + frame->off_y, head_w + frame->off_x, "%s", frame_sheet->content[i]);
    }
}
static void update_animation() {
    int h, w;
    getmaxyx(stdscr, h, w);
    clear();
    if (!check_hw(h, w)) {
        print_warn(h, w);
        //reset
        walk_animation.cur = 0;
    }
    else {
        print_animation(h, w);
        walk_animation.cur = (walk_animation.cur + 1) % walk_animation.count;
    }
    refresh();
}
static int wait_input(int fdmax, fd_set *fds, struct timeval *t) {
    t->tv_sec = 0;
    t->tv_usec = 700000;
    int r = select(fdmax, fds, NULL, NULL, t);
    if (r > 0) {
        getch();
    }
    return r != 0;
}
void start_animate() {
    fd_set master, readfd;
    int fdmax = 1;
    struct timeval time;

    FD_ZERO(&master);
    FD_SET(0, &master);

    init_walk_animation();
    initscr();
    do {
        update_animation();

        readfd = master;
        if (wait_input(fdmax, &readfd, &time)) {
            break;
        }
    } while (1);
    endwin();
}

