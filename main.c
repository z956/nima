#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "sheet.h"
#include "animation.h"

int main(int argc, char **argv) {
    if (read_sheet_file("nima_sheet") != 0) {
        return -1;
    }
    start_animate();
    return 0;
}
