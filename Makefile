ark: ark.cpp
	g++ macros.hpp editorkeys.hpp data.hpp terminal.hpp fileio.hpp buffer.hpp output.hpp input.hpp init.hpp terminal.cpp fileio.cpp buffer.cpp output.cpp input.cpp init.cpp ark.cpp -o ark -Wall -Wextra -pedantic -std=c++14
