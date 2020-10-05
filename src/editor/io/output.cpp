#include "output.hpp"

#include <sstream>
#include <string>
#include <unistd.h>

#include <constants/macros.hpp>
#include <data/buffer.hpp>

void editorDrawRows(struct abuffer *ab) {
    for (int line = 0; line < E.screenrows; line++) {
        int file_row = line + E.rowoff;
        if(file_row >= E.numrows) {
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
            int len = E.row[file_row].size - E.coloff;
            if(len < 0) {
                len = 0;
            }
            if(len > E.screencols) {
                len = E.screencols;
            }
            std::string line_(E.row[file_row].chars);
            line_ = std::string(line_.begin() + E.coloff, line_.end());
            abAppend(ab, line_.c_str(), len);
        }
        
        abAppend(ab, "\x1b[K", 3);
        if(line < E.screenrows - 1) {
            abAppend(ab, "\r\n", 2);
        }
    }
}

void editorScroll() {
    if(E.cy < E.rowoff) {
        E.rowoff = E.cy;
    }
    if(E.cy >= E.rowoff + E.screenrows) {
        E.rowoff = E.cy - E.screenrows + 1;
    }
    if(E.cx < E.coloff) {
        E.coloff = E.cx;
    }
    if(E.cx >= E.coloff + E.screencols) {
        E.coloff = E.cx - E.screencols + 1;
    }
}

void editorRefreshScreen() {
    editorScroll();

    struct abuffer ab = ABUF_INIT;

    abAppend(&ab, "\x1b[?25l", 6);
    // abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    std::stringstream ss;
    ss << "\x1b[" << (E.cy - E.rowoff) + 1 << ";" << (E.cx - E.coloff) + 1 << "H";
    abAppend(&ab, ss.str().c_str(), ss.str().size());

    // abAppend(&ab, "\x1b[H", 3);
    abAppend(&ab, "\x1b[?25h", 6);

    write(STDOUT_FILENO, ab._buffer, ab._len);
    abFree(&ab);
}
