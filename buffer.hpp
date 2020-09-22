#ifndef EDITOR_BUFFER_H
#define EDITOR_BUFFER_H

#include "data.hpp"

void abAppend(struct abuffer *ab, const char *s, int len);

void abFree(struct abuffer *ab);

#endif