#include "buffer.hpp"

#include <cstdlib>
#include <cstring>

void abAppend(struct abuffer *ab, const char *s, int len) {
    char *new_ = (char *) realloc(ab->_buffer, ab->_len + len);
    if(new_ == NULL) {
        return;
    }
    memcpy(&new_[ab->_len], s, len);
    ab->_buffer = new_;
    ab->_len += len;
}

void abFree(struct abuffer *ab) {
    free(ab->_buffer);
    ab->_len = 0;
}
