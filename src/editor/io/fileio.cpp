#include "fileio.hpp"

#include <fstream>
#include <cstring>

#include <data/data.hpp>
#include <terminal/terminal.hpp>
#include <operations/operations.hpp>

void editorOpen(std::string filename) {
    std::fstream file;
    file.open(filename, std::ifstream::in | std::ofstream::out | std::fstream::app );
    if(!file.is_open()) {
        die("file open");
    }

    std::string line;
    std::size_t line_len = 0;
    std::size_t line_cap = 0;
    while(std::getline(file, line)) {
        line_len = line.size();
        while(line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r')) {
            line_len--;
        }
        editorAppendRow(line.c_str(), line_len);
    }
    line.clear();
    file.close();
}
