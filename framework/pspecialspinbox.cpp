#include "pspecialspinbox.h"
#include "pscreen.h"
#include "pportingabstract.h"
#include "pkeyevent.h"
#include "pfont.h"

namespace piris
{

PSpecialSpinBox::PSpecialSpinBox(const specialspinbox_p &p, const PWidgetProperties_t &props, PScreen *screen):
    PWidget(props),
    sp(p),
    value(0)
{
    spinFlags.w = 0;
    setCirculation(true);

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
    const char * p;
    if (sp.text_table && sp.table_size > value)
        p = sp.text_table[value];
    else if(sp.formater)
    {
        sp.formater(value,pole);
        p = pole;
    }
    else
    {
        formatNumber(pole);
        p = pole;
    }

    putItem(disp, p,x,y,tmp,tmp2);


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
    disp->putText(text(),this->x(),this->y()+height(),*f,textColorDelegated());
    disp->putText(text2,this->x() + w,this->y()+height(),*f,textColorDelegated());
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

void PSpecialSpinBox::processEvent(PKeyEvent *key, PTouchEvent *)
{
    if (!toggled())
    {
        PWidget::standardNextPrev(key);
    }

    if (key->key > kENTER || key->event != RELEASED)
        return;

    if (toggled() && (key->key == kDOWN || key->key == kUP) )
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
    }


    if (key->key == kENTER)
    {
        spinFlags.b.Toggled = !spinFlags.b.Toggled;
        qlog(QString("%1 toggled").arg(name));
        if (sp.cb)
            sp.cb(key,this);
    };

    dirty = true;
}

void PSpecialSpinBox::formatNumber(char *output) const
{
    formatNumber(value,output,sp.dot,sp.max_len,sp.flags);
}

void PSpecialSpinBox::formatNumber(int16_t val, char *out, uint8_t dot, uint8_t max_len, uint8_t flags)
{
    uint8_t i = 0;
    bool minus = false;
    char output[20];
    if (val < 0)
    {
        val = -val;
        minus = true;
    }

    while(true)
    {
        if (i == dot && dot != 0)
        {
            output[i] = '.';
            i++;
        }

        if (val == 0)
        {
            if (flags & 2)
                while(max_len -1 > i)
                {
                    output[i] = '0';
                    i++;
                }
            if (i == 0)
                output[0] = '0';

            if (output[i-1] == '.')
            {
                output[i] = '0';
            }

            if (minus)
            {
                if (output[i-1] == '.')
                    i++;
                output[i] = '-';
            }
            else if (flags & 1 && !minus)
            {
                if (output[i-1] == '.')
                    i++;
                output[i] = '+';
            }
            i++;
            while (max_len  > i)
            {
                output[i] = ' ';
                i++;
            }

            output[i] = 0;
            break;
        }

        output[i] = (val % 10) + '0';
        val /= 10;
        i++;
    }

    char *p = &output[strlen(output)-1];
    do
    {
        *out = *p;
        out++;
        p--;
    } while(*p);
    *out = 0;

}

}
