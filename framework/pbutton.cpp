#include "pbutton.h"
#include "pportingabstract.h"
#include "ptouchevent.h"
#include "pkeyevent.h"
#include "passert.h"
#include "pscreen.h"
#include "pfont.h"

namespace piris
{

PButton::PButton(PWidget * par ):
    PWidget(par),
    pressed(false),
    cb(NULL)
{
}

PButton::PButton(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    pressed(false),
    cb(NULL)
{
}

PButton::PButton(const PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    pressed(false),
    cb(NULL)
{

}

void PButton::draw(PPortingAbstract *disp) const
{
    PFont * f = font();
    passert(f,"font must not be NULL");
    char len = strlen(text());
    int temp  = (f->width() * len) / 2;
    pixel_t xx = xGlobal() - temp + width() / 2;
    pixel_t yy = yGlobal() + height() / 2 + f->height()/ 2;

    PColor farba = color();
    if (pressed)
        farba = color().dark(6,8);

    pixel_t xg = xGlobal();
    pixel_t yg = yGlobal();
    disp->putRectangleShaped(xg,xg+width(),yg,yg+height(),farba,true);

    if (!hasFocus())
    {
        disp->putRectangleShaped(xg,xg+width(),yg,yg+height(),textColor());
    }
    else
    {
        disp->putRectangleShaped(xg,xg+width(),yg,yg+height(),parentScreen()->focusColor());
           disp->putRectangleShaped(xg+1,xg+width()-1,yg+1,yg-1+height(),parentScreen()->focusColor());
    }
    disp->putText(text(),xx,yy,*f,textColor());
}


void PButton::processEvent(PKeyEvent *key, PTouchEvent *touch)
{
    if (dragable())
    {
        touch->lock(this);
        qlog(QString("%1 dragging").arg(name));
    }

    //do something
    if (touch->event == PRESS)
    {
        setFocus();
        pressed = true;
    }

    if (touch->event == RELEASE)
    {
        qlog(name + ": button press callback touch");
        if (cb)
            cb(this);
        pressed = false;
    }

    standardNextPrev(key);

    if (key->event == PRESSED)
    {
        if (key->key == kENTER)
        {
            qlog(name + ": button press callback key");
            if (cb)
                cb(this);

            pressed = true;
        }
    }
    if (key->event == RELEASED && key->key == kENTER)
    {
        pressed = false;
    }
}

size_t PButton::dataSize() const
{
    return sizeof(this) + PWidget::dataSize();
}

}
