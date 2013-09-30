#include "pportingabstract.h"

namespace piris
{

void PPortingAbstract::putRectangleEmpty(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color)
{
    putLine(x1,x2,y1,y1,color);
    putLine(x2,x2,y1,y2,color);
    putLine(x2,x1,y2,y2,color);
    putLine(x1,x1,y2,y1,color);
}

}
