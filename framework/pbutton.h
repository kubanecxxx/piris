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
    typedef void(*cb_t)(PButton * but);
    void setCallback(cb_t c) {cb = c;}
    virtual size_t dataSize() const;

protected:
    virtual void draw(PPortingAbstract *disp) const;
    virtual void processEvent(PKeyEvent *key, PTouchEvent *touch);


private:
    bool pressed;
    cb_t cb;
};

}

#endif // PBUTTON_H
