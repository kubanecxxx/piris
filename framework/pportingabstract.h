#ifndef PORTINGABSTRACT_H
#define PORTINGABSTRACT_H

#include "ptypes.h"
#include "pcolor.h"


namespace piris
{

class PFont;
class PTouchEvent;
class PKeyEvent;
class PPortingAbstract
{
public:
    virtual bool readKeyEvent(PKeyEvent * evt) = 0;
    virtual bool readTouchEvent(PTouchEvent * evt) = 0;

    virtual void putPixel(pixel_t x, pixel_t y, PColor color) = 0;
    virtual void putText(const char * text, pixel_t x, pixel_t y, const PFont & font, PColor color) = 0;
    virtual void putRectangle(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color,bool filled = false) = 0;
    virtual void fill(PColor color) = 0;
    virtual void putLine(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color) = 0;

    virtual void putRectangleShaped(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color, bool filled = false);
    //virtual void putArc()

    virtual pixel_t width() const = 0;
    virtual pixel_t height() const = 0;

protected:
    //virtual void suspendThread
    //virtual void wait(ms)

    //friend class guiTrida;
};

}

#endif // PORTINGABSTRACT_H
