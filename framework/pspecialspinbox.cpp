#include "pspecialspinbox.h"
#include "pscreen.h"
#include "pportingabstract.h"
#include "pkeyevent.h"
#include "pfont.h"
#include "chsprintf.h"
#include "ptouchevent.h"

namespace piris
{

PSpecialSpinBox::PSpecialSpinBox(const specialspinbox_p &p, const PWidgetProperties_t &props, PScreen *screen, bool Toggleable):
    PWidget(props),
    sp(p),
    value(0)
{
    spinFlags.w = 0;
    setCirculation(true);
    setToggleable(Toggleable);
    //setShowValue(true);


    if (screen)
        screen->addChild(this);

}

PSpecialSpinBox::PSpecialSpinBox(const specialspinbox_p &p, PWidgetProperties_t &props, PScreen *screen, bool Toggleabe):
    PWidget(props),
    sp(p),
    value(0)
{
    spinFlags.w = 0;
    setCirculation(true);
    setToggleable(Toggleabe);
    //setShowValue(true);

    if (screen)
        screen->addChild(this);
}

void PSpecialSpinBox::draw(PPortingAbstract *disp) const
{
    passert(parentScreen(), "no parent screen yet");
    if (!visible())
        return;

    //delegate color from parent widget or screen
    PColor tmp, tmp2 ;
    if (hasFocus())
    {
        tmp = parentScreen()->focusColor();
        if (toggled())
        {
            tmp = backgroundColorDelegated();
            tmp2 = RED;
        }
        else
        {
            tmp2 = tmp;
        }
    }
    else
    {
        tmp = backgroundColorDelegated();
        tmp2 = tmp;
    }

    pixel_t x = xGlobal();
    pixel_t y = yGlobal();

    char pole[16];
    const char * p = makeString(pole);

    if (hidden())
    {
        pixel_t w, h;
        w = width(); h = height();
        disp->putRectangle(x,x+w,y,y+h, backgroundColorDelegated(),true);
        disp->putRectangle(x+w,x+w+strlen(p) * fontDelegated()->width(),y,y+h, backgroundColorDelegated(),true);
        return;
    }

    putItem(disp, p,x,y,tmp,tmp2);
    if (sp.sec)
        putItem(disp,p,sp.sec->x,sp.sec->y,tmp,tmp2);

}

const char * PSpecialSpinBox::makeString(char *ret) const
{
    const char * p;
    if (sp.text_table && sp.table_size > value)
        p = sp.text_table[value];
    else if(sp.formater)
    {
        sp.formater(value,ret);
        p = ret;
    }
    else
    {
        formatNumber(ret);
        p = ret;
    }
    return p;
}

void PSpecialSpinBox::putItem(PPortingAbstract * disp,const char * text2,  pixel_t x, pixel_t y, PColor color1, PColor color2) const
{
    //draw root widget first
    pixel_t w=0,h=0;

    w = width(); h = height();

    disp->putRectangle(x,x+w,y,y+h, color1,true);
    disp->putRectangle(x+w,x+w+strlen(text2) * fontDelegated()->width(),y,y+h, color2,true);

    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    disp->putText(text(),x,y+height(),*f,textColorDelegated());
    disp->putText(text2,x + w,y+height(),*f,textColorDelegated());

}

void PSpecialSpinBox::setValue(int16_t temp)
{

    if (temp <= sp.high_lim && temp >= sp.low_lim)
    {
        value = temp;
    }
    else if (temp > sp.high_lim)
    {
        value = sp.high_lim;
    }
    else if (temp < sp.low_lim)
    {
        value = sp.low_lim;
    }
}

bool PSpecialSpinBox::eventForMe(const PKeyEvent *key,const PTouchEvent *touch) const
{
    //key event
    if (hasFocus() && key->key)
    {
        qlog(QString("%1: key %2, %3").arg(name).arg(key->key).arg(key->event));
        return true;
    }

    pixel_t x = xGlobal();
    pixel_t y = yGlobal();
    char pole[16];
    const char * p = makeString(pole);
    pixel_t w = width() + strlen(p) * fontDelegated()->width();

    //touch event
    if (touch->event && touch->x >= x && touch->x <= x + w &&
            touch->y >= y && touch->y <= y + height())
    {
        qlog(QString("%1: touch %2;%3 ; %4").arg(name).arg(touch->x).
             arg(touch->y).arg(touch->event));

        return true;
    }

    return false;
}

void PSpecialSpinBox::processEvent(PKeyEvent *key, PTouchEvent * touch)
{
    if (!toggled())
    {
        PWidget::standardNextPrev(key);
    }

    if (key->key == kENTER && key->event == RELEASED)
    {
        if (toggleable())
        {
            spinFlags.b.Toggled = !spinFlags.b.Toggled;
            qlog(QString("%1 toggled").arg(name));
        }
        if (sp.cb)
            sp.cb(key,this);
        dirty = true;
    };

    if (toggled() && (key->key == kDOWN || key->key == kUP) && key->event == PRESSED )
    {
        int16_t s = 1;
        int16_t old = value;
        if (key->key == kDOWN)
            s = -1;


        int16_t temp = value + s*sp.step;
        if (temp <= sp.high_lim && temp >= sp.low_lim)
        {
            value = temp;
        }
        else if (circulation())
        {
            if (s == 1)
                value = sp.low_lim;
            else if (s == -1)
                value = sp.high_lim;
        }

        if (old != value)
            if (sp.cb)
                sp.cb(key,this);

        qlog(QString("%1 value %2").arg(name).arg(value));

        dirty = true;
    }

    if (touch->event == PRESS)
    {
        setFocus();
        dirty = true;
        if (sp.cb)
            sp.cb(key,this);

        qlog(QString("%1 value %2").arg(name).arg(value));
    }
}

void PSpecialSpinBox::formatNumber(char *output) const
{
    chsprintf(output,sp.fmt,value);
    if (sp.dot)
    {
        uint8_t l = strlen(output)  ;
        int i;
        for (i = 0 ; i < sp.dot; i++)
        {
            output[l-i] = output[l-i-1];
        }
        if (abs(value) <= sp.step)
            output[l-i-1] = '0';

        output[l-i] = '.';
        output[l+1] = 0;
    }

}

size_t PSpecialSpinBox::dataSize() const
{
    size_t temp = 0;
    if (!IsReadOnly())
        temp += sizeof(PWidgetProperties_t);

    temp += sizeof(*this);
    return temp;
}


}
