#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE


#include "macros.hpp"
#include "editorkeys.hpp"
#include "data.hpp"
#include "terminal.hpp"
#include "fileio.hpp"
#include "buffer.hpp"
#include "output.hpp"
#include "input.hpp"
#include "init.hpp"


struct editorConfig E;

int main(int argc, char *argv[]) {
    enableRawMode();
    initEditor();

    if(argc >= 2) {
        editorOpen(argv[1]);
    }

    while(true) {
        editorRefreshScreen();
        editorProcessKeyPresses();
    }

    return 0;
}
