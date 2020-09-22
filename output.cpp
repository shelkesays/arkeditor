#include "output.hpp"

#include <sstream>
#include <string>
#include <unistd.h>

#include "macros.hpp"
#include "buffer.hpp"

void editorDrawRows(struct abuffer *ab) {
    for (int line = 0; line < E.screenrows; line++) {
        if(line >= E.numrows) {
            if(E.numrows == 0 && line == E.screenrows / 3) {
                std::stringstream ss; 
                ss << "Ark editor -- version " << ARK_VERSION;
                std::string welcome = ss.str();
                int welcomeln = welcome.size();
                if(welcomeln > E.screencols) {
                    welcomeln = E.screencols;
                }
                int padding = (E.screencols - welcomeln) / 2;
                if(padding) {
                    abAppend(ab, "~", 1);
                    padding--;
                }
                while(padding--) {
                    abAppend(ab, " ", 1);
                }
                abAppend(ab, welcome.c_str(), welcomeln);
            } else {
                abAppend(ab, "~", 1);
            }
        } else {
            int len = E.row.size;
            if(len > E.screencols) {
                len = E.screencols;
            }
            abAppend(ab, E.row.chars, len);
        }
        
        abAppend(ab, "\x1b[K", 3);
        if(line < E.screenrows - 1) {
            abAppend(ab, "\r\n", 2);
        }
    }
}

void editorRefreshScreen() {
    struct abuffer ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    // abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    // char buf[32];
    std::stringstream ss;
    ss << "\x1b[" << E.cy + 1 << ";" << E.cx + 1 << "H";
    abAppend(&ab, ss.str().c_str(), ss.str().size());

    // abAppend(&ab, "\x1b[H", 3);
    abAppend(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab._buffer, ab._len);
    abFree(&ab);
}
