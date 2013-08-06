#ifndef PORTINGABSTRACT_H
#define PORTINGABSTRACT_H

#include "ptypes.h"
#include "pcolor.h"

namespace piris
{

class PTouchEvent;
class PKeyEvent;
class PPortingAbstract
{
#ifndef KDEBUG
protected:
#else
public:
#endif
    virtual bool readKeyEvent(PKeyEvent * evt) = 0;
    virtual bool readTouchEvent(PTouchEvent * evt) = 0;

    virtual void putPixel(pixel_t x, pixel_t y, PColor color) = 0;
    virtual void putText(const char * text, pixel_t x, pixel_t y, pixel_t size, PColor color) = 0;
    virtual void putRectangle(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color) = 0;
    virtual void fill(PColor color) = 0;


    //friend class guiTrida;
};

}

#endif // PORTINGABSTRACT_H
