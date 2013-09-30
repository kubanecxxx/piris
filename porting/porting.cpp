#include "porting.h"
#include "pkeyevent.h"
#include "ptouchevent.h"
#include "qdisplay.h"
#include "QMouseEvent"
#include "QKeyEvent"
#include "passert.h"
#include "ptypes.h"
#include <QDebug>

using namespace piris;

porting::porting(QDisplay * dsp):
    disp(dsp),
    key(new PKeyEvent),
    touch(new PTouchEvent)
{
    connect(disp,SIGNAL(skeyPressEvent(QKeyEvent*)),this,SLOT(keyPressEvent(QKeyEvent*)));
    connect(disp,SIGNAL(skeyReleaseEvent(QKeyEvent*)),this,SLOT(keyReleaseEvent(QKeyEvent*)));
    connect(disp,SIGNAL(smouseMoveEvent(QMouseEvent*)),this,SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(disp,SIGNAL(smousePressEvent(QMouseEvent*)),this,SLOT(mousePressEvent(QMouseEvent*)));
    connect(disp,SIGNAL(smouseReleaseEvent(QMouseEvent*)),this,SLOT(mouseReleaseEvent(QMouseEvent*)));
}

void porting::keyPressEvent(QKeyEvent *key)
{
    this->key->key = key2key(key->key());
    this->key->event = PRESSED;
    if (this->key->key)
        full = true;
}

void porting::keyReleaseEvent(QKeyEvent *key)
{
    this->key->key = key2key(key->key());
    this->key->event = RELEASED;
    if (this->key->key)
        full = true;
}

int porting::key2key(uint16_t input)
{
    QMap<int,int> map;
    map.insert(19,kUP);
    map.insert(21,kDOWN);
    map.insert(4,kENTER);

    int ret = map.value(input,0);
    return ret;
}

    static Qt::MouseButtons moje;

void porting::mouseMoveEvent(QMouseEvent *mouse)
{



    if (mouse->buttons() && moje)
    {
        touchfull = true;
        touch->x = mouse->pos().x();
        touch->y = mouse->pos().y();
        touch->event = MOVE;
    }

    moje = mouse->buttons();
}

void porting::putLine(pixel_t x1, pixel_t x2, pixel_t y1, pixel_t y2, PColor color)
{
    disp->putLine(x1,x2,y1,y2,color.get());
}

void porting::mousePressEvent(QMouseEvent *mouse)
{
    touchfull = true;
    touch->x = mouse->pos().x();
    touch->y = mouse->pos().y();
    touch->event = PRESS;
}

void porting::mouseReleaseEvent(QMouseEvent *mouse)
{
    touchfull = true;
    touch->x = mouse->pos().x();
    touch->y = mouse->pos().y();
    touch->event = RELEASE;
    moje = Qt::NoButton;
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
    passert(evt,"no event");

    if (!touchfull)
        return false;

    touchfull = false;

    *evt = *touch;

    return true;
}

pixel_t porting::height() const
{
    return disp->height();
}

pixel_t porting::width() const
{
   return disp->width();
}
