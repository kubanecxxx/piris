#include "stdint.h"
#include "pfont.h"

namespace piris
{

PFont::PFont(properties_t &prop):
    m(prop)
{
    m.ro = 0;
}

PFont::PFont(const char *table, pixel_t heigth, pixel_t width):
    m(*new properties_t)
{
    m.table = table;
    m.height = heigth;
    m.width = width;
    m.ro = 0;
}

PFont::PFont(const properties_t &prop):
    m((properties_t &) prop)
{
}

}
