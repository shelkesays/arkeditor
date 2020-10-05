// Includes
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE 1

#include <constants/macros.hpp>
#include <constants/editorkeys.hpp>
#include <data/data.hpp>
#include <terminal/terminal.hpp>
#include <io/fileio.hpp>
#include <data/buffer.hpp>
#include <io/output.hpp>
#include <io/input.hpp>
#include <init/init.hpp>

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
