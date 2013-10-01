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

void PButton::draw(PPortingAbstract *disp) const
{
    passert(p.font,"font must not be NULL");

    char len = strlen(text());
    int temp  = (p.font->width() * len) / 2;
    pixel_t xx = xLocal() - temp + width() / 2;
    pixel_t yy = yLocal() + height() / 2 + p.font->height()/ 2;

    if (!pressed)
    {
        disp->putRectangle(xLocal(),xLocal()+width(),yLocal(),yLocal()+height(),color());
    }
    else
    {
        disp->putRectangle(xLocal(),xLocal()+width(),yLocal(),yLocal()+height(),color().dark(7,8));
    }

    if (!hasFocus())
    {
        disp->putRectangleEmpty(x(),x()+width(),y(),y()+height(),textColor());
    }
    else
    {
        disp->putRectangleEmpty(x(),x()+width(),y(),y()+height(),parentScreen()->focusColor());
           disp->putRectangleEmpty(x()+1,x()+width()-1,y()+1,y()-1+height(),parentScreen()->focusColor());
    }
    disp->putText(text(),xx,yy,*p.font,textColor());
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

    PWidget * p = 0;
    if (key->event == PRESSED)
    {
        if (key->key == kUP)
        {
           p = prevSibling();
           while(p != NULL && !(p->visible() && p->enabled()))
               p = p->prevSibling();
        }
        if (key->key == kDOWN)
        {
            p = nextSibling();
            while(p != NULL &&!(p->visible() && p->enabled()))
                p = p->nextSibling();
        }

        if (p)
        {
            p->setFocus();
        }
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
