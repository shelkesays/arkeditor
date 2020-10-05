# Adding executable
set(SOURCE ark.cpp)

add_executable(ark ${SOURCE})

target_link_libraries(ark PUBLIC editor)