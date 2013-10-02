#include "pportingabstract.h"

namespace piris
{

void PPortingAbstract::putRectangleShaped(
        pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color, bool filled)
{
    const uint8_t b = 3;

    if (filled)
    {
        putRectangle(x1+b,x2-b,y1,y2,color,filled);

        uint8_t t = b;
        for (int i = 0 ; i < b ; i++)
        {
            putLine(x1+i,x1+i,y1+t,y2-t,color);
            putLine(x2-i-1,x2-i-1,y1+t,y2-t,color);

            t--;
        }

    }
    else
    {
        putLine(x1+b,x2-b,y1,y1,color);
        putLine(x1+b,x2-b,y2,y2,color);

        putLine(x1,x1,y1+b,y2-b,color);
        putLine(x2,x2,y1+b,y2-b,color);

        putLine(x1,x1+b,y1+b,y1,color);
        putLine(x1,x1+b,y2-b,y2,color);

        putLine(x2,x2-b,y2-b,y2,color);
        putLine(x2,x2-b,y1+b,y1,color);
    }
}

}
