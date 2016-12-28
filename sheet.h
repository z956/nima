#ifndef _SHEET_H_
#define _SHEET_H_

struct sheet {
    int h;
    int w;
    int count;
    char **content;
};

extern int nima_sheet_count;
extern struct sheet *nima_sheets;

extern int max_sheet_w;
extern int max_sheet_h;
extern int limit_sheet_w;
extern int limit_sheet_h;

int read_sheet_file(const char *name);

#endif

