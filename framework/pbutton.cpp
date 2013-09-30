#include "pbutton.h"
#include "pportingabstract.h"
#include "ptouchevent.h"
#include "pkeyevent.h"
#include "passert.h"

namespace piris
{

PButton::PButton(PWidget * par ):
    PWidget(par),
    pressed(false),
    cb(NULL)
{
}

void PButton::draw(PPortingAbstract *disp) const
{


    char len = strlen(text());
    int temp  = (textSize() * len) / 2;
    pixel_t xx = xLocal() - temp + width() / 2;
    pixel_t yy = yLocal() + height() / 2 + textSize()/ 2;

    if (!pressed)
    {
        disp->putRectangle(xLocal(),xLocal()+width(),yLocal(),yLocal()+height(),color());
        disp->putRectangleEmpty(x()-1,x()+width(),y()-1,y()+height(),textColor());
    }
    else
    {
        disp->putRectangle(xLocal(),xLocal()+width(),yLocal(),yLocal()+height(),color().dark(7,8));
        disp->putRectangleEmpty(x()+2,x()+width()-3,y()+2,y()+height()-3,textColor());
    }

    disp->putText(text(),xx,yy,textSize(),textColor());
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
        qlog(name + ": button press callback");
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
            pressed = true;
        }
    }
    if (key->event == RELEASED && key->key == kENTER)
    {
        pressed = false;
    }
}

}
