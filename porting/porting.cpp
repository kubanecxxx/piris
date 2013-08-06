#include "porting.h"
#include "pkeyevent.h"
#include "ptouchevent.h"
#include "qdisplay.h"
#include "QMouseEvent"
#include "QKeyEvent"
#include "passert.h"

using namespace piris;

porting::porting(QDisplay * dsp):
    disp(dsp),
    key(new PKeyEvent)
{
    connect(disp,SIGNAL(skeyPressEvent(QKeyEvent*)),this,SLOT(keyPressEvent(QKeyEvent*)));
    connect(disp,SIGNAL(skeyReleaseEvent(QKeyEvent*)),this,SLOT(keyReleaseEvent(QKeyEvent*)));
    connect(disp,SIGNAL(smouseMoveEvent(QMouseEvent*)),this,SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(disp,SIGNAL(smousePressEvent(QMouseEvent*)),this,SLOT(mousePressEvent(QMouseEvent*)));
    connect(disp,SIGNAL(smouseReleaseEvent(QMouseEvent*)),this,SLOT(mouseReleaseEvent(QMouseEvent*)));

    fill(WHITE);
}

void porting::keyPressEvent(QKeyEvent *key)
{
    this->key->key = key->key();
    this->key->event = PRESSED;
    full = true;
}

void porting::keyReleaseEvent(QKeyEvent *key)
{
    this->key->key = key->key();
    this->key->event = RELEASED;
    full = true;
}

void porting::mouseMoveEvent(QMouseEvent *mouse)
{

}

void porting::mousePressEvent(QMouseEvent *mouse)
{

}

void porting::mouseReleaseEvent(QMouseEvent *mouse)
{

}

void porting::putPixel(pixel_t x, pixel_t y, PColor color)
{
    disp->putPixel(x,y,color.get());
}

void porting::putRectangle(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color)
{
    disp->putRect(x1,x2,y1,y2,color.get());
}

void porting::putText(const char *text, pixel_t x, pixel_t y, pixel_t size, PColor color)
{
    disp->putText(x,y,text,color.get(),size);
}

void porting::fill(PColor color)
{
    disp->putRect(0,disp->width(),0,disp->height(),color.get());
}

bool porting::readKeyEvent(PKeyEvent *evt)
{
    passert(evt,0);

    if (!full)
        return false;

    full = false;

    *evt = *key;

    return true;
}

bool porting::readTouchEvent(PTouchEvent *evt)
{
    return false;
}

pixel_t porting::height() const
{
    return disp->height();
}

pixel_t porting::width() const
{
   return disp->width();
}
