#include "init.hpp"

#include <data/data.hpp>
#include <terminal/terminal.hpp>

void initEditor() {
    E.cx = 0;
    E.cy = 0;
    E.numrows = 0;
    E.row = NULL;

    if(getWindowSize(&E.screenrows, &E.screencols) == -1) {
        die("getWindowsSize");
    }
}
