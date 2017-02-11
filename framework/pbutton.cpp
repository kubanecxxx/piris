#include "pbutton.h"
#include "pportingabstract.h"
#include "ptouchevent.h"
#include "pkeyevent.h"
#include "passert.h"
#include "pscreen.h"
#include "pfont.h"

#ifdef EMBEDDED_TARGET
#include "ch.h"
#endif

namespace piris
{

PButton::PButton(PWidget * par ):
    PWidget(par),
    pressed(false),
    cb(NULL),
    timeout_const(500)
{
}

PButton::PButton(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    pressed(false),
    cb(NULL),
    timeout_const(500)
{
}

PButton::PButton(const PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    pressed(false),
    cb(NULL),
    timeout_const(500)
{

}

void PButton::draw(PPortingAbstract *disp) const
{
    if (!visible())
    {
        return;
    }
    PFont * f = fontDelegated();
    passert(f,"font must not be NULL");
    char len = strlen(text());
    int temp  = (f->width() * len);
    //pixel_t xx = xGlobal() - temp + width() / 2;
    pixel_t xx = xGlobal() + (width() - temp) / 2;
    pixel_t yy = yGlobal() + (height()  + f->height())/ 2;

    PColor farba = color();
    PColor farba2 = textColor();
    if (pressed)
    {
        farba = color().dark(6,8);
       // farba2 = textColor().invert();
    }

    pixel_t xg = xGlobal();
    pixel_t yg = yGlobal();
    disp->putRectangle(xg,xg+width(),yg,yg+height(),farba,true);

    if (!hasFocus())
    {
        disp->putRectangle(xg,xg+width(),yg,yg+height(),textColor(),false);
    }
    else
    {
        //disp->putRectangleShaped(xg,xg+width(),yg,yg+height(),parentScreen()->focusColor());
         //  disp->putRectangleShaped(xg+1,xg+width()-1,yg+1,yg-1+height(),parentScreen()->focusColor());
    }
    disp->putText(text(),xx,yy,*f,farba2);
}

#ifdef EMBEDDED_TARGET
void PButton::timeout(void * arg)
{
    PButton * self = (PButton*)arg;

    self->reset();

}
#endif

void PButton::reset()
{
    dirty = true;
    pressed = false;
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
//#ifdef EMBEDDED_TARGET
        if (this->cb)
            this->cb(this);
#ifdef EMBEDDED_TARGET
        uint8_t l;
        chSysLock();
        l = chVTIsArmedI(&tmr);
        chSysUnlock();
        if (l)
        {
            chVTReset(&tmr);
        }
        chVTSet(&tmr,MS2ST(timeout_const),timeout,this);
#endif
        pressed = true;
    }

    if (touch->event == RELEASE)
    {
        qlog(name + ": button press callback touch");

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

#ifdef DRAWING_MODE_CHANGESONLY
        dirty = true;
#endif
}

size_t PButton::dataSize() const
{    
    return sizeof(pressed) + sizeof(cb) + PWidget::dataSize();
}

}
