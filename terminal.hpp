#ifndef EDITOR_TERMINAL_H
#define EDITOR_TERMINAL_H

#include <vector>
#include <string>

void die(const char *s);

void disableRawMode();

void enableRawMode();

int editorReadKey();

std::vector<int> parseString(std::string str, char delimiter);

int getCursorPosition(int *rows, int *cols);

int getWindowSize(int *rows, int *cols);

#endif