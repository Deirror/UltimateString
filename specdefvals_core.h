#pragma once

/*
SPECIAL DEIRROR'S LIBRARY -> SDL
*/

#define _SDL_BEGIN \
namespace sdl {

#define _SDL_END }

#define _NULLPTR nullptr 
#define _EMPTY "\0"
#define _TERM_NULL '\0'
#define _STR_LOWER 'a'
#define _END_LOWER 'z'

#define _STR_UPPER 'A'
#define _END_UPPER 'Z'

#define _LOW_UP_DIFF 'a' - 'A'

#define _NULL 0x0
#define _ONE 0x1
#define _BIN 0x2
#define _QUAT 0x4
#define _OCT 0x8

#pragma warning(push)
#pragma warning(disable : 4005)

#define _HEX 0x10

#pragma warning(pop)


#define _M_ONE -0x1

#define _MAX_ASCII_CODE 0xFF

#define _MAX_BUFFER_SIZE 0x401

#define _SIZE_MAX 0xffffffffffffffffui64


#define _SDL_FUNC inline
#define _SDL_EXPL explicit
#define _SDL_FR friend
#define _SDL_TMP \
template <class T>

#define _SDL_2TMP \
template <class T, class D>

#define _DELETE_ARRAY(_array) \
delete[] _array

#define _DELETE(_array) \
delete _array

#define _ALLOCATE_NEW_ARRAY(_array, _type, _size) \
_array = new _type[_size]{}

#define _CSTYLE_CAST(type, value) (type)value

typedef char buffer[_MAX_BUFFER_SIZE];

typedef char*               char_ptr;
typedef const char*   const_char_ptr;

typedef short                  index;
typedef short              small_num;
typedef unsigned short small_pos_num;

typedef size_t                  size;
typedef size_t            char_count;
typedef size_t       long_pos_number;