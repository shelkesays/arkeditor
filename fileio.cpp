#include "fileio.hpp"

#include <fstream>
#include <cstring>

#include "data.hpp"
#include "terminal.hpp"

void editorOpen(std::string filename) {
    std::fstream file;
    file.open(filename, std::ifstream::in | std::ofstream::out | std::fstream::app );
    if(!file.is_open()) {
        die("file open");
    }

    std::string line;
    std::size_t line_len;
    std::getline(file, line);
    line_len = line.size();
    if(line_len != 0) {
        while(line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r')) {
            line_len--;
        }

        E.row.size = line_len;
        E.row.chars = (char *) malloc(line_len + 1);
        memcpy(E.row.chars, line.c_str(), line_len);
        E.row.chars[line_len] = '\0';
        E.numrows = 1;
    }
    line.clear();
    file.close();
}
