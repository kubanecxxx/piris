#include "stdint.h"
#include "pfont.h"

namespace piris
{

PFont::PFont(const char *table, pixel_t heigth, pixel_t width)
{
    m.table = table;
    m.height =  heigth;
    m.width = width;
}

}
