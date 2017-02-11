#ifndef PBUTTON_H
#define PBUTTON_H

#include "pwidget.h"

namespace piris
{

class PButton : public PWidget
{
public:
    PButton(PWidget * par = 0);
    PButton(PWidgetProperties_t & props, PWidget *par = NULL);
    PButton(const PWidgetProperties_t & props, PWidget *par = NULL);
    typedef void(*cb_t)(PButton * but);
    void setCallback(cb_t c) {cb = c;}
    virtual size_t dataSize() const;
    bool isPressed() const {return pressed;}

    void reset();


protected:
    virtual void draw(PPortingAbstract *disp) const;
    virtual void processEvent(PKeyEvent *key, PTouchEvent *touch);




private:
#ifdef EMBEDDED_TARGET
    virtual_timer_t tmr;
    static void timeout(void * arg );
#endif

    bool pressed;
    cb_t cb;

public:
    uint16_t timeout_const;
};

#define DECL_BUTTON_PROPERTIES(name,x,y,w,h,text,textColor,backgroundColor,font) \
    _DECL_WIDGET_PROPERTIES(name,x,y,w,h,text,textColor,backgroundColor,font,piris::selectable)

}

#endif // PBUTTON_H
