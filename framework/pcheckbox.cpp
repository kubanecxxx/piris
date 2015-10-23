#include "pcheckbox.h"
#include "plabel.h"
#include "pfont.h"
#include "pportingabstract.h"
#include "pkeyevent.h"
#include "ptouchevent.h"

namespace piris
{

PCheckBox::PCheckBox(PWidget * par ):
    PWidget(par),
    checked(false)
{
}

PCheckBox::PCheckBox(PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    checked(false)
{
}

PCheckBox::PCheckBox(const PWidgetProperties_t &props, PWidget *par):
    PWidget(props,par),
    checked(false)
{

}

void PCheckBox::draw(PPortingAbstract *disp) const
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    PWidget::draw(disp);

    pixel_t x1,x2,y1,y2;
    x1 = x() + 1;
    y1 = y() + 1;
    x2 = x() + f->height() + 2;
    y2 = y() + f->height() + 2;
    pixel_t pul = (f->height() + 2) / 2;

    disp->putRectangle(x1,x2,y1,y2,backgroundColorDelegated().dark(2,1),true);
    disp->putText(text(),x2+2,y()+height()-2,*f,textColorDelegated());

    //paint tick
    if (Checked())
    {
        disp->putLine(x1,x1+pul,y1+pul,y2,textColorDelegated().dark(2,1));
        disp->putLine(x1 + pul ,x2,y2 ,y1,textColorDelegated().dark(2,1));
    }
}

void PCheckBox::processEvent(PKeyEvent *key, PTouchEvent *touch)
{
    PWidget::processEvent(key,touch);

    if ((key->key == kENTER && key->event == PRESSED) || (touch->event == PRESS))
    {
        checked = !checked;
#if DRAWING_MODE_CHANGESONLY
        dirty = true;
#endif
        qlog(QString("check! %1").arg(checked));
    }
}

void PCheckBox::recomputeGeometry()
{
    PFont * f = fontDelegated();
    passert(f,"font is NULL");
    setWidth(f->width()*strlen(text())+f->height()+6);
    setHeight(f->height()+4);
}

}
