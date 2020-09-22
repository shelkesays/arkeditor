#include "terminal.hpp"

#include <cerrno>
#include <sstream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


#include "editorkeys.hpp"
#include "data.hpp"


void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) {
        die("tcsetattr");
    }
}

void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) {
        die("tcgetattr");
    }
    std::atexit(disableRawMode);

    struct termios raw = E.orig_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}

int editorReadKey() {
    int nread;
    char c;
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if(nread == -1 && errno != EAGAIN) {
            die("read");
        }
    }

    if(c == '\x1b') {
        char seq[3];
        if(read(STDIN_FILENO, &seq[0], 1) != 1) {
            return '\x1b';
        }
        if(read(STDIN_FILENO, &seq[1], 1) != 1) {
            return '\x1b';
        }

        if(seq[0] == '[') {
            if(seq[1] >= '0' && seq[1] <= '9') {
                if(read(STDIN_FILENO, &seq[2], 1) != 1) {
                    return '\x1b';
                }
                if(seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        } else if(seq[0] == 'o') {
            switch (seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }

        return '\x1b';
    } else {
        return c;
    }
}

std::vector<int> parseString(std::string str, char delimiter) {
    std::vector<int> parses_numbers_;
    std::stringstream ss_(str);

    int counter_;
    while(ss_ >> counter_) {
        parses_numbers_.push_back(counter_);
        if(ss_.peek() == delimiter) {
            ss_.ignore();
        }
    }

    return parses_numbers_;
} 

int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    int result;
    
    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) {
        result = -1;
    } else {
        unsigned int counter {0};
        while (counter < sizeof(buf) - 1) {
            if(read(STDIN_FILENO, &buf[counter], 1) != 1) {
                break;
            } else if(buf[counter] == 'R') {
                break;
            }

            counter++;
        }
        buf[counter] = '\0';

        if(buf[0] != '\x1b' || buf[1] != '[') {
            result = -1;
        } else {
            std::vector<int> numbers_ = parseString(&buf[2], ';');
            if(numbers_.empty() || numbers_.size() != 2) {
                result = -1;
            } else {
                result = 0;
            }
            *rows = numbers_.at(0);
            *cols = numbers_.at(1);
        }
    }

    return result;
}

int getWindowSize(int *rows, int *cols) {
    int result;
    struct winsize ws;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
            result = -1;
        } else {
            result = getCursorPosition(rows, cols);
        }
    } else {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
        result = 0;
    }

    return result;
}
