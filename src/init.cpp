#include "init.hpp"

#include "data.hpp"
#include "terminal.hpp"

void initEditor() {
    E.cx = 0;
    E.cy = 0;
    E.numrows = 0;

    if(getWindowSize(&E.screenrows, &E.screencols) == -1) {
        die("getWindowsSize");
    }
}
