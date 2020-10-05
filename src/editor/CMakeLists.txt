add_library(
    editor
    constants/macros.hpp
    constants/editorkeys.hpp
    data/data.hpp
    terminal/terminal.hpp
    terminal/terminal.cpp
    io/fileio.hpp
    io/fileio.cpp
    data/buffer.hpp
    data/buffer.cpp
    init/init.hpp
    io/output.hpp
    io/output.cpp
    io/input.hpp
    io/input.cpp
    operations/operations.hpp
    operations/operations.cpp
    init/init.cpp
    init/init.cpp
)

target_include_directories(editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
