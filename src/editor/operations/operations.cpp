#include "operations.hpp"

#include <cstdlib>
#include <cstring>

#include <data/data.hpp>

void editorAppendRow(const char *line, std::size_t line_len) {
    E.row = (erow *) realloc(E.row, sizeof(erow) * (E.numrows + 1));

    int at = E.numrows;
    E.row[at].size = line_len;
    E.row[at].chars = (char *) malloc(line_len + 1);
    std::memcpy(E.row[at].chars, line, line_len);
    E.row[at].chars[line_len] = '\0';
    E.numrows++;
}