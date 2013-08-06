#ifndef PTYPES_H
#define PTYPES_H

#include <stdint.h>

namespace piris
{

//keyevent
typedef uint16_t key_t;
typedef enum
{
    RELEASED, PRESSED
} keyEvt_t;

typedef uint16_t pixel_t;
typedef uint16_t color_t;

typedef enum
{
    RED = 0xF100, GREEN = 0x07E0, BLACK = 0, WHITE = 0xFFFF, BLUE = 0x001F
} globalColors_t;

}

#endif // PTYPES_H
