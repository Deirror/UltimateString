#pragma once

#include <iostream>
#include <specdefvals_core.h>

_SDL_BEGIN

typedef std::ostream dostream;
typedef std::istream distream;

typedef std::ifstream difstream;
typedef std::ofstream dofstream;

typedef std::fstream dfstream;
typedef std::stringstream dstringstream;

dostream& dcout = std::cout;
distream& dcin = std::cin;

_SDL_END
