#ifndef EDITOR_DATA_H
#define EDITOR_DATA_H

#include <termios.h>

typedef struct erow {
    int size;
    char *chars;
} erow;

struct editorConfig {
    int cx, cy;
    int screenrows;
    int screencols;
    int numrows;
    erow row;
    struct termios orig_termios;
};

struct abuffer {
    char *_buffer;
    int _len;
};

extern struct editorConfig E;

#endif