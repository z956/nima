#include "sheet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SHEET_COUNT 20
#define max(a, b) ((a) > (b)) ? (a) : (b)

int nima_sheet_count;
struct sheet *nima_sheets;

int max_sheet_w;
int max_sheet_h;
int limit_sheet_w;
int limit_sheet_h;

static const char *sheet_tag = "---SHEET";
static int sheet_map[MAX_SHEET_COUNT];

static void init_nima_sheets() {
    for (int i = 0; i < nima_sheet_count; i++) {
        nima_sheets[i].h = 0;
        nima_sheets[i].w = 0;
        nima_sheets[i].count = sheet_map[i];
        nima_sheets[i].content = (char **)malloc(sizeof(char *)*sheet_map[i]);
    }
}
static void strip_space(char *line) {
    size_t len = strlen(line);
    char *c = line + len - 1;
    while (*c != 0) {
        if (*c == '\n') {
            *c = 0;
            return;
        }
    }
}
static int sheet_count(FILE *fp) {
    size_t len = strlen(sheet_tag);
    char line[1024];
    while ((fgets(line, 1024, fp)) != NULL) {
        if (strncmp(sheet_tag, line, len) == 0) {
            nima_sheet_count++;
            if (nima_sheet_count > MAX_SHEET_COUNT) {
                return -1;
            }
        }
        else {
            sheet_map[nima_sheet_count - 1]++;
        }
    }
    return 0;
}
static int read_sheet_content(FILE *fp) {
    size_t len = strlen(sheet_tag);
    char line[1024];
    int cur = 0, content_idx = 0;
    while ((fgets(line, 1024, fp)) != NULL) {
        if (strncmp(sheet_tag, line, len) == 0) {
            cur++;
            content_idx = 0;
            nima_sheets[cur-1].h = max(nima_sheets[cur-1].h, sheet_map[cur-1]);
        }
        else {
            strip_space(line);
            size_t llen = strlen(line);
            nima_sheets[cur-1].content[content_idx] = (char *)malloc(sizeof(char)*llen + 1);
            strncpy(nima_sheets[cur-1].content[content_idx], line, llen);
            nima_sheets[cur-1].content[content_idx][llen] = 0;

            nima_sheets[cur-1].w = max(nima_sheets[cur-1].w, llen);
            content_idx++;
        }
    }

    for (int i = 0; i < nima_sheet_count; i++) {
        max_sheet_w = max(max_sheet_w, nima_sheets[i].w);
        max_sheet_h = max(max_sheet_h, nima_sheets[i].h);
    }

    limit_sheet_w = max_sheet_w + 4;
    limit_sheet_h = max_sheet_h + 2;

    return 0;
}

int read_sheet_file(const char *name) {
    FILE *fp = fopen(name, "r");
    if (!fp) {
        return -1;
    }

    int err = -1;
    do {
        if (sheet_count(fp) != 0) {
            break;
        }
        if (nima_sheet_count <= 0) {
            break;
        }

        nima_sheets = (struct sheet*)malloc(sizeof(struct sheet) * nima_sheet_count);
        init_nima_sheets();
        fseek(fp, 0, SEEK_SET);
        err = read_sheet_content(fp);
    } while (0);
    fclose(fp);
    return err;
}

